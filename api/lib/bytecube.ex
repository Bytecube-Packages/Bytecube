defmodule Bytecube do
  use Application

  def start(_type, _args) do
      import Supervisor.Spec, warn: false

      children = [
        Plug.Cowboy.child_spec(
            scheme: :http,
            plug: Api,
            options: [
                port: 8000,
                dispatch: dispatch(),
                protocol_options: [idle_timeout: :infinity]
            ]
        )
      ]

      opts = [strategy: :one_for_one, name: Bytecube.Supervisor]
      Supervisor.start_link(children, opts)
  end

  defp dispatch do
    [
      {:_,
       [
         {:_, Plug.Cowboy.Handler, {Api, []}}
       ]}
    ]
  end
end
