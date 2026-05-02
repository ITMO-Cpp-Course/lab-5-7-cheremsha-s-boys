#include "../src/document_builder.hpp"
#include "../src/InvertedIndex.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <vector>
#include <string>

// Используем твое пространство имен, чтобы не писать lab5::memory везде
using namespace lab5::memory;

TEST_CASE("DocumentBuilder: Processing logic", "[builder]") {

    SECTION("Basic tokenization and normalization") {
        // Создаем документ через билд
        auto doc = DocumentBuilder::build(1, "Lab", "Hello, World!");

        // Ожидаем, что слова будут в нижнем регистре и без пунктуации
        std::vector<std::string> expected = {"hello", "world"};

        // ПРОВЕРЬ: Если у тебя метод называется не get_words, замени на свое имя
        REQUIRE(doc.get_words() == expected);
    }

    SECTION("Empty or special character input") {
        auto doc = DocumentBuilder::build(2, "Empty", "!!! ???");
        REQUIRE(doc.get_words().empty());
    }
}

TEST_CASE("InvertedIndex: Core functionality", "[index]") {
    InvertedIndex index;

    SECTION("Add and Search") {
        // Индексируем пару документов
        index.add_document(DocumentBuilder::build(10, "D1", "physics is cool"));
        index.add_document(DocumentBuilder::build(11, "D2", "coding is physics"));

        // Ищем слово, которое есть в обоих документах
        auto results = index.search("physics");

        REQUIRE(results.size() == 2);
        // Используем Matcher для проверки ID без привязки к порядку в векторе
        REQUIRE_THAT(results, Catch::Matchers::UnorderedEquals(std::vector<size_t>{10, 11}));
    }

    SECTION("Case insensitivity in search") {
        index.add_document(DocumentBuilder::build(1, "D1", "Apple"));

        // Поиск должен работать независимо от регистра
        auto results = index.search("apple");
        REQUIRE(results.size() == 1);
    }

    SECTION("Removing documents") {
        index.add_document(DocumentBuilder::build(1, "D1", "unique"));
        index.remove_document(1);

        auto results = index.search("unique");
        REQUIRE(results.empty());
    }
}