#include "../src/DocumentBuilder.hpp"
#include "../src/InvertedIndex.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace lab5::memory;

TEST_CASE("DocumentBuilder: Processing logic", "[builder]")
{
    SECTION("Basic tokenization and normalization")
    {
        // Проверяем, что билд создает документ и корректно разбивает текст
        auto words = DocumentBuilder::splitAndNormalize("Hello, World! HELLO.");
        std::vector<std::string> expected = {"hello", "world", "hello"};
        REQUIRE(words == expected);
    }

    SECTION("Empty strings handling")
    {
        auto words = DocumentBuilder::splitAndNormalize("   !!!   ");
        REQUIRE(words.empty());
    }
}

TEST_CASE("InvertedIndex: Core functionality", "[index]")
{
    InvertedIndex index;

    SECTION("Add and Search documents")
    {
        // Используем std::move, так как копирование Document запрещено
        index.AddDocument(DocumentBuilder::build(10, "Doc1", "physics is cool"));
        index.AddDocument(DocumentBuilder::build(11, "Doc2", "coding is physics"));

        auto results = index.DocumentSearch("physics");

        // Должно найти в обоих документах
        REQUIRE(results.size() == 2);
        REQUIRE(results.contains(10));
        REQUIRE(results.contains(11));
    }

    SECTION("Correct occurrence counting")
    {
        index.AddDocument(DocumentBuilder::build(1, "Doc1", "test test again test"));

        auto results = index.DocumentSearch("test");
        // Слово "test" встречается 3 раза в документе 1
        REQUIRE(results.at(1) == 3);
    }

    SECTION("Removal logic")
    {
        index.AddDocument(DocumentBuilder::build(1, "Doc1", "delete me"));
        REQUIRE_FALSE(index.DocumentSearch("delete").empty());

        index.RemoveDocument(1);
        auto results = index.DocumentSearch("delete");
        CHECK(results.empty());
    }

    SECTION("Search for non-existent word")
    {
        index.AddDocument(DocumentBuilder::build(1, "Doc1", "simple text"));
        auto results = index.DocumentSearch("ghost");
        REQUIRE(results.empty());
    }
}