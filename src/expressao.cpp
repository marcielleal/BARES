#include <iostream>
#include <cstdlib>
#include "header.hpp"

void Expressao::setExp(std::string e){
    this->exp=e;
}
std::string Expressao::subStr(unsigned int i,unsigned int j){
    std::string str="";
    for(;i<j&&i<this->exp.length();i++)
        str+=this->exp[i];
    return str;
}
char Expressao::getChar(unsigned int c){
    return this->exp[c];
}
Expressao::Expressao(std::string exp){
    this->exp=exp;
}
std::string Expressao::getExp(void){
    return this->exp;
}
bool Expressao::isDigit(unsigned int c){
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
}
bool Expressao::isValOpd(unsigned int i, unsigned int f){
    /**
    *Expressao::is valid operand
    */
    int v=atoi(this->subStr(i,f).c_str());
    if(v>32767||v<(-32767)) return false;
    return true;
}
int Expressao::extSintFromStr(Simbolo &num,unsigned int inicio){
    /**
    * Extrai um inteiro de uma string e retorna o indice no qual aparece um caractere na string que nao e mais digito
    */
    unsigned int i;
    for(i=inicio;i<this->getExp().length()&&this->isDigit(i)&&this->getChar(i)!='\n';i++);


    num+=this->subStr(inicio,i);
    num.setCol(i);
    return i-1;
}

bool Expressao::isParnt(unsigned int c){
    if(this->getChar(c)=='('||this->getChar(c)==')')
        return true;
    return false;
}

