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
#include <semaphore.h>

void* func (void* arg);

int command = -1;
char* filename = "/home/sgrrr/IoT/serverWifiInfo.txt";
char eom[256] = "---";
sem_t semaphore;


int main()
{	
	sem_init(&semaphore, 0, 1);
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
	sem_wait(&semaphore);
	while (socketC!= -1)
	{
		socketC = accept(socketL, NULL, NULL);
		pthread_create(&id, NULL, func, &socketC);
	}
	close (socketL);
	sem_destroy(&semaphore);
			
	return 0;				
}


void* func (void* arg)
{
	int socket = *(int*)arg;
	int clientType = 0;
	char str[256] = "s";
		
	read (socket, &clientType, sizeof(clientType));
	
	if (clientType == 1) // сканер wifi
	{
		system("echo wifi scan connected");	
					
		while(socket > 0)
		{	
			sem_wait(&semaphore);	
			if (command == 1)
			{
				system("echo ----- request received from mobile client");
				write(socket, &command, sizeof(command));
				system("echo ----- request sended to wifi scaner");
				
				FILE *fp = fopen(filename, "w");
				if(fp)
				{
					while (read (socket, &str, 256) > 0 && strcmp(str, eom) != 0)
					{	
						
						//printf("%s\n", str);	
						fputs(str, fp);											
					}
					fclose(fp);
					system("echo ----- wifi info received from wifi scaner");			
				}			
			}
			sem_post(&semaphore);	
			sleep(3);
		}
		
		system("echo wifi scan disconnected");
	}
	
	if (clientType == 2) // мобильный клиент
	{
		system("echo mobile client connected");
		
		while(read (socket, &command, sizeof(command)) > 0)
		{	
			sem_post(&semaphore);
			sleep(1);
			sem_wait(&semaphore);			
			if (command == 1)
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
				system("echo ----- wifi info sended to mobile client\n\n");
				sleep(5);
			}			
					
		}
		system("echo mobile client disconnected");
	}

	close (socket);
	return NULL;
}
	

