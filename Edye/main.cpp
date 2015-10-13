#include <iostream>
#include "Pilha.cpp"
#include "Fila.cpp"
#include "header.hpp"
#include "infx2psfx.cpp"


int main(void){
    Fila<std::string> *b=new Fila<std::string>;

    b->push("2");
    b->push("^");
    b->push("3");
    b->push("*");
    b->push("4");
    b->push("-");
    b->push("5");
    b->push("+");
    b->push("6");
    b->push("/");
    b->push("7");
    b->push("/");
    b->push("(");
    b->push("8");
    b->push("+");
    b->push("9");
    b->push(")");



    std::cout << *b << '\n' << std::endl;

    std::cout << infx2Psfx(*b) << std::endl;

	return 0;
}
