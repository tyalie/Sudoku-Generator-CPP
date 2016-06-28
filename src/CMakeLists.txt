# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required(VERSION 3.0)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/Georg/Documents/Qt/5.6/clang_64")
set(CMAKE_CXX_FLAGS -std="c++11")


# Include qt basic functions
include(QtCommon)

# Basic info about project

project(example VERSION 1.0)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

# Set additional project information
set(COMPANY "Example")
set(COPYRIGHT "Copyright (c) 2014 Vincent Lee. All rights reserved.")
set(IDENTIFIER "com.example.Example")

file(GLOB Sudoku_SRC
    "Commons/*.h"

    "*.h"
    "*.cpp"

    "GUI/*.h"
    "GUI/*.cpp"
    "GUI/*.ui"

    "Sudoku/*.h"
    "Sudoku/*.cpp"

    "Generator/*.h"
    "Generator/*.cpp"

    "Saver/*.h"
    "Saver/*.cpp"
)

set(SOURCE_FILES ${Sudoku_SRC})

add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES ../example.qrc)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Concurrent REQUIRED)


# source_group("UI Files" FILES ${UI_FILES})

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

qt5_use_modules(${PROJECT_NAME} Widgets Svg PrintSupport Concurrent)
