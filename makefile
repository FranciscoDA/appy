
CC=g++
CFLAGS=$(shell pkg-config --cflags --libs gtkmm-3.0) -std=c++14

appy: *.cpp
	$(CC) -o appy *.cpp $(CFLAGS)

