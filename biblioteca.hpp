#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP
#include <iostream>

#ifndef Fila
#include <queue>
#define Fila std::queue
#endif // Fila

#ifndef Pilha
#include <stack>
#define Pilha std::stack
#endif // Pilha

template <typename T>
std::string to_string(T value);

std::string errorString(int i,int col);

int extSintFromStr(std::string &num,std::string str);

bool isValOpd(std::string str);

bool isParnt(char c);
bool isValOpt(char c);
bool isnValOpt(char c);
bool isIgnChar(char c);
bool isValChar(char c);
bool isNotMinus(char c);

int extSMinusFromStr(std::string &num,std::string str);

/** \brief Função que tokeniza uma expressão matemática
 *  Função recebe uma string correspondente a expressão matemática,
 * \param entrada é do tipo std::string e é a expressão matemática que será tokenizada
 * \param tokens é do tipo Fila<std::string>, se a função retornar true, tokens terá a sequência dos termos da expressão tokenizada, senão será vazia
 * \param erros é do tipo Fila<std::string>, se a função retornar false, erros terá a sequência dos erros sintáticos da expressão, senão será vazia
 * \see
 * \return true se a expressão for válida sintaticamente e false senão
 */

bool tokeniza(std::string entrada,Fila<std::string> &tokens,Fila<std::string> &erros);
