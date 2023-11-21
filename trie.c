#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

#define TAM_MAX_NOME_ARQ 256

/*Inicializa uma nova trie alocando memória para 
o nodo raiz e definindo um filho para cada letra 
inicial possível das palavras.*/
nodo *inicializaTrie() { 
    nodo *raiz = (nodo *)malloc(sizeof(nodo)); 
    raiz->caractere = '\0';
    raiz->nomeArquivo = NULL;

    for (int i = 0; i < 52; i++) 
        raiz->filhos[i] = NULL; 
    
    return raiz;
}

/*Função auxiliar para o processo de inserção de nomes
de arquivos ao final de cada caractere das palavras.*/
int contemNomeArquivo(const char *nomesArquivos, const char *nomeArquivo) {
    const char *ptr = strstr(nomesArquivos, nomeArquivo);
    return (ptr != NULL);
}

/*Insere uma palavra válida (com mais de quatro caracteres que
correspondam à letras maiúsculas ou minúsculas) na trie.*/
void insereChave(nodo *raiz, char *chave, char *nomeArqTexto) {
    nodo *atual = raiz;
    int indiceCaractere, tam;
    char *palavra = chave;

    /*Remove da string caracteres que 
    não sejam letras maiúsculas ou 
    minúsculas (não acentuadas)*/
    int k = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (isalpha(palavra[i]))
            palavra[k++] = palavra[i];
    }
    palavra[k] = '\0';
    tam = strlen(palavra);

    /*Faz a inserção de caracteres e (se 
    necessário) a criação de novos nodos*/
    for (int i = 0; i < tam; i++) {

        /*Transforma um caractere ASCII da 
        palavra em índice de vetor filhos*/
        if (palavra[i] >= 'A' && palavra[i] <= 'Z')
            indiceCaractere = palavra[i] - 65;
        else if (chave[i] >= 'a' && palavra[i] <= 'z')
            indiceCaractere = palavra[i] - 71;

        /*Se o caractere recebido é uma letra válida, e a que 
        o origina tem mais de 4 símbolos (letras), insere-a 
        no nodo correspondente de acordo com seu índice*/
        if (tam >= 4 && atual) {
            if (!atual->filhos[indiceCaractere]) {
                atual->filhos[indiceCaractere] = inicializaTrie();
                atual->filhos[indiceCaractere]->caractere = chave[i];
            }
            atual = atual->filhos[indiceCaractere];

            if (i == tam - 1) {
                /*Se for o último caractere da palavra, 
                adiciona o nome do arquivo*/
                if (atual->nomeArquivo == NULL) {
                    size_t tamAux = strlen(nomeArqTexto);
                    if (tamAux < TAM_MAX_NOME_ARQ - 3) { 
                        atual->nomeArquivo = (char *)malloc(tamAux + 3);  
                        
                        if (atual->nomeArquivo != NULL)
                            sprintf(atual->nomeArquivo, "[%s]", nomeArqTexto);
                        else
                            fprintf(stderr, "Falha na alocação de memória para nomeArquivo.\n");
                    } else
                        fprintf(stderr, "O nome do arquivo é muito longo para ser armazenado.\n");
                
                } else {

                    /*Verifica se o nome do arquivo já está na lista*/
                    if (!contemNomeArquivo(atual->nomeArquivo, nomeArqTexto)) {
                        size_t tamNomeArquivo = strlen(atual->nomeArquivo);
                        size_t novoTam = tamNomeArquivo + strlen(nomeArqTexto) + 3;
                        atual->nomeArquivo = (char *)realloc(atual->nomeArquivo, novoTam);
                        if (atual->nomeArquivo != NULL) {
                            strcat(atual->nomeArquivo, "[");
                            strcat(atual->nomeArquivo, nomeArqTexto);
                            strcat(atual->nomeArquivo, "]");
                        } else {
                            fprintf(stderr, "Falha na realocação de memória para nomeArquivo.\n");
                        }
                    }
                }
            }
        }
    }
}

/*Libera a memória alocada percorrendo recursivamente 
todos os nodos da trie e liberar a memória alocada 
para eles e para suas respectivas strings nomeArquivo.*/
void destroiTrie(nodo *raiz) {
    if (raiz) {
        for (int i = 0; i < 52; i++) {
            if (raiz->filhos[i] != NULL)
                destroiTrie(raiz->filhos[i]);
        }
        free(raiz->nomeArquivo);
        free(raiz);
    }
}
