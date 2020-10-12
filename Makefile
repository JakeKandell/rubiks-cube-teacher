all: teacher

teacher: teacher.cpp colors.o
	 g++ -g -Wall teacher.cpp colors.o -o teacher `pkg-config --cflags --libs opencv`

colors.o: colors.h colors.cpp
	g++ -g -Wall -c colors.cpp -o colors.o
