all:bares
bares:main.o simbolo.o expressao.o erro.o fila.o pilha.o
	g++ main.o simbolo.o expressao.o erro.o fila.o pilha.o -o bares -std=c++11
main.o: main.cpp header.hpp
	g++ -c main.cpp header.hpp -std=c++11
simbolo.o: simbolo.cpp
	g++ -o simbolo.o -c simbolo.cpp -std=c++11
expressao.o: expressao.cpp
	g++ -c expressao.cpp Fila.cpp Pilha.cpp -std=c++11
erro.o: erro.cpp
	g++ -o erro.o -c erro.cpp -std=c++11
fila.o: Fila.cpp
	g++ -o fila.o -c Fila.cpp -std=c++11
pilha.o: Pilha.cpp
	g++ -o pilha.o -c Pilha.cpp -std=c++11

clean:
	rm -rf *.o
mrproper: clean
	rm -rf bares
