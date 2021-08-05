defmodule Api.Plugs.Cors do
  import Plug.Conn

  def init(_) do
  end

  def call(conn, _opts) do
    conn
    |> put_resp_header("Access-Control-Allow-Origin", "*")
    |> put_resp_header("Access-Control-Allow-Method", "POST, GET, OPTIONS")
    |> put_resp_header("Access-Control-Max-Age", "86400")
    |> put_resp_header(
      "Access-Control-Allow-Headers",
      "Origin, Content-Type, Accept X-Forwarded-For"
    )
  end
end
