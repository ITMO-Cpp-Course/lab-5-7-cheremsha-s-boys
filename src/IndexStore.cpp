#include "IndexStore.hpp"
#include "DocumentBuilder.hpp"
#include "UpdateTransaction.hpp"
#include <utility>
namespace lab5::memory
{
Result<void> IndexStore::AddDocument(Document&& doc)
{
    if (doc.content.empty() || doc.name.empty())
    {
        return std::unexpected(IndexError::Invalid_Input);
    }
    if (index_.ExistsDocument(doc.id))
    {
        return std::unexpected(IndexError::Duplicate_Document);
    }
    index_.AddDocument(std::move(doc));
    return {};
}
Result<void> IndexStore::RemoveDocument(size_t id)
{
    if (!(index_.ExistsDocument(id)))
    {
        return std::unexpected(IndexError::Document_Not_Found);
    }
    index_.RemoveDocument(id);
    return {};
}
Result<std::map<size_t, size_t>> IndexStore::DocumentSearch(const std::string& query) const
{
    if (query.empty())
    {
        return std::unexpected(IndexError::Invalid_Input);
    }
    auto tokens = DocumentBuilder::splitAndNormalize(query);
    if (tokens.empty())
    {
        return std::unexpected(IndexError::Invalid_Input);
    }
    auto result = index_.DocumentSearch(query);
    return result;
}
Result<UpdateTransaction> IndexStore::BeginTransaction()

{
    return Result<UpdateTransaction>(std::in_place, *this);
}
} // namespace lab5::memory
