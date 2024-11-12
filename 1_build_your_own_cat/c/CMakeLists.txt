cmake_minimum_required(VERSION 3.11..3.29)
project(cccat
        LANGUAGES C)


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Enables output of compile commands for debug purposes
    set(CMAKE_C_EXTENSIONS OFF) # disable gnu extensions

endif()

# Set C standard (c23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)


# Create an executable
add_executable(cccat src/cccat.c)

# Add src directory to cccat
target_sources(cccat PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(cccat PRIVATE -Wall -Wextra -Werror -O3 -g -fdiagnostics-color=always -fanalyzer -fuse-ld=mold)
target_compile_options(cccat PRIVATE -fsanitize=address -fsanitize=undefined,unreachable -fstack-protector -fno-sanitize-recover -fno-omit-frame-pointer)
target_compile_definitions(cccat PRIVATE _XOPEN_SOURCE=700)


# Add the library directory (will be linked as a shared library)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include)
# Link the executable to the library
target_link_libraries(cccat PUBLIC lib_${PROJECT_NAME})

# Add a tests directory (which will make an independant executable)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)


# # Add the required compile flags
# # Link the api library
target_link_options(cccat PRIVATE -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fstack-protector -fno-sanitize-recover -fno-omit-frame-pointer)
