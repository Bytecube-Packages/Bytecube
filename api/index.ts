import { Request, Response } from "express";
import { Server } from './src/server';
import { Route } from './src/types/Route';
import glob from 'glob';

function useRoute(route: typeof Route) {
  const response = async (req: Request, res: Response) => {
    try {
        const original = await route.handler(req, res);
        res.status(200).json(original);
    } catch (e) {
        res.status(500).json({
            error: e.message
        });
    }
  };

  Server.instance.app[route.config.method](route.config.path, response);
}

glob('./src/routes/**/*.ts', (_err, files) => {
  files.forEach((file) => {
    const route = require(file.replace('.ts', '')).default;
    useRoute(route);
  });
});
Server.instance.start();