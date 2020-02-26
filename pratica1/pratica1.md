# Prática 1 - Confidencialidade e Cifras Clássicas

## Enunciado
Caro(a) estudante,

Submeta os exercícios abaixo via Tidia. 

Você pode fazer com ajuda de colegas, mas sua solução e entrega deve ser individual.

Após a data limite, há uma tolerância para entrega em atraso até o domingo seguinte.
  
Codifique a cifra de Vigenère, usando alguma linguagem de programação que você conheça.

Use a expressão algébrica vista em aula, com aritmética modular (resto da divisão) e codificação ASCII para entrada e saída.

A implementação pode ser bem simplificada, em linha de comando e com a chave fixa no próprio código.
Entregue o código de duas funcionalidades: cifrar e decifrar

Responda com suas palavras: por que a expressão algébrica equivale ao uso da Tabela de Vigenère? 
  
Desafio: faça um código que tenta descobrir a chave de um texto cifrado com cifra de Vigenère, usando as simplificações e premissas a seguir:
  
Mensagens relativamente longas cifradas com chave curtas podem preservar a seguinte característica: o caractere mais frequente de todo o texto original também é o mais frequente em todas as posições da chave (ao segmentar o texto original em blocos de tamanho da chave). Em anexo, há dois exemplos de mensagens (texto1.txt e texto2.txt) em que o caractere “espaço em branco” é o mais frequente em todas as posições para chaves com tamanhos pequenos (quatro, por exemplo).

Considerando que Ci = ( Pi + Ki ) mod (tamanho do alfabeto usado), o caractere mais frequente de um texto cifrado guarda uma relação trivialmente dedutível com a chave e o caractere mais frequente do texto original (Plain text). Qual é?

Entregue um código que descobre a chave, dado um texto cifrado com Vigenère com uma chave de tamanho fixo (por exemplo 4). Você pode supor que o texto original tem o caractere espaço como o mais frequente.
Responda: qual foi a chave usada para cifrar o texto texto_cripto.txt?

## Respostas

### Codificando a cifra
A cifra de Vigenère foi codificada em C no arquivo `vigenere.c`. Ela utiliza como chave a palavra do arquivo `chave.txt` e codifica e decodifica o conteúdo do arquivo `mensagem.txt`.

Foi necessário alterar a expressão algébrica para cifrar a mensagem. Seja $n$ o tamanho do alfabeto, a expressão $C_i=(M_i+Ki)\%n+65$ funciona para o alfabeto `A` até `Z` em ASCII pois $M_i+K_i=(65+x)+(65+y)=130+x+y$ (onde $x$ e $y$ são os _offsets_ de `A` até $M_i$ e $K_i$) e $n=26$, logo $(130+x+y)\%n=(x+y)\%n$.

Porém, ao alterar o alfabeto para incluir outros caracteres, como do `space` até `z`, essa propriedade deixa de valer. Logo a expressão foi alterada para $C_i=(M_i+Ki-2\times32)\%n+32$, onde $32$ é o valor ASCII do `space` e com $n=91$. A saída do programa criado foi comparada com o resultado do [cryptii](https://cryptii.com/pipes/vigenere-cipher).

### Equivalência algébrica
A tabela é construída de modo que o alfabeto 'inicia' com o símbolo da chave. Isso pode ser interpretado como a distância do primeiro símbolo do alfabeto até o símbolo da chave, assim podemos somar a posição no alfabeto do símbolo que queremos cifrar com a posição do alfabeto do símbolo da chave. Como essa soma pode sair do alfabeto, é necessário pegar o resto da divisão com o tamanho do alfabeto.

### Descobrindo a chave
Seja $k$ o tamanho da chave. Temos que cada $k_\text{ésimo}$ símbolo da mensagem é cifrado com o mesmo símbolo da chave. Logo, separando a mensagem em $k$ submensagens, nas quais cada uma foi codificada com o mesmo símbolo da chave, $K_i$, simplificamos o problema para $k$ cifras de César, que pode ser atacada com análise de frequência.

Como podemos assumir que o símbolo da mensagem original mais frequente é o espaco, conseguimos descobrir um símbolo da chave por submensagem. Basta pegar o símbolo cifrado mais frequente, $C_{freq}$, de cada submensagem e assumir que ele é o `space`, logo $K_i=(C_{freq}-32)\%n+32$

A chave descoberta do `texto_cripto.txt` obtida através do `descobrirChave.c` foi `eaOm`. Embora eu acredite que o resultado não está certo, em todos os testes que realizei com textos e chaves conhecidas o resultado era certo.