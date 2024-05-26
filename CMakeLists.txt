cmake_minimum_required(VERSION 3.28)
project(FliwaBot)

file(GLOB_RECURSE FLIWABOT_HEADERS "src/*.h")
file(GLOB_RECURSE FLIWABOT_SOURCES "src/*.cpp")

add_executable(FliwaBot ${FLIWABOT_HEADERS} ${FLIWABOT_SOURCES})
configure_file(".env" ".env" COPYONLY)
configure_file("bot_config.yml" "bot_config.yml" COPYONLY)
configure_file("bot_language.yml" "bot_language.yml" COPYONLY)

target_compile_features(FliwaBot PUBLIC cxx_std_23)

add_subdirectory("libs/FliwaCord")
add_subdirectory("libs/yaml-cpp")

target_link_libraries(FliwaBot PRIVATE FliwaCord)
target_link_libraries(FliwaBot PRIVATE yaml-cpp)