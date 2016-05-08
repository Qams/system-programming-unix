#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 100

int main()
{
   int client_to_server;
   char *myfifo = "client2server";

   int server_to_client;
   char *myfifo2 = "server2client";

   char str[SIZE];
	char resp[SIZE];
   /* write str to the FIFO */
	client_to_server = open(myfifo, O_WRONLY);
	server_to_client = open(myfifo2, O_RDONLY);

	do{
		printf("> ");
		gets(str);
	   	write(client_to_server, str, sizeof(str));
	   	read(server_to_client,resp,sizeof(str));
		printf("%s\n", resp);
	}while(strcmp(str,"bye"));

   close(client_to_server);
   close(server_to_client);

   /* remove the FIFO */

   return 0;
}
