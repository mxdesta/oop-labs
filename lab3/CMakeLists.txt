cmake_minimum_required(VERSION 3.10)

project(BitString)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(FiguresLab 
    main.cpp
    src/FigureArray.cpp include/FigureArray.h
    include/Figure.h
    src/Hexagon.cpp include/Hexagon.h
    src/Octagon.cpp include/Octagon.h
    src/Pentagon.cpp include/Pentagon.h
)
add_library(${CMAKE_PROJECT_NAME}_lib
    src/Hexagon.cpp
    src/Octagon.cpp
    src/Pentagon.cpp
    src/FigureArray.cpp
)

target_include_directories(FiguresLab PRIVATE include)
# Добавление тестов
enable_testing()

add_executable(tests test/test01.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)


# Добавление тестов в тестовый набор
add_test(NAME FiguresTests COMMAND tests)