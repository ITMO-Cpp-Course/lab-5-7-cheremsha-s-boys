add_library(index_core
        Document.hpp
        InvertedIndex.cpp
        InvertedIndex.hpp
        document_builder.cpp
        document_builder.hpp
)
target_include_directories(index_core PUBLIC .)