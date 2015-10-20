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

/**
Lista dos tipos de erros identificados pelo programa

Todos os erros(excetuando-se o de entradas vazias), vêm seguidos por um inteiro x que representa a coluna da expressão na qual o erro foi identificado.
Nota: A contagem das colunas começa por 1 e espaços e tabulações não são ignorados em nenhum dos casos.

*Tipo 1: "Constante numérica inválida: um dos operandos da expressão está fora da faixa permitida. (Coluna x)"
    Sempre que houver uma constante numérica inteira que é maior que 32767.
    A coluna indicada será o índice do primeiro caractere da constante numérica em relação à expressão original.

    Note que aqui não se considera unários, somente a constante em si, logo se houver uma entrada do tipo -100000000-2, a coluna indicada pelo erro
    será a coluna 2.

*Tipo 2: "Falta operando: em alguma parte da expressão está faltando um operando . (Coluna: x)"
    Sempre que houver falta de operando.
    A coluna indicada será o índice do último operador ou parêntese válido.
    Exemplo: 12* *14
    A coluna indicada pelo erro será a coluna 3.

* Tipo 3: "Operando inválido: existe um operando que não é constante numérica. (Coluna: x)"
	Sempre que houver um caractere que não está na lista de caracteres válidos e nem na de um operando válido
	A coluna indicada será a coluna na qual o caractere está em relação à expressão original

* Tipo 4: "Operador inválido: existe um símbolo correspondente a um operador que não está na lista de operadores válidos. (Coluna: x)"
	Sempre que houver um dos caracteres ',', '<', '>', '=', '.'
	A coluna indicada será a coluna na qual o caractere está em relação à expressão original

* Tipo 5: "Falta operador: em alguma parte da expressão está faltando um operador. (Coluna: x)"
    Sempre que houver falta de operador.
    A coluna indicada será o índice do último operada ou parêntese válido.
    Exemplo: 12  14
    A coluna indicada pelo erro será a coluna 1.

* Tipo 6: "Fechamento de escopo inválido: existe um parêntese fechando sem haver um parêntese abrindo correspondente. (Coluna: x)"
    Sempre que houver um parêntese fechando sem ter um correspondente abrindo.
    A coluna indicada será a coluna na qual o caractere está em relação à expressão original.

* Tipo 7: "Escopo aberto: existe um parêntese de abertura '(' sem um parêntese de fechamento ')' correspondente. (Coluna: x)"
    Sempre que houver um parêntese abrindo ser ter um correspondente fechando.
    A coluna indicada será a coluna na qual o caractere está em relação à expressão original.

* Tipo 8: "Divisão por zero: Existe uma divisão cujo divisor é zero. (Coluna: x)"
    Sempre que houver uma divisão na qual o divisor é zero.
    A coluna indicada será a coluna do operador sobre o qual o erro ocorreu, coluna essa em relação a string original.

* Tipo 9:"Escopo vazio: Parênteses sem nada em seu interior. (Coluna: x)"
	Parênteses de abertura e fechamento contíguos, ou seja, "( )".
	A coluna indicada será a coluna na qual o parêntese de fechamento está em relação a string original

* Tipo 10:"Erro: expressão vazia!!"
	Expressão que só contém espaços ou tabulações.
	A coluna armazenada por esse erro é o inteiro -1, o que é irrelevante.

  @brief Uma instância dessa classe guarda um tipo de erro e a coluna em que ele ocorreu em relação a expressão matemática original.
*/
class Erro{
    std::string str[10]={"Constante numérica inválida: um dos operandos da expressão está fora da faixa permitida. (Coluna: ",
                            "Falta operando: em alguma parte da expressão está faltando um operando . (Coluna: ",
                            "Operando inválido: existe um operando que não é constante numérica. (Coluna: ",
                            "Operador inválido: existe um símbolo correspondente a um operador que não está na lista de operadores válidos. (Coluna: ",
                            "Falta operador: em alguma parte da expressão está faltando um operador. (Coluna: ",
                            "Fechamento de escopo inválido: existe um parêntese fechando sem haver um parêntese abrindo correspondente. (Coluna: ",
                            "Escopo aberto: existe um parêntese de abertura '(' sem um parêntese de fechamento ')' correspondente. (Coluna: ",
                            "Divisão por zero: Existe uma divisão cujo divisor é zero. (Coluna: ",
                            "Escopo vazio: Parênteses sem nada em seu interior. (Coluna: ",
                            "Erro: expressão vazia!!"};
    int erro;
    int col;
    public:
        Erro(int i=1,int col=0);
        inline friend
		std::ostream &operator <<(std::ostream &_os,const Erro &_oErr){
			_os<<_oErr.str[_oErr.erro-1];
			if(_oErr.col>=0)
                _os<<_oErr.col+1<<")";
			return _os;
		}
};
/**
 * @brief armazena uma string simb(um símbolo) e possui vários métodos para identificar propriedades dela.
 */
