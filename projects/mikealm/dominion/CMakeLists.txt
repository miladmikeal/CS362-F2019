cmake_minimum_required(VERSION 3.14)
project(dominion)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dominion
        dominion.c
        dominion.h
        dominion_helpers.h
        interface.c
        interface.h
        playdom.c
        player.c
        READM.md
        rngs.c
        rngs.h
        rt.c
        testdrawcard.c)
