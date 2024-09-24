project(arkanoid)
cmake_minimum_required(VERSION 3.1)

option(ARKANOID_USE_SANITIZERS "add sanitizers" ON)

add_executable(arkanoid
  BallObject.cpp
  BallObject.h
  BoxObject.cpp
  BoxObject.h
  GameState.cpp
  GameState.h
  main.cpp
)

target_link_libraries(arkanoid PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_options(arkanoid PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(arkanoid PRIVATE cxx_std_17)

if (ARKANOID_USE_SANITIZERS)
target_compile_options(arkanoid PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_libraries (arkanoid PRIVATE -fsanitize=address -fsanitize=undefined)
endif()