class Simbolo{
	std::string simb;//!<sim guardará uma string contendo o símbolo
	int coluna;//!<coluna guardará a coluna do símbolo em relação a string original
	public:
        bool isUnrMinus;//!<Diz se simb corresponde
		/**Nota: não funciona com tipos diferente de string ou char
		 * @brief Construtor da classe Simbolo
		 * @param simb será o valor do atributo simb
		 * @param col será o valor do atributo coluna
		 */
		template<typename T>
		Simbolo(T simb="",int col=0);
		/**
		 * @brief Destrutor da classe Simbolo
		 */
		Simbolo();

		/**
		 *@brief Método que diz se um caractere i da string simb é um dígito
		 * @param i corresponde a um índice da string simb
		 * @return true se for dígito e false se não
		 */
		bool isDigit(unsigned int i) const;
		/**
		 *@brief Método que mostra se a string simb corresponde a um operando, ou seja, se é uma constante inteira menos que 32767
		 *@return true se for operando e false se não for
		 */
		bool isOperand(void) const;
		/**Operadores para o projeto são: + - * /  % ^
		 *@brief Método que mostra se a string simb corresponde a um operador
		 *@return true se for operador e false se não for
		 */
		bool isOperator(void) const;
		/** Precedência é a dominância que um operador tem sobre o outro. Nesse método foi considerada na maioria uma precedência reversa: o de maior dominância ficou
		 * com uma precedência menor. Eis a lista de precedências:
		 * Menos unário= 1;
		 * Parênteses= 5;
		 * Potenciação(^)= 2;
		 * Multiplicação(*), divisão(/) e resto de divisão(%)= 3;
		 * Adição(+) e substração(-)= 4
		 * Para os demais caracteres o método retorna -1
		 * @brief Calcula a precedência do símbolo contido nessa classe(stributo simb)
		 * @return a precedência do símbolo
		 */
		int prec() const;
		/**
		 * @brief Calcula o inteiro correspondente à string simb
		 * @see isOperand
		 * @return inteiro correspondente a string simb, caso isOperand for true, ou 0, caso isOperand for false
		 */
		int getInt() const;

        /**Nota: não funciona com tipos diferente de string ou char
		 * @brief Altera o atributo simb
		 * @param str será o novo valor de simb
		 */
		template <typename T>
        void setSimb(T str);
		/**
		 * @brief Retorna o valor do atributo simb
		 * @return o valor do atributo simb
		 */
		std::string getSimb() const;
		/**
		 * @brief Altera o atributo coluna
		 */
		void setCol(int col);
		/**
		 * @brief Retorna o valor do atributo coluna
		 * @param col inteiro que passará a ser o valor do atributo coluna
		 * @return o valor do atributo coluna
		 */
		int getCol(void) const;
		/**
		 * @brief Verifica se simb é um parêntese de abertura
		 * @return true se for um parêntese de abertura, false se não for
		 */
		bool isOpenPar() const;
		/**
		 * @brief Verifica se simb é um parêntese de fechamento
		 * @return true se for um parêntese de fechamento, false se não for
		 */
		bool isClosePar() const;
		/** Repare que se simb for / ou %, b precisa ser não nulo para que seja possível o cálculo(já que b é sempre o segundo operando). Caso tivermos operadores desse tipo e
		 * b for nulo, este método retornará false.
		 * @brief Se simb for um operador, este método calcula o valor da expressão cujos operandos são a e b e o operador é simb
		 * @param a,b são os valores que se deseja calcular
		 * @param res é uma referência a uma variável na qual será escrita o valor da expressão
		 * @return true caso não estiver ocorrido erro no cálculo
		 * @see avalPosFixa, isOperator
		 */
		bool aplic(int a,int b,int &res) const;
		/**Altera o atributo simb igualando a s
		 * @brief Sobrecarga do operator =
		 */
        void operator=(std::string s);
        /**Compara o atributo simb igualando a s
		 * @brief Sobrecarga do operator ==
		 * @return true se s for igual a simb
		 */
		bool operator==(std::string s);
		/**Compara o valor do atributo simb a s
		 * @brief Sobrecarga do operator !=
		 * @return true se s for diferente de simb
		 */
		bool operator!=(std::string s);
		/** Se tentarmos imprimir um objeto dessa classe, será impresso somente o valor de simb
		 * @brief Método para facilitar a impressão de dados.
		 */
		inline friend
		std::ostream &operator <<(std::ostream &_os,const Simbolo &_oSim){
			_os<<_oSim.simb;
			return _os;
		}
};
/**Essa classe tem como objetivo armazenar e gerar valor ou mostrar os erros da expressão matemática inserida no programa principal. Essa expressão matemática deve ser passada
 * como string para o construtor dessa classe e chama-se o método exprValue para calcular o valor da expressão. Caso esse método retorne false é necessário a chamada do método
 * printErros para a amostra dos erros contidos na expressão.
 * @brief Armazena a expressão matemárica e os intermediários de sua avaliação e cálculo, assim como faz as tarefas de analisar e calcular a expressão
 * @see Erro, Simbolo
 */
