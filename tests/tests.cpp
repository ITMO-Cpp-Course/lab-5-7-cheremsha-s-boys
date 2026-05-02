#include "document_builder.hpp"
#include "inverted_index.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

TEST_CASE("DocumentBuilder: Processing logic", "[builder]")
{
    SECTION("Basic tokenization")
    {
        auto doc = DocumentBuilder::build(1, "Lab", "Hello, World!");
        std::vector<std::string> expected = {"hello", "world"};
        REQUIRE(doc.getWords() == expected);
    }

    SECTION("Empty strings handling")
    {
        auto doc = DocumentBuilder::build(2, "Empty", "  !!!  ");
        REQUIRE(doc.getWords().empty());
    }
}

TEST_CASE("InvertedIndex: Core functionality", "[index]")
{
    InvertedIndex index;

    SECTION("Add and Search")
    {
        index.addDocument(DocumentBuilder::build(10, "D1", "physics is cool"));
        index.addDocument(DocumentBuilder::build(11, "D2", "coding is physics"));

        auto results = index.search("physics");
        REQUIRE(results.size() == 2);
        // Проверка наличия айди
        REQUIRE_THAT(results, Catch::Matchers::UnorderedEquals(std::vector<size_t>{10, 11}));
    }

    SECTION("Word counting")
    {
        index.addDocument(DocumentBuilder::build(1, "D1", "test test again"));
        REQUIRE(index.getWordCount("test", 1) == 2);
        REQUIRE(index.getWordCount("missing", 1) == 0);
    }

    SECTION("Removal logic")
    {
        index.addDocument(DocumentBuilder::build(1, "D1", "delete me"));
        REQUIRE_FALSE(index.search("delete").empty());

        index.removeDocument(1);
        CHECK(index.search("delete").empty());
    }
}