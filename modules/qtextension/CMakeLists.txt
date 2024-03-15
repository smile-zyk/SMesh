project(qtextension)

aux_source_directory(src SRC_DIR)

add_library(${PROJECT_NAME} STATIC ${SRC_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PUBLIC qtpropertybrowser)
target_compile_definitions(${PROJECT_NAME} PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)