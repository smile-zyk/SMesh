cmake_minimum_required(VERSION 3.21)

project(application VERSION 0.0.1 LANGUAGES CXX)

aux_source_directory(src SRC_DIR)

message("CMAKE_AUTORCC is ${CMAKE_AUTORCC}")

qt5_add_resources(QRC_FILES
 resources/application.qrc
 resources/qdarkstyle/dark/darkstyle.qrc
 resources/qdarkstyle/light/lightstyle.qrc
 )

add_executable(${PROJECT_NAME} ${SRC_DIR} ${QRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
target_link_libraries(${PROJECT_NAME} PRIVATE smesh_core)
target_compile_definitions(${PROJECT_NAME} PRIVATE SMESH_PLATFORM_WINDOWS)
target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)

# run windeployqt
add_custom_command(TARGET
    ${PROJECT_NAME} POST_BUILD
    COMMAND "$ENV{Qt5_PREFIX_PATH}/bin/windeployqt.exe" $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "run windeployqt")