#ifndef TRIE_H
#define TRIE_H

/*Struct para representar um nodo da trie.*/
typedef struct nodo {
    char caractere; //Caractere armazenado no nó (ASCII)
    char *nomeArquivo; //Nome do(s) arquivo(s) da palavra
    struct nodo *filhos[52]; //Ponteiros para os filhos (letras minúsculas e maiúsculas)
    struct nodo *pai; //Ponteiro para o pai do caractere
} nodo;

/*Inicializa uma nova trie alocando memória para 
o nodo raiz e definindo um filho para cada letra 
inicial possível das palavras.*/
nodo *inicializaTrie();

/*Função auxiliar para o processo de inserção de nomes
de arquivos ao final de cada caractere das palavras.*/
int contemNomeArquivo(const char *nomesArquivos, const char *nomeArquivo);

/*Insere uma palavra válida (com mais de quatro caracteres que
correspondam à letras maiúsculas ou minúsculas) na trie.*/
void insereChave(nodo *raiz, char *chave, char *nomeArqTexto);

/*Libera a memória alocada para a trie.*/
void destroiTrie(nodo *raiz);

#endif
