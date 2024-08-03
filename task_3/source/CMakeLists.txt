cmake_minimum_required(VERSION 3.16.0)

set(CC gcc)
set(CMAKE_C_COMPILER ${CC})

project(bst
        VERSION 0.0.1
        LANGUAGES C
)

set(EXECUTABLE test)
add_compile_options(-Wall -Werror)
#add_executable(test test.c bst.c)
add_executable(${EXECUTABLE} test.c bst.c)
target_link_directories(${EXECUTABLE} PRIVATE C:\\Users\\petrakos\\Projects\\Libraries\\lib)
target_include_directories(${EXECUTABLE} PRIVATE C:\\Users\\petrakos\\Projects\\Libraries\\include)
target_link_libraries(${EXECUTABLE} Queue Stack)

#============================================================================================================
