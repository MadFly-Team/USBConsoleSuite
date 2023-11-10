# make sure the minimum cmake version is compatible with your compiler
cmake_minimum_required(VERSION 3.9.1)

# set a project name and version number
project(CabrigDaatGenerator VERSION 0.0.1)

# set C Make to use the C++20 Language version
set(CMAKE_CXX_STANDARD 20)

include(ExternalProject)
include(FetchContent)

find_package(Git REQUIRED)

ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Add(
    BlackstarCabrig
    PREFIX ${CMAKE_BINARY_DIR}/HIDAPI
    GIT_REPOSITORY https://github.com/libusb/hidapi.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")
ExternalProject_Get_Property(BlackstarCabrig source_dir)
set(DCABRIG_INCLUDE_DIR ${source_dir}/BlackstarCabrig CACHE INTERNAL "Path to include folder for doctest")


# add the subdirectories for the library and testing framework being used
add_subdirectory(HIDAPI)
add_subdirectory(USBConsoleController)

# add doctest globally
include_directories(${DOCTEST_INCLUDE_DIR})
# include_directories(${CABRIG_INCLUDE_DIR})



