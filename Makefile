all: compile link

compile:
	g++ -I src/include -c main.cpp
	g++ -I src/include -c game.cpp
	g++ -I src/include -c starship.cpp
	g++ -I src/include -c enemy.cpp
	g++ -I src/include -c screens.cpp
	g++ -I src/include -c tutorial.cpp
	g++ -I src/include -c audio.cpp


link:
	g++ main.o game.o enemy.o starship.o screens.o tutorial.o audio.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio