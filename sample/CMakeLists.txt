set(SAMPLE_FILENAMES
    leibniz
    factorial
    basel_problem
    )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
include_directories("${PROJECT_SOURCE_DIR}/extlib/callable_traits/include/")

add_definitions(-Ofast -march=native -mtune=native)

foreach(SAMPLE_FILENAME ${SAMPLE_FILENAMES})
    add_executable(${SAMPLE_FILENAME} ${SAMPLE_FILENAME}.cpp)
endforeach(SAMPLE_FILENAME)
