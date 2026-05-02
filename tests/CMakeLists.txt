add_executable(resource_tests tests.cpp)

target_include_directories(resource_tests PRIVATE ../src)

target_link_libraries(resource_tests
        PRIVATE
        engine_lib
        Catch2::Catch2WithMain
)