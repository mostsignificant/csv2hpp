#include <build>

auto
main() -> int {
    const char* CSV2HPP_PROJECT_NAME = "csv2hpp";

    build::add_executable(CSV2HPP_PROJECT_NAME, "converter.cpp", "errors.cpp", "main.cpp", "program_options.cpp");
    build::target_compile_features(CSV2HPP_PROJECT_NAME, PRIVATE, {cxx_std_17});
    build::target_include_directories(CSV2HPP_PROJECT_NAME, PUBLIC, {"/include"})
}