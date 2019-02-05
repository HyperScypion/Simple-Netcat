#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, flag, odp, ip, sock, sock2, udp, pid, bytes;
    int iter = 1;
    char buf[1024];
    if (argc >= 2)
    {
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        for (iter; iter < argc; iter++)
        {
            if (argv[iter][0] == '-')
            {
                if (argv[iter][1] == '4')
                {
                    printf("Option -4\n");
                    hints.ai_family = AF_INET;
                }
                else if (argv[iter][1] == '6')
                {
                    printf("Option -6\n");
                    hints.ai_family = AF_INET6;
                }
                else if (argv[iter][1] == 'u')
                {
                    printf("UDP\n");
                    hints.ai_socktype = SOCK_DGRAM;
                    udp = 1;
                }
                else if (argv[iter][1] == 'l')
                {
                    printf("Server Mode\n");
                    flag = 10;
                }
                else
                {
                    printf("Error: Usage nc [destination] [port] [-option]\n");
                    exit(1);
                }
            }
        }
        if ((odp = getaddrinfo(argv[1], argv[2], &hints, &result)) != 0)
        {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(odp));
        }
        for (rp = result; rp != NULL; rp = rp->ai_next)
        {
            if ((sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1)
            {
                perror("Socket");
                exit(1);
            }
            if (flag == 10)
            {
                if (bind(sock, rp->ai_addr, rp->ai_addrlen) == -1)
                {
                    close(sock);
                    perror("Bind");
                    continue;
                }
            }
            else
            {
                if (connect(sock, rp->ai_addr, rp->ai_addrlen) == -1)
                {
                    close(sock);
                    perror("Connect");
                    continue;
                }
            }
            break;

        }
	if (rp == 0) {
		fprintf(stderr, "Nie udalo sie utworzyc");
		exit(1);
	}
        sock2 = sock;
        if (flag == 10)
        {
            if (udp != 1)
            {
                if (listen(sock, 20) == -1)
                {
                    perror("Listen");
                    exit(1);
                }
                sock2 = accept(sock, NULL, NULL);
                if (sock2 == -1)
                {
                    perror("Accept");
                    exit(1);
                }
            }
        }
        if ((pid = fork()) == 0)
        {
            while(1)
            {
                if ((bytes = recv(sock2, buf, 1024, 0)) == -1)
                {
                    perror("recv");
                    exit(1);
                }
                if (bytes == 0)
                {
                    close(sock);
                    close(sock2);
                    exit(0);
                }
                write(1, buf, bytes);
            }
        }
        else
        {
            while(1)
            {
                bytes = read(0, buf, 1024);
                if (bytes == 0)
                {
                    close(sock2);
   
                    exit(0);
                }
                if (send(sock2, buf, bytes, 0) == -1)
                {
                    perror("Send");
                    exit(1);
                }
            }
        }
    }
    else if (argc < 2)
    {
        printf("Za malo argumentow\n");
        exit(1);
    }

    return 0;
}

