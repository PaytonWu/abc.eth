aux_source_directory(./ SRCS)
aux_source_directory(./rlp RLP_SRCS)

add_library(${ABC_ETH_LIBRARY} ${SRCS} ${RLP_SRCS})

add_dependencies(${ABC_ETH_LIBRARY} abc)

target_link_libraries(${ABC_ETH_LIBRARY} PRIVATE abc fmt::fmt-header-only cryptopp-static)