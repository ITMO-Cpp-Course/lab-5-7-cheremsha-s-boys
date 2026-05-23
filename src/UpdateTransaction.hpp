#pragma once
#include "IndexStore.hpp"
#include "InvertedIndex.hpp"
#include "Result.hpp"
#include <string>

namespace lab5::memory
{
class UpdateTransaction
{
  public:
    explicit UpdateTransaction(IndexStore& store);
    ~UpdateTransaction();

    UpdateTransaction(const UpdateTransaction&) = delete;
    UpdateTransaction& operator=(const UpdateTransaction&) = delete;
    UpdateTransaction(UpdateTransaction&&) = delete;
    UpdateTransaction& operator=(UpdateTransaction&&) = delete;

    Result<void> add_document(size_t id, const std::string& content);
    Result<void> remove_document(size_t id);
    Result<void> commit();

  private:
    IndexStore& store_;
    bool is_committed_;
    InvertedIndex backup_state_;
};
} // namespace lab5::memory