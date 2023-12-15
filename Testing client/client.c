#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
	int sd;
	struct sockaddr_in tss_addr;
	int number = 1;
	char scommand[256] = "1";
	char answer[256] = "";
	char clientType[256] = "2";
	char eom[256] = "---";

	sd = socket (AF_INET, SOCK_STREAM, 0);

	memset(&tss_addr, 0, sizeof(tss_addr));
	tss_addr.sin_family=AF_INET;
	tss_addr.sin_port=htons (1230);
	tss_addr.sin_addr.s_addr=inet_addr ("127.0.0.1");

	if (connect(sd, (struct sockaddr *)&tss_addr, sizeof(tss_addr)) == -1)
	{
		printf("Ошибка подключения");
		return -1;
	}
	else
	{
		printf("Connected\n");
		write(sd, &clientType, sizeof(clientType));
	}
	int i = 0;
	while (i < 3)
	{
		write(sd, &scommand, sizeof(scommand));
		read (sd, &answer, 256);
		while (read (sd, &answer, 256) > 0 && strcmp(answer, eom) != 0)
		{
			printf("%s", answer);						
		}
		i++;
	}
	close (sd);
	return 0;
}

// clang -o client client.c
// gcc -pthread -o serv serv.c
// (void*)(size_t)
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
