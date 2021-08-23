import { Request, Response } from "express";
import { METHOD, Route, RouteConfig } from "../../types/Route";
import QueryString from "qs";
import axios from "axios";

export default class implements Route {
  static get config(): RouteConfig {
    return {
      method: METHOD.POST,
      path: "/auth/authorize",
    };
  }
  static async handler(request: Request, _response: Response): Promise<any> {
    const code = request.query.code;

    const url = process.env.AUTH0_DOMAIN;
    const query = QueryString.stringify({
      grant_type: 'authorization_code',
      client_id: process.env.AUTH0_CLIENT_ID,
      client_secret: process.env.AUTH0_CLIENT_SECRET,
      redirect_uri: process.env.AUTH0_REDIRECT_URI,
      code
    });

    const result = await axios.post(`${url}/oauth/token`, query, {
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded'
      }
    });

    const data = {
      access_token: result.data.access_token,
    };
    return data;
  }
}
