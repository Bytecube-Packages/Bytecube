import { Request, Response } from "express";
import { METHOD, routeConfig } from "../..";

interface PackageInstall {
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

interface Package {
  name: string;
  description: string;

  install: PackageInstall;
}

const packages = new Map<string, Package>();
packages.set('chrome', {
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
});
packages.set('skyline', {
  name: "skyline",
  description: "The Super Fast Code Editor",
  install: {
    macos: {
      url: "https://github.com/skyline-editor/skyline/releases/download/v0.1.0/Skyline_0.1.0_x64.dmg",
      type: "dmg",
    },
    windows: {
      url: "https://github.com/skyline-editor/skyline/releases/download/v0.1.0/Skyline_0.1.0_x64.msi",
      type: "msi",
    },
  }
});

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

    if (!packages.has(package_id)) throw new Error(`Couldn't find package "${package_id}"`);
    return packages.get(package_id)!;
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
    
    if (!packages.has(package_id)) throw new Error(`Couldn't find package "${package_id}"`);
    const package_data = packages.get(package_id)!;

    if (!(platform in package_data.install)) throw new Error(`Package "${package_id}", cant be installed on your system`);
    return package_data.install[platform as keyof PackageInstall]!.url;
  }
}