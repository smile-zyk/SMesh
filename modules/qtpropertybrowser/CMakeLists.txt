cmake_minimum_required (VERSION 3.8.1)
project(qtpropertybrowser)

set(Qt5_DIR $ENV{Qt5_PREFIX_PATH}/lib/cmake/Qt5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core Quick Gui Widgets REQUIRED)

aux_source_directory(src SRC_DIR)

qt5_add_resources(QRC_FILES
 src/qtpropertybrowser.qrc
)

add_library(${PROJECT_NAME} STATIC ${SRC_DIR} ${QRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_compile_definitions(${PROJECT_NAME} PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)