import { Prisma } from "@prisma/client";

import { Request, Response } from "express";
import { METHOD, routeConfig } from "../..";
import { db, Install, InstallOptions, Package, PackageOptions } from "../db/Database";

/* Temporary package creation queries */

// Chrome
(async () => {
  const existingPackage = await db.package.findFirst({
    where: {
      name: "chrome",
    },
  });

  if (existingPackage) return;

  addPackage({
    name: "chrome",
    description: "The Google Chrome browser",
    version: "1.0.0",
  }, {
    macos: {
      url: "https://dl.google.com/chrome/mac/stable/GGRO/googlechrome.dmg",
      type: "dmg",
    },
    windows: {
      url: "https://dl.google.com/chrome/install/1/chrome_installer.exe",
      type: "exe",
    },
  });
})();

// Skyline
(async () => {
  const existingPackage = await db.package.findFirst({
    where: {
      name: "skyline",
    },
  });

  if (existingPackage) return;

  addPackage(
    {
      name: "skyline",
      description: "The Super Fast Code Editor",
      version: "1.0.0",
    },
    {
      macos: {
        url: "https://github.com/skyline-editor/skyline/releases/download/v0.1.0/Skyline_0.1.0_x64.dmg",
        type: "dmg",
      },
      windows: {
        url: "https://github.com/skyline-editor/skyline/releases/download/v0.1.0/Skyline_0.1.0_x64.msi",
        type: "msi",
      },
    }
  );
})();

/* Temporary package creation done */

/**
 * Add package to database
 * @param {PackageOptions} pkg - Info about the package
 * @param {InstallOptions} opts - Install options
 * @example
 * // Add a package
 * addPackage({
 *   name: 'chrome',
 *   description: 'The Google Chrome browser',
 *   version: '1.0.0',
 * }, {
 *   macos: {
 *     url: 'https://dl.google.com/chrome/mac/stable/GGRO/googlechrome.dmg',
 *     type: 'dmg'
 *   },
 *   windows: {
 *     url: 'https://dl.google.com/chrome/install/1/chrome_installer.exe',
 *     type: 'exe'
 *   },
 * })
 **/
async function addPackage(
  pkg: PackageOptions,
  opts: InstallOptions
): Promise<void> {
  const { name, description, version } = pkg;

  const install: Prisma.PackageInstallCreateWithoutPackageInput = {};
  if (opts.macos) {
    install.macos = {
      create: {
        url: opts.macos.url,
        type: opts.macos.type,
      },
    };
  }
  if (opts.windows) {
    install.windows = {
      create: {
        url: opts.windows.url,
        type: opts.windows.type,
      },
    };
  }
  if (opts.linux) {
    install.linux = {
      create: {
        url: opts.linux.url,
        type: opts.linux.type,
      },
    };
  }

  await db.package.create({
    data: {
      name,
      description,
      version,
      install: {
        create: install,
      },
    },
  });
}

class PackageController {
  @routeConfig({
    method: METHOD.GET,
    path: "/package/install",
  })
  public async install(request: Request, _response: Response): Promise<Install> {
    const packageID = request.query.package?.toString().toLowerCase();
    const platform = request.query.platform?.toString().toLowerCase();

    if (!packageID) throw new Error(`"package" is required`);
    if (!platform) throw new Error(`"platform" is required`);

    const packageData = await db.package.findFirst({
      where: {
        name: packageID,
      },
      include: {
        install: {
          include: {
            macos: true,
            windows: true,
            linux: true,
          },
        },
      },
    });

    if (!packageData) throw new Error(`Couldn't find package "${packageID}"`);
    if (!(platform in packageData.install!))
      throw new Error(
        `Package "${packageID}", cant be installed on your system`
      );

    const data = packageData.install![platform as keyof InstallOptions]!;

    return {
      url: data.url,
      type: data.type,
    };
  }

  @routeConfig({
    method: METHOD.GET,
    path: "/package/meta",
  })
  public async meta(request: Request, _response: Response): Promise<Package> {
    const packageID = request.query.package?.toString().toLowerCase();
    const platform = request.query.platform?.toString().toLowerCase();

    if (!packageID) throw new Error(`"package" is required`);
    if (!platform) throw new Error(`"platform" is required`);

    const packageData = await db.package.findFirst({
      where: {
        name: packageID,
      },
    });

    if (!packageData) throw new Error(`Couldn't find package "${packageID}"`);
    return {
      name: packageData.name,
      description: packageData.description,
      version: packageData.version,
    };
  }

  @routeConfig({
    method: METHOD.GET,
    path: "/package/list",
  })
  public async list(_request: Request, _response: Response): Promise<Package[]> {
    const packages = await db.package.findMany({
      where: {},
    });

    return packages.map(v => ({
      name: v.name,
      description: v.description,
      version: v.version,
    }));
  }

  @routeConfig({
    method: METHOD.POST,
    path: "/package/publish",
  })
  public async publish(request: Request, _response: Response): Promise<any> {
    console.log(request.body);
    if (!request.body) throw new Error("No body");
    if (!request.body.info) throw new Error("No info");

    const info = request.body.info;
    const install = request.body.install ?? {};

    if (!info.name) throw new Error("No name");
    if (!info.description) throw new Error("No description");
    if (!info.version) throw new Error("No version");

    const { name, description, version } = info;

    let packageData;
    try {
      packageData = await db.package.findFirst({
        where: {
          name,
        },
      });
    } catch(_) {}
    if (packageData) throw new Error(`Package "${name}" already exists`);

    const installers: InstallOptions = {};
    if (install.macos) {
      const types = ["dmg", "app", "pkg", "zip", "sh"];
      const installer = install.macos;

      if (!installer.url) throw new Error("No macos url");
      if (!installer.type) throw new Error("No macos type");

      if (!installer.url.endsWith(installer.type)) throw new Error("macos url must end with macos type");
      if (!types.includes(installer.type)) throw new Error("macos type must be one of: " + types.join(", "));

      installers.macos = {
        url: installer.url,
        type: installer.type,
      };
    }
    if (install.windows) {
      const types = ["msi", "exe", "zip", "sh"];
      const installer = install.windows;

      if (!installer.url) throw new Error("No windows url");
      if (!installer.type) throw new Error("No windows type");

      if (!installer.url.endsWith(installer.type)) throw new Error("windows url must end with windows type");
      if (!types.includes(installer.type)) throw new Error("windows type must be one of: " + types.join(", "));

      installers.windows = {
        url: installer.url,
        type: installer.type,
      };
    }
    if (install.linux) {
      const types = ["deb", "zip", "sh"];
      const installer = install.linux;

      if (!installer.url) throw new Error("No linux url");
      if (!installer.type) throw new Error("No linux type");

      if (!installer.url.endsWith(installer.type)) throw new Error("linux url must end with linux type");
      if (!types.includes(installer.type)) throw new Error("linux type must be one of: " + types.join(", "));

      installers.linux = {
        url: installer.url,
        type: installer.type,
      };
    }

    addPackage(
      {
        name,
        description,
        version,
      },
      installers
    );
  }
}
