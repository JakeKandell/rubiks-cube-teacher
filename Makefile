all: teacher

teacher: teacher.cpp colors.o algorithms.o
	 g++ -g -Wall teacher.cpp colors.o algorithms.o -o teacher `pkg-config --cflags --libs opencv`

colors.o: colors.h colors.cpp
	g++ -g -Wall -c colors.cpp -o colors.o

algorithms.o: algorithms.h algorithms.cpp
	g++ -g -Wall -c algorithms.cpp -o algorithms.o
