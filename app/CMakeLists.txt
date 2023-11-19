set(APP_SOURCES
    "main.cc")

add_executable(${APP_NAME} ${APP_SOURCES})
target_link_libraries(${APP_NAME} PUBLIC
    ${FILE_MANAGER_LIB_NAME})