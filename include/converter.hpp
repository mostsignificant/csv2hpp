#ifndef THAT_THIS_CONVERTER_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_CONVERTER_HEADER_IS_ALREADY_INCLUDED

#include <iostream>
#include <string_view>

class program_options;

namespace converter {

void convert(std::istream& input, std::ostream& output, const program_options& po);

}  // namespace converter

#endif  // THAT_THIS_CONVERTER_HEADER_IS_ALREADY_INCLUDED