bool Expressao::isValOpt(unsigned int c){
    if(this->getChar(c)=='%'||this->getChar(c)=='*'||this->getChar(c)=='+'||this->getChar(c)=='-'||this->getChar(c)=='/'||this->getChar(c)=='^')
        return true;
    return false;
}
bool Expressao::isnValOpt(unsigned int c){                             //Se later
    if(this->getChar(c)==','||this->getChar(c)=='.'||this->getChar(c)=='<'||this->getChar(c)=='>'||this->getChar(c)=='=')
        return true;
    return false;
}
bool Expressao::isValChar(unsigned int c){
    if(this->isDigit(c)||this->isValOpt(c)||this->isIgnChar(c)||this->isParnt(c))
        return true;
    return false;
}
bool Expressao::isNotMinus(unsigned int c){
    return this->getChar(c)=='-'? false:true;
}
bool Expressao::isIgnChar(unsigned int c){
    if(this->getChar(c)==32||this->getChar(c)==9)
        return true;
    return false;
}
int Expressao::extSMinusFromStr(Simbolo &num, unsigned inicio){
    /**
    * Analisa uma sequencia de operadores '-'
    */
    unsigned int i;
    unsigned int contIgnC=0;
    for(i=inicio;i<this->getExp().length()&&
            (!this->isNotMinus(i)||this->isIgnChar(i))
            &&this->getChar(i)!='\n';i++){
                if(this->isIgnChar(i)) contIgnC++;
                std::cout<<this->getChar(i)<<"POSICAO"<<i<<" "<<this->subStr(inicio,i)<<std::endl;
            }
    if((this->subStr(inicio,i).length()-contIgnC)%2==0) num.setSimb("");
    else num.setSimb("-");
    num.setCol(--i);
    return i;
}
bool Expressao::tokeniza(Fila<Simbolo> &tokens,Fila<Erro> &erros){
    Pilha<unsigned int> contPar;                            //Pilha controladora de parenteses
    Simbolo token;                                        //Buffer do token
    bool isLastOpt=true;                               //is the last a operator?
    bool isLastUnrMinus=false;                               //is the last a operator?
    for(unsigned int i=0;i<this->getExp().length();i++){
        if(this->isValChar(i)){
            if(this->isDigit(i)){
                if(!isLastOpt&&token!="("){
                    erros.push(Erro(5,i-1));
                }
                if(!isLastUnrMinus)
                    token="";
                int aux=this->extSintFromStr(token,i);
                if(!this->isValOpd(i,aux)){
                    erros.push(Erro(1,i));
                    token="0";
                }
                token.setCol(i);
                tokens.push(token);
                i=aux;
                isLastOpt=0;
                isLastUnrMinus=0;
            }else if(this->isParnt(i)){////////
                if(this->getExp()[i]=='('){
                    if(!isLastOpt&&token!="(")
                        erros.push(Erro(5,i));
                    contPar.push(i);
                }else{
                    if(isLastOpt&&!tokens.empty())
                        erros.push(Erro(2,i));       //ERROR: ultimo eh operador
                    if(!contPar.empty()){                   //Se houver parentese abraindo
                        if(token=="(")
                            erros.push(Erro(9,i));
                        contPar.pop();
                    }else
                        erros.push(Erro(6,i));       //ERROR: fechando sem abrir
                }

                if(!isLastUnrMinus)
                    token="";
                token+=this->getChar(i);
                token.setCol(i);
                tokens.push(token);

                isLastOpt=0;
                isLastUnrMinus=0;
            }else if(this->isValOpt(i)){
                if(this->isNotMinus(i)){
                    if(!isLastOpt){
                        if(!contPar.empty()){
                            if(token=="(")
                                erros.push(Erro(2,i));
                        }
                    }else
                        erros.push(Erro(2,i));

                    if(!isLastUnrMinus)
                        token="";
                    token+=this->getChar(i);
                    isLastUnrMinus=0;
                }else{
                    Simbolo num;
                    int aux=this->extSMinusFromStr(num,i);
                    if(num.getSimb().length()>0){
                        if(isLastOpt||token.getSimb()=="("){
                            isLastUnrMinus=1;
                        }else isLastUnrMinus=0;
                    }token=num;
                    i=aux;
                }
                if(!isLastUnrMinus&&token.getSimb().length()>0){
                    token.setCol(i);
                    tokens.push(token);
                }
                isLastOpt=1;
            }
        }else if(isnValOpt(this->getExp()[i])){
            erros.push(Erro(4,i+1));
            isLastOpt=0;
            if(!isLastUnrMinus)
                token="";
            token+=this->getExp()[i];
            token.setCol(i);
            tokens.push(token);
            isLastUnrMinus=0;
        }else if(this->getExp()[i]=='\n'){
            if(isLastOpt)
                erros.push(Erro(2,i));
            if(!contPar.empty())
                erros.push(Erro(7,i));
            break;
        }else{
            erros.push(Erro(3,i+1));
            isLastOpt=0;
            if(!isLastUnrMinus)
                token="";
            token+=this->getExp()[i];
            token.setCol(i);
            tokens.push(token);
            isLastUnrMinus=0;
        }
    }

    if(erros.empty()&&!tokens.empty())
        return true;
    while(!tokens.empty()){
        tokens.pop();
    }
    return false;
}
Fila<Simbolo> Expressao::inf2PosFix(Fila<Simbolo> &fila){
	Simbolo simb;
	Fila<Simbolo> filaAux;
	Pilha<Simbolo> pilhaAux;
	while(!fila.empty()){
		simb=fila.front();
		fila.pop();
		if(simb.isOperand()){
			filaAux.push(simb);
		}
		else{
			if(simb.isClosePar()){										//Se for um closed parentese
				while(!pilhaAux.empty()){
					if(pilhaAux.top().isOpenPar()){						//Procura na pilha um "(", se achar, remove e sai do laco
						pilhaAux.pop();
						break;
					}
					else{
						filaAux.push(pilhaAux.top());
						pilhaAux.pop();
					}
				}
			}else{
				while(!pilhaAux.empty()&&!simb.isOpenPar()){
					if(pilhaAux.top().prec()<=simb.prec()){
						if(pilhaAux.top().isOpenPar())
							pilhaAux.pop();
						else{
							filaAux.push(pilhaAux.top());
							pilhaAux.pop();
						}
					}
					else break;
				}
				pilhaAux.push(simb);
			}
		}
	}while(!pilhaAux.empty()){
		if(pilhaAux.top().isOpenPar())
			pilhaAux.pop();
		else{
			filaAux.push(pilhaAux.top());
			pilhaAux.pop();
		}
	}
	return filaAux;
}

int Expressao::avalPosFixa(Fila<Simbolo> simbolos){
	Simbolo simb;
	Pilha<int> pilhaOpnd;

	int opnd1,opnd2;
	int resultado;

	while(!simbolos.empty()){
		simb=simbolos.front();
		simbolos.pop();
		if(simb.isOperand()){
			pilhaOpnd.push(simb.getInt());
		}
		else{
			opnd2=pilhaOpnd.top();
			pilhaOpnd.pop();
			opnd1=pilhaOpnd.top();
			pilhaOpnd.pop();

			resultado=simb.aplic(opnd1,opnd2);
			pilhaOpnd.push(resultado);
		}
	}if(!pilhaOpnd.empty()){
		resultado=pilhaOpnd.top();
		pilhaOpnd.pop();
	}
	return resultado;
}
