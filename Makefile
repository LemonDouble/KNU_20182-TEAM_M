default: build

build:
	gcc -o snake src/main.c src/snake.h src/snake.c  -lncurses -g

run:build
	./snake
