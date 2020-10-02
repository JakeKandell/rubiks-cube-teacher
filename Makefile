all: teacher

teacher: teacher.cpp
	 g++ -g -Wall teacher.cpp -o teacher `pkg-config --cflags --libs opencv`
