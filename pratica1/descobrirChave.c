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

char maisFrequente(char* mensagem){
    int tamanhoMensagem = strlen(mensagem);
    int alfabeto[255] = {0};

    for(int i = 0; i < tamanhoMensagem; i++){
        alfabeto[mensagem[i]]++;
    }
    
    int maisFrequente = 0;
    for(int i = 1; i < 255; i++){
        if(alfabeto[i] > alfabeto[maisFrequente]){
            maisFrequente = i;
        }
    }

    return(maisFrequente);
}

void main(){
    int primeiroChar = ' ';
    int ultimoChar = 'z';

    int tamanhoChave = 4;
    int tamanhoAlfabeto = ultimoChar - primeiroChar + 1;

    char* mensagem = lerArquivo("texto_cripto_chave04.txt");
    int tamanhoMensagem = strlen(mensagem);
    int tamanhoSubMensagem = tamanhoMensagem / tamanhoChave;

    char* subMensagem = malloc(sizeof(char) * tamanhoSubMensagem);
    char chave[4];

    for(int i = 0; i < tamanhoChave; i++){
        for(int j = 0; j < tamanhoSubMensagem; j++){
            subMensagem[j] = mensagem[tamanhoChave * j + i];
        }
        char maxFreq = maisFrequente(subMensagem);
        chave[i] = (maxFreq - ' ') % tamanhoAlfabeto + ' ';
    }

    char* decifrada = (char*) malloc(sizeof(char) * tamanhoMensagem);

    for(int i = 0; i < tamanhoMensagem; i++){
        decifrada[i] = (mensagem[i] - chave[i % tamanhoChave] + tamanhoAlfabeto) % tamanhoAlfabeto + primeiroChar;
    }

    printf("Mensagem cifrada: %s\n", mensagem);
    printf("Chave descoberta: %s\n", chave);
    printf("Mensagem decifrada: %s\n", decifrada);
}