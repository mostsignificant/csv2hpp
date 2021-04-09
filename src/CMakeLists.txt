########################################################################################################################
### CSV2HPP EXECUTABLE
########################################################################################################################

add_executable(${CSV2HPP_PROJECT_NAME}
        converter.cpp
        main.cpp
        program_options.cpp
)

target_compile_features(${CSV2HPP_PROJECT_NAME} PRIVATE
        cxx_std_17
)

target_include_directories(${CSV2HPP_PROJECT_NAME} PUBLIC
        ${CSV2HPP_INC_DIR}
)
