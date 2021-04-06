#include <errors.hpp>

using errors::exception;

exception::exception(const char* message, const int64_t code_value)
    : message(message), code_value(code_value) {}

const char*
exception::what() const noexcept {
    return message;
}

int64_t
exception::code() const noexcept {
    return code_value;
}
