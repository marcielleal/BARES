#include <iostream>
#include <cstdlib>
#include <cmath>
#ifndef DEFINITIVO
#include <stack>
#include <queue>
#define Pilha std::stack
#define Fila std::queue
#endif

template <typename T>
Fila<T> inf2PosFix(Fila<T> &fila){
	T simb;
	Fila<T> filaAux;
	Pilha<T> pilhaAux;
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
			pilhaOpnd.push(simb.getInt());
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
template<typename T>
void imprime(Fila<T> fila){
    if(!fila.empty()){
        std::cout<<"[";
        while(!fila.empty()){
            std::cout<<fila.front()<<",";
            fila.pop();
        }std::cout<<"]";
    }else std::cout<<"FILA IS EMPTY!";
}
int main(void){
	Fila<Simbolo> fila;
	Simbolo s("=");
	/*unsigned int n=7;
	std::string a[21] =//{"(","(","12","+","14",")","*","13","-","(","15","-","14",")",")","^","(","1","+","2",")"};
    {"3","/","(","1","-","1",")"};
	for(unsigned int i=0;i<n;i++){
		s.setSimb(a[i]);
		fila.push(s);
	}
	fila=inf2PosFix(fila);
	imprime(fila);
	std::cout<<avalPosFixa(fila)<<std::endl;
    imprime(fila);
    */
	return 0;
}
