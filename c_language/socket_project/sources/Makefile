
all: server client

server:
	gcc -o server socket_server.c socket_list.c socket_queue.c -I ../include/ -pthread

client:
	gcc -o client socket_client.c socket_list.c -I ../include/

clean:
	rm -rf server client
