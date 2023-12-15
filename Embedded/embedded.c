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
	char clientType[256] = "1";
	char* filename = "/home/sugar/iot/wifiInfo.txt";
	int command = 0;	
		
	sd = socket (AF_INET, SOCK_STREAM, 0);
		
	memset(&tss_addr, 0, sizeof(tss_addr));
	tss_addr.sin_family=AF_INET; 
	tss_addr.sin_port=htons (1230);
	tss_addr.sin_addr.s_addr=inet_addr ("127.0.0.1");
		
	if (connect(sd, (struct sockaddr *)&tss_addr, sizeof(tss_addr)) == -1)
	{ 
		printf("Connection error\n"); 
		system("systemd-cat -t WifiScan echo CONNECTION ERROR");
		return -1; 
	}
	else
	{
		write(sd, &clientType, sizeof(clientType));
		printf("Connected\n");
		system("systemd-cat -t WifiScan echo SUCCESSFULLY CONNECTED"); 
	}
		
	while (read(sd, &command, sizeof(command) > 0))
	{
		if (command == 1)
		{
			system("systemd-cat -t WifiScan echo RECIEVED WIFI INFO REQUEST");
			//system("nmcli dev wifi list > /home/sugar/iot/wifiInfo.txt");
			printf("wifi info collected\n");
			system("systemd-cat -t WifiScan echo INFO COLLECTED");
			// чтение из файла и передача серверу
			FILE *fp = fopen(filename, "r");
			if(fp)
			{
				fgets(str, 256, fp);
				while(fgets(str, 256, fp) != NULL)
				{				
					write(sd, str, sizeof(str));
					//printf("%s\n", str);	
				}
				write(sd, eom, sizeof(eom));
				fclose(fp);
			} 
			system("systemd-cat -t WifiScan echo WIFI INFO SENDED");
		}
	}
	
	close (sd);
	system("systemd-cat -t WifiScan echo SUCCESSFULLY DISCONNECTED"); 
	return 0;
}
