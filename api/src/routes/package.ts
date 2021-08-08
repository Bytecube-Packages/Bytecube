import { Package, prisma } from "@prisma/client";
import { Request, Response } from "express";
import { METHOD, routeConfig } from "../..";
import { db } from "../db/Database";

// interface PackageInstall {
//   macos?: {
//     url: string;
//     type: "dmg" | "app";
//     checksum?: string;
//   }
//   windows?: {
//     url: string;
//     type: "exe" | "msi";
//     checksum?: string;
//   }
//   linux?: {
//     url: string;
//     type: "deb";
//     checksum?: string;
//   }
// }

// interface Package {
//   name: string;
//   description: string;

//   install: PackageInstall;
// }

//Temporary package creation queries
(async () => {
  const existingPackage = await db.package.findFirst({
    where: {
      name: "chrome",
    },
  });

  if (existingPackage) {
    return;
  } else {
    return await db.package.create({
      data: {
        name: "chrome",
        description: "The Google Chrome browser",
        version: "1.0.0",
        install: {
          create: {
            macos: {
              create: {
                url: "https://dl.google.com/chrome/mac/stable/GGRO/googlechrome.dmg",
                type: "dmg",
              },
            },

            windows: {
              create: {
                url: "https://dl.google.com/chrome/install/1/GGRO/googlechrome.exe",
                type: "exe",
              },
            },

            linux: {
              create: {
                url: "https://dl.google.com/chrome/install/1/GGRO/google-chrome",
                type: "deb",
              },
            },
          },
        },
      },
    });
  }
})();

// const packages = new Map<string, Package>();
// packages.set("chrome", {
//   name: "chrome",
//   description: "The Google Chrome browser",
//   install: {
//     macos: {
//       url: "https://dl.google.com/chrome/mac/stable/GGRO/googlechrome.dmg",
//       type: "dmg",
//     },
//     windows: {
//       url: "https://dl.google.com/chrome/install/1/GGRO/googlechrome.exe",
//       type: "exe",
//     },
//     linux: {
//       url: "https://dl.google.com/chrome/install/1/GGRO/google-chrome",
//       type: "deb",
//     },
//   },
// });
// packages.set("skyline", {
//   name: "skyline",
//   description: "The Super Fast Code Editor",
//   install: {
//     macos: {
//       url: "https://github.com/skyline-editor/skyline/releases/download/v0.1.0/Skyline_0.1.0_x64.dmg",
//       type: "dmg",
//     },
//     windows: {
//       url: "https://github.com/skyline-editor/skyline/releases/download/v0.1.0/Skyline_0.1.0_x64.msi",
//       type: "msi",
//     },
//   },
// });

class PackageController {
  @routeConfig({
    method: METHOD.GET,
    path: "/package/",
  })
  public async get(request: Request, response: Response): Promise<Package> {
    const packageID = request.query.id?.toString()?.toLowerCase();
    if (!packageID) throw new Error(`"id" is required`);

    const packageData = await db.package.findUnique({
      where: {
        id: packageID,
      },
    });

    if (!packageData) {
      throw new Error(`Couldn't find package "${packageID}"`);
    } else {
      return packageData as Package;
    }
  }

  @routeConfig({
    method: METHOD.GET,
    path: "/package/install",
  })
  public async install(request: Request, response: Response): Promise<strin> {
    const packageID = request.query.package?.toString().toLowerCase();
    const platform = request.query.platform?.toString().toLowerCase();

    if (!packageID) throw new Error(`"package" is required`);
    if (!platform) throw new Error(`"platform" is required`);

    const packageData = await db.package.findUnique({
      where: {
        id: packageID,
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
    if (!packageData.install[platform]) throw new Error("");

    if (!(platform in package_data.install))
      throw new Error(
        `Package "${package_id}", cant be installed on your system`
      );

    return package_data.install[platform as keyof PackageInstall]!.url;
  }
}
