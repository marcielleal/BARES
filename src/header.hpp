#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP
#include <iostream>
#define DEF
#ifndef DEF
#include <queue>
#define Fila std::queue
#include <stack>
#define Pilha std::stack
#else
/**
  * @brief Classe Pilha e seu construtor
  * A função construtora recebe o argumento _MaxSz a fim de definir o tamanho máximo da pilha.
  * Depois testa se a pilha foi criada e inicializa seus elementos.
  * @param _MaxSz tamanho maximo da pilha
  * @param pt_fila ponteiro para a pilha
  * @param tamanho tamanho da pilha, é incrementado ou decrementado de acordo com as ações.
  * @param capacidade capacidade máxima da pilha
  */
template<typename P>
class Pilha{
	protected:
		P *pt_Pilha;
		int tamanho;
		int capacidade;
 /**
 * @brief _duplica() Duplica a pilha caso tenha alcançado a capacidade máxima
 *
 * @param *aux ponteiro auxiliar que vai receber a pilha temporariamente
 * @param *novo ponteiro para um vetor do tipo pilha com o dobro da capacidade anterior
 * o laço for copia o vetor aux para o "novo" que em seguida em copiado para
 * @see pt_Pilha
 * @return true or false
 * */
		bool _duplica(void);
	public:
		Pilha(int _MaxSz=50);
  /**
  * @brief Destructor da pilha.
  * Destrói a pilha.
  */
		~Pilha(void);
 /**
 *@brief pop() remove o último elemento da pilha somente decrementando seu tamanho
 *
 * @see pt_Pilha
 * @see empty()
 * @see tamanho
 **/
		bool pop();
 /**
 * @brief push(P _data) insere o elemento _data do tipo P na pilha
 * @param _data
 * @see pt_Pilha
 * @see tamanho
 * @return true or false
 * */
		bool push(P _data);
 /**
 * top() retorna o último elemento da pilha (tamanho-1)
 * @see pt_Pilha
 * @see tamanho
 * @return pt_Pilha[tamanho-1]
 * */
		P top();
 /**
 * @brief size() retorna o tamanho atual da pilha
 * caso não seja inválida
 **/
		int size() const;
 /**
 * @brief Full() retorna true se o tamanho do vetor tiver alcançado o tamanho máximo
 * @see tamanho
 * @see _MaxSz
 * */
		bool Full() const;
 /**
 * @brief empty() retorna true se a pilha estiver vazia
 * @see tamanho
 * */
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


 /**
  * @brief classe fila e seu construtor com o tipo genérico F
  * A função construtora recebe o argumento _MaxSz a fim de definir o tamanho máximo da fila.
  * Depois testa se a fila foi criada e inicializa seus elementos.
  * @param _MaxSz tamanho maximo da fila
  * @param pt_fila ponteiro para a fila
  * @param tamanho tamanho da fila, é incrementado ou decrementado de acordo com as ações.
  * @param inicio o primeiro elemento da fila
  * @param fim o último elemento da fila.
  */
template<typename F>
class Fila{
	protected:
		F *pt_fila;
		int inicio;
		int fim;
		int tamanho;
        bool _duplica();
        int capacidade;
	public:
		Fila(int _MaxSz=50);
  /**
  * @brief ~Fila() Destructor da fila.
  *
  * Destrói a fila.
  */
		~Fila(void);
  /**
  * front retorna o primeiro elemento da fila.
  * @see pt_fila
  * @see inicio
  * @return pt_fila[inicio]
  */		F front() const;
  /**
  * back retorna o último elemento da fila.
  * @see pt_fila
  * @see fim
  * @return pt_fila[fim]
  */		F back() const;
   /**
  * @brief "pop" tem por objetivo remover um elemento da fila.
  *
  * Primeiro a função avalia se a fila foi criada/é válida para então remover o primeiro elemento da fila e
  * decrementar o tamanho. Retorna true caso dê certo.
  * @see pt_fila
  * @see empty()
  * @see inicio
  * @see tamanho
  * @return true or false
  */        	bool pop();
   /**
  * @brief Push tem por objetivo inserir um elemento na fila.
  *
  * "push" recebe um argumento _data e, caso a fila seja válida e não estiver cheia, testa se está vazia
  * para então inserir o elemento e incrementar o tamanho da fila.
  * @see pt_fila ponteiro para o primeiro elemento da fila
  * @see full()
  * @see inicio
  * @see fim
  * @see tamanho
  */		bool push(F _data);
   /**
  * A função full retorna verdadeiro se a fila estiver cheia e falso caso não.
  * @return true or false
  */
		bool full() const;
  /**
  * empty() retorna true se fila estiver vazia.
  * @return true or false
  */
		bool empty() const;
  /**
  * A função size retorna o tamanho da fila.
  * @return this->tamanho
  */
        	int size() const;
        	void clear(void);
  /**
  * sobrecarga do operador <<
  */

