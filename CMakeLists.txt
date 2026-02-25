cmake_minimum_required(VERSION 3.15)
project(URLShortener VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Source files
set(SOURCES
    src/main.cpp
    src/server.cpp
    src/url_shortener.cpp
    src/storage.cpp
    src/utils.cpp
)

# Header files
set(HEADERS
    include/server.h
    include/url_shortener.h
    include/storage.h
    include/utils.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ============================================================================
# TODO (Stretch Goal): Add a third-party HTTP library
# ============================================================================
# Once you've built the core logic, consider integrating a real HTTP library:
#   - cpp-httplib (header-only, great for learning)
#   - Boost.Beast (powerful, production-grade)
#   - Crow (Flask-like, easy to use)
#
# Example with FetchContent (CMake 3.11+):
#   include(FetchContent)
#   FetchContent_Declare(httplib
#       GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
#       GIT_TAG v0.15.0
#   )
#   FetchContent_MakeAvailable(httplib)
#   target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)
# ============================================================================
