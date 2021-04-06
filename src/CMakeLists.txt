####################################################################################################
### CSV2HPP EXECUTABLE
####################################################################################################

set(TARGET csv2hpp)

add_executable(${TARGET}
        converter.cpp
        errors.cpp
        main.cpp
        program_options.cpp)

target_compile_features(${TARGET} PUBLIC
        cxx_std_17)

target_include_directories(${TARGET} PUBLIC
        ${CSV2HPP_INC_DIR})
