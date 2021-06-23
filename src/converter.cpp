#include <converter.hpp>
#include <exceptions.hpp>
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

enum struct mode { header, first_row, row };

struct declaration {
    struct field {
        std::string type;
        std::string name;
    };

    auto
    is_complete() const noexcept -> bool {
        return std::none_of(fields.begin(), fields.end(), [](auto field) { return field.type.empty(); });
    }

    std::vector<field> fields = {};
};

void
print_declaration(const program_options& po, const declaration& decl, std::ostream& out) {
    out << "struct " << po.cpp_instance_type() << "{\n";

    for (const auto& field : decl.fields) {
        out << po.tab() << field.type << " " << field.name << ";\n";
    }

    out << "};\n\n";
}

mode
parse_header(const program_options& po, const std::string& line, declaration& decl, std::ostream& out) {
    std::string        token;
    std::istringstream is(line);

    while (getline(is, token, po.delimiter())) {
        const regex field_regex(" ?\"?(\\w+)\"? *(\\((\\w+)\\))*\"?");
        smatch      field_match;

        if (regex_match(token, field_match, field_regex) && field_match.size() == 4) {
            const ssub_match name_match = field_match[1];
            const string     name       = name_match.str();

            const ssub_match type_match = field_match[3];
            const string     type       = type_match.str();

            decl.fields.push_back({type, name});
        } else {
            throw exceptions::parsing::could_not_determine_csv_fields();
        }
    }

    return mode::first_row;
}

mode
parse_first_row(const program_options& po, const std::string& line, declaration& decl, std::ostream& out) {
    std::string        token;
    std::istringstream is(line);

    // parse first line to complete declaration with missing type defines

    if (!decl.is_complete()) {
        int i = 0;
        while (std::getline(is, token, po.delimiter())) {
            auto& type = decl.fields.at(i).type;
            if (type.empty()) {
                if (regex_match(token, std::regex(" ?\".+\" ?")))
                    type = "std::string_view";
                else if (regex_match(token, std::regex(" ?[0-9]+ ?")))
                    type = "int";
                else if (regex_match(token, std::regex(" ?[0-9]+\\.[0-9]* ?")))
                    type = "double";
            }
            i++;
        }
    }

    // if all field types could be found print declaration or except out of here

    if (decl.is_complete())
        print_declaration(po, decl, out);
    else
        throw exceptions::parsing::could_not_determine_column_types();

    // print the first data row

    out << "const " << po.cpp_container_type() << ' ' << po.cpp_container_name() << "{\n";

    bool first_cell = true;
    while (std::getline(is, token, po.delimiter())) {
        if (!first_cell)
            out << ',';
        else
            first_cell = false;

        out << token;
    }

    return mode::row;
}

mode
parse_row(const program_options& po, const std::string& line, std::ostream& out) {
    out << po.tab() << po.cpp_instance_type() << '{';

    std::string        token;
    std::istringstream is(line);

    bool first_cell = true;
    while (std::getline(is, token, po.delimiter())) {
        if (!first_cell)
            out << ',';
        else
            first_cell = false;

        out << token;
    }

    out << "},\n";

    return mode::row;
}

}  // namespace

void
converter::convert(const program_options& po, std::istream& in, std::ostream& out) {
    out << "#pragma once\n\n";
    out << "#include <any>\n";
    out << "#include <array>\n";
    out << "#include <string_view>\n\n";

    if (!po.cpp_namespace().empty()) out << "namespace " << po.cpp_namespace() << "{\n\n";

    mode        parse_mode = po.no_header() ? mode::first_row : mode::header;
    declaration decl;

    string line;
    while (getline(in, line)) {
        switch (parse_mode) {
            case mode::header: {
                parse_mode = parse_header(po, line, decl, out);
                break;
            }
            case mode::first_row: {
                parse_mode = parse_first_row(po, line, decl, out);
                break;
            }
            case mode::row:
                parse_mode = parse_row(po, line, out);
                break;
        }
    }

    out << "};\n";

    if (!po.cpp_namespace().empty()) out << "} // namespace " << po.cpp_namespace() << '\n';

    out << '\n';
}