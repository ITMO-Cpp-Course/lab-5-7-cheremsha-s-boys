include(FetchContent)

add_executable(resource_tests
        tests.cpp
        ../src/Document.hpp
        ../src/InvertedIndex.cpp
        ../src/DocumentBuilder.cpp
)

target_compile_options(resource_tests PRIVATE -Wno-c23-extensions)

target_link_libraries(resource_tests PRIVATE
        resource_core
        project_warnings
        Catch2::Catch2WithMain
)

if (TARGET project_sanitizers)
    target_link_libraries(resource_tests PRIVATE project_sanitizers)
endif ()

add_test(NAME resource_tests COMMAND resource_tests)