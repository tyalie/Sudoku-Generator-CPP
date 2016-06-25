cmake_minimum_required(VERSION 3.5)
project(Sudoku)

set(CMAKE_PREFIX_PATH "/Users/Georg/Documents/Qt/5.6/clang_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS -std="c++11")

set(SOURCE_FILES main.cpp GUI/mainwindow.h GUI/mainwindow.cpp GUI/mainwindow.ui)
find_package(Qt5Widgets)

add_executable(Sudoku ${SOURCE_FILES})
target_link_libraries(Sudoku Qt5::Widgets)
