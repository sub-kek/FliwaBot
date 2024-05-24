cmake_minimum_required(VERSION 3.28)
project(FliwaBot)

set(CMAKE_CXX_STANDARD 26)

file(GLOB_RECURSE FLIWABOT_HEADERS "src/*.h")
file(GLOB_RECURSE FLIWABOT_SOURCES "src/*.cpp")

add_executable(FliwaBot ${FLIWABOT_HEADERS} ${FLIWABOT_SOURCES})
configure_file(".env" ".env" COPYONLY)

add_subdirectory("libs/FliwaCord")

target_link_libraries(FliwaBot PRIVATE FliwaCord)