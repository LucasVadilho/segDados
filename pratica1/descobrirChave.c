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

    char* mensagem = lerArquivo("texto_cripto.txt");
    int tamanhoMensagem = strlen(mensagem);
    int tamanhoSubMensagem = tamanhoMensagem / tamanhoChave;
    
    char* mensagem1 = malloc(sizeof(char) * tamanhoSubMensagem);
    char* mensagem2 = malloc(sizeof(char) * tamanhoSubMensagem);
    char* mensagem3 = malloc(sizeof(char) * tamanhoSubMensagem);
    char* mensagem4 = malloc(sizeof(char) * tamanhoSubMensagem);

    for(int i = 0; i < tamanhoSubMensagem; i++){
        mensagem1[i] = mensagem[tamanhoChave * i];
        mensagem2[i] = mensagem[tamanhoChave * i + 1];
        mensagem3[i] = mensagem[tamanhoChave * i + 2];
        mensagem4[i] = mensagem[tamanhoChave * i + 3];
    }
    
    char chave[4];

    char m1 = maisFrequente(mensagem1);
    chave[0] = (m1 - ' ') % tamanhoAlfabeto + ' ';

    char m2 = maisFrequente(mensagem2);
    chave[1] = (m2 - ' ') % tamanhoAlfabeto + ' ';

    char m3 = maisFrequente(mensagem3);
    chave[2] = (m3 - ' ') % tamanhoAlfabeto + ' ';

    char m4 = maisFrequente(mensagem4);
    chave[3] = (m4 - ' ') % tamanhoAlfabeto + ' ';

    char* decifrada = (char*) malloc(sizeof(char) * tamanhoMensagem);

    for(int i = 0; i < tamanhoMensagem; i++){
        decifrada[i] = (mensagem[i] - chave[i % tamanhoChave] + tamanhoAlfabeto) % tamanhoAlfabeto + primeiroChar;
    }

    printf("Mensagem cifrada: %s\n", mensagem);
    printf("Chave descoberta: %s\n", chave);
    printf("Mensagem decifrada: %s\n", decifrada);
}