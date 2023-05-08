#include <stdlib.h>
#include <string.h> 
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
		pthread_create(&id, NULL, func, &socketC);
	}
	close (socketL);
			
	return 0;				
}

void* func (void* arg)
{
	int socket = *(int*)arg;
	int clientType = 0;
	char str[256] = "s";
	char eom[256] = "---";
	char* filename = "/home/sgrrr/IoT/serverWifiInfo.txt";
		
	read (socket, &clientType, sizeof(clientType));
	
	if (clientType == 1) // сканер wifi
	{
		system("echo wifi scan connected");
				
		while(read (socket, &str, 256) > 0)
		{	
			FILE *fp = fopen(filename, "w");
			if(fp)
			{
				while (strcmp(str, eom) != 0)
				{				
					fputs(str, fp);	
					read (socket, &str, 256);					
				}
				fclose(fp);
				system("echo ----- wifi info received");
				sleep(5);			
			}		
		}
		system("echo wifi scan disconnected");
	}
	if (clientType == 2) // мобильный клиент
	{
		system("echo mobile client connected");
		
		while(read (socket, &str, 256) > 0)
		{				
			FILE *fp = fopen(filename, "r");
			if(fp)
			{
				while(fgets(str, 256, fp) != NULL)
				{				
					write(socket, str, sizeof(str));
				}
				write(socket, eom, sizeof(eom));
				fclose(fp);
			} 								
			system("echo ----- wifi info sended");
			sleep(5);			
					
		}
		system("echo mobile client disconnected");
	}

	close (socket);
	return NULL;
}
	

