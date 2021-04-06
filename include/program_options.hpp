#ifndef THAT_THIS_PROGRAM_OPTIONS_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_PROGRAM_OPTIONS_HEADER_IS_ALREADY_INCLUDED

#include <filesystem>
#include <limits>
#include <string>
#include <string_view>

/**
 * Saves all command line options passed to the application. Ctor parses options and throws if parameters missing.
 * Exceptions that can be thrown: @see errors.hpp
 */
class program_options {
public:
    program_options(int argc, char** argv);

    static std::string usage() noexcept;

    std::string_view      cpp_container_name() const noexcept;
    std::string_view      cpp_container_type() const noexcept;
    std::string_view      cpp_instance_name() const noexcept;
    std::string_view      cpp_instance_type() const noexcept;
    std::filesystem::path input_file() const noexcept;
    std::filesystem::path output_file() const noexcept;
    const std::string&    tab() const noexcept;
    char                  delimiter() const noexcept;
    bool                  no_header() const noexcept;
    bool                  skip_header() const noexcept;

private:
    std::filesystem::path _input_file;
    std::filesystem::path _output_file;
    std::string_view      _cpp_container_name;
    std::string_view      _cpp_container_type;
    std::string_view      _cpp_instance_name;
    std::string_view      _cpp_instance_type;
    std::string           _tab         = "";
    char                  _delimiter   = std::numeric_limits<char>::max();
    bool                  _no_header   = false;
    bool                  _skip_header = false;
};

#endif  // THAT_THIS_PROGRAM_OPTIONS_HEADER_IS_ALREADY_INCLUDED