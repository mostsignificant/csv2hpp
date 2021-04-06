########################################################################################################################
### CSV2HPP EXECUTABLE
########################################################################################################################

cmake_minimum_required(VERSION 3.2)

########################################################################################################################
### PROJECT DESCRIPTION
########################################################################################################################

set(CSV2HPP_PROJECT_NAME        "csv2hpp")
set(CSV2HPP_PROJECT_DESCRIPTION "a tool to convert files into header files for easy include")
set(CSV2HPP_AUTHOR_DOMAIN       "https://github.com/mostsignificant/csv2hpp")
set(CSV2HPP_AUTHOR_MAINTAINER   "mostsig@gmail.com")
set(CSV2HPP_VERSION_MAJOR       "0")
set(CSV2HPP_VERSION_MINOR       "0")
set(CSV2HPP_VERSION_PATCH       "1")
set(CSV2HPP_VERSION             "${CSV2HPP_VERSION_MAJOR}.${CSV2HPP_VERSION_MINOR}.${CSV2HPP_VERSION_PATCH}")
set(CSV2HPP_NAME_VERSION        "${CSV2HPP_PROJECT_NAME} v${CSV2HPP_VERSION}")

########################################################################################################################
### PROJECT OPTIONS
########################################################################################################################

option(OPTION_BUILD_DOCS  "Build documentation." OFF)
option(OPTION_BUILD_TESTS "Build tests."         OFF)

if(OPTION_BUILD_DOCS)

    add_subdirectory(docs)

endif(OPTION_BUILD_DOCS)

if(OPTION_BUILD_TESTS)

    enable_testing()
    add_subdirectory(tests)

endif(OPTION_BUILD_TESTS)

########################################################################################################################
### PROJECT DEFINITION
########################################################################################################################

project(${CSV2HPP_PROJECT_NAME})

set(CSV2HPP_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(CSV2HPP_INC_DIR ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
