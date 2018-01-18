set(TEST_FILENAMES
    test_aitken
    )

include_directories("${PROJECT_SOURCE_DIR}/extlib/callable_traits/include/")
include_directories("${PROJECT_SOURCE_DIR}/extlib")

add_definitions("-std=c++11 -pedantic -Wall")
add_definitions("-Ofast -march=native -mtune=native")

foreach(TEST_NAME ${TEST_FILENAMES})
    add_executable(${TEST_NAME} ${TEST_NAME}.cpp)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach(TEST_NAME)
