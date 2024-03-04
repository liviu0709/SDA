build:
	gcc -o lista main.c functiiLista.c
run: build
	./lista
clean:
	rm lista
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./lista