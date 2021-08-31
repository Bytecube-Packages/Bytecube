import { Prisma } from "@prisma/client";
import { Request } from "express";
import { db, InstallOptions, PackageOptions } from "../db/Database";
import { UserData } from "../types/Auth";

export function parseRequestPackage(request: Request) {
  if (!request.body) throw new Error("No body");
  if (!request.body.info) throw new Error("No info");

  const info = request.body.info;
  const install = request.body.install ?? {};

  if (!info.name) throw new Error("No name");
  if (!info.description) throw new Error("No description");
  if (!info.version) throw new Error("No version");
  const { name, description, version } = info;

  const installers: InstallOptions = {};
  if (install.macos) {
    const types = ["dmg", "app", "pkg", "zip", "sh"];
    const installer = install.macos;

    if (!installer.url) throw new Error("No macos url");
    if (!installer.type) throw new Error("No macos type");

    if (!types.includes(installer.type))
      throw new Error("macos type must be one of: " + types.join(", "));

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

    if (!types.includes(installer.type))
      throw new Error("windows type must be one of: " + types.join(", "));

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

    if (!types.includes(installer.type))
      throw new Error("linux type must be one of: " + types.join(", "));

    installers.linux = {
      url: installer.url,
      type: installer.type,
    };
  }

  return {
    info: {
      name,
      description,
      version,
    },
    installers,
  };
}

export async function fetchPackage(name: string) {
  try {
    return await db.package.findFirst({
      where: {
        name,
      },
      include: {
        author: true,
        install: {
          include: {
            macos: true,
            windows: true,
            linux: true,
          },
        },
      },
    });
  } catch (_) {}

  return null;
}

export async function addPackage(
  pkg: PackageOptions,
  opts: InstallOptions,
  user?: UserData
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

  let author;
  if (user) {
    author = {
      connectOrCreate: {
        where: {
          id: user.id,
        },
        create: {
          id: user.id,
          name: user.name,
        },
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
      author,
    },
  });
}
