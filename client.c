#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char** argv)
{
	int sockfd;
	char buffer[1024];
	char *send_buffer = "good \n sajdflkj\n  kasdjlf jlk\n";
	
	struct sockaddr_in server_addr;
	struct hostent *host;

	int portnumber, nbytes;

	if (3 != argc)
	{
		fprintf(stdout, "Usage:%s hostname portnumber \a\n", argv[0]);
		exit(1);
	}

	if (0 > (portnumber = atoi(argv[2])))
	{
		fprintf(stderr, "Usage:%s hostname portnumber \a\n", argv[0]);
		exit(1);
	}

	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		fprintf(stderr, "Socket Error \a\n");
		exit(1);
	}

	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	fprintf(stdout, "%s \a\n", argv[1]);

	//if (0 >= inet_pton(AF_INET, argv[1], &server_addr.sin_addr))
	//{
	//	fprintf(stdout, "inet_pton error for %s \a\n", argv[1]);
	//	exit(0);
	//}

	
	if (-1 == connect(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)))
	{
		fprintf(stderr, "Connect Error \a\n");
		exit(1);
	}
	
	write(sockfd, send_buffer, strlen(send_buffer));

	if (-1 == (nbytes = read(sockfd, buffer, 1024)))
	{
		fprintf(stderr, "Read Error \a\n");
		exit(1);
	}

	buffer[nbytes] = 0;
	printf("I have received:%s \n", buffer);

	send(sockfd, "thank you \n", strlen("thank you \n"), 0);
	close(sockfd);
	exit(0);
}
