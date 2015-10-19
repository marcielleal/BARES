#include <iostream>
#include <cstdlib>
#include "header.hpp"

#define DEF
#ifdef DEF
#include "erro.cpp"
#include "simbolo.cpp"
#endif // DEF
#define DEBUG
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
        std::cout<<fila.front()<<","<<fila.front().isUnrMinus<<"|";
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
}/*
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
}*/
bool Expressao::tokeniza(Fila<Simbolo> &filaAux){
   if(this->isEmptyExp()){
        this->erros->push(Erro(10,-1));
        return false;
   }

   // this->tokens.clear();
    //this->erros.clear();
    //this->fila.clear();
    Pilha<int> contPar;                            //Pilha controladora de parenteses
    Simbolo num('+',0);                                        //Buffer do num
    std::string aux="";
    unsigned int i;
    std::cout<<"TOKENS= ";
    for(i=0;i<this->getExp().length();i++){
        /*if(filaAux.empty())
            std::cout<<"CAR: "<<this->getChar(i)<<" AUX: "<<aux<<" FRONT: "<<std::endl;
        else
            std::cout<<"CAR: "<<this->getChar(i)<<" AUX: "<<aux<<" BRACK: "<<filaAux.back()<<std::endl;*/

        if(this->isValChar(i)){
            if(this->isDigit(i)){
                unsigned int inicio=i;

                for(;i<this->getExp().length()&&this->isDigit(i)&&this->getChar(i)!='\n';i++);

                aux="";
                aux+=this->subStr(inicio,i);
                //std::cout<<aux<<" ITERACAO:"<<i<<std::endl;
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
                        this->erros->push(Erro(7,i));
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
            this->erros->push(Erro(4,i));        //Confirir
        }else if(this->getChar(i)=='\n'){
            break;
        }else{
            this->erros->push(Erro(3,i));        //Confirir
        }
        /*if(filaAux.empty())
            std::cout<<"FIM: "<<"CAR: "<<this->getChar(i)<<" AUX: "<<aux<<" BACK: "<<std::endl;
        else
            std::cout<<"FIM: "<<"CAR: "<<this->getChar(i)<<" AUX: "<<aux<<" BACK: "<<filaAux.back()<<std::endl;*/
    }
    //imprime(filaAux);
    if(!contPar.empty())
        this->erros->push(Erro(7,i));        //Confirir

    if(!filaAux.empty()&&this->erros->empty()){
        Simbolo now=filaAux.front();
        Simbolo last('+',0);
        filaAux.pop();
        bool inicio=1;
        int i=0;
        while(!filaAux.empty()){
            if(!inicio){
                last=now;
                now=filaAux.front();
                filaAux.pop();
            }inicio=0;
            if(now.isOpenPar()||now.isOperand()){
                if(last.isOperand()||last.isClosePar())
                    this->erros->push(Erro(5,now.getCol()));
                else if(last.isOpenPar()||last.isOperator()||last.isUnrMinus){
                }else std::cout<<"ERRO now.isOpenPar()||now.isOperand"<<std::cout;
            }
            else if(now.isClosePar()||now.isOperator()){
                if(!now.isUnrMinus){
                    if(last.isOperator()||last.isUnrMinus)
                        this->erros->push(Erro(2,now.getCol()));
                    else if(last.isOpenPar()){
                        if(now.isClosePar())
                            this->erros->push(Erro(9,now.getCol()));
                        else
                            this->erros->push(Erro(2,now.getCol()));
                    }
                    else if(last.isOperand()){
                    }else if(last.isClosePar()){
                    }
                    else std::cout<<"ERRO !now.isUnarMinus"<<std::endl;
                }else{
                    if(last.isUnrMinus||last.isOperator()){
                        if(!filaAux.empty()){
                            if(filaAux.front().isUnrMinus){ //if next
                                filaAux.pop();
                                now=last;
                                continue;
                            }
                        }
                    }else if(last.isOperand()||last.isClosePar())
                        std::cout<<"WTF?"<<std::endl;
                }
            }else std::cout<<"ERRO"<<std::endl;
            std::cout<<now<<",";
            this->tokens->push(now);
        }
        if(now.isOperator()){
            this->erros->push(Erro(2,now.getCol()));
            return false;
        }
        else if(now.isClosePar()){
        }else if(now.isOperand()){
        }else std::cout<<"ERRO"<<std::endl;

    }std::cout<<std::endl;
    if(this->erros->empty())
        return true;
    return false;
}
void Expressao::inf2PosFix(void){
    //tokens->clear();
	Simbolo simb(' ',0);
	Pilha<Simbolo> pilhaAux;
	std::cout<<"FILA= ";
	while(!this->tokens->empty()){
		simb=tokens->front();
		tokens->pop();
		if(simb.isOperand()){                               //Se for operando
			this->fila->push(simb);
			std::cout<<simb<<",";
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
						std::cout<<pilhaAux.top()<<",";
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
							std::cout<<pilhaAux.top()<<",";
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
			std::cout<<pilhaAux.top()<<",";
			pilhaAux.pop();
		}
	}std::cout<<"\n";
}

int Expressao::avalPosFixa(void){
	Simbolo simb(' ',0);
	Pilha<int> pilhaOpnd;

	int opnd1,opnd2;
	int resultado;

	while(!this->fila->empty()){
		simb=this->fila->front();
		this->fila->pop();
		if(simb.isOperand()){
			pilhaOpnd.push(simb.getInt());
			//std::cout<<"WHERE"<<std::endl;
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
                    this->erros->push(Erro(8,simb.getCol()+1));  //getCol irá mostrar a coluna do / na expressão original
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
/*
bool Expressao::exprValue(int &res){

    if(this->tokeniza()){
        this->inf2PosFix();
        int i=this->avalPosFixa();
        if(this->erros->empty()){
            res=i;
            return true;
        }
    }return false;
}*/
void Expressao::getErros(void){

}
/*
#ifdef DEF
int main(void){
    Expressao e("        1 ");

    std::string a("12-1-(-(-(-2)))");

    if(e.tokeniza()){
        e.inf2PosFix();
        int i=e.avalPosFixa();
        if(e.erros->empty()){
            res=i;
            std::cout<<i<<std::endl;
        }
    }

    e.print();std::cout<<e.isEmptyExp();
    return 0;
}
#endif
*/
