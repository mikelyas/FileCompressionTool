set(FILE_MANAGER_SOURCES
    "FileManager.cc")
set(FILE_MANAGER_HEADERS
    "FileManager.h")

add_library(${FILE_MANAGER_LIB_NAME} STATIC
    ${FILE_MANAGER_HEADERS}
    ${FILE_MANAGER_SOURCES})
target_include_directories(${FILE_MANAGER_LIB_NAME} PUBLIC "./")
target_link_libraries(${FILE_MANAGER_LIB_NAME} PUBLIC
    ${COMPRESSION_MANAGER_LIB_NAME}
    nlohmann_json::nlohmann_json)   