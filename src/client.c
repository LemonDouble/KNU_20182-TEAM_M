/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  client module to make scoreboard
 *
 *        Version:  1.0
 *        Created:  12/20/18 20:36:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  성민규 (Seong Min Kyu)
 *   Organization:  KNU
 *
 * =====================================================================================
 */
//gcc -o client client.c
//client : client <ip> <port>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>


int sendMessage(int s,char *buf, struct sockaddr_in *servaddr,int addrlen)
{

    if((sendto(s, buf, strlen(buf), 0, (struct sockaddr *)servaddr, addrlen)) < 0)
    {
        perror("sendto fail");
        return -1;
    }
}

int sendScoreToServer(char *sendScore, char *serverAddress, char *serverPort)
{    
  struct sockaddr_in servaddr;
  int addrlen = sizeof(servaddr);
        int sendSocket;

        if((sendSocket=socket(PF_INET,SOCK_DGRAM,0))<0)
        {
                perror("socket fail\n");
                return 0;
        }

        memset(&servaddr,0,addrlen);
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(serverAddress);
        servaddr.sin_port = htons(atoi(serverPort));

        
        if(sendMessage(sendSocket,sendScore,&servaddr,addrlen) != -1){
          printf("Your score send! Thanks!! : %s\n",sendScore);
        }
        close(sendSocket);
}

