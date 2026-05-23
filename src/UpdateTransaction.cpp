#include "UpdateTransaction.hpp"
#include "Document.hpp"
#include "IndexStore.hpp"

namespace lab5::memory
{

UpdateTransaction::UpdateTransaction(IndexStore& store) : store_(store), is_committed_(false)
{
    backup_state_ = store_.get_snapshot();
}
UpdateTransaction::~UpdateTransaction()
{
    if (!is_committed_)
    {
        store_.restore_snapshot(backup_state_);
    }
}

Result<void> UpdateTransaction::add_document(size_t id, const std::string& content)
{
    return store_.AddDocument(Document{id, "DefaultName", content});
}

Result<void> UpdateTransaction::remove_document(size_t id)
{
    return store_.RemoveDocument(id);
}

Result<void> UpdateTransaction::commit()
{
    is_committed_ = true;
    return {};
}

} // namespace lab5::memory
