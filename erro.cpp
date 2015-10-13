class Erro{

    std::string str[]={"Constante numérica inválida: um dos operandos da expressão está fora da faixa permitida. (Coluna: ",
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
        inline friend
		std::ostream &operator <<(std::ostream &_os,const Erro &_oErr){
			_os<<_oErr.str[_oErr.erro-1]<<col<<")";
			return _os;
		}
};
Erro::Erro(int i,int col){
    this->erro=i;
    this->col=col;
}
