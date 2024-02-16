aux_source_directory(./ RLP_SRCS)
aux_source_directory(./zone RLP_ZONE_SRCS)

add_library(${ABC_ETH_RLP_LIBRARY} ${RLP_SRCS} ${RLP_ZONE_SRCS})
add_dependencies(${ABC_ETH_RLP_LIBRARY} abc)
target_link_libraries(${ABC_ETH_RLP_LIBRARY} PRIVATE abc)
