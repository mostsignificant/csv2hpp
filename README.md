# csv2hpp

This command line tool converts CSV files into header files for easy include and compile in C or C++ programs.

## Options

The following options are all optional.

--output output_file_path
    Writes the resulting header file to the given file path. By default, the header file is named as the input csv file
    with an .hpp file ending.

--delimiter-<comma|semicolon|space|tab>
    Sets the delimiter in the csv file, for example --delimiter-tab if the csv entries are divided by tabs. Uses
    --delimiter-comma by default.

--skip-header|--no-header
    Set --skip-header if the first row in the csv file should be skipped or --no-header if the csv file does not contain
    a header row. Assumes the csv file's first line as header row by default.

--tab-char|--tab-spaces count
    Uses tab character for intendation in the output header or spaces with an argument for how many spaces, for example
    --tab-spaces 2 for intendation with two spaces. Uses --tab-spaces 4 as default.

--cpp-container-name name
    The name to use for the resulting container containing all csv entries. Uses `csv_data` as default.

--cpp-container-type type
    The type of the container for all csv entries. Uses `std::array` as default.

--cpp-instance-type type
    The name of the individual instances representing a row from the csv file. Must be included if used.

--cpp-namespace name
    The name of the cpp namespace to use. Uses no namespace as default.
