cmake_minimum_required(VERSION 3.10)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(ProjectName "MidnightMath")

project("${ProjectName}" VERSION 0.1)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    DOWNLOAD_EXTRACT_TIMESTAMP false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 20)

add_custom_target(q_start_clock ALL
    COMMENT "Starting console clock"
    COMMAND "${PROJECT_SOURCE_DIR}/console_clock/bin/run.bat"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/console_clock/bin"
)

#app executable
add_library("${ProjectName}" STATIC
        #src files
        src/information.cpp
        #header files
        include/information.hpp
        include/vector.hpp
        include/constants.hpp
        include/matrix.hpp
)

add_dependencies("${ProjectName}" q_start_clock)

enable_testing()

add_executable(md-math-tests 
    tests/sanity_test.cpp
    tests/vector_tests.cpp
    tests/simd_vector_tests.cpp
    tests/matrix_tests.cpp
)

target_link_libraries(md-math-tests gtest_main ${ProjectName})

include(googletest)