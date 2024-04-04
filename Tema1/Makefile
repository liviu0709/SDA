CFLAGS=-Wall -Werror

run: tema1
	./tema1

tema1: main.c coada.c tren.c operatiiSearch.c
	gcc main.c coada.c tren.c operatiiSearch.c $(CFLAGS) -o tema1

clean:
	rm -f tema1

valgrind: tema1
	valgrind --leak-check=yes --track-origins=yes ./tema1
	