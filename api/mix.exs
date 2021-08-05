defmodule Bytecube.MixProject do
  use Mix.Project

  def project do
    [
      app: :bytecube,
      version: "0.0.1",
      start_permanent: true,
      deps: deps(),
      elixirc_paths: elixirc_paths(),
      aliases: aliases()
    ]
  end

  def application do
    [
      mod: {Bytecube, []}
    ]
  end

  defp deps do
    [
      {:plug_cowboy, "~> 2.5"},
      {:phoenix_pubsub, "~> 2.0.0"},
      {:ecto_sql, "~> 3.0"},
      {:ecto_enum, "~> 1.4"},
      {:jason, "~> 1.2"},
      {:joken, "~> 2.0"},
      {:elixir_uuid, "~> 1.2"},
      {:net_address, "~> 0.3"},

      {:httpoison, "~> 1.8"},
      {:finch, "~> 0.6"},
      {:sentry, "~> 8.0"},
      {:postgrex, ">= 0.0.0"},
    ]
  end

  defp elixirc_paths(), do: ["lib"]

  defp aliases do
    [
      "ecto.setup": ["ecto.create", "ecto.migrate"],
      "ecto.reset": ["ecto.drop", "ecto.setup"],
      test: ["ecto.create --quiet", "ecto.migrate", "test"]
    ]
  end
end
