cmake_minimum_required(VERSION 3.11..3.29)
project(ccwc
        LANGUAGES CXX)


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Enables output of compile commands for debug purposes
    set(CMAKE_CXX_EXTENSIONS OFF) # disable gnu extensions

endif()

# Set C++ standard (c++23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ccwc src/ccwc.cpp)
target_compile_options(ccwc PRIVATE -Wall -Wextra -Werror -O3 -g -fdiagnostics-color=always -fuse-ld=mold)
# target_compile_options(ccwc PRIVATE -fsanitize=address -fsanitize=undefined,unreachable -fstack-protector -fno-sanitize-recover -fno-omit-frame-pointer)


# Add src directory
target_sources(ccwc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add include directory
target_include_directories(ccwc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create library header (in addition to the executable)
add_library(ccwc_lib INTERFACE)
target_include_directories(ccwc_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Enable testing
enable_testing()

# Add tests directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Configure clang-format
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    format
    COMMAND ${CLANG_FORMAT}
    -i
    -style=file
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
  )
endif()

# Configure clang-tidy
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()


# # Set the C++ standard
# target_compile_features(hw4 PRIVATE cxx_std_20)

# # Add the required compile flags

# # Additionsal flags to enable address sanitizer and ub sanitizers
# target_compile_options(ccwc PRIVATE -fdiagnostics-color=always -fsanitize=address -fsanitize=undefined,unreachable -fstack-protector -fno-sanitize-recover -fno-omit-frame-pointer)
# # Link the api library
# target_link_options(ccwc PRIVATE -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fstack-protector -fno-sanitize-recover -fno-omit-frame-pointer)
