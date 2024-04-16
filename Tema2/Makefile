CFLAGS=-Wall -Werror -g

build: main.c arbori_build.c
	gcc main.c arbori_build.c coada.c $(CFLAGS) -o tema2

run: build
	./tema2

clean:
	rm -f tema2

valgrind: build
	valgrind -s --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema2

valgrind-c1: build
	valgrind -s --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema2 -c1 ex1.in out.out

valgrind-c2: build
	valgrind -s --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema2 -c2 3 ex1.in out.out

valgrind-c3: build
	valgrind -s --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema2 -c3 ex3.in out.out

valgrind-c4: build
	valgrind -s --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema2 -c4 ex1.in out.out 