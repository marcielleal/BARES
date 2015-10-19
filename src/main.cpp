#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "header.hpp"
//#include "simbolo.cpp"
#include "expressao_try.cpp"
//#include "erro.cpp"


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
    Fila<Simbolo> fila;

    while(!inputFile.fail()){
		inputFile.getline(buff, 500);

		e.clear();
		e.setExp(buff);

		std::cout<<e.getExp()<<std::endl;
        if(e.tokeniza(fila)){
            e.inf2PosFix();
            int i=e.avalPosFixa();
            if(e.erros->empty()){
                std::cout<<i<<std::endl;
            }else e.print();
        }else e.print();

        std::cout<<"--------------\n";
    }
    std::cout<<"CARALEO\n";

	inputFile.close();

	if(argc>2)
		outputFile.close();

    return 0;
}
