import { Request, Response } from "express";

export enum METHOD {
  GET = 'get',
  POST = 'post',
  PUT = 'put',
  PATCH = 'patch',
  DELETE = 'delete'
}

export interface RouteConfig {
  path: string;
  method: METHOD;
}

export class Route {
  static get config(): RouteConfig {
    return {} as RouteConfig;
  }
  static handler: (_request: Request, _response: Response) => unknown;
}