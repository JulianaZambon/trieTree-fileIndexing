#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "aplicacoes.h"

/*Função que insere um texto em uma
base de dados em formato de trie.*/
void insereTextoNaTrie(FILE *base, FILE *texto, char *nomeArqTexto, nodo *raiz) {
    char linha[1024];
    char *palavra;

    /*Lê linha por linha do arquivo 
    e insere suas palavras na trie*/
    while (fgets(linha, sizeof(linha), texto) != NULL) {
        palavra = strtok(linha, " \t\n"); 

        while (palavra) {
            insereChave(raiz, palavra, nomeArqTexto);
            palavra = strtok(NULL, " \t\n");
        }
    }

    char armazenaPalavra[1024];
    escreveTrieNaBase(base, raiz, armazenaPalavra, 0);
}

/*Função auxiliar para escrever trie no 
arquivo base de maneira recursiva.*/
void escreveTrieNaBase(FILE *base, nodo *atual, char palavra[], int cont) {
    if (atual->nomeArquivo != NULL) {
        char *nomesArquivos = strtok(atual->nomeArquivo, ",");
        
        palavra[cont] = '\0';

        /*Se a palavra não corresponder a um prefixo,
        faz a impressão seguida de seu arquivo origem*/
        if (strlen(palavra) > 1) {
            fprintf(base, "%s", palavra);

            while (nomesArquivos != NULL) {
                fprintf(base, "%s", nomesArquivos);
                nomesArquivos = strtok(NULL, ",");
            }
            fprintf(base, "\n");
        }
    }

    for (int i = 0; i < 52; i++) {
        if (atual->filhos[i] != NULL) {
            palavra[cont] = atual->filhos[i]->caractere;
            escreveTrieNaBase(base, atual->filhos[i], palavra, cont + 1);
        }
    }
}

/*Procura o caractere fornecido em uma base de dados que 
contém a estrutura trie (procura caractere entre simbolo e 
faz um contador para verificar cada palavra encontrada).*/
void procuraPalavrasPorPrefixo(FILE *base, char *prefixo) {
    char linha[100];
    char *arquivo;
    char arquivosImpressos[50][100];
    int contArquivosImpressos = 0;

    while (fgets(linha, sizeof(linha), base) != NULL) {
        if (linha[0] == prefixo[0]) {
            arquivo = strchr(linha, '[');
            
            /*Se certifica de não realizar a 
            impressão de arquivos duplicados*/
            while (arquivo != NULL) {
                char nomeArquivo[50];
                sscanf(arquivo, "[%[^]]", nomeArquivo);

                int duplicado = 0;
                for (int i = 0; i < contArquivosImpressos; i++) {
                    if (strcmp(nomeArquivo, arquivosImpressos[i]) == 0) {
                        duplicado = 1;
                        break;
                    }
                }
                if (!duplicado) {
                    printf("%s %s\n", prefixo, nomeArquivo);
                    strcpy(arquivosImpressos[contArquivosImpressos], nomeArquivo);
                    contArquivosImpressos++;
                }

                arquivo = strchr(arquivo + 1, '[');
            }
        }
    }
}