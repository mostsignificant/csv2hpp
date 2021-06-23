# csv2hpp

This command line tool converts CSV files into header files for easy include and compile in C++ programs.

## Installation

Download the latest version from the releases or build by hand:

```sh
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install .
```

## Usage

The simplest use case is to call csv2hpp with the csv file you want to convert as input:

```sh
csv2hpp data.csv
```

This call will generate a `data.hpp` file with the contents of the csv file to include in your C++ program.

The tool will generate a sruct for each entry with fields for the cell data. The types of these fields can be determined
within brackets in the header cell. It defaults to std::any if it cannot be determined.

`".*"` -> std::string
`[0-9]+` -> int
`[0-9]+\.[0-9]*` -> double


### Examples

The folder `examples` contains different csv files to try. The `baseball.csv` contains baseball data looking like this:

```csv
"Name", "Team", "Position", "Height (int)", "Weight (int), "Age (float)"
"Adam Donachie", "BAL", "Catcher", 74, 180, 22.99
"Paul Bako", "BAL", "Catcher", 74, 215, 34.69
"Ramon Hernandez", "BAL", "Catcher", 72, 210, 30.78
...
```

If you call csv2hpp to convert this file, the resulting header file will look like this:

```cpp
#pragma once

#include <array>
#include <string>

struct csv_data_entry{
    std::string Name;
    std::string Team;
    std::string Position;
    int Height;
    int Weight;
    float Age;
};

const std::array csv_data{
    csv_data_entry{"Adam Donachie", "BAL", "Catcher", 74, 180, 22.99},
    csv_data_entry{"Paul Bako", "BAL", "Catcher", 74, 215, 34.69},
    csv_data_entry{"Ramon Hernandez", "BAL", "Catcher", 72, 210, 30.78},
    // ...
};
```

### Options

The following options are all optional.

#### --output output_file_path

Writes the resulting header file to the given file path. By default, the header file is named as the input csv file with
an .hpp file ending.

#### --delimiter-<comma|semicolon|space|tab>

Sets the delimiter in the csv file, for example --delimiter-tab if the csv entries are divided by tabs. Uses
--delimiter-comma by default.

#### --skip-header|--no-header

Set --skip-header if the first row in the csv file should be skipped or --no-header if the csv file does not contain a
header row. Assumes the csv file's first line as header row by default.

#### --tab-char|--tab-spaces count

Uses tab character for intendation in the output header or spaces with an argument for how many spaces, for example
--tab-spaces 2 for intendation with two spaces. Uses --tab-spaces 4 as default.

#### --cpp-container-name name

The name to use for the resulting container containing all csv entries. Uses `csv_data` as default.

#### --cpp-container-type type

The type of the container for all csv entries. Uses `std::array` as default.

#### --cpp-instance-type type

The name of the individual instances representing a row from the csv file. Must be included if used.

#### --cpp-namespace name

The name of the cpp namespace to use. Uses no namespace as default.
