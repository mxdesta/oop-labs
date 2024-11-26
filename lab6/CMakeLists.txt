cmake_minimum_required(VERSION 3.10)
project(lr6 VERSION 1.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")

# Установка Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(lab_6_lib)

# Добавление директорий для заголовочных файлов
target_include_directories(lab_6_lib
    PUBLIC
        src
        include
)

file(GLOB_RECURSE LAB6_SRC src/*.cpp)
target_sources(lab_6_lib PRIVATE ${LAB6_SRC})

# Основной исполняемый файл
add_executable(lab_6_exe main.cpp)
target_link_libraries(lab_6_exe PRIVATE lab_6_lib)

# Настройка тестов
enable_testing()

# Создание тестового исполняемого файла
add_executable(tests test/test01.cpp)
target_link_libraries(tests PRIVATE lab_6_lib gtest_main)

# Добавление тестов в набор
add_test(NAME Tests6 COMMAND tests)
