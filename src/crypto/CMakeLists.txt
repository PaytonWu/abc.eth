aux_source_directory(./ CRYPTO_SRCS)

add_library(${ABC_ETH_CRYPTO_LIBRARY} ${CRYPTO_SRCS})
add_dependencies(${ABC_ETH_CRYPTO_LIBRARY} abc)
target_link_libraries(${ABC_ETH_CRYPTO_LIBRARY} PRIVATE abc)
