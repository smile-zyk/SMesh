cmake_minimum_required (VERSION 3.5)

project(smesh_core)

find_package(spdlog CONFIG REQUIRED)

aux_source_directory(src SRC_DIR)

add_library(${PROJECT_NAME} SHARED ${SRC_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_compile_definitions(${PROJECT_NAME} PRIVATE SMESH_PLATFORM_WINDOWS SMESH_BUILD_LIBRARY)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
