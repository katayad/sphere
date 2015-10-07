#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

std::string message = "Hello\n";
char buf[1024];

int main()
{
    int ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12346);
    SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(ClientSocket, (const sockaddr*) &SockAddr, sizeof 	(SockAddr));

    while (getline(std::cin, message))
    {
        //std::cerr << "local   " << message << "\n";
        send(ClientSocket, message.c_str(), message.size(), 0);
        //for(int i = 0; i < 100000; ++i);
        recv(ClientSocket, buf, sizeof(buf), 0);
        printf(buf);
        printf("\n");
    }




    close(ClientSocket);
}
