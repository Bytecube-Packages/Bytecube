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
}