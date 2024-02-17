cmake_minimum_required (VERSION 3.8.1)
project(qtimgui)

set(Qt5_DIR $ENV{Qt5_PREFIX_PATH}/lib/cmake/Qt5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core Quick Gui Widgets REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(
    qt_imgui_sources
    src/ImGuiRenderer.h
    src/ImGuiRenderer.cpp
    src/QtImGui.h
    src/QtImGui.cpp
)

# qt_imgui_quick: library with a qt renderer for Qml / QtQuick applications
add_library(qt_imgui_quick STATIC ${qt_imgui_sources})
target_include_directories(qt_imgui_quick PUBLIC src)
target_link_libraries(
    qt_imgui_quick
    PUBLIC
    imgui::imgui
    Qt5::Gui
    )

# qt_imgui_widget: library with a qt renderer for classic Qt Widget applications
add_library(qt_imgui_widgets STATIC ${qt_imgui_sources})
target_include_directories(qt_imgui_widgets PUBLIC src)
target_link_libraries(
    qt_imgui_widgets
    PUBLIC
    imgui::imgui
    Qt5::Widgets
    )
target_compile_definitions(qt_imgui_widgets PUBLIC QT_WIDGETS_LIB)
