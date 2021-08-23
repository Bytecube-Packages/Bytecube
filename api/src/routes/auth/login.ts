import { Request, Response } from "express";
import { METHOD, Route } from "../../types/Route";
import QueryString from "qs";

export default class implements Route {
  static get config() {
    return {
      method: METHOD.GET,
      path: "/auth/login",
    };
  }
  static async handler(_request: Request, response: Response): Promise<any> {
    const url = process.env.AUTH0_DOMAIN;
    const query = QueryString.stringify({
      redirect_uri: process.env.AUTH0_REDIRECT_URI,
      client_id: process.env.AUTH0_CLIENT_ID,
      response_type: 'code',
      scope: 'openid profile',
    });

    response.redirect(`${url}/authorize?${query}`);
  }
}
