#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP
#include <iostream>

template<typename P>
class Pilha{
	protected:
		P *pt_Pilha;
		int tamanho;
		int _MaxSz;
		int capacidade;
		bool _duplica(void);
	public:
		Pilha(int _MaxSz=25);
		~Pilha(void);

		bool pop();
		bool push(P _data);
		P top();
		int size() const;
		bool Full() const;
		bool empty() const;


		inline friend
		std::ostream &operator <<(std::ostream &_os,const Pilha &_obj){
			_os<<"[ ";
			for(int i=0;i<_obj.tamanho;i++)
				_os<<_obj.pt_Pilha[i]<< " ";
			_os<<" ]"<<std::endl;
			return _os;
		}
};
template<typename F>
class Fila{
	protected:
		F *pt_fila;
		int _MaxSz;
		int inicio;
		int fim;
		int tamanho;
	public:
		Fila(int _MaxSz=50);
		~Fila(void);

		F front() const;
		F back() const;
        bool pop();
		bool push(F _data);
		bool full() const;
		bool empty() const;
        int size() const;

        inline friend
		std::ostream &operator <<(std::ostream &_os,const Fila &_obj){
			_os<<"[";
			for(int i=0;i<_obj.tamanho;i++)
				_os<<_obj.pt_fila[(_obj.inicio+i)%_obj._MaxSz]<<" ";
			_os<<"]"<<std::endl;
			return _os;
		}
};
class Erro{
    std::string str[9]={"Constante numérica inválida: um dos operandos da expressão está fora da faixa permitida. (Coluna: ",
                            "Falta operando: em alguma parte da expressão está faltando um operando . (Coluna: ",
                            "Operando inválido: existe um operando que não é constante numérica. (Coluna: ",
                            "Operador inválido: existe um símbolo correspondente a um operador que não está na lista de operadores válidos. (Coluna: ",
                            "Falta operador: em alguma parte da expressão está faltando um operador. (Coluna: ",
                            "Fechamento de escopo inválido: existe um parêntese fechando sem haver um parêntese abrindo correspondente.",
                            "Escopo aberto: existe um parêntese de abertura '(' sem um parêntese de fechamento ')' correspondente.",
                            "Divisão por zero: Houve uma divisão cujo quociente é zero. Coluna: ",
                            "Parênteses desnecessários: Parênteses sem nada em seu interior. Coluna: "};
    int erro;
    int col;
    public:
        Erro(int i,int col);
        Erro();
        inline friend
		std::ostream &operator <<(std::ostream &_os,const Erro &_oErr){
			_os<<_oErr.str[_oErr.erro-1]<<_oErr.col<<")";
			return _os;
		}
};
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
class Expressao{
    std::string exp;
    public:
        Expressao(std::string exp);
        std::string getExp(void);
        void setExp(std::string e);
        bool tokeniza(Fila<Simbolo> &tokens,Fila<Erro> &erros);
        Fila<Simbolo> inf2PosFix(Fila<Simbolo> &fila);
        int avalPosFixa(Fila<Simbolo> simbolos);

        char getChar(unsigned int c);
        bool isDigit(unsigned int c);
        bool isValOpd(unsigned int i, unsigned int f);
        bool isParnt(unsigned int c);
        bool isValOpt(unsigned int c);
        bool isnValOpt(unsigned int c);
        bool isIgnChar (unsigned int c);
        bool isValChar (unsigned int c);
        bool isNotMinus(unsigned int c);

        std::string subStr(unsigned int i,unsigned int j);
        int extSintFromStr(Simbolo &num,unsigned int inicio);
        int extSMinusFromStr(Simbolo &num,unsigned int inicio);

};


#endif
