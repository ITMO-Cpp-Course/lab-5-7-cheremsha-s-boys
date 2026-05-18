#include "InvertedIndex.hpp"
#include "DocumentBuilder.hpp"
#include <utility>
namespace lab5::memory
{
void InvertedIndex::AddDocument(Document&& doc)
{
    size_t id = doc.id;
    if (documents.find(id) != documents.end())
    {
        return;
    }
    auto document_text = DocumentBuilder::splitAndNormalize(doc.content);
    for (const auto& word : document_text)
    {
        indexes[word][id]++;
        document_contents[id].insert(word);
    }
    documents.emplace(id, std::move(doc));
}
bool InvertedIndex::ExistsDocument(size_t id) const
{
    if (documents.find(id) != documents.end())
        return true;
    return false;
}
void InvertedIndex::RemoveDocument(size_t id)
{
    auto it_contents = document_contents.find(id);
    if (it_contents == document_contents.end())
    {
        return;
    }
    for (const auto& word : it_contents->second)
    {
        indexes[word].erase(id);
    }
    documents.erase(id);
    document_contents.erase(it_contents);
}
std::map<size_t, size_t> InvertedIndex::DocumentSearch(const std::string& query) const
{
    auto word = indexes.find(query);
    if (word != indexes.end())
    {
        return word->second;
    }
    else
        return {};
}
const Document& InvertedIndex::Get_Document(size_t id) const
{
    return documents.at(id);
}
} // namespace lab5::memory