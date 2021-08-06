import { Request, Response } from "express";
import { METHOD, routeConfig } from "../..";

interface Package {
  name: string;
  description: string;

  install: {
    macos?: {
      url: string;
      type: "dmg" | "app";
      checksum?: string;
    }
    windows?: {
      url: string;
      type: "exe" | "msi";
      checksum?: string;
    }
    linux?: {
      url: string;
      type: "deb";
      checksum?: string;
    }
  }
}

class PackageController {
  @routeConfig({
    method: METHOD.GET,
    path: "/package/"
  })
  public get(
    request: Request,
    response: Response
  ): Package {
    const package_id = request.query.id?.toString()?.toLowerCase();
    if (!package_id) throw new Error(`"id" is required`);
    if (package_id !== 'chrome') throw new Error(`Couldn't find package "${package_id}"`);

    return {
      name: "chrome",
      description: "The Google Chrome browser",
      install: {
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
        }
      }
    };
  }

  @routeConfig({
    method: METHOD.GET,
    path: "/package/install"
  })
  public install(
    request: Request,
    response: Response
  ): string {
    const package_id = request.query.package?.toString().toLowerCase();
    const platform = request.query.platform?.toString().toLowerCase();

    if (!package_id) throw new Error(`"package" is required`);
    if (!platform) throw new Error(`"platform" is required`)
    
    if (package_id !== 'chrome') throw new Error(`Couldn't find package "${package_id}"`);
    if (platform !== 'macos') throw new Error(`Couldn't find package "${package_id}"`);

    const package_data = {
      name: "chrome",
      description: "The Google Chrome browser",
      install: {
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
        }
      }
    };

    if (!package_data.install[platform]) throw new Error(`Package "${package_id}", cant be installed on your system`);
    return package_data.install.macos.url;
  }
}