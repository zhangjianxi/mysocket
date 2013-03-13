#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>

#define SERVER_PORT 4000
#define BACKLOG 10

int main(int argc, char** argv)
{
	int sock_fd, new_fd;

	int sin_size;

	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sock_fd)
	{
		fprintf(stdout, "create socket failed\n");
		return -1;
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(SERVER_PORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(my_addr.sin_zero), 8);

	bind(sock_fd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
	listen(sock_fd, BACKLOG);

	sin_size = sizeof(struct sockaddr_in);

	new_fd = accept(sock_fd, (struct sockaddr*)&their_addr, &sin_size);

	if (-1 == new_fd)
	{
		fprintf(stdout, "create accept failed \n");
		return -1;
	}
}
