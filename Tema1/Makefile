CFLAGS=-Wall -Werror

run: build
	./tema1

build: main.c coada.c tren.c operatiiSearch.c
	gcc main.c coada.c tren.c operatiiSearch.c $(CFLAGS) -o tema1

clean:
	rm -f tema1

valgrind: build
	valgrind --leak-check=yes --track-origins=yes ./tema1
