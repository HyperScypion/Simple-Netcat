#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"

int server_option(int port)
{
	struct sockaddr_in server_addr, client_addr;
	int sock, connected, bytes_recieved, true = 1;
	int sin_size;
	char recv_data[1024];
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int)) == -1) {
		perror("Setsocktopt");
		exit(1);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_addr.sin_zero),8);
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
		perror("Unable to bind");
		exit(1);
	}
	if (listen(sock, 10) == -1) {
		perror("Listen");
		exit(1);
	}
	while (1) {
		connected = accept(sock, (struct sockaddr *)&client_addr, (socklen_t *)&sin_size);
		if (connected == -1) {
			perror("Accept");
			exit(1);
		}
		bytes_recieved = recv(connected, recv_data, 1024, 0);
		recv_data[bytes_recieved] = '\0';
		printf("%s", recv_data);
		fflush(stdout);
	}

}
