enable_testing()

project(tests)

find_package(GTest CONFIG REQUIRED)

add_executable(configtest configtest.cc)

target_link_libraries(configtest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(configtest PRIVATE smesh_core)
target_compile_definitions(configtest PRIVATE SMESH_PLATFORM_WINDOWS)
target_compile_definitions(configtest PRIVATE _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)

add_test(NAME configtest
        COMMAND $<TARGET_FILE:configtest>
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})