# minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# project name
PROJECT(Socks-Proxy-Server)

# set sourcecs
FilE(GLOB SOURCES "src/*.cpp")

# include headers
include_directories(include)
# include_directories(spdlog/include)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME spdlog
    GITHUB_REPOSITORY gabime/spdlog
    VERSION 1.7.0)

# include boost libraries
find_package(Boost 1.65.1 COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# add executable
ADD_EXECUTABLE (main ${SOURCES})
TARGET_LINK_LIBRARIES(main LINK_PUBLIC ${Boost_LIBRARIES})