all: run

run: main.cpp lapiz.cpp
	g++ -std=c++11 -o run main.cpp lapiz.cpp 

clean: 
	rm run
