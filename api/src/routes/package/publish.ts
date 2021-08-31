import { METHOD, Route } from "../../types/Route";
import { Request, Response } from "express";
import {
  addPackage,
  fetchPackage,
  parseRequestPackage,
} from "../../util/package";
import { getToken, getUserdata } from "../../types/Auth";

export default class implements Route {
  static get config() {
    return {
      method: METHOD.POST,
      path: "/package/publish",
    };
  }
  static async handler(request: Request, _response: Response): Promise<void> {
    const token = getToken(request);
    if (!token) throw new Error("Couldn't parse token");

    const data = await getUserdata(token);
    if (!data) throw new Error("Couldn't fetch user data");

    const packageData = parseRequestPackage(request);
    if (await fetchPackage(packageData.info.name))
      throw new Error(`Package "${packageData.info.name}" already exists`);

    addPackage(packageData.info, packageData.installers, data);
  }
}
