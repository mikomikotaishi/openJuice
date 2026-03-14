# Dependencies

This directory contains all dependencies consumed by the `openJuice` project. These are, at the time of writing:
- [Discord Social SDK](https://discord.com/developers/social-sdk) (as `discordpp`; v1.8.14856)
- [FTXUI](https://github.com/ArthurSonzogni/FTXUI) (as `ftxui`; latest version (target v7.0.0))
- [nlohmann-json](https://github.com/nlohmann/json) (aliased as `me::nlohmann::json`; latest version (target next release))
- [re2](https://github.com/google/re2) (as `google::re2`; v2025-11-05)
- [SFML](https://github.com/SFML/SFML) (as `sfml`; v3.1.0)
- [tomlplusplus](https://github.com/marzer/tomlplusplus) (as `marzer::toml`; latest version)

It is necessary to provide "wrapper libraries" as seen in this directory to ensure dependencies align with our stylistic choices regarding naming conventions, as well as various API modifications to suit our design choices more closely.

For instance, we may choose to make some namespaces into Java-style "utility classes" (stateless classes consisting only of static methods).
