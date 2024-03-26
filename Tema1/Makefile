CFLAGS=-Wall -Werror

run: main
	./main

main: main.c coada.c tren.c operatiiSearch.c
	gcc main.c coada.c tren.c operatiiSearch.c $(CFLAGS) -o main

clean:
	rm -f main

valgrind: main
	valgrind --leak-check=yes --track-origins=yes ./main
