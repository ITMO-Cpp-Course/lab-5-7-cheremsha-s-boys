#include "document_builder.hpp"
#include <algorithm>
#include <cctype>
namespace lab5::memory
{
Document DocumentBuilder::build(size_t id, std::string name, std::string content)
{

    std::vector<std::string> words = splitAndNormalize(content);

    return Document(id, std::move(name), std::move(content), std::move(words));
}

std::vector<std::string> DocumentBuilder::splitAndNormalize(const std::string& content)
{
    std::vector<std::string> result;
    std::string current_word;

    for (unsigned char ch : content)
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
}