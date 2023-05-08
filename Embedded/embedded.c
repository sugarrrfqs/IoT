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
	char str[256];	
	char eom[256] = "---";
	int clientType = 1;
	char* filename = "/home/sgrrr/IoT/wifiInfo.txt";	
		
	sd = socket (AF_INET, SOCK_STREAM, 0);
		
	memset(&tss_addr, 0, sizeof(tss_addr));
	tss_addr.sin_family=AF_INET; 
	tss_addr.sin_port=htons (1230);
	tss_addr.sin_addr.s_addr=inet_addr ("127.0.0.1");
		
	if (connect(sd, (struct sockaddr *)&tss_addr, sizeof(tss_addr)) == -1)
	{ 
		printf("Connection error\n"); 
		return -1; 
	}
	else
	{
		write(sd, &clientType, sizeof(clientType));
		printf("Connected\n"); 
	}
		
	while (sd != -1)
	{
		//system("nmcli dev wifi list > wifiInfo.txt");
		//system("cat /home/sgrrr/IoT/wifiInfo.txt | awk -v sum=0 -v c=$1 '{sum++} END {print sum}'");
		printf("wifi info collected\n");
			
		// чтение из файла и передача серверу
		FILE *fp = fopen(filename, "r");
		if(fp)
		{
			fgets(str, 256, fp);
			while(fgets(str, 256, fp) != NULL)
			{				
				write(sd, str, sizeof(str));
			}
			write(sd, eom, sizeof(eom));
			fclose(fp);
		} 
		sleep(5);
	}
	
	close (sd);
	return 0;
}
