const domain = "https://api.bytecube.tk";

export default function handler(req, res) {
  res.redirect(`${domain}/auth/login`);
}
