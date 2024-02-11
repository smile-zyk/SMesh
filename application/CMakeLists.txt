cmake_minimum_required(VERSION 3.5)

project(application VERSION 0.0.1 LANGUAGES CXX)

# set Qt6 path 
# see in https://stackoverflow.com/questions/71086422/cmake-cannot-find-packages-within-qt6-installation
list(APPEND CMAKE_PREFIX_PATH ${Qt6_PREFIX_PATH})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Core Gui OpenGLWidgets REQUIRED)

aux_source_directory(src SRC_DIR)

add_executable(application ${SRC_DIR} src/main)

target_link_libraries(application Qt6::Widgets Qt6::Widgets Qt6::Core Qt6::OpenGLWidgets)
target_link_libraries(application glwrapper)

add_custom_command(TARGET application POST_BUILD
    COMMAND "${Qt6_PREFIX_PATH}/bin/windeployqt.exe" $<TARGET_FILE:application>
    COMMENT "run windeployqt"
)