#include <converter.hpp>
#include <errors.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <program_options.hpp>

using std::cerr;
using std::exception;
using std::fstream;
using std::ios;
using std::ofstream;

auto
main(int argc, char** argv) -> int {
    try {
        program_options po(argc, argv);

        fstream input_file(po.input_file().c_str(), ios::in);
        if (!input_file) throw errors::main::could_not_open_input_file;

        ofstream output_file(po.output_file().c_str(), ios::out);
        if (!output_file) throw errors::main::could_not_open_output_file;

        converter::convert(input_file, output_file, po);
    } catch (const errors::exception& ex) {
        cerr << "csv2hpp: " << ex.what() << '\n';
        cerr << program_options::usage();
        return ex.code();
    } catch (const exception& ex) {
        cerr << "csv2hpp: " << ex.what() << '\n';
        return -1;
    }
}