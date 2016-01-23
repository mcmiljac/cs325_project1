all: project1

project1: project1.cpp
	g++ -std=c++0x project1.cpp -o project1

clean:
	rm *.o project1
