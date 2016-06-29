cmake_minimum_required(VERSION 3.5)

if(APPLE)
    set(CMAKE_PREFIX_PATH "/Users/Georg/Documents/Qt/5.6/clang_64")
elseif(UNIX)
    set(CMAKE_PREFIX_PATH "/home/gansgar/Qt/5.6/gcc_64")
endif()

set (pack true)
if(pack)
    include(CMakeLists_pack.txt)
else()

    project(Sudoku)

    

    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_CXX_FLAGS -std="c++11")

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


    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Svg REQUIRED)
    find_package(Qt5PrintSupport REQUIRED)
    find_package(Qt5Concurrent REQUIRED)

    add_executable(Sudoku ${SOURCE_FILES})
    target_link_libraries(Sudoku Qt5::Widgets Qt5::Svg Qt5::PrintSupport Qt5::Concurrent)
endif()
