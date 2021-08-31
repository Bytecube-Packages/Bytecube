import axios from "axios";
import { Request } from "express";

export interface UserData {
  id: string;
  name: string;
}

export function getToken(request: Request) {
  const token = request.headers.authorization;
  if (!token) throw new Error("No token provided");

  return parseToken(token);
}

export function parseToken(token: string) {
  const token_parts = token.split(" ");
  if (token_parts.length !== 2) return;

  const token_type = token_parts[0];
  const token_value = token_parts[1];

  if (token_type !== "Bearer") return;
  return token_value;
}

export async function getUserdata(token: string) {
  try {
    const url = process.env.AUTH0_DOMAIN;
    const data = await axios.get(`${url}/userinfo`, {
      headers: {
        Authorization: `Bearer ${token}`,
        "Content-Type": "application/json",
      },
    });

    return {
      id: data.data.sub,
      name: data.data.name,
    } as UserData;
  } catch (_error) {}
}
