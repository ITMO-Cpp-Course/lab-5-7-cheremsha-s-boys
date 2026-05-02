#pragma once
#include <string>
#include <utility>
namespace lab5::memory
{
struct Document
{
    size_t id;
    std::string name;
    std::string content;

    Document(size_t id, std::string name, std::string content)
        : id(id), name(std::move(name)), content(std::move(content)) {}; //
    ~Document() = default;
    Document(const Document&) = delete;
    Document& operator=(const Document&) = delete;
    Document(Document&& other) noexcept = default;
    Document& operator=(Document&& other) noexcept = default;
};
} // namespace lab5::memory
