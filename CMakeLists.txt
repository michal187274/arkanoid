cmake_minimum_required(VERSION 3.13)
project(arkanoid)

option(ARKANOID_USE_SANITIZERS "add sanitizers" ON)

add_executable(arkanoid)
target_sources(arkanoid PRIVATE
	BallObject.cpp
	BallObject.h
	BoxObject.cpp
	BoxObject.h
	GameState.cpp
	GameState.h
	main.cpp
	Menu.h
	Menu.cpp
)

target_link_libraries(arkanoid PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_options(arkanoid PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(arkanoid PRIVATE cxx_std_17)

if (ARKANOID_USE_SANITIZERS)
	target_compile_options(arkanoid PRIVATE -fsanitize=address -fsanitize=undefined)
	target_link_libraries (arkanoid PRIVATE -fsanitize=address -fsanitize=undefined)
endif()
