cmake_minimum_required(VERSION 3.25)
project(FliwaBot)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE FLIWABOT_HEADERS "src/*.h")
file(GLOB_RECURSE FLIWABOT_SOURCES "src/*.cpp" "src/*.c")

add_executable(FliwaBot ${FLIWABOT_HEADERS} ${FLIWABOT_SOURCES})
configure_file(".env" ".env" COPYONLY)

target_compile_options(FliwaBot PRIVATE -Wall -Wextra -Wpedantic)

target_compile_features(FliwaBot PRIVATE cxx_std_23)

add_subdirectory("libs/FliwaCord")

target_link_libraries(FliwaBot PRIVATE FliwaCord)