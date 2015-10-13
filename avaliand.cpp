#include <iostream>
#include <cstdlib>
#ifndef DEFINITIVO
#include <stack>
#include <queue>
#define Pilha std::stack
#define Fila std::queue
#endif
class Simbolo{
	std::string simb;
	public:
		Simbolo(std::string simb);
		Simbolo(){/*Empty*/};
		bool isOperand(void) const;
		bool isOperator(void) const;
		int prec() const;
		int getValue() const;		//If osOperand true
		
		void setSimb(std::string str);
		
		int aplic(int a,int b) const;
		inline friend
		std::ostream &operator <<(std::ostream &_os,const Simbolo &_oSim){
			_os<<_oSim.simb;
			return _os;
		}
};

Simbolo::Simbolo(std::string simb){
	this->simb=simb;
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
	if(this->simb=="+"||this->simb=="-"||this->simb=="*"||this->simb=="/"||this->simb=="%")
		return true;
	return false;
}
int Simbolo::prec() const{
	if(simb.length()==1){
		switch(simb[0]){
			case '(': return 1;
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
int Simbolo::getValue() const{
	if(isOperand())
		return atoi(this->simb.c_str());
	return 0;
}
void Simbolo::setSimb(std::string str){
	this->simb=str;
}
int Simbolo::aplic(int a,int b) const{
	if(isOperator()){
		switch(simb[0]){
			case '+': return a+b;
			case '-': return a-b;
			case '*': return a*b;
			case '/': return a/b;
			case '%': return a%b;
		}
	}
	return 0;
}
template <typename T>
Fila<T> inf2PosFix(Fila<T> &fila){
	T simb;
	Fila<T> filaAux;
	Pilha<T> pilhaAux;
	while(!fila.empty()){
		simb=fila.front();
		fila.pop();
		if(simb.isOperand())
			filaAux.push(simb);
		else{
			while(!pilhaAux.empty()){
				if(pilhaAux.top().prec()>=simb.prec()){
					fila.push(pilhaAux.top());
					pilhaAux.pop();
				}
				else break;
			}
			pilhaAux.push(simb);
		}
	}while(!pilhaAux.empty()){
		fila.push(pilhaAux.top());
		pilhaAux.pop();
	}
	return filaAux;

}

template <typename T>
int avalPosFixa(Fila<T> simbolos){
	T simb;
	Pilha<int> pilhaOpnd;
	
	int opnd1,opnd2;
	int resultado;
	
	while(!simbolos.empty()){
		simb=simbolos.front();
		simbolos.pop();
		if(simb.isOperand()){
			pilhaOpnd.push(simb.getValue());
		}
		else{
			opnd2=pilhaOpnd.top();
			pilhaOpnd.pop();
			opnd1=pilhaOpnd.top();
			pilhaOpnd.pop();
			
			resultado=simb.aplic(opnd1,opnd2);
			pilhaOpnd.push(resultado);
			std::cout<<opnd1<<simb<<opnd2<<"="<<resultado<<std::endl;
		}
	}if(!pilhaOpnd.empty()){
		resultado=pilhaOpnd.top();
		pilhaOpnd.pop();
	}
	return resultado;
}
int main(void){
	Fila<Simbolo> fila;
	Simbolo s("21");
	fila.push(s);
	s.setSimb("+");
	fila.push(s);
//	s.setSimb("-9");
	//fila.push(s);
	//s.setSimb("+");
	//fila.push(s);
	s.setSimb("7");
	fila.push(s);
	//s.setSimb("15");
	//fila.push(s);
	s.setSimb("*");
	fila.push(s);
	s.setSimb("1");
	fila.push(s);
	
	inf2PosFix(fila);
	//	std::cout<<avalPosFixa()<<std::endl;
	if(!fila.empty()){
        std::cout<<"FILA HAS: [";
        while(!fila.empty()){
            std::cout<<fila.front()<<",";
            fila.pop();
        }std::cout<<"]"<<std::endl;
    }
    else std::cout<<"FILA IS EMPTY"<<std::endl;
    
    
	return 0;
}
