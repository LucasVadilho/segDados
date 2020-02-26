#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* lerArquivo(char* nomeArquivo){
    FILE *fp = fopen(nomeArquivo, "r");
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char c;
    char* mensagem = (char*)malloc(sz * sizeof(char));

    for(int i = 0; i < sz; i++){
        c = fgetc(fp);
        if(c != EOF){
            mensagem[i] = c;
        }
    }

    return(mensagem);
}

void printAlfabeto(char primeiroChar, char ultimoChar){
    for(int i = primeiroChar; i <= ultimoChar; i++){
        printf("%c", i);
    }
    printf("\n");
}

void main(){
    int primeiroChar = ' ';
    int ultimoChar = 'z';
    int tamanhoAlfabeto = ultimoChar - primeiroChar + 1;

    char* chave = lerArquivo("chave.txt");
    size_t tamanhoChave = strlen(chave);

    char* mensagem = lerArquivo("mensagem.txt");
    size_t tamanhoMensagem = strlen(mensagem);

    char* cifrada = (char*) malloc(sizeof(char) * tamanhoMensagem);

    for(int i = 0; i < tamanhoMensagem; i++){
        cifrada[i] = (mensagem[i] + chave[i % tamanhoChave] - 2 * primeiroChar) % tamanhoAlfabeto + primeiroChar;
    }

    char* decifrada = (char*) malloc(sizeof(char) * tamanhoMensagem);

    for(int i = 0; i < tamanhoMensagem; i++){
        decifrada[i] = (cifrada[i] - chave[i % tamanhoChave] + tamanhoAlfabeto) % tamanhoAlfabeto + primeiroChar;
    }

    printf("Estamos utilizando o seguinte alfabeto: ");
    printAlfabeto(primeiroChar, ultimoChar);

    printf("Mensagem original: %s\n", mensagem);
    printf("Chave: %s\n", chave);
    printf("Mensagem cifrada: %s\n", cifrada);
    printf("Mensagem decifrada: %s\n", decifrada);
}