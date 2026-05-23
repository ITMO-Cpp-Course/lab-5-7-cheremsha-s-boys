#pragma once
#include "Document.hpp"
#include <map>
#include <memory>
#include <set>
#include <vector>
namespace lab5::memory
{
class InvertedIndex
{
  private:
    std::map<size_t, Document> documents;
    std::map<std::string, std::map<size_t, size_t>> indexes;
    std::map<size_t, std::set<std::string>> document_contents;

  public:
    InvertedIndex() = default;
    ~InvertedIndex() = default;
    bool ExistsDocument(size_t id) const;
    void AddDocument(Document&& doc);
    std::map<size_t, size_t> DocumentSearch(const std::string& query) const;
    void RemoveDocument(size_t id);
    const Document& Get_Document(size_t id) const;
};
} // namespace lab5::memory
