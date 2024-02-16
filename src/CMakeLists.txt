set(ABC_ETH_CRYPTO_LIBRARY "abc.ethereum.crypto")
set(ABC_ETH_RLP_LIBRARY "abc.ethereum.rlp")
set(ABC_ETH_TRIE_LIBRARY "abc.ethereum.trie")
set(ABC_ETH_TYPES_LIBRARY "abc.ethereum.types")

add_subdirectory(crypto)
add_subdirectory(rlp)
add_subdirectory(trie)
add_subdirectory(types)

aux_source_directory(./ ETH_SRCS)

add_library(${ABC_ETH_LIBRARY} ${ETH_SRCS})
add_dependencies(${ABC_ETH_LIBRARY} ${ABC_ETH_TYPES_LIBRARY} ${ABC_ETH_CRYPTO_LIBRARY} ${ABC_ETH_RLP_LIBRARY} ${ABC_ETH_TRIE_LIBRARY} abc)

target_link_libraries(${ABC_ETH_LIBRARY} PRIVATE ${ABC_ETH_TRIE_LIBRARY} ${ABC_ETH_TYPES_LIBRARY} ${ABC_ETH_CRYPTO_LIBRARY} ${ABC_ETH_RLP_LIBRARY} abc fmt::fmt-header-only cryptopp-static)