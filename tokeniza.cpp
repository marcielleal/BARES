bool tokeniza(Expressao entrada,Fila<Simbolo> &tokens,Fila<Erro> &erros){
    Pilha<unsigned int> contPar;                            //Pilha controladora de parenteses
    Simbolo token;                                        //Buffer do token
    bool isLastOpt=true;                               //is the last a operator?
    bool isLastUnrMinus=false;                               //is the last a operator?
    for(unsigned int i=0;i<entrada.getExp().length();i++){
        if(entrada.isValChar(i)){
            if(entrada.isDigit(i)){
                if(!isLastOpt&&token!="("){
                    erros.push(Erro(5,i-1));
                }
                if(!isLastUnrMinus)
                    token="";

                int aux=extSintFromStr(token,entrada.getExp().substr(i,entrada.getExp().length()));
                if(!isValOpd(token)){
                    erros.push(Erro(1,i));
                    token="0";
                }
                token.setCol(i);
                tokens.push(token);
                i+=aux;
                isLastOpt=0;
                isLastUnrMinus=0;
            }else if(entrada.isParnt(i)){////////
                if(entrada.getExp()[i]=='('){
                    if(!isLastOpt&&token!="(")
                        erros.push(Erro(5,i));
                    contPar.push(i);
                }else{
                    if(isLastOpt&&!tokens.empty())
                        erros.push(Erro(2,i));       //ERROR: ultimo eh operador
                    if(!contPar.empty()){                   //Se houver parentese abraindo
                        if(token=="(")
                            erros.push(Erro(9,i));
                        contPar.pop();
                    }else
                        erros.push(Erro(6,i));       //ERROR: fechando sem abrir
                }

                if(!isLastUnrMinus)
                    token="";
                token+=entrada.getExp()[i];
                token.setCol(i);
                tokens.push(token);

                isLastOpt=0;
                isLastUnrMinus=0;
            }else if(isValOpt(entrada.getExp()[i])){
                if(isNotMinus(entrada.getExp()[i])){
                    if(!isLastOpt){
                        if(!contPar.empty()){
                            if(token=="(")
                                erros.push(Erro(2,i));
                        }
                    }else
                        erros.push(Erro(2,i));

                    if(!isLastUnrMinus)
                        token="";
                    token+=entrada.getExp()[i];
                    isLastUnrMinus=0;
                }else{
                    std::string num;
                    int aux=extSMinusFromStr(num,entrada.getExp().substr(i,entrada.getExp().length()));
                    if(token.length()>0){
                        if(isLastOpt||token=="("){
                            isLastUnrMinus=1;
                        }else isLastUnrMinus=0;
                    }token=num;
                    i+=aux;
                }
                if(!isLastUnrMinus&&token.length()>0){
                    token.setCol(i);
                    tokens.push(token);
                }
                isLastOpt=1;
            }
        }else if(isnValOpt(entrada.getExp()[i])){
            erros.push(Erro(4,i+1));
            isLastOpt=0;
            if(!isLastUnrMinus)
                token="";
            token+=entrada.getExp()[i];
            token.setCol(i);
            tokens.push(token);
            isLastUnrMinus=0;
        }else if(entrada.getExp()[i]=='\n'){
            if(isLastOpt)
                erros.push(Erro(2,i));
            if(!contPar.empty())
                erros.push(Erro(7,i));
            break;
        }else{
            erros.push(Erro(3,i+1));
            isLastOpt=0;
            if(!isLastUnrMinus)
                token="";
            token+=entrada.getExp()[i];
            token.setCol(i);
            tokens.push(token);
            isLastUnrMinus=0;
        }
    }

    if(erros.empty())
        return true;
    while(!tokens.empty()){
        tokens.pop();
    }
    return false;
}
