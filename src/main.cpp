#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "simbolo.cpp"
#include "expressao.cpp"
#include "erro.cpp"
#include "header.hpp"
#include "Pilha.cpp"
#include "Fila.cpp"


int main (int argc, char *argv[]){
    std::ostream* pOut;
    std::ifstream inputFile;
    std::ofstream outputFile;
    char buff[500];
    std::string b;

    if(argc<2){
        std::cout<<"Argumentos insuficientes!"<<std::endl;
        std::cout<<"É preciso a inserção de mais argumentos!"<<std::endl;
        std::cout<<"A forma geral de chamada do programa é:"<<std::endl;
        std::cout<<"./bares arquivo_entrada [arquivo_saida]"<<std::endl;
        return 1;
    }else if(argc==2)
        pOut=&std::cout;
	else{
		outputFile.open(argv[2],std::ifstream::out);
		if(!outputFile.is_open()) {
			std::cout<<"Erro ao abrir o arquivo "<<argv[2]<<std::endl;
			return 1;
		}
		pOut=&outputFile;		//Ponteiro de saida
	}

	inputFile.open(argv[1],std::ifstream::in);
	if(!inputFile.is_open()) {
		std::cout<<argv[1]<<std::endl;
		std::cout<<"Erro ao abrir o arquivo "<<argv[1]<<std::endl;
		return 1;
	}
    Expressao e;
    while(!inputFile.fail()){
		inputFile.getline(buff, 500);
		e.setExp(buff);
		if(e.tokeniza()){
            e.inf2PosFix();
            //std::cout<<e.avalPosFixa()<<std::endl;
        }std::cout<<"--------------\n"<<e;

	}
	inputFile.close();

	if(argc>2)
		outputFile.close();

    return 0;
}
