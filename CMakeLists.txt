cmake_minimum_required(VERSION 3.20)

project(competitive_programming_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CP_ROOT "${PROJECT_SOURCE_DIR}")

file(GLOB_RECURSE CP_LIBRARY_CPP_FILES CONFIGURE_DEPENDS
        "${CP_ROOT}/library/*.hpp"
        "${CP_ROOT}/library/*.h"
        "${CP_ROOT}/library/*.cpp"
        "${CP_ROOT}/library/*.cc"
        "${CP_ROOT}/library/*.cxx"
)

include_directories(BEFORE "${CP_ROOT}")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/generated")
file(WRITE "${CMAKE_BINARY_DIR}/generated/cp_library_dummy.cpp"
        "void cp_library_dummy() {}\n"
)

add_library(cp_library_ide STATIC
        "${CMAKE_BINARY_DIR}/generated/cp_library_dummy.cpp"
        ${CP_LIBRARY_CPP_FILES}
)

set_source_files_properties(${CP_LIBRARY_CPP_FILES}
        PROPERTIES HEADER_FILE_ONLY ON
)

target_include_directories(cp_library_ide PRIVATE
        "${CP_ROOT}"
)