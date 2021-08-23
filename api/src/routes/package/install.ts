import { METHOD, Route } from "../../types/Route";
import { Request, Response } from "express";
import { fetchPackage } from "../../util/package";
import { Install, InstallOptions } from "../../db/Database";

export default class implements Route {
  static get config() {
    return {
      method: METHOD.GET,
      path: "/package/install",
    };
  }
  static async handler(request: Request, _response: Response): Promise<Install> {
    const packageID = request.query.package?.toString().toLowerCase();
    const platform = request.query.platform?.toString().toLowerCase();

    if (!packageID) throw new Error(`"package" is required`);
    if (!platform) throw new Error(`"platform" is required`);

    const packageData = await fetchPackage(packageID);
    if (!packageData) throw new Error(`Couldn't find package "${packageID}"`);

    if (!(platform in packageData.install!))
      throw new Error(
        `Package "${packageID}", cant be installed on your system`
      );

    const data = packageData.install![platform as keyof InstallOptions]!;
    return {
      url: data.url,
      type: data.type,
    };
  }
}