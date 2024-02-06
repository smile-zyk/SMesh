cmake_minimum_required(VERSION 3.10)

project(glwrapper)

find_package(glm REQUIRED)
find_package(glad REQUIRED)
find_package(Stb REQUIRED)

add_library(${PROJECT_NAME} STATIC
    src/buffer.cc
    src/buffer.h
    src/gl_common.cc
    src/gl_common.h
    src/gl_client.cc
    src/gl_client.h
    src/shader.cc
    src/shader.h
    src/shader_program.cc
    src/shader_program.h
    src/texture.cc
    src/texture.h
    src/vertex_array.cc
    src/vertex_array.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm glad::glad)