include(CTest)

set(TEST_BINARY ${PROJECT_NAME}_test)
add_executable(${TEST_BINARY}
               test_cccat.c
            )

target_compile_options(${TEST_BINARY} PRIVATE -Wall -Wextra -Werror -O3 -g -fdiagnostics-color=always -fuse-ld=mold)
target_compile_features(${TEST_BINARY} PRIVATE c_std_23)


# target_link_options(${TEST_BINARY} PRIVATE -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fstack-protector -fno-sanitize-recover -fno-omit-frame-pointer)
