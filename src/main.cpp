/**
 * @mainpage BARES
 *
 * @section sec_header BARES
 * Universidade Federal do Rio Grande do Norte \n
 * Instituto Metrópole Digital \n
 * Bacharelado em Tecnologia da Informação \n
 * Estruturas de Dados Básicas I \n
 * Projeto BARES - Calculadora aritmética simples \n
 *
 * @section sec_descripion Descrição:
 * Realiza a análise de expressões aritméticas contidas em um arquivo de texto, tal que, cada expressão está em uma linha diferente.
 * Se forem expressões válidas, o programa calcula seus valores e envia para um arquivo de saída ou para a saída padrão.
 * Se não forem expressões válidas, envia uma lista de erros para um arquivo de saída ou para a saída padrão(cada erro está em uma linha diferente).
 *
 * Nota: expressões válidas para o projeto, são todas as que não envolvam nada além de números inteiros (entre -32767 e 32767),
 * operadores binários ('+', '-', '*', '/', '%', '^'), menos unário('-') e parênteses e que estejam sintaticamente corretas.
 *
 * @section sec_install Compilação
 *
 * Dentro da pasta BARES:
 * make clean
 * make
 *
 * @author Marciel Manoel Leal e Edye Lautter Cunha de Oliveira
 * @date Tue Oct 20 21:24:50 BRT 2015
 */
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "../include/header.hpp"
#include "expressao.cpp"

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
