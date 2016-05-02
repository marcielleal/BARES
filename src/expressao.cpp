/**
 * @file expressao.cpp
 * @brief Implementação dos métodos da classe Expressao
 *
 * @author Marciel Manoel Leal
 *
 */
#include <iostream>
#include <cstdlib>

#include "../include/header.hpp"
#include "Fila.cpp"
#include "Pilha.cpp"
#include "simbolo.cpp"
#include "erro.cpp"

bool Expressao::isEmptyExp(){
    for(unsigned int i=0;i<this->exp.length();i++)
        if(!this->isIgnChar(i))
            return false;
    return true;
}
std::string Expressao::subStr(unsigned int i,unsigned int j){
    std::string str="";
    for(;i<j&&i<this->exp.length();i++)
        str+=this->exp[i];
    return str;
}
void Expressao::setExp(std::string e){
    this->clear();
    this->exp=e;
    return;
}
char Expressao::getChar(unsigned int c){
    if(c<this->exp.length())
        return this->exp[c];
    else return ' ';
}
Expressao::Expressao(std::string exp){
    this->exp=exp;
    this->tokens=new Fila<Simbolo>;
    this->fila=new Fila<Simbolo>;
    this->erros=new Fila<Erro>;
}
Expressao::~Expressao(){
    delete this->tokens;
    delete this->fila;
    delete this->erros;
}
std::string Expressao::getExp(void){
    return this->exp;
}
bool Expressao::isDigit(unsigned int c){
    if(c<this->exp.length()){
        switch(this->getChar(c)){
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
    }return false;
}

bool Expressao::isParnt(unsigned int c){
    if(c<this->exp.length())
        if(this->getChar(c)=='('||this->getChar(c)==')')
            return true;
    return false;
}

bool Expressao::isValOpt(unsigned int c){
    if(c<this->exp.length()){
        if(this->getChar(c)=='%'||this->getChar(c)=='*'||this->getChar(c)=='+'||this->getChar(c)=='-'||this->getChar(c)=='/'||this->getChar(c)=='^')
            return true;
    }
    return false;
}
bool Expressao::isnValOpt(unsigned int c){                             //Se later
    if(c<this->exp.length()){
        switch(this->getChar(c)){
            case',':
            case'<':
            case'>':
            case'=':
            case'.':
                return true;
        }
    }
    return false;
}
bool Expressao::isValChar(unsigned int c){
    if(c<this->exp.length())
        if(this->isDigit(c)||this->isValOpt(c)||this->isIgnChar(c)||this->isParnt(c))
            return true;
    return false;
}
bool Expressao::isNotMinus(unsigned int c){
    if(c<this->exp.length())
        return this->getChar(c)=='-'? false:true;
    return false;
}
bool Expressao::isIgnChar(unsigned int c){
    if(c<this->exp.length())
        if(this->getChar(c)==32||this->getChar(c)==9)
            return true;
    return false;
}
bool Expressao::tokeniza(void){
   if(this->isEmptyExp()){
   	if(exp!="\n")
            this->erros->push(Erro(10,-1));
        return false;
   }//this->clear();

    Fila<Simbolo> filaAux;
    Pilha<int> contPar;                            //Pilha controladora de parenteses
    Simbolo num('+',0);                                        //Buffer do num
    std::string aux="";
    unsigned int i;
    for(i=0;i<this->getExp().length();i++){
        if(this->isValChar(i)){
            if(this->isDigit(i)){
                unsigned int inicio=i;

                for(;i<this->getExp().length()&&this->isDigit(i)&&this->getChar(i)!='\n';i++);

                aux="";
                aux+=this->subStr(inicio,i);
                num.setSimb(aux);
                num.setCol(inicio);
                if(num.isOperand()){
                    filaAux.push(num);
                }
                else
                    this->erros->push(Erro(1,num.getCol()));
                i--;
            }else if(this->isParnt(i)){
                if(this->getChar(i)=='('){
                    Simbolo s(this->getChar(i),i);
                    filaAux.push(s);
                    contPar.push(i);
                }else{
                    if(contPar.empty())
                        this->erros->push(Erro(6,i));
                    else{
                        Simbolo s(this->getChar(i),i);
                        filaAux.push(s);
                        contPar.pop();
                    }
                }
            }else if(this->isValOpt(i)){
                Simbolo s(this->getChar(i),i);
                if(!isNotMinus(i)){
                    if(!filaAux.empty()){
                        if(filaAux.back().isOpenPar()||filaAux.back().isOperator()||filaAux.back().isUnrMinus)
                            s.isUnrMinus=true;
                    }else s.isUnrMinus=true;
                }

                else s.isUnrMinus=false;

                filaAux.push(s);
            }
        }else if(this->isnValOpt(i)){
            this->erros->push(Erro(4,i));
        }else if(this->getChar(i)=='\n'){
            break;
        }else{
            this->erros->push(Erro(3,i));
        }
    }

    if(!contPar.empty()){
        while(!contPar.empty()){
            this->erros->push(Erro(7,contPar.top()));
            contPar.pop();
        }
    }

    if(!filaAux.empty()&&this->erros->empty()){
        Simbolo now=filaAux.front();
        Simbolo last('+',0);
        filaAux.pop();
        bool inicio=1;
        while(!filaAux.empty()){
            if(!inicio){
                last=now;
                now=filaAux.front();
                filaAux.pop();
            }inicio=0;
            if(now.isOpenPar()||now.isOperand()){
                if(last.isOperand()||last.isClosePar())
                    this->erros->push(Erro(5,last.getCol()));
                else if(last.isOpenPar()||last.isOperator()||last.isUnrMinus){
                }else std::cout<<"ERRO now.isOpenPar()||now.isOperand";
            }
            else if(now.isClosePar()||now.isOperator()){
                if(!now.isUnrMinus){
                    if(last.isOperator()||last.isUnrMinus)
                        this->erros->push(Erro(2,last.getCol()));
                    else if(last.isOpenPar()){
                        if(now.isClosePar())
                            this->erros->push(Erro(9,now.getCol()));
                        else
                            this->erros->push(Erro(2,last.getCol()));
                    }
                    else if(last.isOperand()){
                    }else if(last.isClosePar()){
                    }
                    else std::cout<<"ERRO !now.isUnarMinus"<<std::endl;
                }else{
                    if(last.isUnrMinus||last.isOperator()){
                        if(!filaAux.empty()){
                            if(filaAux.front().isUnrMinus){
                                filaAux.pop();
                                now=last;
                                continue;
                            }
                        }
                    }else if(last.isOperand()||last.isClosePar())
                        std::cout<<"ERRO"<<std::endl;
                }
            }else std::cout<<"ERRO"<<std::endl;
            this->tokens->push(now);
        }
        if(now.isOperator()){
            this->erros->push(Erro(2,now.getCol()));
            return false;
        }
        else if(now.isClosePar()){
        }else if(now.isOperand()){
        }else std::cout<<"ERRO"<<std::endl;
    }
    if(this->erros->empty())
        return true;
    return false;
}
void Expressao::inf2PosFix(void){
	Simbolo simb(' ',0);
	Pilha<Simbolo> pilhaAux;

	while(!this->tokens->empty()){
		simb=tokens->front();
		tokens->pop();
		if(simb.isOperand()){                               //Se for operando
			this->fila->push(simb);

		}
		else{
			if(simb.isClosePar()){										//Se for um closed parentese
				while(!pilhaAux.empty()){
					if(pilhaAux.top().isOpenPar()){						//Procura na pilha um "(", se achar, remove e sai do laco
						pilhaAux.pop();
						break;
					}
					else{
						this->fila->push(pilhaAux.top());
						pilhaAux.pop();

					}
				}
			}else{
				while(!pilhaAux.empty()&&!simb.isOpenPar()){
					if(pilhaAux.top().prec()<=simb.prec()){

						if(pilhaAux.top().isOpenPar())
							pilhaAux.pop();
						else{
							this->fila->push(pilhaAux.top());
							pilhaAux.pop();
						}
					}
					else break;
				}
				pilhaAux.push(simb);
			}
		}
	}
	while(!pilhaAux.empty()){
		if(pilhaAux.top().isOpenPar())
			pilhaAux.pop();
		else{
			this->fila->push(pilhaAux.top());
			pilhaAux.pop();
		}
	}
}

int Expressao::avalPosFixa(void){
	Simbolo simb(' ',0);
	Pilha<int> pilhaOpnd;

	int opnd1,opnd2;
	int resultado;
	bool flag=0;

	while(!this->fila->empty()){
		simb=this->fila->front();
		this->fila->pop();
		if(simb.isOperand()){
			pilhaOpnd.push(simb.getInt());
		}
		else{
			opnd2=pilhaOpnd.top();
			pilhaOpnd.pop();

            if(simb.isUnrMinus){
                resultado=-1*opnd2;
            }
            else{
                opnd1=pilhaOpnd.top();
                pilhaOpnd.pop();
                if(!simb.aplic(opnd1,opnd2,resultado)){
                    this->erros->push(Erro(8,simb.getCol()));
                    flag=1;
                }
            }
			pilhaOpnd.push(resultado);
		}
	}if(!pilhaOpnd.empty()){
		resultado=pilhaOpnd.top();
		pilhaOpnd.pop();
	}
	if(flag) return 0;
	return resultado;
}
bool Expressao::exprValue(int &res){
    if(this->tokeniza()){
        this->inf2PosFix();
        int i=this->avalPosFixa();
        if(this->erros->empty()){
            res=i;
            return true;
        }
    }return false;
}
void Expressao::printErros(std::ostream* pOut){
    Fila<Erro> *tmp;
    tmp=this->erros;
    while(!erros->empty()){
        *pOut<<tmp->front()<<std::endl;
        tmp->pop();
    }
}
void Expressao::clear(){
    while(!this->tokens->empty()){
        this->tokens->pop();
    }

    while(!fila->empty()){
        this->fila->pop();
    }

    while(!erros->empty()){
        this->erros->pop();
    }
}
