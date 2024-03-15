cmake_minimum_required (VERSION 3.5)

project(SMesh LANGUAGES CXX)

# set Qt6 path
# see in https://stackoverflow.com/questions/71086422/cmake-cannot-find-packages-within-qt6-installation
# list(APPEND CMAKE_PREFIX_PATH ${Qt6_PREFIX_PATH})

# use Qt5
set(Qt5_DIR $ENV{Qt5_PREFIX_PATH}/lib/cmake/Qt5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core Quick Gui Widgets REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Add sub directories
add_subdirectory(modules)
add_subdirectory(core)
add_subdirectory(application)
add_subdirectory(tests)