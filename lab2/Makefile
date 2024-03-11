build:
	gcc -g -o main main.c functiiLista.c

debug: main.c
	gcc -g -o debug main.c functiiLista.c

run: build
	./main

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./lista