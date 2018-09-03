cmake_minimum_required(VERSION 3.11)
project(blackjack_simulation_C C)

set(CMAKE_C_STANDARD 11)

add_executable(blackjack_simulation_C deck.c card.c card.h blackjack.c deck.h blackjack.h simulation.c)