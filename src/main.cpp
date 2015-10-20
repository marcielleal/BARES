/**
 * @mainpage bares
 *
 * @section sec_intro Introdução
 *
 * Projeto solicitado pelo professor Sela Rodrigues dos Santos
 *
 * @section sec_install Compilação e Instalação
 *
 * Informações sobre compilação e instalação do programa, dependências,
 * links para o SVN, wiki, etc.
 *
 * @section sec_summary Resumo
 *
 * @author Marciel Manoel Leal e Edye Lautter Cunha de Oliveira
 * @date Tue Oct 20 14:03:50 BRT 2015
 */

#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "header.hpp"
//#include "simbolo.cpp"
#include "expressao.cpp"
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

		e.setExp(buff);

		*pOut<<e.getExp()<<std::endl;
        int i;
        if(e.exprValue(i)){
                *pOut<<i<<std::endl;
        }else e.printErros(pOut);
    }

	inputFile.close();

	if(argc>2)
		outputFile.close();

    return 0;
}
