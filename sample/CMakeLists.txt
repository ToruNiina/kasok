set(SAMPLE_FILENAMES
    leibniz
    )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
include_directories("${PROJECT_SOURCE_DIR}/extlib/callable_traits/include/")

add_definitions(-std=c++11 -pedantic -Wall)
add_definitions(-Ofast -march=native -mtune=native)

foreach(SAMPLE_FILENAME ${SAMPLE_FILENAMES})
    add_executable(${SAMPLE_FILENAME} ${SAMPLE_FILENAME}.cpp)
endforeach(SAMPLE_FILENAME)
