default: build

build:
	gcc -o snake src/client.h src/client.c src/main.c src/snake.h src/snake.c  -lncurses -g

server:
	gcc -o server src/server.c -lpthread

runserver:server
	./server 9872

run:build
	./snake
