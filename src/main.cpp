#include <converter.hpp>
#include <exception>
#include <exceptions.hpp>
#include <fstream>
#include <iostream>
#include <program_options.hpp>

auto
main(int argc, char** argv) -> int {
    try {
        program_options po(argc, argv);

        std::fstream input_file(po.input_file().c_str(), std::ios::in);
        if (!input_file) throw exceptions::main::could_not_open_input_file();

        std::ofstream output_file(po.output_file().c_str(), std::ios::out);
        if (!output_file) throw exceptions::main::could_not_open_output_file();

        converter::convert(input_file, output_file, po);
        return 0;
    } catch (const exceptions::exception& ex) {
        std::cerr << "csv2hpp: " << ex.what() << '\n';
        std::cerr << program_options::usage();
        return ex.code();
    } catch (const std::exception& ex) {
        std::cerr << "csv2hpp: " << ex.what() << '\n';
        return -1;
    }
}