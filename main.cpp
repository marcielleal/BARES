#include <iostream>
#include "biblioteca.hpp"

int main(void){
    Fila<std::string> fila, erros;
    std::string str="\n";
    if(tokeniza(str,fila,erros))
        std::cout<<"TOKENIZA IS TRUE! FILA HAS SIZE="<<fila.size()<<std::endl;
    else std::cout<<"TOKENIZA IS FALSE! FILA HAS SIZE="<<fila.size()<<std::endl;
    if(!fila.empty()){
        std::cout<<"FILA HAS: [";
        while(!fila.empty()){
            std::cout<<fila.front()<<",";
            fila.pop();
        }std::cout<<"]"<<std::endl;
    }
    else std::cout<<"FILA IS EMPTY"<<std::endl;

    if(!erros.empty())
        while(!erros.empty()){
            std::cout<<erros.front()<<std::endl;
            erros.pop();
        }
    else std::cout<<"ERROS VAZIA"<<std::endl;

    return 0;
}
