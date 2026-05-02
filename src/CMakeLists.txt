
set(ENGINE_SOURCES
        InvertedIndex.cpp
        DocumentBuilder.cpp
)

add_library(engine_lib STATIC ${ENGINE_SOURCES})

target_include_directories(engine_lib PUBLIC .)