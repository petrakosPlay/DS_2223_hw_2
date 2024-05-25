cmake_minimum_required(VERSION 3.16.0)

set(CC gcc)
set(CMAKE_C_COMPILER ${CC})

project(bst
        VERSION 0.0.1
        LANGUAGES C
)

add_compile_options(-Wall -Werror)
add_executable(test test.c bst.c)


#============================================================================================================
