#pragma once
#include "Document.hpp"
#include "InvertedIndex.hpp"
#include "Result.hpp"
#include "expected"
namespace lab5::memory
{
class UpdateTransaction;
class IndexStore
{
  private:
    InvertedIndex index_;

  public:
    IndexStore() = default;
    ~IndexStore() = default;
    Result<void> AddDocument(Document&& doc);
    Result<void> RemoveDocument(size_t id);
    Result<std::map<size_t, size_t>> DocumentSearch(const std::string& query) const;
    Result<UpdateTransaction> BeginTransaction();
    InvertedIndex get_snapshot() const
    {
        return index_;
    } //
    void restore_snapshot(const InvertedIndex& snapshot)
    {
        index_ = snapshot;
    } //
    bool HasDocument(size_t id) const
    {
        return index_.Only_Document(id);
    }
};
} // namespace lab5::memory