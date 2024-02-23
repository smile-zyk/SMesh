cmake_minimum_required(VERSION 3.21)

project(application VERSION 0.0.1 LANGUAGES CXX)

# set Qt6 path
# see in https://stackoverflow.com/questions/71086422/cmake-cannot-find-packages-within-qt6-installation
# list(APPEND CMAKE_PREFIX_PATH ${Qt6_PREFIX_PATH})

# use Qt5
set(Qt5_DIR $ENV{Qt5_PREFIX_PATH}/lib/cmake/Qt5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

aux_source_directory(src SRC_DIR)

add_executable(${PROJECT_NAME} ${SRC_DIR} src/main)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
target_link_libraries(${PROJECT_NAME} PRIVATE smesh_core)
target_compile_definitions(${PROJECT_NAME} PRIVATE SMESH_PLATFORM_WINDOWS)

# run windeployqt
add_custom_command(TARGET 
    ${PROJECT_NAME} POST_BUILD
    COMMAND "$ENV{Qt5_PREFIX_PATH}/bin/windeployqt.exe" $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "run windeployqt")