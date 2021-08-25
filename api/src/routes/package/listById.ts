import { METHOD, Route } from "../../types/Route";
import { Request, Response } from "express";
import { db, Package } from "../../db/Database";

export default class implements Route {
  static get config() {
    return {
      method: METHOD.GET,
      path: "/package/:id",
    };
  }
  static async handler(
    _request: Request,
    _response: Response
  ): Promise<Package | null> {
    const specificPackageData = await db.package.findUnique({
      where: {
        id: _request.params.id,
      },
    });

    return specificPackageData;
  }
}
