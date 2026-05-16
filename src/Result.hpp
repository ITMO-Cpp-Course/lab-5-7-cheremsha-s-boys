#pragma once
#include "expected"
namespace lab5::memory
{
enum class IndexError
{
    Document_Not_Found,
    Duplicate_Document,
    Invalid_Input
};
template <typename T> using Result = std::expected<T, IndexError>;
} // namespace lab5::memory