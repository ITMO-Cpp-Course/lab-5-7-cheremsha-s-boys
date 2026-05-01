add_library(index_core
        document.cpp
        document.hpp
        inverted_index.cpp
        inverted_index.hpp
        document_builder.cpp
        document_builder.hpp
)
target_include_directories(index_core PUBLIC .)

target_include_directories(index_core PUBLIC ..)