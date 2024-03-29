cmake_minimum_required(VERSION 3.28)

if (DEFINED PROJECT_NAME)
    set(IS_SUBPROJECT ON)
else ()
    set(IS_SUBPROJECT OFF)
endif ()

project(libnet
    VERSION 0.1
    LANGUAGES CXX
    DESCRIPTION "A network library of Skymarlin")


### Target ###
add_library(libnet INTERFACE)
target_compile_features(libnet INTERFACE cxx_std_20)
if (MSVC)
    target_compile_options(libnet INTERFACE /W4)
else ()
    target_compile_options(libnet INTERFACE -Wall -Wextra -Wpedantic)
endif ()

target_include_directories(libnet INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")


### Dependency ###
include(FetchContent)

# Boost
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.7z
    DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

# OpenSSL
find_package(OpenSSL REQUIRED)

# Flatbuffers
FetchContent_Declare(
    flatbuffers
    GIT_REPOSITORY https://github.com/google/flatbuffers.git
    GIT_TAG v23.5.26
)
FetchContent_MakeAvailable(flatbuffers)

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(spdlog)

#TODO: Chagne public to interface?
target_link_libraries(libnet
    INTERFACE
    Boost::asio
    spdlog
    flatbuffers
    OpenSSL::SSL
    OpenSSL::Crypto
)

### Test ###
if (NOT IS_SUBPROJECT)
    add_executable(tests
        # net
        skymarlin/net/Server.test.cpp
        skymarlin/net/Client.test.cpp

        # utility
        skymarlin/util/BitConverter.test.cpp
        skymarlin/util/Map.test.cpp
        skymarlin/util/MemoryPool.test.cpp
        skymarlin/util/Queue.test.cpp)
    target_compile_features(tests PRIVATE cxx_std_20)

    if (MSVC)
        target_compile_options(tests PRIVATE /W4)
    else ()
        target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
    endif ()

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.3
    )
    FetchContent_MakeAvailable(Catch2)

    target_link_libraries(tests PRIVATE libnet Catch2::Catch2WithMain)
endif ()