        inline friend
		std::ostream &operator <<(std::ostream &_os,const Fila &_obj){
			for(int i=0;i<_obj.tamanho;i++)
				_os<<_obj.pt_fila[(_obj.inicio+i)%_obj.capacidade]<<",";

			return _os;
		}
};


#endif // DEFs


class Erro{
    std::string str[10]={"Constante numérica inválida: um dos operandos da expressão está fora da faixa permitida. (Coluna: ",
                            "Falta operando: em alguma parte da expressão está faltando um operando . (Coluna: ",
                            "Operando inválido: existe um operando que não é constante numérica. (Coluna: ",
                            "Operador inválido: existe um símbolo correspondente a um operador que não está na lista de operadores válidos. (Coluna: ",
                            "Falta operador: em alguma parte da expressão está faltando um operador. (Coluna: ",
                            "Fechamento de escopo inválido: existe um parêntese fechando sem haver um parêntese abrindo correspondente. (Coluna: ",
                            "Escopo aberto: existe um parêntese de abertura '(' sem um parêntese de fechamento ')' correspondente. (Coluna: ",
                            "Divisão por zero: Existe uma divisão cujo divisor é zero. (Coluna: ",
                            "Parênteses desnecessários: Parênteses sem nada em seu interior. (Coluna: ",
                            "Erro: expressão vazia!!"};
    int erro;
    int col;
    public:
        Erro(int i=1,int col=0);
        inline friend
		std::ostream &operator <<(std::ostream &_os,const Erro &_oErr){
			_os<<_oErr.str[_oErr.erro-1];
			if(_oErr.col>=0)
                _os<<_oErr.col<<")";
			return _os;
		}
};
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
class Expressao{
    std::string exp;//!<exp guardará uma expressão matemática
    Fila<Simbolo> *tokens;//!<Fila que guardará os tokens de exp
    Fila<Simbolo> *fila;//!<Fila que guardará os tokens no formato pós-fixo
    //!<Fila que guardará os erros na formação da expressão contida em exp, caso houver

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
    Fila<Erro> *erros;
        int avalPosFixa(void);
        void inf2PosFix(void);
        bool tokeniza(Fila<Simbolo> &filaAux);

        bool isEmptyExp();
        /**@brief Construtor de Expressao*/
        Expressao(std::string exp="");
        ~Expressao(){delete this->tokens;delete this->fila;delete this->erros;};

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
        std::string subStr(unsigned int i,unsigned int j);
        void print(){
            std::cout<<"EXPRESSAO= "<<this->exp<<std::endl;
            std::cout<<"TOKENS= ";
            std::cout<<"[";
            while(!tokens->empty()){
                std::cout<<tokens->front()<<",";
                tokens->pop();
            }std::cout<<"]"<<std::endl;

            std::cout<<"FILA= ";
            std::cout<<"[";
            while(!fila->empty()){
                std::cout<<fila->front()<<",";
                fila->pop();
            }std::cout<<"]"<<std::endl;

            std::cout<<"ERROS= ";
            while(!erros->empty()){
                std::cout<<erros->front()<<",";
                erros->pop();
            }std::cout<<"]"<<std::endl;

        }
        void clear(){
            while(!tokens->empty()){
                tokens->pop();
            }

            while(!fila->empty()){
                fila->pop();
            }

            while(!erros->empty()){
                erros->pop();
            }

        }
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


#endif
