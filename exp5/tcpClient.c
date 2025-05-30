#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
int clientSocket;
char buffer[1024];
struct sockaddr_in serverAddr, placeHolder;
socklen_t addr_size;
clientSocket = socket(PF_INET, SOCK_STREAM , 0);
printf("\nThe Socket ID (clientSocket ) = %d\n", clientSocket);
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(7891);
serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
addr_size = sizeof serverAddr;
connect(clientSocket, (struct sockaddr *) &serverAddr , addr_size);
recv(clientSocket, buffer ,1024,0);
printf("Data recieved : %s",buffer);
close(clientSocket);
return 0;
}
