#pragma once

#include "document.hpp"
#include <string>
#include <vector>


class DocumentBuilder
{
  public:
    static Document build(size_t id, std::string name, std::string text);

  private:
    static std::vector<std::string> splitAndNormalize(const std::string& text);
};