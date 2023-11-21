CFLAGS = -Wall -std=c99 -g --debug
LDFLAGS = -lm

CC = gcc

	objects = main.o aplicacoes.o trie.o

main: main.o aplicacoes.o trie.o
	$(CC) -o main main.o aplicacoes.o trie.o $(LDFLAGS)

aplicacoes.o: aplicacoes.c
	$(CC) -c $(CFLAGS) aplicacoes.c

trie.o: trie.c
	$(CC) -c $(CFLAGS) trie.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) main