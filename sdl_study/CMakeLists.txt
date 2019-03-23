cmake_minimum_required(VERSION 2.8)

project(play_sound)

aux_source_directory(. DIR_SRCS)

add_executable(${PROJECT_NAME} ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME} SDL2)


