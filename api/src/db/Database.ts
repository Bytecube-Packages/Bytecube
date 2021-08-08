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
    type: 'dmg' | 'zip' | 'app';
  };
  windows?: {
    url: string;
    type: 'msi' | 'exe';
  };
  linux?: {
    url: string;
    type: 'deb' | 'zip'; 
  };
}