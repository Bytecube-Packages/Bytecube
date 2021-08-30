import { PrismaClient } from "@prisma/client";

export const db: PrismaClient = new PrismaClient();
export interface PackageOptions {
  name: string;
  description: string;
  version: string;
}
export interface InstallOptions {
  macos?: {
    url: string;
    type: 'dmg' | 'app' | 'pkg' | 'zip' | 'sh';
  };
  windows?: {
    url: string;
    type: 'msi' | 'exe' | 'zip' | 'sh';
  };
  linux?: {
    url: string;
    type: 'deb' | 'zip' | 'sh'; 
  };
}
export interface Install {
  url: string;
  type: string;
}
export interface Package {
  name: string;
  description: string;
  version: string;

  author?: {
    name: string;
  }
};