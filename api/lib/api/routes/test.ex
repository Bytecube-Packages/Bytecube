defmodule Api.Routes.Test do
  import Plug.Conn

  use Plug.Router

  plug(Api.Plugs.Cors)
  plug(:match)
  plug(:dispatch)

  get "/:id" do
    %Plug.Conn{params: %{"id" => id}} = conn

    conn
    |> put_resp_content_type("application/json")
    |> send_resp(
        200,
        Jason.encode!(%{id: id})
    )
  end
end
