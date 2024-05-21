CFLAGS=-Wall -Werror -g

build: main.c
	gcc main.c graf.c cerinta1.c cerinta2.c $(CFLAGS) -o tema3

run: build
	./tema3

run-c2: build
	./tema3 2

clean:
	rm -f tema3

valgrind: build
	valgrind -s --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema3

valgrind-c1: build
	valgrind -s --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema3 1

valgrind-c2: build
	valgrind -s --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema3 2
