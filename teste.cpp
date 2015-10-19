#include <iostream>
#include <cstdlib>
#include "teste_classes.cpp"

bool tokeniza(Fila<Simbolo> &fila,Fila<Erro> &erros){
   // this->tokens.clear();
    //this->erros.clear();
    //this->fila.clear();
    Expressao e("12-1-(-(-(-2)))");
    Fila<Simbolo> filaAux;
    Pilha<int> contPar;                            //Pilha controladora de parenteses
    Simbolo num;                                        //Buffer do num
    std::string aux;
    unsigned int i;
    std::cout<<"AS";

    for(i=0;i<e.getExp().length();i++){
        if(e.isValChar(i)){
            if(e.isDigit(i)){
                if((i+1)<e.getExp().length()){
                    if(!e.isDigit(i+1)){                                //Next is not a digit
                        if(num.isOperand()){
                            num.setSimb(aux);
                            filaAux.push(num);
                        }
                        else
                            erros.push(Erro(1,num.getCol()));
                    }
                }else{
                    if(num.isOperand()){
                        num.setSimb(aux);
                        filaAux.push(num);
                    }
                    else
                        erros.push(Erro(1,num.getCol()));
                }
                if(!e.isDigit(i-1)){
                    aux="";
                    num.setCol(i);
                }
                aux+=e.getChar(i);
            }else if(e.isParnt(i)){
                if(e.getChar(i)=='('){
                    filaAux.push(Simbolo(e.getChar(i),i));
                    contPar.push(i);
                }else{
                    if(contPar.empty())
                        erros.push(Erro(7,i));
                    else{
                        filaAux.push(Simbolo(e.getChar(i),i));
                        contPar.pop();
                    }
                }
            }else if(e.isValOpt(i)){
                if(!e.isNotMinus(i)){
                    if(!filaAux.empty()){
                        if(filaAux.back().isOpenPar()||filaAux.back().isOperator()||filaAux.back().isUnrMinus){
                            Simbolo m(e.getChar(i),i);
                            m.isUnrMinus=true;
                            filaAux.push(m);
                        }
                    }
                }
                else filaAux.push(Simbolo(e.getChar(i),i));
            }
        }else if(e.isnValOpt(i)){
            erros.push(Erro(4,i));        //Confirir
        }else if(e.getChar(i)=='\n'){
            break;
        }else{
            erros.push(Erro(3,i));        //Confirir
        }
    }

    if(!contPar.empty())
        erros.push(Erro(7,i));        //Confirir

    if(!filaAux.empty()&&erros.empty()){
        Simbolo now=filaAux.front();
        Simbolo last;
        filaAux.pop();
        bool inicio=1;

        while(!filaAux.empty()){
            if(!inicio){
                last=now;
                now=filaAux.front();
                filaAux.pop();
                inicio=0;
            }
            if(now.isOpenPar()||now.isOperand()){
                if(last.isOperand()||last.isClosePar())
                    erros.push(Erro(5,now.getCol()));
                else if(last.isOpenPar()||last.isOperator()||last.isUnrMinus){
                }else std::cout<<"ERRO now.isOpenPar()||now.isOperand"<<std::cout;
            }
            else if(now.isClosePar()||now.isOperator()){
                if(!now.isUnrMinus){
                    if(last.isOperator()||last.isOpenPar())
                        erros.push(Erro(2,now.getCol()));
                    else if(last.isOpenPar()){
                        if(now.isClosePar())
                            erros.push(Erro(9,now.getCol()));
                    }
                    else if(last.isOperand()){
                    }
                    else std::cout<<"ERRO !now.isUnarMinus"<<std::endl;
                }else{
                    if(last.isUnrMinus){
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
            }else std::cout<<"ERRO"<<std::cout;
            fila.push(now);
        }
        if(now.isOperator()){
            erros.push(Erro(2,now.getCol()));
            return false;
        }
        else if(now.isClosePar()){
        }else if(now.isOperand()){
        }else std::cout<<"ERRO"<<std::endl;

    }
    return false;
}

int main(void){
    std::cout<<"DAS";
    Expressao e("12-1-(-(-(-2)))");
    Fila<Simbolo> fila;
    Fila<Erro> erros;

    std::cout<<"DAS";
    tokeniza(fila,erros);
    imprime(fila);

    return 0;
}

