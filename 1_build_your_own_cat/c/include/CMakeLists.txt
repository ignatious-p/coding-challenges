set(LIBRARY_NAME lib_${PROJECT_NAME})
add_library(${LIBRARY_NAME}
            SHARED
            print_lines.c
            print_lines.h
            )

target_include_directories(${LIBRARY_NAME} PUBLIC . )

target_compile_features(${LIBRARY_NAME} PRIVATE c_std_23)
target_compile_options(${LIBRARY_NAME} PRIVATE -Wall -Wextra -Werror -O3 -g -fdiagnostics-color=always -fuse-ld=mold)