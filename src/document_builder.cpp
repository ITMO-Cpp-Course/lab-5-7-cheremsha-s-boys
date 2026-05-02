#include "document_builder.hpp"
#include <algorithm>
#include <cctype>

Document DocumentBuilder::build(size_t id, std::string name, std::string text)
{

    std::vector<std::string> words = splitAndNormalize(text);

    return Document(id, std::move(name), std::move(text), std::move(words));
}


std::vector<std::string> DocumentBuilder::splitAndNormalize(const std::string& text)
{
    std::vector<std::string> result;
    std::string current_word;

    for (unsigned char ch : text)
    {
        if (std::isalnum(ch))
        {
            current_word += static_cast<char>(std::tolower(ch));
        }
        else if (!current_word.empty())
        {
            result.push_back(std::move(current_word));
            current_word.clear();
        }
    }

    if (!current_word.empty())
    {
        result.push_back(std::move(current_word));
    }

    return result;
}