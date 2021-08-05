defmodule Api do
  import Plug.Conn

  alias Api.Routes.Test

  use Plug.Router
  use Sentry.PlugCapture

  @type json :: String.t() | number | boolean | nil | [json] | %{String.t() => json}

  plug(Api.Plugs.Cors)
  plug(:match)
  plug(:dispatch)

  # define all routes here
  forward("/test", to: Test)

  options _ do
      send_resp(conn, 200, "")
  end

  get _ do
      send_resp(conn, 404, "not found")
  end

  post _ do
      send_resp(conn, 404, "not found")
  end
end
