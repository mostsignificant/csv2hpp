#include <cstdlib>
#include <errors.hpp>
#include <filesystem>
#include <program_options.hpp>
#include <string>

using std::atoi;
using std::exception;
using std::numeric_limits;
using std::string;
using std::string_view;

namespace fs = std::filesystem;
namespace po = errors::program_options;

program_options::program_options(int argc, char** argv) {
    if (argc < 2) throw po::missing_input_file;

    // parse command line arguments

    _input_file = argv[1];

    for (auto i = 2; i < argc; ++i) {
        const auto option = string_view{argv[i]};

        if (option == "--no-header") {
            if (_skip_header) throw po::only_skip_or_no_header;
            _no_header = true;
        } else if (option == "--skip-header") {
            if (_no_header) throw po::only_skip_or_no_header;
            _skip_header = true;
        } else if (option == "--cpp-container-name") {
            if (++i == argc) throw po::missing_cpp_container_name_param;
            _cpp_container_name = string_view{argv[i]};
        } else if (option == "--cpp-container-type") {
            if (++i == argc) throw po::missing_cpp_container_type_param;
            _cpp_container_type = string_view{argv[i]};
        } else if (option == "--cpp-instance-name") {
            if (++i == argc) throw po::missing_cpp_instance_name_param;
            _cpp_instance_name = string_view{argv[i]};
        } else if (option == "--cpp-container-type") {
            if (++i == argc) throw po::missing_cpp_instance_type_param;
            _cpp_instance_type = string_view{argv[i]};
        } else if (option == "--delimiter-comma") {
            if (_delimiter != std::numeric_limits<char>::max()) throw po::more_than_one_delimiter_param;
            _delimiter = ',';
        } else if (option == "--delimiter-semicolon") {
            if (_delimiter != std::numeric_limits<char>::max()) throw po::more_than_one_delimiter_param;
            _delimiter = ';';
        } else if (option == "--delimiter-space") {
            if (_delimiter != std::numeric_limits<char>::max()) throw po::more_than_one_delimiter_param;
            _delimiter = ' ';
        } else if (option == "--delimiter-tab") {
            if (_delimiter != std::numeric_limits<char>::max()) throw po::more_than_one_delimiter_param;
            _delimiter = '\t';
        } else if (option == "--output") {
            if (++i == argc) throw po::missing_output_param;
            _output_file = string_view{argv[i]};
        } else if (option == "--tab-spaces") {
            if (_tab != "") throw po::more_than_one_tab_param;
            if (++i == argc) throw po::missing_tab_spaces_param;

            try {
                auto count = atoi(argv[i]);
                if (count < 1 || count > 16) throw po::out_of_tab_spaces_param_range;

                while (--count) _tab += " ";
            } catch (const exception& std_ex) {
                throw po::invalid_tab_spaces_param;
            }
        } else if (option == "--tab-char") {
            if (_tab != "") throw po::more_than_one_tab_param;
            _tab = "\n";
        }
    }

    // set defaults if options not set by command line arguments

    if (_cpp_container_name == "") _cpp_container_name = "csv_data";
    if (_cpp_container_type == "") _cpp_container_type = "std::array";
    if (_cpp_instance_type == "") _cpp_instance_type = "csv_data_entry";
    if (_tab == "") _tab = "    ";
    if (_delimiter == numeric_limits<char>::max()) _delimiter = ',';

    if (_output_file == "") {
        _output_file = _input_file;
        if (_output_file.has_extension())
            _output_file.replace_extension(".hpp");
        else
            _output_file.replace_filename(_output_file.filename().string() + ".hpp");
    }
}

string
program_options::usage() noexcept {
    return "usage: csv2hpp input_file [--output output_file_path] [--delimiter-<comma|semicolon|space|tab>] "
           "[--skip-header|--no-header] [--tab-char|--tab-spaces count] [--cpp-container-name name] "
           "[--cpp-container-type type]\n";
}

string_view
program_options::cpp_container_name() const noexcept {
    return _cpp_container_name;
}

string_view
program_options::cpp_container_type() const noexcept {
    return _cpp_container_type;
}

string_view
program_options::cpp_instance_name() const noexcept {
    return _cpp_instance_name;
}

string_view
program_options::cpp_instance_type() const noexcept {
    return _cpp_instance_type;
}

fs::path
program_options::input_file() const noexcept {
    return _input_file;
}

fs::path
program_options::output_file() const noexcept {
    return _output_file;
}

const std::string&
program_options::tab() const noexcept {
    return _tab;
}

char
program_options::delimiter() const noexcept {
    return _delimiter;
}

bool
program_options::no_header() const noexcept {
    return _no_header;
}

bool
program_options::skip_header() const noexcept {
    return _skip_header;
}
