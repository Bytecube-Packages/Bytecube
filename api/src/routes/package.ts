import { Package, Prisma } from "@prisma/client";

import { Request, Response } from "express";
import { METHOD, routeConfig } from "../..";
import { db, InstallOptions, PackageOptions } from "../db/Database";

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
      url: "https://dl.google.com/chrome/install/1/GGRO/googlechrome.exe",
      type: "exe",
    },
    linux: {
      url: "https://dl.google.com/chrome/install/1/GGRO/google-chrome",
      type: "deb",
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

  addPackage({
    name: "skyline",
    description: "The Super Fast Code Editor",
    version: "1.0.0",
  }, {
    macos: {
      url: "https://github.com/skyline-editor/skyline/releases/download/v0.1.0/Skyline_0.1.0_x64.dmg",
      type: "dmg",
    },
    windows: {
      url: "https://github.com/skyline-editor/skyline/releases/download/v0.1.0/Skyline_0.1.0_x64.msi",
      type: "msi",
    },
  });
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
 *     url: 'https://dl.google.com/chrome/install/1/GGRO/googlechrome.exe',
 *     type: 'exe'
 *   },
 *   linux: {
 *     url: 'https://dl.google.com/chrome/install/1/GGRO/google-chrome',
 *     type: 'deb'
 *   }
 * })
**/
async function addPackage(pkg: PackageOptions, opts: InstallOptions): Promise<void> {
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
        create: install
      }
    },
  });
}

class PackageController {
  @routeConfig({
    method: METHOD.GET,
    path: "/package/",
  })
  public async get(request: Request, _response: Response): Promise<Package> {
    const packageID = request.query.id?.toString()?.toLowerCase();
    if (!packageID) throw new Error(`"id" is required`);

    const packageData = await db.package.findFirst({
      where: {
        name: packageID,
      },
    });

    if (!packageData) throw new Error(`Couldn't find package "${packageID}"`);
    return packageData as Package;
  }

  @routeConfig({
    method: METHOD.GET,
    path: "/package/install",
  })
  public async install(request: Request, _response: Response): Promise<string> {
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
    if (!(platform in packageData.install!)) throw new Error(`Package "${packageID}", cant be installed on your system`);

    return packageData.install![platform as keyof InstallOptions]!.url;
  }

  @routeConfig({
    method: METHOD.GET,
    path: "/package/list",
  })
  public async list(request: Request, _response: Response): Promise<Package[]> {
    const packages = await db.package.findMany({
      where: {}
    });

    return packages;
  }
}
