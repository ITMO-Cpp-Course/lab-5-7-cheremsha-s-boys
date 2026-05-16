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
    Document() = default;
    Document(size_t id, std::string name, std::string content)
        : id(id), name(std::move(name)), content(std::move(content))
    {
    }
    ~Document() = default;
    Document(const Document&) = default;
    Document& operator=(const Document&) = default;
    Document(Document&& other) = default;
    Document& operator=(Document&& other) = default;
};
} // namespace lab5::memory
