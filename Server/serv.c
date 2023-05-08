#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <pthread.h>

void* func (void* arg);


int main()
{	
	struct sockaddr_in adr;
	int socketL = socket(AF_INET, SOCK_STREAM, 0);		
	adr.sin_family = AF_INET;
	adr.sin_port = htons(1230);
	adr.sin_addr.s_addr = htonl (INADDR_ANY);
	// проверки
	int bind_check = bind (socketL, (struct sockaddr*)&adr, sizeof(adr));
	if (bind_check == -1)
	{
		printf("Ошибка при попытке bind\n");
		return -1;
	}
	else
	{
		printf("Выполнен bind\n");
	}
	

	int listen_check = listen (socketL,1);
	if (listen_check == -1)
	{
		printf("Ошибка при попытке listen\n");
		return -2;
	}
	else
	{
		printf("Выполнен listen\n");
	}
	
		
	pthread_t id;
	int socketC;
	while (socketC!= -1)
	{
		socketC = accept(socketL, NULL, NULL);
		if (socketC == -1) printf("before pthread"); 
		pthread_create(&id, NULL, func, &socketC);
	}
	close (socketL);
			
	return 0;				
}

void* func (void* arg)
{
	int socket = *(int*)arg;
	int number = 1;
	
//обработка соединения
	close (socket);
	return NULL;
}
	

