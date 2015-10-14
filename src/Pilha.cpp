#include <iostream>
#include "header.hpp"

template<typename P>
Pilha<P>::Pilha(int _MaxSz){
	this->pt_Pilha=new P[_MaxSz];
	if(this->pt_Pilha){
		this->capacidade=_MaxSz;
		this->tamanho=0;
	}
}
template<typename P>
Pilha<P>::~Pilha(){
	delete [] this->pt_Pilha;
}
template<typename P>
bool Pilha<P>::_duplica(){				//Duplicar o vetor caso tenha enchido
	P *aux=this->pt_Pilha;
	P *novo=new P[this->capacidade*2];
	if(!novo) return false;
	for(int i=0;i<this->capacidade;i++)
        novo[i]=aux[i];
	this->pt_Pilha=novo;
	delete [] aux;
	return true;
}
template<typename P>
int Pilha<P>::size() const
{
	if(this->pt_Pilha==NULL) return false;

	return this->tamanho;
}
template<typename P>
bool Pilha<P>::Full() const
{
	if(pt_Pilha==NULL) return true;
	return (this->tamanho==this->_MaxSz);
}
template <typename P>
bool Pilha<P>::empty() const
{
	return this->tamanho==0;
}
template <typename P>
bool Pilha<P>::push(P _data)  // insere
{
	if(pt_Pilha==NULL) return false;
	this->pt_Pilha[this->tamanho] = _data;
	tamanho++;
	return true;
}
template <typename P>
bool Pilha<P>::pop() //remove
{
	if(pt_Pilha == NULL || this->empty())
		return false;
	this->tamanho--;
	return true;
}
template <typename P>
P Pilha<P>::top()
{
	return this->pt_Pilha[tamanho-1];
}
