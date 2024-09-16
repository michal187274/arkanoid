sfml-app : main.o BoxObject.o GameState.o BallObject.o
	g++ main.o BoxObject.o GameState.o BallObject.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system


main.o  : main.cpp
	g++ -c main.cpp
	
BoxObject.o : BoxObject.cpp BoxObject.h
	g++ -c BoxObject.cpp

BallObject.o : BallObject.cpp BallObject.h
	g++ -c BallObject.cpp

GameState.o : GameState.cpp GameState.h
	g++ -c GameState.cpp