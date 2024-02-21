aux_source_directory(./ TRIE_SRCS)
aux_source_directory(./rlp TRIE_RLP_SRCS)

add_library(${ABC_ETH_TRIE_LIBRARY} ${TRIE_SRCS} ${TRIE_RLP_SRCS})
add_dependencies(${ABC_ETH_TRIE_LIBRARY} ${ABC_ETH_TYPES_LIBRARY} ${ABC_ETH_RLP_LIBRARY} abc)
target_link_libraries(${ABC_ETH_TRIE_LIBRARY} PRIVATE ${ABC_ETH_TYPES_LIBRARY} ${ABC_ETH_RLP_LIBRARY} abc)
