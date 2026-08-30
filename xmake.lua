set_project("openJuice")
set_version("0.0.1")

add_rules("mode.release", "mode.debug")
set_languages("c++23")

-- Forcing Clang temporarily, will probably change this later
set_toolchains("llvm")

set_warnings("all")
-- set_warnings("all", "error")

if is_mode("debug") then 
    set_symbols("debug")
    set_optimize("none")
else 
    set_symbols("hidden")
    set_optimize("fastest")
    set_strip("all")
end

add_requires("boost[asio,regex,system] >= 1.88.0", { alias = "boost" })
add_requires("ftxui >= 6.1.9", { alias = "ftxui" })
add_requires("sqlitecpp >= 3.3.3", { alias = "sqlitecpp" })
add_requires("tomlplusplus >= 3.4.0", { alias = "tomlpp" })

set_policy("build.sanitizer.address", true)
set_policy("build.c++.modules", true)

target("openJuice")
set_kind("binary")
add_includedirs("include")
add_includedirs("deps/discordpp/discordpp")
add_files(
    "deps/**/*.cppm",

    -- Source directories
    "src/**/*.cppm",
    "src/Main.cpp"
)
add_packages(
    "ftxui", 
    "nlohmann-json",
    "sqlitecpp",
    "tomlpp", 
    { public = true }
)
add_packages("boost", { links = {"boost_asio", "boost_regex", "boost_system"} })
