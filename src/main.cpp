#include <iostream>
#include <fstream>
#include <string>

#include "header.hpp"
#include "expressao.cpp"
#include "simbolo.cpp"
#include "erro.cpp"
#include "Pilha.cpp"
#include "Fila.cpp"


int main (int argc, char *argv[]){
    Expressao e("12+\n");
    Fila<Simbolo> fila;
    Fila<Erro> erros;
    std::string line;
    e.tokeniza(fila,erros);


    std::cin>>line;
    e.setExp(line);
    e.tokeniza(fila,erros);
    if(erros.empty()){
        std::cout<<e.avalPosFixa(e.inf2PosFix(fila))<<std::endl;
    }
    else{
        while(!erros.empty()){
            std::cout<<erros.front()<<"\n";
            erros.pop();
        }
    }

    return 0;
}
