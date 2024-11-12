find_package(Catch2 REQUIRED)
include(Catch)

set(TEST_BINARY test_${PROJECT_NAME})
enable_language(CXX)
add_executable(${TEST_BINARY}
               test_ccsh.cpp
            )

target_compile_options(${TEST_BINARY} PRIVATE -Wall -Wextra -Werror -O3 -g -fdiagnostics-color=always -fuse-ld=mold)
target_compile_features(${TEST_BINARY} PRIVATE cxx_std_23)
target_compile_definitions(${TEST_BINARY} PRIVATE _XOPEN_SOURCE=700)

target_link_libraries(${TEST_BINARY} PUBLIC lib_${PROJECT_NAME} Catch2::Catch2WithMain)
catch_discover_tests(${TEST_BINARY})


target_link_options(${TEST_BINARY} PRIVATE -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fstack-protector -fno-sanitize-recover -fno-omit-frame-pointer)
