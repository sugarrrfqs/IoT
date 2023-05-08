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
	string str;		
		
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
		printf("Подключен"); 
	}
		
	//while (true)
	//{
		//system("nmcli dev wifi list > wifiInfo.txt");
		system("echo wifi info recieved");
		system("cat ~/IoT/wifiInfo.txt | awk -v sum=0 -v c=$1 '{sum++} END {print sum}'");
		
		printf("Введите число\n");
		scanf("%d", &number);
		
		char * filename = "data.txt";
		char buffer[256];
		// чтение из файла
		FILE *fp = fopen(filename, "r");
		if(fp)
		{
			// пока не дойдем до конца, считываем по 256 байт
			while((fgets(buffer, 256, fp))!=NULL)
			{
				printf("%s", buffer);
			}
			fclose(fp);
		} 
		while ()
		{
			write(sd, str, sizeof(str));
		}

	//}
	
	close (sd);
	return 0;
}
