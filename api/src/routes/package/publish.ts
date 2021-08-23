import { METHOD, Route } from "../../types/Route";
import { Request, Response } from "express";
import { addPackage, fetchPackage, parseRequestPackage } from "../../util/package";

export default class implements Route {
  static get config() {
    return {
      method: METHOD.POST,
      path: "/package/publish",
    };
  }
  static async handler(request: Request, _response: Response): Promise<void> {
    const packageData = await parseRequestPackage(request);
    if (await fetchPackage(packageData.info.name)) throw new Error(`Package "${packageData.info.name}" already exists`);  

    addPackage(
      packageData.info,
      packageData.installers
    );
  }
}