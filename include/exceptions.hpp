#ifndef THAT_THIS_EXCEPTIONS_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_EXCEPTIONS_HEADER_IS_ALREADY_INCLUDED

#include <cstdint>
#include <exception>

// clang-format off

#define DEFINE_EXCEPTION(name, text)             \
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

DEFINE_EXCEPTION(missing_input_file, "input file parameter missing!")
DEFINE_EXCEPTION(missing_template_param, "--template parameter missing!")
DEFINE_EXCEPTION(missing_output_param, "--output parameter missing!")
DEFINE_EXCEPTION(more_than_one_delimiter_param, "only one --delimiter-<X> parameter allowed!")
DEFINE_EXCEPTION(more_than_one_tab_param, "only one --tab-<X> parameter allowed!")
DEFINE_EXCEPTION(missing_tab_spaces_param, "--tab-spaces parameter missing!")
DEFINE_EXCEPTION(invalid_tab_spaces_param, "--tab-spaces parameter invalid, must be number in range [1;16]!")
DEFINE_EXCEPTION(out_of_tab_spaces_param_range, "--tab-spaces parameter must be between [1;16]!")
DEFINE_EXCEPTION(only_skip_or_no_header, "either --skip-header or --no-header allowed!")
DEFINE_EXCEPTION(missing_cpp_container_type_param, "--cpp-container-type parameter missing!")
DEFINE_EXCEPTION(missing_cpp_container_name_param, "--cpp-container-name parameter missing!")
DEFINE_EXCEPTION(missing_cpp_instance_type_param, "--cpp-instance-type parameter missing!")
DEFINE_EXCEPTION(missing_cpp_namespace_name_param, "--cpp-namespace parameter missing!")

}  // namespace program_options

namespace main {

DEFINE_EXCEPTION(could_not_open_input_file, "could not open input file!")
DEFINE_EXCEPTION(could_not_open_output_file, "could not open output file!")

}  // namespace main

}  // namespace exceptions

#endif  // THAT_THIS_EXCEPTIONS_HEADER_IS_ALREADY_INCLUDED
