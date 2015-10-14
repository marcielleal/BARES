#include <iostream>
#include "header.hpp"
/**
 *  @brief O objetivo é definir o tipo de dados da classe pilha
 *  e a implementação de suas funções. 
 */
 
 /**
  * @brief Constructor da pilha. 
  * A função construtora recebe o argumento _MaxSz a fim de definir o tamanho máximo da pilha.
  * Depois testa se a pilha foi criada e inicializa seus elementos.
  * @param _MaxSz tamanho maximo da pilha
  * @param pt_fila ponteiro para a pilha
  * @param tamanho tamanho da pilha, é incrementado ou decrementado de acordo com as ações.
  * @param capacidade capacidade máxima da pilha
  */

template<typename P>
Pilha<P>::Pilha(int _MaxSz){
	this->pt_Pilha=new P[_MaxSz];
	if(this->pt_Pilha){
		this->capacidade=_MaxSz;
		this->tamanho=0;
	}
}
 /**
  * @brief Destructor da pilha. 
  * 
  * Destrói a pilha.
  */
template<typename P>
Pilha<P>::~Pilha(){
	delete [] this->pt_Pilha;
}

/**
 * @brief _duplica() Duplica a pilha caso tenha alcançado a capacidade máxima
 * 
 * @param *aux ponteiro auxiliar que vai receber a pilha temporariamente
 * @param *novo ponteiro para um vetor do tipo pilha com o dobro da capacidade anterior
 * o laço for copia o vetor aux para o "novo" que em seguida em copiado para
 * @see pt_Pilha
 * @return true or false
 * 
 * */
template<typename P>
bool Pilha<P>::_duplica(){
	P *aux=this->pt_Pilha;
	P *novo=new P[this->capacidade*2];
	if(!novo) return false;
	for(int i=0;i<this->capacidade;i++)
        novo[i]=aux[i];
	this->pt_Pilha=novo;
	delete [] aux;
	return true;
}
/**
 * @brief size() retorna o tamanho atual da pilha
 * caso não seja inválida 
 **/
template<typename P>
int Pilha<P>::size() const
{
	if(this->pt_Pilha==NULL) return false;

	return this->tamanho;
}
/**
 * @brief Full() retorna true se o tamanho do vetor tiver alcançado o tamanho máximo
 * @see tamanho 
 * @see _MaxSz
 * */
template<typename P>
bool Pilha<P>::Full() const
{
	if(pt_Pilha==NULL) return true;
	return (this->tamanho==this->_MaxSz);
}
/**
 * @brief empty() retorna true se a pilha estiver vazia
 * @see tamanho
 * */
template <typename P>
bool Pilha<P>::empty() const
{
	return this->tamanho==0;
}
/**
 * @brief push(P _data) insere o elemento _data do tipo P na pilha
 * @param _data 
 * @see pt_Pilha
 * @see tamanho
 * @return true or false
 * 
 * */
template <typename P>
bool Pilha<P>::push(P _data)  // insere
{
	if(pt_Pilha==NULL) return false;
	this->pt_Pilha[this->tamanho] = _data;
	tamanho++;
	return true;
}

/**
 *@brief pop() remove o último elemento da pilha somente decrementando seu tamanho
 * 
 * @see pt_Pilha
 * @see empty()
 * @see tamanho
 **/
template <typename P>
bool Pilha<P>::pop() //remove
{
	if(pt_Pilha == NULL || this->empty())
		return false;
	this->tamanho--;
	return true;
}

/**
 * top() retorna o último elemento da pilha (tamanho-1)
 * @see pt_Pilha
 * @see tamanho
 * @return pt_Pilha[tamanho-1]
 * */
template <typename P>
P Pilha<P>::top()
{
	return this->pt_Pilha[tamanho-1];
}
