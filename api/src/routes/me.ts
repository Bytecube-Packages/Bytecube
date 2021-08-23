import { Request, Response } from "express";
import { METHOD, Route, RouteConfig } from "../types/Route";
import { getToken, getUserdata } from "../types/Auth";

export default class implements Route {
  static get config(): RouteConfig {
    return {
      method: METHOD.GET,
      path: "/me",
    };
  }
  static async handler(request: Request, _response: Response): Promise<void> {
    const token = getToken(request);
    if (!token) throw new Error("Couldn't parse token");
    
    const data = await getUserdata(token);
    if (!data) throw new Error("Couldn't fetch user data");

    return data;
  }
}
