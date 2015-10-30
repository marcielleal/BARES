# Projeto BARES
Avaliador de expressões aritméticas simples

###Descrição
Realiza a análise de expressões aritméticas contidas em um arquivo de texto, tal que, cada expressão está em uma linha diferente. 
Se forem expressões válidas, o programa calcula seus valores e envia para um arquivo de saída ou para a saída padrão.
Se não forem expressões válidas, envia uma lista de erros para um arquivo de saída ou para a saída padrão(cada erro está em uma linha diferente).

Nota: expressões válidas para o projeto, são todas as que não envolvam nada além de números inteiros (entre -32767 e 32767), operadores binários ('+', '-', '*', '/', '%', '^'), menos unário('-') e parênteses e que estejam sintaticamente corretas.

###Autores:
* Edye Lautter Cunha Oliveira - abcdedye@gmail.com

* Marciel Manoel Leal - marcielmanoel15@gmail.com

###Compilação

Dentro da pasta BARES:
* make clean
* make

###Execução

Dentro da pasta BARES:
./bin/bares arquivo_de_entrada [arquivo_de_saida]

###Lista de erros que o programa trata
#####(Coluna x) indica a coluna na qual se encontra o erro
* Constante numérica inválida: um dos operandos da expressão está fora da faixa permitida. (Coluna x)
* Falta operando: em alguma parte da expressão está faltando um operando . (Coluna: x)
* Operando inválido: existe um operando que não é constante numérica. (Coluna: x)
* Operador inválido: existe um símbolo correspondente a um operador que não está na lista de operadores válidos. (Coluna: x)
* Falta operador: em alguma parte da expressão está faltando um operador. (Coluna: x)
* Fechamento de escopo inválido: existe um parêntese fechando sem haver um parêntese abrindo correspondente. (Coluna: x)
* Escopo aberto: existe um parêntese de abertura '(' sem um parêntese de fechamento ')' correspondente. (Coluna: x)
* Divisão por zero: Existe uma divisão cujo divisor é zero. (Coluna: x)
* Parênteses desnecessários: Parênteses sem nada em seu interior. (Coluna: x)
* Erro: expressão vazia!!

###Disponível em: 
https://github.com/marcielleal/BARES
