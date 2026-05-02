set(SRC_FILES
        InvertedIndex.cpp
        #DocumentBuilder.cpp

)

add_library(engine_lib STATIC ${SRC_FILES})

target_include_directories(engine_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)