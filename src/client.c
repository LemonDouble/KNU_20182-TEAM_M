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

#define MAXLINE 511
#define BLOCK 255

struct sockaddr_in servaddr;
int addrlen = sizeof(servaddr);

void sendMessage(int s,char *buf)
{

    if((sendto(s, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, addrlen)) < 0)
    {
        perror("sendto fail");
        exit(0);
            }
}

int main(int argc,char *argv[])
{
        int s;
        int nbyte;
        char buf[MAXLINE+1];

        if(argc!=3)
        {
                printf("Usage : %s address port\n",argv[0]);
                exit(0);
        }

        if((s=socket(PF_INET,SOCK_DGRAM,0))<0)
        {
                perror("socket fail\n");
                exit(0);
        }

        memset(&servaddr,0,addrlen);
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(argv[1]);
        servaddr.sin_port = htons(atoi(argv[2]));

        fgets(buf,BLOCK,stdin);
        printf("Send : %s\n",buf);

        sendMessage(s,buf);
        close(s);
}

