CFLAGS=-Wall -Werror -g

run: build
	./tema2

build: main.c arbori_build.c
	gcc main.c arbori_build.c $(CFLAGS) -o tema2

clean:
	rm -f tema2

valgrind: build
	valgrind --leak-check=yes --track-origins=yes ./tema2
