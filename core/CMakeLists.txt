cmake_minimum_required (VERSION 3.5)

project(smesh_core)

set(Qt5_DIR $ENV{Qt5_PREFIX_PATH}/lib/cmake/Qt5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(OpenMesh CONFIG REQUIRED)

aux_source_directory(src/smesh SRC_DIR)
aux_source_directory(src/smesh/log SRC_DIR)
aux_source_directory(src/smesh/mesh SRC_DIR)
aux_source_directory(src/smesh/render SRC_DIR)
aux_source_directory(src/smesh/qt SRC_DIR)

add_library(${PROJECT_NAME} SHARED ${SRC_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} PRIVATE glwrapper)
target_link_libraries(${PROJECT_NAME} PRIVATE qt_imgui_widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMeshCore OpenMeshTools)
target_compile_definitions(${PROJECT_NAME} PRIVATE SMESH_PLATFORM_WINDOWS SMESH_BUILD_LIBRARY)
target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)