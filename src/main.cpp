#include <converter.hpp>
#include <errors.hpp>
#include <fstream>
#include <iostream>
#include <program_options.hpp>

auto
main(int argc, char** argv) -> int {
    try {
        program_options po(argc, argv);

        std::fstream input_file(std::string(po.input_file()), std::ios::in);
        if (!input_file) throw errors::main::could_not_open_input_file;

        std::cout << "po.output_file()=" << po.output_file() << '\n';

        std::ofstream output_file(std::string(po.output_file()), std::ios::out);
        if (!output_file) throw errors::main::could_not_open_output_file;

        converter::convert(input_file, output_file, po);
    } catch (const errors::exception& ex) {
        std::cerr << "csv2hpp: " << ex.what() << '\n';
        std::cerr << program_options::usage();
        return ex.code();
    } catch (const std::exception& ex) {
        std::cerr << "csv2hpp: " << ex.what() << '\n';
        return -1;
    }
}