#ifndef THAT_THIS_ERRORS_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_ERRORS_HEADER_IS_ALREADY_INCLUDED

#include <cstdint>
#include <exception>

namespace errors {

class exception : public std::exception {
public:
    exception(const char* message, int32_t code_value);

    virtual const char* what() const noexcept;
    int32_t             code() const noexcept;

private:
    const char* message;
    int32_t     code_value;
};

namespace program_options {

static const exception missing_input_file{"input file missing!", -2};
static const exception missing_template_param{"--template parameter missing!", -3};
static const exception missing_output_param{"--output parameter missing!", -4};
static const exception more_than_one_delimiter_param{"only one --delimiter-<X> parameter allowed!", -5};
static const exception more_than_one_tab_param{"only one --tab-<X> parameter allowed!", -6};
static const exception missing_tab_spaces_param{"--tab-spaces parameter missing!", -7};
static const exception invalid_tab_spaces_param{"--tab-spaces parameter invalid, must be number in range [1;16]!", -8};
static const exception out_of_tab_spaces_param_range{"--tab-spaces parameter must be between [1;16]!", -9};
static const exception only_skip_or_no_header{"either --skip-header or --no-header allowed!", -10};
static const exception missing_cpp_container_type_param{"--cpp-container-type parameter missing!", -11};
static const exception missing_cpp_container_name_param{"--cpp-container-name parameter missing!", -12};
static const exception missing_cpp_instance_type_param{"--cpp-instance-type parameter missing!", -11};
static const exception missing_cpp_instance_name_param{"--cpp-instance-name parameter missing!", -12};

}  // namespace program_options

namespace main {

static const exception could_not_open_input_file{"could not open input file!", -6};
static const exception could_not_open_output_file{"could not open output file!", -7};

}  // namespace main

}  // namespace errors

#endif  // THAT_THIS_ERRORS_HEADER_IS_ALREADY_INCLUDED
