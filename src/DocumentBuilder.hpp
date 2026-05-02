#pragma once
#include "Document.hpp"
#include <string>
#include <vector>
namespace lab5::memory
{
class DocumentBuilder
{
  public:
    static Document build(size_t id, std::string name, std::string text);
    static std::vector<std::string> splitAndNormalize(const std::string& text);
};
} // namespace lab5::memory