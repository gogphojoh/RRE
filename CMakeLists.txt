cmake_minimum_required(VERSION 3.16)
project(RRE C)

set(CMAKE_C_STANDARD 11)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# SDL source is inside vendored/SDL
#add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
#add_subdirectory(vendored/SDL3_image EXCLUDE_FROM_ALL)
#add_subdirectory(vendored/SDL3_ttf EXCLUDE_FROM_ALL)
#add_subdirectory(vendored/SDL3_mixer EXCLUDE_FROM_ALL)
find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

# Your executable
add_executable(RRE main.c
        main.h
        game.h
        game.c
        init_sdl.c
        init_sdl.h
        load_media.c
        load_media.h
        main.c
        text.c
        text.h
        main.c
        bubble.c
        bubble.h
        main.c
        player.c
        player.h
        main.c
        main.c
        main.c
        main.c
        music.c
        music.h
        bullet.c
        bullet.h
        enemy.c
        enemy.h
        power.h
        power.c
)

# Link SDL
target_link_libraries(RRE PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer m)