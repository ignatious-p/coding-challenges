find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

set(TEST_BINARY ${PROJECT_NAME}_test)
add_executable(${TEST_BINARY}
               test_argument_parser.cpp
               test_counters.cpp
            )

target_compile_options(${TEST_BINARY} PRIVATE -Wall -Wextra -Werror -O3 -g -fdiagnostics-color=always -fuse-ld=mold)
target_compile_features(${TEST_BINARY} PRIVATE cxx_std_23)


target_link_libraries(${TEST_BINARY} ccwc_lib Catch2::Catch2WithMain)
# target_link_options(${TEST_BINARY} PRIVATE -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fstack-protector -fno-sanitize-recover -fno-omit-frame-pointer)
catch_discover_tests(${TEST_BINARY})
