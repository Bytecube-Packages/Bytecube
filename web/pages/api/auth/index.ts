import axios from "axios";
import QueryString from "qs";
const domain = "https://api.bytecube.tk";

export default async function handler(req, res) {
  if (!req.query.code) return res.status(400).send("No code provided");

  const params = QueryString.stringify({
    code: req.query.code,
  });

  console.log(params);

  try {
    const data = await axios.post(`${domain}/auth/authorize?${params}`);
    const accessToken = data.data.access_token;

    res.setHeader("Set-Cookie", `access_token=${accessToken}; Path=/; Secure`);
    res.redirect("/token");
  } catch (error) {
    console.log(error.message);
    res.status(500).send("An Error Occurred");
  }
}
