#include <iostream>
#include <cstdlib>
#include "header.hpp"

#define DEF
#ifdef DEF
#include "erro.cpp"
#include "simbolo.cpp"
#endif // DEF

#ifdef DEBUG
#include "Pilha.cpp"
#include "Fila.cpp"
#else
#include <stack>
#include <queue>
#define Fila std::queue
#define Pilha std::stack
#endif // DEF

template <typename T>
void imprime(Fila<T> fila){
    std::cout<<"[";
    while(!fila.empty()){
        std::cout<<fila.front()<<",";
        fila.pop();
    }std::cout<<"]"<<std::endl;
}
template <typename T>
void imprime(Pilha<T> fila){
    std::cout<<"[";
    while(!fila.empty()){
        std::cout<<fila.top()<<",";
        fila.pop();
    }std::cout<<"]"<<std::endl;
}

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
    switch(this->getChar(c)){
        case',':
        case'<':
        case'>':
        case'=':
        case'.':
            return true;
    }
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
bool Expressao::isValOpd(unsigned int i, unsigned int f){
    int v=atoi(this->subStr(i,f).c_str());
    if(v>32767||v<(-32767)) return false;
    return true;
}
int Expressao::extSintFromStr(Simbolo &num,unsigned int inicio){
    unsigned int i;
    for(i=inicio;i<this->getExp().length()&&
                this->isDigit(i)&&
                this->getChar(i)!='\n';
                i++);
    num+=this->subStr(inicio,i);
    num.setCol(inicio);

    return i-1;
}

