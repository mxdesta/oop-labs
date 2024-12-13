cmake_minimum_required(VERSION 3.10)
project(lr4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)


add_library(lab_4_lib INTERFACE)

target_include_directories(lab_4_lib INTERFACE src)

add_executable(lab_4_exe main.cpp)

target_link_libraries(lab_4_exe PRIVATE lab_4_lib)

target_include_directories(lab_4_exe PRIVATE lab_4_lib)
# Добавление тестов
enable_testing()

add_executable(tests test/test01.cpp)
target_link_libraries(tests lab_4_lib gtest_main)


# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)