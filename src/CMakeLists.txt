project(Main)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

add_executable(Main main.cpp)

target_link_libraries(Main PUBLIC random_word)

target_include_directories(Main PUBLIC
                          "${CMAKE_BINARY_DIR}"
                          "${CMAKE_SOURCE_DIR}/include"
                          )