int Expressao::extSMinusFromStr(Simbolo &num, unsigned inicio){
    unsigned int i;
    unsigned int contIgnC=0;
    for(i=inicio;i<this->getExp().length()&&
            (!this->isNotMinus(i)||this->isIgnChar(i))
            &&this->getChar(i)!='\n';i++){
                if(this->isIgnChar(i)) contIgnC++;
            }
    if((this->subStr(inicio,i).length()-contIgnC)%2==0) num="";
    else num="-";
    num.setCol(--i);
    return i;
}
bool Expressao::tokeniza(void){
   // this->tokens.clear();
    //this->erros.clear();
    //this->fila.clear();

    Pilha<unsigned int> contPar;                            //Pilha controladora de parenteses
    Simbolo token;                                        //Buffer do token
    bool isLastOpt=true;                               //is the last a operator?
    bool isLastUnrMinus=false;                               //is the last a operator?
    unsigned int i;
    for(i=0;i<this->getExp().length();i++){
        if(this->isValChar(i)){
            if(this->isDigit(i)){
                if(!isLastOpt&&token!="("){
                    this->erros.push(Erro(5,i-1));
                }
                if(!isLastUnrMinus)
                    token="";
                int aux=this->extSintFromStr(token,i);
                if(!this->isValOpd(i,aux)){
                    this->erros.push(Erro(1,i));
                    token="0";
                }
                token.setCol(i);
                this->tokens.push(token);
                i=aux;
                isLastOpt=0;
                isLastUnrMinus=0;
            }else if(this->isParnt(i)){
                if(this->getExp()[i]=='('){
                    if(isLastUnrMinus){
                        token="-";
                        this->tokens.push(token);
                        isLastUnrMinus=0;
                    }
                    if(!isLastOpt&&token!="(")
                        this->erros.push(Erro(5,i));
                    contPar.push(i);
                }else{
                    if(isLastOpt&&!this->tokens.empty())
                        this->erros.push(Erro(2,i));       //ERROR: ultimo eh operador
                    if(!contPar.empty()){                   //Se houver parentese abraindo
                        if(token=="(")
                            this->erros.push(Erro(9,i));
                        contPar.pop();
                    }else
                        this->erros.push(Erro(6,i));       //ERROR: fechando sem abrir
                }

                token="";
                token+=this->getChar(i);
                token.setCol(i);
                this->tokens.push(token);

                isLastOpt=0;
                isLastUnrMinus=0;
            }else if(this->isValOpt(i)){
                if(this->isNotMinus(i)){
                    if(!isLastOpt){
                        if(!contPar.empty()){
                            if(token=="(")
                                this->erros.push(Erro(2,i));
                        }
                    }else
                        this->erros.push(Erro(2,i));
                    token="";
                    token+=this->getChar(i);
                    isLastUnrMinus=0;
                }else{
                    if(!isLastOpt&&token.getSimb()!="("){
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
                        }
                        token=num;
                        i=aux;
                    }
                }
                if(!isLastUnrMinus&&token.getSimb().length()>0){
                    token.setCol(i);
                    this->tokens.push(token);
                }
                isLastOpt=1;
            }
        }else if(this->isnValOpt(i)){
            this->erros.push(Erro(4,i+1));
            isLastOpt=0;
            if(!isLastUnrMinus)
                token="";
            token+=this->getExp()[i];
            token.setCol(i);
            this->tokens.push(token);
            isLastUnrMinus=0;
        }else if(this->getChar(i)=='\n'){
            if(isLastOpt)
                this->erros.push(Erro(2,i));
            if(!contPar.empty())
                this->erros.push(Erro(7,i));
            break;
        }else{
            this->erros.push(Erro(3,i+1));
            isLastOpt=0;
            if(!isLastUnrMinus)
                token="";
            token+=this->getExp()[i];
            token.setCol(i);
            this->tokens.push(token);
            isLastUnrMinus=0;
        }
    }
    //O main.cpp nao le o \n do teclado
    if(this->getChar(i-1)!='\n'){
        if(isLastOpt)
            this->erros.push(Erro(2,i));
        if(!contPar.empty())
            this->erros.push(Erro(7,i));
    }
    if(erros.empty()&&!this->tokens.empty())
        return true;

    if(!this->tokens.empty())
       // this->tokens.clear();

    return false;

}
void Expressao::inf2PosFix(void){
    //fila.clear();
	Simbolo simb("",0);
	Pilha<Simbolo> pilhaAux;

	while(!tokens.empty()){
		simb=tokens.front();
		tokens.pop();
		if(simb.isOperand()){                               //Se for operando
			this->fila.push(simb);
		}
		else{
			if(simb.isClosePar()){										//Se for um closed parentese
				while(!pilhaAux.empty()){
					if(pilhaAux.top().isOpenPar()){						//Procura na pilha um "(", se achar, remove e sai do laco
						pilhaAux.pop();
						break;
					}
					else{
						this->fila.push(pilhaAux.top());
						pilhaAux.pop();
					}
				}
			}else{
				while(!pilhaAux.empty()&&!simb.isOpenPar()){
					if(pilhaAux.top().prec()<=simb.prec()){

						if(pilhaAux.top().isOpenPar())
							pilhaAux.pop();
						else{
							this->fila.push(pilhaAux.top());
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
			this->fila.push(pilhaAux.top());
			pilhaAux.pop();
		}
	}
}

int Expressao::avalPosFixa(void){
	Simbolo simb("",0);
	Pilha<int> pilhaOpnd;

	int opnd1,opnd2;
	int resultado;

	while(!this->fila.empty()){
		simb=this->fila.front();
		this->fila.pop();
		if(simb.isOperand()){
			pilhaOpnd.push(simb.getInt());
		}
		else{
			opnd2=pilhaOpnd.top();
			pilhaOpnd.pop();

            if(simb.isUnarMinus){
                resultado=-1*opnd2;
            }
            else{
                opnd1=pilhaOpnd.top();
                pilhaOpnd.pop();
                if(!simb.aplic(opnd1,opnd2,resultado)){
                    this->erros.push(Erro(8,simb.getCol()+1));  //getCol irá mostrar a coluna do / na expressão original
                    return 0;
                }
            }
			pilhaOpnd.push(resultado);
		}
	}if(!pilhaOpnd.empty()){
		resultado=pilhaOpnd.top();
		pilhaOpnd.pop();
	}
	return resultado;
}

bool Expressao::exprValue(int &res){
    if(this->tokeniza()){
        this->inf2PosFix();
        int i=this->avalPosFixa();
        if(this->erros.empty()){
            res=i;
            return true;
        }
    }return false;
}
void Expressao::getErros(void){

}

#ifdef DEF
int main(void){
    Expressao e("12-1-(-(-(-2)))");
    int i;
    e.tokeniza();
    if(e.exprValue(i)) std::cout<<i<<std::endl;
    std::cout<<e;
    return 0;
}
#endif
