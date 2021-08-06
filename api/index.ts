import { Server } from './src/server';
import { Request, Response } from "express";
import glob from 'glob';

export enum METHOD {
    GET = 'get',
    POST = 'post'
}

export interface RouteConfigProps {
    method: METHOD;
    path: string;
}

export function routeConfig({method, path}: RouteConfigProps): MethodDecorator {
    return function (
        target: Object,
        propertyKey: string | symbol,
        descriptor: PropertyDescriptor
    ) {
        const response = (req: Request, res: Response) => {
            const original = descriptor.value(req, res);

            res.status(200).json(original);
        }

        server.app[method](path, response);
    }
}

const server = new Server();

glob('./src/routes/**/*.ts', (err, files) => {
    files.forEach((file) => require(file.replace('.ts', '')));
});

server.start();