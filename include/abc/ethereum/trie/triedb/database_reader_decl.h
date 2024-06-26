// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_DATABASE_READER_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_DATABASE_READER_DECL

#pragma once

#include "database_reader_fwd_decl.h"

#include <abc/ethereum/trie/nibble_bytes_view_decl.h>

#include <abc/bytes.h>
#include <abc/expected.h>
#include <abc/fixed_hash.h>

namespace abc::ethereum::trie::triedb
{

// database_reader wraps the node method of a backing trie store.
class database_reader
{
public:
    database_reader() = default;
    database_reader(database_reader const &) = delete;
    database_reader(database_reader &&) = default;
    virtual ~database_reader() = default;

    auto
    operator=(database_reader const &) -> database_reader & = delete;

    auto
    operator=(database_reader &&) -> database_reader & = default;

    // Node retrieves the trie node blob with the provided trie identifier, node path and
    // the corresponding node hash. No error will be returned if the node is not found.
    //
    // When looking up nodes in the account trie, 'owner' is the zero hash. For contract
    // storage trie nodes, 'owner' is the hash of the account address that containing the
    // storage.
    [[nodiscard]] virtual auto
    node(h256_t const & owner, h256_t const & hash, nibble_bytes_view path) const -> expected<bytes_t, std::error_code> = 0;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_DATABASE_READER_DECL
