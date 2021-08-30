import { METHOD, Route } from "../../types/Route";
import { Request, Response } from "express";
import { fetchPackage } from "../../util/package";
import { Package } from "../../db/Database";

export default class implements Route {
  static get config() {
    return {
      method: METHOD.GET,
      path: "/package/meta",
    };
  }
  static async handler(request: Request, _response: Response): Promise<Package> {
    const packageID = request.query.package?.toString().toLowerCase();
    if (!packageID) throw new Error(`"package" is required`);

    const packageData = await fetchPackage(packageID);
    if (!packageData) throw new Error(`Couldn't find package "${packageID}"`);

    const data = {
      name: packageData.name,
      description: packageData.description,
      version: packageData.version,
    } as Package;

    if (packageData.author) data.author = {
      name: packageData.author?.name,  
    };

    return data;
  }
}