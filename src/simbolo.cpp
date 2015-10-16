#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "header.hpp"

Simbolo Simbolo::operator=(std::string s){
    return this->simb=s;
}
bool Simbolo::operator!=(std::string s){
    return (this->simb!=s);
}
bool Simbolo::operator==(std::string s){
    return (this->simb==s);
}
template <typename T>
Simbolo Simbolo::operator+(T s){
    return this->simb+s;
}
template <typename T>
Simbolo Simbolo::operator+=(T s){
    return this->simb+=s;
}

Simbolo::Simbolo(std::string simb,int col){
	this->simb=simb;
	this->coluna=col;
}
bool Simbolo::isOperand(void) const{
	bool flag;
	for(unsigned int i=0;i<this->simb.length();i++)
		if(!isdigit(this->simb[i]))
            flag=false;
        else
            flag=true;

    return flag;
}
bool Simbolo::isOperator(void) const{
	if(this->simb=="+"||this->simb=="-"||this->simb=="*"||this->simb=="/"||this->simb=="%"||this->simb=="^")
		return true;
	return false;
}
void Simbolo::setCol(int col){
    this->coluna=col;
}
int Simbolo::prec() const{
	if(simb.length()==1){
		switch(simb[0]){
			case '(': return 5;
			case ')': return 5;
			case '^': return 2;
			case '*': return 3;
			case '/': return 3;
			case '%': return 3;
			case '-': return 4;
			case '+': return 4;
		}
	}
	return 5;
}
int Simbolo::getCol(void) const{
    return this->coluna;
}
int Simbolo::getInt() const{
	if(isOperand())
		return atoi(this->simb.c_str());
	int soma=0;
	for(unsigned int i=0;i<this->simb.length();i++)
		soma+=simb[i];
	return soma;
}
std::string Simbolo::getSimb() const{
	return this->simb;
}
bool Simbolo::isOpenPar() const{
	return (this->simb=="(");
}
bool Simbolo::isClosePar()const{
	return (this->simb==")");
}
bool Simbolo::aplic(int a,int b,int &res) const{
	res=0;
	if(this->isOperator()){
		switch(this->simb[0]){
			case '+': res=a+b; return true;
			case '-': res=a-b; return true;
			case '*': res=a*b; return true;
			case '^': res=(int)pow(a,b); return true;
            case '/': if(b==0) return false; res= a/b;return true;
            case '%': if(b==0) return false; res= a%b;return true;
		}
	}
	return false;
}

