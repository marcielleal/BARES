#include <iostream>
#include "header.hpp"
/**
 *  @brief O objetio é definir o tipo de dados da classe lista
 *  e a implementação de suas funções. 
 */
 
 /**
  * @brief Constructor da fila. 
  * A função construtora recebe o argumento _MaxSz a fim de definir o tamanho máximo da fila.
  * Depois testa se a fila foi criada e inicializa seus elementos.
  * @param _MaxSz tamanho maximo da fila
  * @param pt_fila ponteiro para a fila
  * @param tamanho tamanho da fila, é incrementado ou decrementado de acordo com as ações.
  * @param inicio o primeiro elemento da fila
  * @param fim o último elemento da fila.
  */
template<typename F>
Fila<F>::Fila(int _MaxSz){
	this->pt_fila=new F[_MaxSz];
	if(this->pt_fila){
		this->_MaxSz=_MaxSz;
		this->tamanho=0;
		this->inicio=-1;
		this->fim=-1;
	}
}
 /**
  * @brief Destructor da fila. 
  * 
  * Destrói a fila.
  */
template<typename F>
Fila<F>::~Fila(){
	delete [] this->pt_fila;
}
 /**
  * A função size retorna o tamanho da fila.
  */
template <typename F>
int Fila<F>::size() const
{
	if(pt_fila==NULL) return false;

	return this->tamanho;
}
 /**
  * A função full retorna verdadeiro se a fila estiver cheia e falso caso não.
  */
template <typename F>
bool Fila<F>::full() const
{
	if(pt_fila==NULL) return true;
	if(this->tamanho==this->_MaxSz) return true;
	else return false;
}
 /**
  * Empty retorna true se fila estiver vazia.
  */
template <typename F>
bool Fila<F>::empty() const
{
	if(this->tamanho==0) return true;
	else return false;
}
 /**
  * @brief Push tem por objetivo inserir um elemento na fila.
  * 
  * "push" recebe um argumento _data e, caso a fila seja válida e não estiver cheia, testa se está vazia
  * para então inserir o elemento e incrementar o tamanho da fila.
  */
template <typename F>
bool Fila<F>::push(F _data) 
{
	if(pt_fila==NULL) return false;
	if(full()) return false;
	if(this->inicio==-1) this->inicio=0;
	this->fim = (fim+1)%this->_MaxSz;
	this->pt_fila[fim] = _data;
	this->tamanho++;
	return true;
}
 /**
  * @brief "pop" tem por objetivo remover um elemento da fila.
  * 
  * Primeiro a função avalia se a fila foi criada/é válida para então remover o primeiro elemento da fila e
  * decrementar o tamanho. Retorna true caso dê certo.
  */
template <typename F>
bool Fila<F>::pop()		//remove
{
	if(pt_fila == NULL || this->empty())
		return false;
	this->inicio = (this->inicio+1)%this->_MaxSz;
	this->tamanho--;
	return true;
}
 /**
  * front retorna o primeiro elemento da fila.
  * 
  */
template <typename F>
F Fila<F>::front() const
{
	return this->pt_fila[inicio];
}
 /**
  * back retorna o último elemento da fila. 
  * 
  */
template <typename F>
F Fila<F>::back() const
{
	return this->pt_fila[this->fim];
}
