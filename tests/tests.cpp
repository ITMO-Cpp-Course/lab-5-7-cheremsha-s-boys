#include "../src/DocumentBuilder.hpp"
#include "../src/InvertedIndex.hpp"
#include "IndexStore.hpp"
#include "Result.hpp"
#include "UpdateTransaction.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace lab5::memory;

TEST_CASE("DocumentBuilder: Processing logic", "[builder]")
{
    SECTION("Basic tokenization and normalization")
    {
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
        index.AddDocument(DocumentBuilder::build(10, "Doc1", "physics is cool"));
        index.AddDocument(DocumentBuilder::build(11, "Doc2", "coding is physics"));

        auto results = index.DocumentSearch("physics");

        REQUIRE(results.size() == 2);
        REQUIRE(results.contains(10));
        REQUIRE(results.contains(11));
    }

    SECTION("Correct occurrence counting")
    {
        index.AddDocument(DocumentBuilder::build(1, "Doc1", "test test again test"));

        auto results = index.DocumentSearch("test");

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

TEST_CASE("UpdateTransaction: Успешный коммит (commit) сохраняет изменения", "[transaction]")
{
    IndexStore store;

    {
        UpdateTransaction tx(store);

        auto res = tx.add_document(1, "First Document");
        REQUIRE(res.has_value());

        tx.commit();
    }

    REQUIRE(store.HasDocument(1) == true);
}

TEST_CASE("UpdateTransaction: RAII при ошибке", "[transaction]")
{
    IndexStore store;

    Document doc(1, "Original Document", "content");
    auto init_res = store.AddDocument(std::move(doc));
    REQUIRE(init_res.has_value());

    {
        UpdateTransaction tx(store);

        auto res1 = tx.remove_document(1);
        REQUIRE(res1.has_value());
        REQUIRE(store.HasDocument(1) == false);

        auto res2 = tx.add_document(2, "");
        REQUIRE_FALSE(res2.has_value());
        REQUIRE(res2.error() == IndexError::Invalid_Input);
    }

    REQUIRE(store.HasDocument(1) == true);
    REQUIRE(store.HasDocument(2) == false);
}

TEST_CASE("UpdateTransaction: обработка ошибок", "[transaction]")
{
    IndexStore store;

    Document doc(10, "Existing Document", "content");
    auto init_res = store.AddDocument(std::move(doc));
    REQUIRE(init_res.has_value());

    UpdateTransaction tx(store);

    SECTION("Попытка добавить уже существующий документ")
    {
        auto res = tx.add_document(10, "New Content");
        REQUIRE_FALSE(res.has_value());
        REQUIRE(res.error() == IndexError::Duplicate_Document);
    }

    SECTION("Попытка удалить несуществующий документ")
    {
        auto res = tx.remove_document(999);
        REQUIRE_FALSE(res.has_value());
        REQUIRE(res.error() == IndexError::Document_Not_Found);
    }
}