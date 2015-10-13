#include <iostream>
#include <cstdlib>
#include <cmath>
class Simbolo{
	std::string simb;
	int coluna;
	public:
		Simbolo(std::string simb,int col);
		Simbolo(std::string simb);
		Simbolo(void);
		bool isOperand(void) const;
		bool isOperator(void) const;
		int prec() const;
		int getInt() const;		//If osOperand true

		std::string getSimb() const;
		void setSimb(std::string str);
		void setCol(int col);

		bool isOpenPar() const;
		bool isClosePar() const;

		int aplic(int a,int b) const;

		template <typename T> Simbolo operator+(T s);
		template <typename T> Simbolo operator+=(T s);
		Simbolo operator=(std::string s);
		bool operator==(std::string s);
		bool operator!=(std::string s);

		inline friend
		std::ostream &operator <<(std::ostream &_os,const Simbolo &_oSim){
			_os<<_oSim.simb;
			return _os;
		}
};
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
Simbolo::Simbolo(std::string simb){
	this->simb=simb;
	this->coluna=0;
}
Simbolo::Simbolo(void){
	this->simb="";
	this->coluna=0;
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
int Simbolo::getInt() const{
	if(isOperand())
		return atoi(this->simb.c_str());
	int soma=0;
	for(unsigned int i=0;i<this->simb.length();i++)
		soma+=simb[i];
	return soma;
}
void Simbolo::setSimb(std::string str){
	this->simb=str;
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
int Simbolo::aplic(int a,int b) const{
	if(isOperator()){
		switch(this->simb[0]){
			case '+': return a+b;
			case '-': return a-b;
			case '*': return a*b;
			case '/':
                if(b==0){
                    std::cout<<"Divisão por zero: Houve uma divisão cujo quociente é zero. Coluna: "<<this->coluna+1<<")"<<std::endl;
                    exit(1);
                }return a/b;
			return a/b;
			case '%': return a%b;
			case '^': return (int)pow(a,b);
		}
	}
	return 0;
}
