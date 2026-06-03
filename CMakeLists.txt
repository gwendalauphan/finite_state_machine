cmake_minimum_required(VERSION 3.16)
project(finite-state-automata C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Debug flags
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -O0 -Wall -Wextra -Wpedantic -fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

# Source files
set(SRC_FILES
    src/main.c
    src/part_1.c
    src/part_2.c
    src/part_3.c
    src/settings.c
    src/functions/input.c
    src/functions/librairies.c
    src/functions/ht.c
    src/functions/demo.c
    src/functions/algo.c
    src/functions/modif.c
    src/functions/test.c
    src/functions/readFile.c
    src/functions/writeFile.c
    src/functions/utils_split.c
)

add_executable(automate ${SRC_FILES})

add_custom_target(run
    COMMAND automate
    DEPENDS automate
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running the main program"
)

enable_testing()
add_executable(test_basic src/test_basic.c)
add_test(NAME BasicTest COMMAND $<TARGET_FILE:test_basic>)
