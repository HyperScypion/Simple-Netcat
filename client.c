#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netdb.h>
#include <unistd.h>
#include "client.h"

int client_tcp(struct addrinfo *result)
{
	printf("XD2\n");
	int pid, bytes_recieved, sock, sock2;
	char send_data[1024], recv_data[1024];
	struct addrinfo *iter;
	for (iter = result; iter != NULL; iter = iter->ai_next) {
		if ((sock = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol)) == -1) {
			perror("Socket");
			exit(1);
		}
		if (connect(sock, iter->ai_addr, iter->ai_addrlen) == -1) {
			close(sock);
			perror("Connect");
			continue;
		}
		break;
	}
	sock2 = accept(sock, NULL, NULL);
	if (sock2 == -1) {
		perror("Accept");
		exit(1);
	}
	if ((pid = fork()) == 0) {
		while(1) {
			int pom; 
			pom = read(0, send_data, 1024);
			if (pom == 0) {
				close(sock2);
				kill(pid, SIGINT);
				exit(0);
			}
			if (send(sock, send_data, pom, 0) == -1) {
				perror("Send");
				exit(1);
			}	
		}
	}
	else {
		while(1) {
			if ((bytes_recieved = recv(sock, recv_data, 1024, 0) == -1)) {
				perror("Recv");
				exit(1);	
			}
			if (bytes_recieved == 0) {
				close(sock);
				close(sock2);
				exit(0);
			}
			write(1, recv_data, bytes_recieved);
		}
	}
}	

