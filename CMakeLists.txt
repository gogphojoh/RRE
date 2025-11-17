cmake_minimum_required(VERSION 3.16)
project(RRE C)

set(CMAKE_C_STANDARD 11)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/src")

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
add_executable(RRE src/mainloop/main.c
        src/mainloop/main.h
        src/mainloop/game.h
        src/mainloop/game.c
        src/mainloop/init_sdl.c
        src/mainloop/init_sdl.h
        src/mainloop/load_media.c
        src/mainloop/load_media.h
        src/text/text.c
        src/text/text.h
        src/text/bubble.c
        src/text/bubble.h
        src/game/player.c
        src/game/player.h
        src/game/music.c
        src/game/music.h
        src/game/bullet.c
        src/game/bullet.h
        src/game/enemy.c
        src/game/enemy.h
        src/game/power.h
        src/game/power.c
)

# Link SDL
target_link_libraries(RRE PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer m)