#include <iostream>
#include "header.hpp"

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
template<typename F>
Fila<F>::~Fila(){
	delete [] this->pt_fila;
}

template <typename F>
int Fila<F>::size() const
{
	if(pt_fila==NULL) return false;

	return this->tamanho;
}

template <typename F>
bool Fila<F>::full() const
{
	if(pt_fila==NULL) return true;
	if(this->tamanho==this->_MaxSz) return true;
	else return false;
}

template <typename F>
bool Fila<F>::empty() const
{
	if(this->tamanho==0) return true;
	else return false;
}

template <typename F>
bool Fila<F>::push(F _data) // insere
{
	if(pt_fila==NULL) return false;
	if(full()) return false;
	if(this->inicio==-1) this->inicio=0;
	this->fim = (fim+1)%this->_MaxSz;
	this->pt_fila[fim] = _data;
	this->tamanho++;
	return true;
}

template <typename F>
bool Fila<F>::pop()		//remove
{
	if(pt_fila == NULL || this->empty())
		return false;
	this->inicio = (this->inicio+1)%this->_MaxSz;
	this->tamanho--;
	return true;
}

template <typename F>
F Fila<F>::front() const
{
	return this->pt_fila[inicio];
}

template <typename F>
F Fila<F>::back() const
{
	return this->pt_fila[this->fim];
}
