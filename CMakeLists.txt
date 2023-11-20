# make sure the minimum cmake version is compatible with your compiler
cmake_minimum_required(VERSION 3.9.1)

project(USBHIDConsoleSuite)

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
    hidapi
    PREFIX ${CMAKE_BINARY_DIR}/HIDAPI
    GIT_REPOSITORY https://github.com/libusb/hidapi.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# add the subdirectories for the library and testing framework being used
add_subdirectory(HIDAPI)
add_subdirectory(USBHIDConsoleLibrary)
add_subdirectory(USBHIDConsoleApplication)
add_subdirectory(USBHIDConsoleUnitTests)

# add doctest globally
include_directories(${DOCTEST_INCLUDE_DIR})
# include_directories(${CABRIG_INCLUDE_DIR})



