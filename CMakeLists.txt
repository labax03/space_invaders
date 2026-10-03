cmake_minimum_required(VERSION 3.11)
project(space_invaders)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

add_executable(space_invaders
    main.cpp
    game_system.cpp
    ship.cpp
    bullet.cpp
)

target_include_directories(space_invaders PRIVATE ${SFML_INCS})

target_link_libraries(space_invaders
    sfml-graphics
    sfml-window
    sfml-system
)
