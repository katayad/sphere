#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

char buf[1024];
int bytes_read;

int main()
{
    /*int Socket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in SockAddr;
    // memset(&SockAddr, 0, sizeof(SockAddr));
    bzero(&SockAddr, sizeof(SockAddr));
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12345);
    // SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    //SockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    struct hostent * hp = gethostbyname("rvncerr.org");
    bcopy(hp->h_addr, &(SockAddr.sin_addr.s_addr), hp->h_length);

    bind(Socket, (struct sockaddr *)&SockAddr, sizeof(SockAddr));
    listen(Socket, SOMAXCONN);

    while(1)
    {
        struct sockaddr *addr;
        int SlaveSocket = accept(Socket, 0, 0);

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            send(sock, buf, bytes_read, 0);
        }

        close(sock);
    }*/



    int MasterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12346);
    SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(MasterSocket, (struct sockaddr *)&SockAddr, 	sizeof(SockAddr));

    listen(MasterSocket, SOMAXCONN);



    int SlaveSocket = accept(MasterSocket, 0, 0);
    while(true)
    {

        //while(1)
        //{
            bzero(buf, 1024);
            bytes_read = recv(SlaveSocket, buf, 1024, 0);
            //printf(buf);
            printf("\n");
            //if(bytes_read <= 0) break;
            send(SlaveSocket, buf, bytes_read, 0);
        //}
    }
    close(SlaveSocket);
}
