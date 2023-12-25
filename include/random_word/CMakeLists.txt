set(CURL_MIN_VERSION “7.28.0”)
include(FetchContent)

# ADD EXTERNAL LIBRARIES

# manage http -> curlcpp
FetchContent_Declare(
    curlcpp
  GIT_REPOSITORY https://github.com/JosephP91/curlcpp
  GIT_TAG        3.1
)

FetchContent_MakeAvailable(curlcpp)

# set json -> nlohmann_json
find_package(nlohmann_json REQUIRED)

# ADD LOCAL LIBRARY
add_library(random_word random_word.cpp)

# Link  external libraries
target_link_libraries(random_word curlcpp nlohmann_json::nlohmann_json)