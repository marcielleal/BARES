all:bares
bares:
	g++ -Wall -std=c++11 -o ./bin/bares ./src/main.cpp

clean:
	rm -f ./bin/bares 
