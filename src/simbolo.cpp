#include <iostream>
#include <cstdlib>
#include <cmath>
#include "header.hpp"

void Simbolo::operator=(std::string s){
    this->isUnrMinus=false;
    this->simb=s;
    return;
}
bool Simbolo::operator!=(std::string s){
    this->isUnrMinus=false;
    return (this->simb!=s);
}
bool Simbolo::operator==(std::string s){
    return (this->simb==s);
}
template <typename T>
Simbolo::Simbolo(T sim,int col){
	this->isUnrMinus=false;
	this->simb="";
	this->simb+=sim;
	this->coluna=col;
}
Simbolo::Simbolo(){
	this->isUnrMinus=false;
	this->simb="";
	this->coluna=0;
}

bool Simbolo::isOperand(void) const{
	for(unsigned int i=0;i<this->simb.length();i++)
		if(!this->isDigit(i))
            return false;
    int v=atoi(this->simb.c_str());
    if(v>32767||v<-32767)
        return false;
    return true;
}

bool Simbolo::isDigit(unsigned int i) const{
    switch(this->simb[i]){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}
bool Simbolo::isOperator(void) const{
	if(this->simb=="+"||this->simb=="-"||this->simb=="*"||this->simb=="/"||this->simb=="%"||this->simb=="^")
		return true;
	return false;
}
void Simbolo::setCol(int col){
    this->coluna=col;
}
template <typename T>
void Simbolo::setSimb(T str){
    this->simb="";
    this->simb+=str;
    return;
}
int Simbolo::prec() const{
    if(this->isUnrMinus)
        return 1;
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
	if(this->isOperand())
		return atoi(this->simb.c_str());
	return 0;
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

