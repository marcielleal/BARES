
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
class Simbolo{
	std::string *simb;
	int *coluna;
	public:
        bool isUnarMinus;
		Simbolo(std::string simb="",int col=0);
		 ~Simbolo();
		bool isOperand(void) const;
		bool isOperator(void) const;
		int prec() const;
		int getInt() const;		//If osOperand true

        template <typename T>
        void setSimb(T str);
		std::string getSimb() const;

		void setCol(int col);
		int getCol(void) const;

		bool isOpenPar() const;
		bool isClosePar() const;

		bool aplic(int a,int b,int &res) const;

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
    std::string exp;//!<exp guardará uma expressão matemática
    Fila<Simbolo> tokens;//!<Fila que guardará os tokens de exp
    Fila<Simbolo> fila;//!<Fila que guardará os tokens no formato pós-fixo
    Fila<Erro> erros;//!<Fila que guardará os erros na formação da expressão contida em exp, caso houver

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
    int avalPosFixa(void);

    public:
        void inf2PosFix(void);
        bool tokeniza(void);
        /**@brief Construtor de Expressao*/
        Expressao(std::string exp="");

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
         /**@brief Avalia se uma substring de exp, que representa um inteiro, está na faixa de -32.767 a 32.767
         * @param i é o índice inicial da substring
         * @param f é o índice final da substring+1
         * @see extSintFromStr
         * @return true se exp[c] o inteiro da faixa, false se não estiver
         */
        bool isValOpd(unsigned int i, unsigned int f);
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
        /**@brief Extrai do atributo exp uma substring
         * @param num é um objeto do tipo Simbolo que guardará a sequência de dígitos
         * @param i é o índice de exp que será o índice 0 da substring
         * @param j é o tamanho da substring
         * @return a substring do atributo exp com as expecificações citadas
         */
        std::string subStr(unsigned int i,unsigned int j);
        /**@brief Extrai do atributo exp uma sequência de dígitos contíguos
         * @param num é um objeto do tipo Simbolo que guardará a sequência de dígitos
         * @param inicio é o índice de exp a partir do qual o método procurará mais dígitos contíguos
         * @see tokeniza
         * @return o índice do último dígito contíguo ao dígito do índice inicial
         */
        int extSintFromStr(Simbolo &num,unsigned int inicio);
        /**@brief Analisa uma sequência de caracteres '-' numa substring de exp
         * Mesmo se tivermos uma sequência de caracteres '-' numa expressão, como por exemplo, "1----2", ela continua válida, pois
         * boa parte desses caracteres '-' são unários. O objetivo dessa função é pegar uma sequência de caracteres '-' e torná-la
         * menos redundante. É feito retirando o excesso de unários e transformando os em único unário ou retirando-os, já que uma
         * sequência ímpar de unários é o mesmo que termos um único e uma sequência par é o mesmo que não termos unário algum.
         * No caso do exemplo, temos 3 '-' unários e um '-' operador, a função percorreria a substring em inicio=2 e guardaria em
         * num o valor de '-' que será inserido na fila de tokens posteriormente.
         * Repare que ao percorrer a substring, espaços e tabulações são ignorados.
         * @param num é um objeto do tipo Simbolo que guardará "" "-"
         * @param inicio é o índice de exp a partir do qual o método procurará mais caracteres '-'
         * @see tokeniza
         * @return o índice do último caractere '-' seguido ao caractere do índice inicial
         */
        int extSMinusFromStr(Simbolo &num,unsigned int inicio);
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
