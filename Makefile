all: compile link

compile:
	g++ -I src/include -c main.cpp
	g++ -I src/include -c game.cpp
	g++ -I src/include -c starship.cpp
	g++ -I src/include -c enemy.cpp
	g++ -I src/include -c screens.cpp
	g++ -I src/include -c tutorial.cpp


link:
	g++ main.o game.o enemy.o starship.o screens.o tutorial.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system