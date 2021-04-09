#ifndef THAT_THIS_EXCEPTIONS_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_EXCEPTIONS_HEADER_IS_ALREADY_INCLUDED

#include <cstdint>
#include <exception>

// clang-format off

#define DECLARE_EXCEPTION(name, text)             \
    struct name : exception {                     \
        const char*                               \
        what() const noexcept override {          \
            return text;                          \
        }                                         \
        int64_t code() const noexcept override {  \
            return __COUNTER__;                   \
        }\
    };

// clang-format on

namespace exceptions {

struct exception : std::exception {
    virtual int64_t code() const noexcept = 0;
};

namespace program_options {

DECLARE_EXCEPTION(missing_input_file, "input file parameter missing!")
DECLARE_EXCEPTION(missing_template_param, "--template parameter missing!")
DECLARE_EXCEPTION(missing_output_param, "--output parameter missing!")
DECLARE_EXCEPTION(more_than_one_delimiter_param, "only one --delimiter-<X> parameter allowed!")
DECLARE_EXCEPTION(more_than_one_tab_param, "only one --tab-<X> parameter allowed!")
DECLARE_EXCEPTION(missing_tab_spaces_param, "--tab-spaces parameter missing!")
DECLARE_EXCEPTION(invalid_tab_spaces_param, "--tab-spaces parameter invalid, must be number in range [1;16]!")
DECLARE_EXCEPTION(out_of_tab_spaces_param_range, "--tab-spaces parameter must be between [1;16]!")
DECLARE_EXCEPTION(only_skip_or_no_header, "either --skip-header or --no-header allowed!")
DECLARE_EXCEPTION(missing_cpp_container_type_param, "--cpp-container-type parameter missing!")
DECLARE_EXCEPTION(missing_cpp_container_name_param, "--cpp-container-name parameter missing!")
DECLARE_EXCEPTION(missing_cpp_instance_type_param, "--cpp-instance-type parameter missing!")
DECLARE_EXCEPTION(missing_cpp_instance_name_param, "--cpp-instance-name parameter missing!")

}  // namespace program_options

namespace main {

DECLARE_EXCEPTION(could_not_open_input_file, "could not open input file!")
DECLARE_EXCEPTION(could_not_open_output_file, "could not open output file!")

}  // namespace main

}  // namespace exceptions

#endif  // THAT_THIS_EXCEPTIONS_HEADER_IS_ALREADY_INCLUDED
