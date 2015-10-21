/**
 * @file Fila.cpp
 * @brief Implementação dos métodos da classe Pilha
 *
 * @author Edye Lautter Cunha de Oliveira
 * @date Sat Oct 10 23:03:50 BRT 2015
 *
 */
#include <iostream>
#include "../include/header.hpp"

template<typename F>
Fila<F>::Fila(int _MaxSz){
	this->pt_fila=new F[_MaxSz];
	if(this->pt_fila){
		this->capacidade=_MaxSz;
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
	if(this->tamanho==this->capacidade) return true;
	else return false;
}

template <typename F>
bool Fila<F>::empty() const
{
	if(this->tamanho==0)
        return true;
	else return false;
}

template <typename F>
bool Fila<F>::push(F _data)
{
	if(pt_fila==NULL) return false;
	if(this->full())
        if(!this->_duplica())
            return false;

	if(this->inicio==-1) this->inicio=0;
	this->fim = (fim+1)%this->capacidade;
	this->pt_fila[fim] = _data;
	this->tamanho++;
	return true;
}

template <typename F>
bool Fila<F>::pop()		//remove
{
	if(pt_fila == NULL || this->empty())
		return false;
    if(this->inicio==this->fim){
        this->inicio=-1;
        this->fim=-1;
    }else
        this->inicio = (this->inicio+1)%this->capacidade;
	this->tamanho--;
	return true;
}

template <typename F>
F Fila<F>::front() const
{
	return this->pt_fila[this->inicio];
}

template <typename F>
F Fila<F>::back() const
{
	return this->pt_fila[this->fim];
}
template<typename F>
bool Fila<F>::_duplica(){
	F *aux=this->pt_fila;
	F *novo=new F[this->capacidade*2];
	if(!novo) return false;
	for(int i=this->inicio,j=0;j<this->capacidade;i=(i+1)%this->capacidade,j++)
        novo[j]=aux[i];
	this->pt_fila=novo;
	delete [] aux;
	this->inicio=0;
    this->fim=this->tamanho-1;
	this->capacidade*=2;
	return true;
}
