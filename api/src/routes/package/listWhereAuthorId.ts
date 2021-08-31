import { METHOD, Route } from "../../types/Route";
import { Request, Response } from "express";
import { db, Package } from "../../db/Database";
import { getToken, getUserdata } from "../../types/Auth";

export default class implements Route {
  static get config() {
    return {
      method: METHOD.GET,
      path: "/package/list",
    };
  }
  static async handler(
    _request: Request,
    _response: Response
  ): Promise<Package[]> {
    const token = getToken(_request);
    if (!token) throw new Error("Couldn't parse token");

    const data = await getUserdata(token);
    if (!data) throw new Error("Couldn't fetch user data");

    const packages = await db.package.findMany({
      where: {
        authorId: data.id,
      },
    });

    return packages.map((v) => ({
      name: v.name,
      description: v.description,
      version: v.version,
    }));
  }
}
