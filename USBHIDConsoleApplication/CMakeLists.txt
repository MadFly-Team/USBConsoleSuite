# make sure the minimum cmake version is compatible with your compiler
cmake_minimum_required(VERSION 3.9.1)

# set a project name
project(USBHIDConsole)

# set C Make to use the C17 Language version
set(CMAKE_C_STANDARD 17)

include(ExternalProject)
include(FetchContent)
find_package(Git REQUIRED)

# FTXUI
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v3.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

file(GLOB_RECURSE APP_SOURCE_FILES CONFIGURE_DEPENDS "inc/*.h" "src/*.cpp" )

set(HIDAPI_HIDTEST_TARGETS)
if(NOT WIN32 AND NOT APPLE AND CMAKE_SYSTEM_NAME MATCHES "Linux")
    if(TARGET hidapi::hidraw)
        add_executable(USBHIDConsole ${APP_SOURCE_DIR})
        target_link_libraries(hidtest_hidraw hidapi::hidraw)
        list(APPEND HIDAPI_HIDTEST_TARGETS hidtest_hidraw)
    endif()
    if(TARGET hidapi::libusb)
        add_executable(USBHIDConsole ${APP_SOURCE_DIR})
        target_compile_definitions(hidtest_libusb PRIVATE USING_HIDAPI_LIBUSB)
        target_link_libraries(hidtest_libusb hidapi::libusb)
        list(APPEND HIDAPI_HIDTEST_TARGETS hidtest_libusb)
    endif()
else()
     add_executable(USBHIDConsole ${APP_SOURCE_DIR})
    target_link_libraries(hidtest hidapi::hidapi)
    list(APPEND HIDAPI_HIDTEST_TARGETS hidtest)
endif()


# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# tells cmake that it will be creating a library 
target_link_libraries(CabrigDataFileGenerator
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

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
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
