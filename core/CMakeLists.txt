cmake_minimum_required (VERSION 3.5)

project(smesh_core)

find_package(spdlog CONFIG REQUIRED)
find_package(OpenMesh CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)

aux_source_directory(src/smesh SRC_DIR)
aux_source_directory(src/smesh/log SRC_DIR)
aux_source_directory(src/smesh/mesh SRC_DIR)
aux_source_directory(src/smesh/render SRC_DIR)
aux_source_directory(src/smesh/qt SRC_DIR)
aux_source_directory(src/smesh/config SRC_DIR)

add_library(${PROJECT_NAME} SHARED ${SRC_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} PUBLIC glwrapper)
target_link_libraries(${PROJECT_NAME} PUBLIC qt_imgui_widgets)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets Qt5::Core Qt5::Gui)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMeshCore OpenMeshTools)
target_link_libraries(${PROJECT_NAME} PUBLIC imguizmo::imguizmo)
target_link_libraries(${PROJECT_NAME} PUBLIC qtpropertybrowser)
target_compile_definitions(${PROJECT_NAME} PRIVATE SMESH_PLATFORM_WINDOWS SMESH_BUILD_LIBRARY)
target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)
target_compile_definitions(${PROJECT_NAME} PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)