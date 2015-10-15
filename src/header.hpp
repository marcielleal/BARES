#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP
#include <iostream>
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
		int _MaxSz;
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
		int _MaxSz;
		int inicio;
		int fim;
		int tamanho;
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
  /*
  * sobrecarga do operador <<
  **/
        inline friend
		std::ostream &operator <<(std::ostream &_os,const Fila &_obj){
			_os<<"[";
			for(int i=0;i<_obj.tamanho;i++)
				_os<<_obj.pt_fila[(_obj.inicio+i)%_obj._MaxSz]<<" ";
			_os<<"]"<<std::endl;
			return _os;
		}
};
/** @brief Classe Erro guarda strings que descrevem tipos de erros de uma expressão matemática
 *Considerando os tipos de
 **/
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
        Erro(int i=1,int col=0);
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
		Simbolo(std::string simb="",int col=0);
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
    Fila<Simbolo> tokens;
    Fila<Erro> erros;
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
