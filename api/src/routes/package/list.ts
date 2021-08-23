import { METHOD, Route } from "../../types/Route";
import { Request, Response } from "express";
import { db, Package } from "../../db/Database";

export default class implements Route {
  static get config() {
    return {
      method: METHOD.GET,
      path: "/package/list",
    };
  }
  static async handler(_request: Request, _response: Response): Promise<Package[]> {
    const packages = await db.package.findMany({
      where: {},
    });

    return packages.map(v => ({
      name: v.name,
      description: v.description,
      version: v.version,
    }));
  }
}