class Expressao{
    std::string exp;//!<exp guardará uma expressão matemática
    Fila<Simbolo> *tokens;//!<Ponteiro para uma Fila que guardará os tokens de exp
    Fila<Simbolo> *fila;//!<Ponteiro para uma Fila que guardará os tokens no formato pós-fixo
    Fila<Erro> *erros; //!<Ponteiro para uma Fila que guardará os erros na formação da expressão contida em exp, caso houver
	/**A partir de uma expressão pós-fixada gerada por inf2PosFixa, ou seja, a partir do atributo fila, este método calcula o valor da expressão contida nessa classe. Caso haja
	 * alguma divisão na qual o divisor é nulo, esse método incluirá na fila de erros esse erro e retornará 0.
	 * @brief Calcula o valor da expressão matemática exp contida nessa classe
	 * @return o valor da expressão exp ou 0 caso não seja válida
	 * @see tokeniza, inf2PosFixa
	 */
    int avalPosFixa(void);
    /** Esse método armazena em fila(atributo dessa classe) os mesmos simbolos contidos em tokens, porém numa ordem que representa o formato pós-fixado dessa expressão
     * @brief Gera uma fila com símbolos que representam uma expressão pós-fixada
     * @see tokeniza
     */
    void inf2PosFix(void);
    /** Método lê a string exp(que é uma expressão matemática) procurando por erros de sintaxe e por caracteres inválidos. Se encontrar erros, adiciona à fila erros(atributo desta
     * classe), se não adiciona os tokens(termos da expressão matemática) à fila tokens(atributo desta classe) na ordem que eles estão na expressão.
     *
     * Nota: tokens são os termos de uma expressão matemática, como por exemplo:
     * exp="1000+14*(16-12)"
     * os tokens gerados serão: "1000", "+","14","(","16","-","12",")"
     * Note que esses tokens gerados serão do tipo Simbolo.
     * @brief Método que gera uma fila símbolos a partir da string exp
     * @see Erro, inf2PosFixa, avalPosFixa, tokens, erros
     * @return true se for uma expressão válida e false se não
     */
    bool tokeniza(void);
    /**
    * @brief Método limpa os atributos tokens, fila e erros
    */
    void clear(void);

    public:
        /**@brief Construtor de Expressao
        * @param std::string que será o valor do atributo exp (A expressão matemática que se deseja trabalhar)
        */
        Expressao(std::string exp="");
        /**@brief Destrutor de Expressao
        */
        ~Expressao();

        /**@brief Calcula o resultado da expressão
        * @param res será o inteiro correspondente ao resultado da expressão exp, caso a função retorne true
        * @return true se não houver erros na expressão ou false caso exista erros
        */
        bool exprValue(int &res);
        /**@brief Retorna o valor do atributo exp
        * @return atributo exp
        */
        std::string getExp(void);
        /**@brief Modifica o atributo exp
        * @param e será o novo valor do atributo exp
        */
        void setExp(std::string e);
		/**@brief Verifica se a expressão contém algum caractere além de espaços e tabulações
        * @return booleano true se só houver espaços e tabulações e false se houver pelo menos um diferente
        */
        bool isEmptyExp();


        //------------------------------------------------------
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
        /** Para o projeto, operadores válidos são '+','-'.'*','/','^','%'
        * @brief Avalia se um caractere é um operador válido
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for um operador válido e false se não
        */
        bool isValOpt(unsigned int c);
        /** Para o projeto, operadores não válidos são '>','<','=','.',','
        * @brief Avalia se um caractere é um operador não válido
        * @param c é um índice qualquer do atributo exp
        * @return true se exp[c] for um operador não válido e false se não
        */
        bool isnValOpt(unsigned int c);
        /**Para o projeto, caracteres ignorável são tabulações(código ASCII 9) e espaços(código ASCII 32)
         * @brief Avalia se um caractere é ignorável
         * @param c é um índice qualquer do atributo exp
         * @return true se exp[c] for caractere ignorável e false se não
        */
        bool isIgnChar(unsigned int c);
        /**Para o projeto, caracteres válidos são todos '(',')','+','-'.'*','/','^','%',tabulações(código ASCII 9),
        * espaços(código ASCII 32) e dígitos de 0 a 9.
        * @brief Avalia se um caractere válido para o programa
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
        /**@brief Método que retorna uma substring de exp baseado em dois índices
        * @param i o índice da string exp que determinará o índice inicial dessa substring
        * @param j o índice da string exp tal que
        * @return retorna uma substring com índice inicial i e final j-1, baseados na string inicial exp
        */
        std::string subStr(unsigned int i,unsigned int j);
        /**Este método lê todos os erros contidos no atributo Fila<Simbolo> erros e imprime no objeto pOut passado como parâmetro
         * @brief Método que imprime os erros gerados pela expressão, caso existam
         * @param um ponteiro do tipo std::ostream para onde a impressão dos elementos da fila de erros serão direcionadas
         * @see exprValue
        */
        void printErros(std::ostream* pOut);
};


#endif
