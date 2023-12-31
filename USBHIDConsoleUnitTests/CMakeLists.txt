# make sure the minimum cmake version is compatible with your compiler
cmake_minimum_required(VERSION 3.9.1)

# set a project name
project(USBHIDConsoleUnitTests)

# set C Make to use the C17 Language version
set(CMAKE_C_STANDARD 17)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}../../../doctest CACHE INTERNAL "Path to include folder for doctest")


file(GLOB_RECURSE APP_SOURCE_FILES CONFIGURE_DEPENDS "inc/*.h" "src/*.cpp" )

set(HIDAPI_HIDTEST_TARGETS)
set(CMAKE_BUILD_TYPE Debug)

add_executable(USBHIDConsoleUnitTests ${APP_SOURCE_FILES})
target_link_libraries(USBHIDConsoleUnitTests
  PRIVATE hidapi
  PRIVATE USBHIDConsoleLibrary
)

list(APPEND HIDAPI_HIDTEST_TARGETS USBHIDConsoleUnitTests)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( DocsUSBHIDConsoletUnitTests ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# install the files needed for this application
file( COPY "Libraries/hidapi.dll" DESTINATION "Debug/" )
