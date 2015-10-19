#include <iostream>
#include <cstdlib>
#include <cmath>
#ifdef DEBUG
#include "Pilha.cpp"
#include "Fila.cpp"
#else
#include <stack>
#include <queue>
#define Fila std::queue
#define Pilha std::stack
#endif // DEF


class Erro{
    std::string str[9]={"Constante numérica inválida: um dos operandos da expressão está fora da faixa permitida. (Coluna: ",
                            "Falta operando: em alguma parte da expressão está faltando um operando . (Coluna: ",
                            "Operando inválido: existe um operando que não é constante numérica. (Coluna: ",
                            "Operador inválido: existe um símbolo correspondente a um operador que não está na lista de operadores válidos. (Coluna: ",
                            "Falta operador: em alguma parte da expressão está faltando um operador. (Coluna: ",
                            "Fechamento de escopo inválido: existe um parêntese fechando sem haver um parêntese abrindo correspondente. (Coluna: ",
                            "Escopo aberto: existe um parêntese de abertura '(' sem um parêntese de fechamento ')' correspondente. (Coluna: ",
                            "Divisão por zero: Existe uma divisão cujo divisor é zero. (Coluna: ",
                            "Parênteses desnecessários: Parênteses sem nada em seu interior. (Coluna: "};
    int erro;
    int col;
    public:
        Erro(int i=1,int col=0);
        inline friend
		std::ostream &operator <<(std::ostream &_os,const Erro &_oErr){
			_os<<_oErr.str[_oErr.erro-1]<<_oErr.col<<")";
			return _os;
		}
};
Erro::Erro(int i,int col){
    this->erro=i;
    this->col=col;
}

class Simbolo{
	std::string simb;
	int coluna;
	public:
        bool isUnrMinus;
		template<typename T>
		Simbolo(T simb="",int col=0);
		Simbolo();

		bool isOperand(void) const;
		bool isOperator(void) const;
		int prec() const;
		int getInt() const;		//If osOperand true

        bool isDigit(unsigned int i) const;

        template <typename T>
        void setSimb(T str);
		std::string getSimb() const;

		void setCol(int col);
		int getCol(void) const;

		bool isOpenPar() const;
		bool isClosePar() const;

		bool aplic(int a,int b,int &res) const;

        void operator=(std::string s);
		bool operator==(std::string s);
		bool operator!=(std::string s);

		inline friend
		std::ostream &operator <<(std::ostream &_os,const Simbolo &_oSim){
			_os<<_oSim.simb;
			return _os;
		}
};


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
	this->simb=""+sim;
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
    this->simb=str;
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

class Expressao{
    std::string exp;//!<exp guardará uma expressão matemática
    /**@brief Separa os termos da expressão exp
    *
    * @return true a tokenização for bem-sucedida
    */

    /**@brief Separa os termos da expressão exp
    *
    * @return true a tokenização for bem-sucedida
    */

    /**@brief Separa os termos da expressão exp
    *
    * @return true a tokenização for bem-sucedida
    */
    public:
        /**@brief Construtor de Expressao*/
        Expressao(std::string exp="");
        ~Expressao(){};

        /**@brief Retorna o valor do atributo exp
        * @return atributo exp
        */
        std::string getExp(void);
        /**@brief Modifica o atributo exp
        * @param e será o novo valor do atributo exp
        */
        void setExp(std::string e);

        /**@brief Calcula o resultado da expressão
        * @param res será o inteiro correspondente ao resultado da expressão exp, caso a função retorne true
        * @return true se não houver erros na expressão ou false caso exista erros
        */
        bool exprValue(int &res);

        /**@brief Retorna a fila de erros contidos na expressão exp
        * @return fila de erros da expressão(membro erros da classe)
        */
        void getErros(void);

        /**@brief Avalia se um caractere é um dígito
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for um dígito e false se não for
        */
        bool isDigit(unsigned int c);
        /**@brief Avalia se um caractere é um parêntese
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for um parêntese e false se não for
        */
        bool isParnt(unsigned int c);
        /**@brief Avalia se um caractere é um operador válido
        * Para o projeto, operadores válidos são '+','-'.'*','/','^','%'
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for um operador válido e false se não
        */
        bool isValOpt(unsigned int c);
        /**@brief Avalia se um caractere é um operador não válido
        * Para o projeto, operadores não válidos são '>','<','=','.',','
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for um operador não válido e false se não
        */
        bool isnValOpt(unsigned int c);
        /**@brief Avalia se um caractere é ignorável
        * Para o projeto, caracteres ignorável são tabulações(código ASCII 9) e espaços(código ASCII 32)
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for caractere ignorável e false se não
        */
        bool isIgnChar(unsigned int c);
        /**@brief Avalia se um caractere válido para o programa
        * Para o projeto, caracteres válidos são todos '(',')','+','-'.'*','/','^','%',tabulações(código ASCII 9),
        * espaços(código ASCII 32) e dígitos de 0 a 9.
        * @see isValOpt
        * @see isParnt
        * @see isIgnChar
        * @see isDigit
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for caractere válido e false se não
        */
        bool isValChar(unsigned int c);
        /**@brief Avalia se um caractere não é igual a '-'
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for diferente de '-' e false se for
        */
        bool isNotMinus(unsigned int c);
        /**@brief Extrai um caractere do atributo exp
         * @param c é um índice de exp
         * @return o caractere de exp do índice c
         */
        char getChar(unsigned int c);
/*
        inline friend
        std::ostream &operator <<(std::ostream &_os,const Expressao &_oExp){
			_os<<"EXPRESSÃO: "<<_oExp.exp<<std::endl;
			_os<<"TOKENS: "<<_oExp.tokens<<std::endl;
			_os<<"FILA: "<<_oExp.fila<<std::endl;
			_os<<"ERROS: "<<_oExp.erros<<std::endl;
            return _os;
		}*/
};
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
    return;
}
char Expressao::getChar(unsigned int c){
    return this->getExp()[c];
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
