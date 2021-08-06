import { Request, Response } from "express";
import { METHOD, routeConfig } from "../..";

class Test {
  @routeConfig({
    method: METHOD.GET,
    path: "/test"
  })
  public getTest(
    request: Request,
    response: Response
  ) {
    return "Hello World!";
  }
}