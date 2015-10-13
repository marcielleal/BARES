#include <iostream>
#include <string>
#include "header.hpp"
#include <ctype.h>

using std::string;

inline
bool is_num(string str){
    unsigned int sizeOfString = str.length();
    bool flag;
    for(unsigned int i=0; i<sizeOfString; i++)
    {
      if(!isdigit(str[i]))
        {
            flag=false;
        }else{
            flag=true;}
      }
    return flag;
}

template<typename F>
int prec(F a)  //analisa a precedencia dos digitos
{
    switch(a[0]){
    case '(':
        return 1;
    case ')':
        return 5;
    case '^':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    case '%':
        return 3;
    case '-':
        return 4;
    case '+':
        return 4;
    }
    return -1;
}

template<typename F>
bool is_opr(F x)
{
    if(x[0]=='+') return true;
    else if (x[0]=='-') return true;
    else if(x[0]=='*') return true;
    else if(x[0]=='/') return true;
    else if(x[0]=='%') return true;

    else return false;
}

template<typename F>
bool is_op_par(F x) //se abre parenteses
{
    return (x[0]=='(');
}

template<typename F>
bool is_cls_par(F x) //se fecha parenteses
{
    return (x[0]==')');
}
template<typename F>
Fila<F> infx2Psfx(Fila<F> & fila){
	Fila<F> FilaAux;
	Pilha<F> pilha;
	int topSymbol,symbol;
	while(!fila.empty()){
		symbol=prec(fila.front());
		if(is_num(fila.front())){
			FilaAux.push(fila.front());
			fila.pop();
		}
		else{
		    if(pilha.empty()) topSymbol=10;
		    else topSymbol=prec(pilha.top());

			while((topSymbol<=symbol) && (!pilha.empty()) && (!is_op_par(pilha.top()))){
				if(topSymbol<=symbol){
					if(!pilha.empty()){
                        FilaAux.push(pilha.top());
                        pilha.pop();
                    }else{
                        FilaAux.push(fila.front());
                    }
				}
			}
            pilha.push(fila.front());
            fila.pop();
		}
		if(is_cls_par(fila.front()))
        {
            fila.pop();
            while(!pilha.empty())
            {
                if(is_op_par(pilha.top()))
                    pilha.pop();
                else{
                    FilaAux.push(pilha.top());
                    pilha.pop();
                }
            }
        }
	}
	while(!pilha.empty())
	{
		FilaAux.push(pilha.top());
		pilha.pop();
	}
	return FilaAux;
}

