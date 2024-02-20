aux_source_directory(./ TYPES_SRCS)
aux_source_directory(./rlp TYPES_RLP_SRCS)
aux_source_directory(./rlp/eth1 TYPES_RLP_ETH1_SRCS)

add_library(${ABC_ETH_TYPES_LIBRARY} ${TYPES_SRCS} ${TYPES_RLP_SRCS} ${TYPES_RLP_ETH1_SRCS})
add_dependencies(${ABC_ETH_TYPES_LIBRARY} ${ABC_ETH_RLP_LIBRARY} abc)
target_link_libraries(${ABC_ETH_TYPES_LIBRARY} PRIVATE ${ABC_ETH_RLP_LIBRARY} abc)
