class Expressao{
    std::string exp;
    public:
        Expressao(std::string exp);
        std::string getExp(void);
        bool tokeniza(Expressao entrada,Fila<Simbolo> &tokens,Fila<Erro> &erros);
        bool inf2PosFix(Fila<Simbolo> &fila);
        int avalPosFixa(Fila<Simbolo> fila);

        bool isValOpd(std::string str);
        bool isParnt(unsigned int c);
        bool isValOpt(unsigned int c);
        bool isnValOpt(unsigned int c);
        bool isIgnChar int(unsigned int c);
        bool isValChar int(unsigned int c);
        bool isNotMinus(unsigned int c);

        int extSintFromStr(std::string &num,std::string str);
        int extSMinusFromStr(std::string &num,std::string str);
};
std::string Expressao::getExp(void);
bool Expressao::tokeniza(Expressao entrada,Fila<Simbolo> &tokens,Fila<Erro> &erros);
bool Expressao::inf2PosFix(Fila<Simbolo> &fila);
int Expressao::avalPosFixa(Fila<Simbolo> fila);

bool Expressao::isValOpd(){
    /**
    *Expressao::is valid operand
    */
    int v=atoi(this->c_str());
    if(v>32767||v<(-32767)) return false;
    return true;
}

std::string errorString(int i,int col){
    /**
    * Retorna a string correspondente ao erro do tipo i na coluna col
    */
    std::string str[]={"Constante numérica inválida: um dos operandos da expressão está fora da faixa permitida. (Coluna: ",
                        "Falta operando: em alguma parte da expressão está faltando um operando . (Coluna: ",
                        "Operando inválido: existe um operando que não é constante numérica. (Coluna: ",
                        "Operador inválido: existe um símbolo correspondente a um operador que não está na lista de operadores válidos. (Coluna: ",
                        "Falta operador: em alguma parte da expressão está faltando um operador. (Coluna: ",
                        "Fechamento de escopo inválido: existe um parêntese fechando sem haver um parêntese abrindo correspondente.",
                        "Escopo aberto: existe um parêntese de abertura '(' sem um parêntese de fechamento ')' correspondente.",
                        "Divisão por zero: Houve uma divisão cujo quociente é zero. Coluna: ",
                        "Parênteses desnecessários: Parênteses sem nada em seu interior. Coluna: "};
    return str[i-1]+to_string(col)+")";
}

int extSintFromStr(Simbolo &num,int inicio){
    /**
    * Extrai um inteiro de uma string e retorna o indice no qual aparece um caractere na string que nao e mais digito
    */
    unsigned int i;
    for(i=inicio;i<this->getExp().length()&&this->isDigit(i)&&this->getExp()[i]!='\n';i++);

    num.setSimb(this->get.substr(0,i));
    num.setCol(--i);
    return i;
}

bool Expressao::isValOpd(int i,int f){         //Provável bug na conversao de string pra inteiro
    /**
    * is valid operand
    */
    int v=atoi(this->getExp().substr(i,f).c_str());
    if(v>32767||v<(-32767)) return false;
    return true;
}
bool Expressao::isParnt(unsigned int c){
    if(this->getExp[c]=='('||this->getExp[c]==')')
        return true;
    return false;
}

bool Expressao::isValOpt(unsigned int c){
    if(this->getExp[c]=='%'||this->getExp[c]=='*'||this->getExp[c]=='+'||this->getExp[c]=='-'||this->getExp[c]=='/'||this->getExp[c]=='^')
        return true;
    return false;
}
bool Expressao::isnValOpt(unsigned int c){                             //Se later
    if(this->getExp[c]==','||this->getExp[c]=='.'||this->getExp[c]=='<'||this->getExp[c]=='>'||this->getExp[c]=='=')
        return true;
    return false;
}
bool Expressao::isValChar(unsigned int c){
    if(isdigitthis->getExp[c])||isValOptthis->getExp[c])||isIgnCharthis->getExp[c])||isParntthis->getExp[c]))
        return true;
    return false;
}
bool isNotMinus(unsigned int c){
    return this->getExp[c]=='-'? false:true;
}
int extSMinusFromStr(Simbolo &num){
    /**
    * Analisa uma sequencia de operadores '-'
    */
    unsigned int i;
    unsigned int contIgnC=0;
    for(i=0;i<this->getExp().length()&&
            (!this->isNotMinus(i)||this->isIgnChar(i))
            &&this->getExp()[i]!='\n';i++)
                if(this->isIgnChar(i)) contIgnC++;
    if((this->getExp.substr(0,i).length()-contIgnC)%2==0) num.setSimb("");
    else num.setSimb("-");
    num.setCol(--i);
    return i;
}
