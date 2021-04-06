#include <converter.hpp>
#include <errors.hpp>
#include <program_options.hpp>
#include <regex>
#include <sstream>

using std::getline;
using std::istream;
using std::ostream;
using std::regex;
using std::regex_match;
using std::smatch;
using std::ssub_match;
using std::string;

namespace {

enum struct mode { header, row };

mode
parse_header(const std::string& line, const program_options& po, std::ostream& output_file) {
    std::string        token;
    std::istringstream is(line);

    if (!po.cpp_instance_type().empty()) {
        output_file << "struct " << po.cpp_instance_type() << "{\n";

        while (getline(is, token, po.delimiter())) {
            const regex field_regex(" ?\"?(\\w+)\"? *(\\((\\w+)\\))*\"?");
            smatch      field_match;

            if (regex_match(token, field_match, field_regex) && field_match.size() == 4) {
                const ssub_match name_match = field_match[1];
                const string     name       = name_match.str();

                const ssub_match type_match = field_match[3];
                const string     type       = type_match.str() == "" ? "std::string" : type_match.str();

                output_file << po.tab() << type << ' ' << name << ";\n";
            }
        }

        output_file << "};\n\n";
    }

    return mode::row;
}

mode
parse_row(const std::string& line, const program_options& po, std::ostream& output_file) {
    if (line.size() < 10) return mode::row;

    static bool first_row = true;
    if (first_row) {
        output_file << "const " << po.cpp_container_type() << ' ' << po.cpp_container_name() << "{\n";
        first_row = false;
    }

    output_file << po.tab() << po.cpp_instance_type() << '{';

    std::string        token;
    std::istringstream is(line);

    bool first_cell = true;
    while (std::getline(is, token, po.delimiter())) {
        if (!first_cell)
            output_file << ',';
        else
            first_cell = false;

        const auto start = token.find('\"');
        const auto end   = token.rfind('\"');

        output_file << token;
    }

    output_file << "},\n";

    return mode::row;
}

}  // namespace

void
converter::convert(std::istream& input, std::ostream& output, const program_options& po) {
    output << "#pragma once\n\n";
    output << "#include <array>\n";
    output << "#include <string>\n\n";

    mode parse_mode = po.no_header() ? mode::row : mode::header;

    string line;
    while (getline(input, line)) {
        switch (parse_mode) {
            case mode::header:
                parse_mode = parse_header(line, po, output);
                break;
            case mode::row:
                parse_mode = parse_row(line, po, output);
                break;
        }
    }

    output << "};\n";
}