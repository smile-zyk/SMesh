cmake_minimum_required(VERSION 3.10)

project(glwrapper)

find_package(glm REQUIRED)
find_package(glad REQUIRED)
find_package(Stb REQUIRED)
find_package(spdlog CONFIG REQUIRED)

aux_source_directory(src SRC_DIR)

add_library(${PROJECT_NAME} STATIC ${SRC_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC ${Stb_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)