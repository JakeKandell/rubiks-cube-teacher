all: teacher

teacher: teacher.cpp teacher.h colors.o algorithms.o
	 g++ -g -Wall teacher.cpp colors.o algorithms.o -o teacher `pkg-config --cflags --libs opencv`

threshold: threshold.cpp
	g++ -g -Wall threshold.cpp -o threshold `pkg-config --cflags --libs opencv`

colors.o: colors.h colors.cpp
	g++ -g -Wall -c colors.cpp -o colors.o

algorithms.o: algorithms.h algorithms.cpp
	g++ -g -Wall -c algorithms.cpp -o algorithms.o

clean:
	rm *.o
