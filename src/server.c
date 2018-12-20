/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  server program to get data / sorting data / print data
 *
 *        Version:  1.0
 *        Created:  12/20/18 20:34:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  성민규 (Seong Min Kyu)
 *   Organization:  KNU
 *
 * =====================================================================================
 */

// command : gcc -o server server.c -lpthread
// server : server <port>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>

#define MAX_RANK 100

#define MAXLINE 512
#define BLOCK   255
#define LISTENQ 10


typedef struct _User_data{
        char *id;
        int score;
}User_data;

typedef struct _Rank{
        User_data data[MAX_RANK];
        int count;
        //next node
}Rank;

//ranking
void *ranking(void *data);
//linked list

//ranking linked list
pthread_mutex_t mutex;// =  PTHREAD_MUTEX_INITIALIZER;
Rank* rank_arr;
int cntNum = 0;


void insert_rank(User_data user);
void print_ranking();
void sort(User_data arr[],int size);

//ranking print
void print_ranking()
{
        printf("---------RANKING----------\n");
        //print ranking
        for(int i=0;i<rank_arr->count;i++)
        {
                printf("%d >> ID :  %s   SCORE : %d\n", i+1,rank_arr->data[i].id,rank_arr->data[i].score);
        }
        printf("---------RANKING----------\n");
}

//bubble sorting
void sort(User_data arr[],int size)
{
        User_data  tmp;

        for(int i =0;i<size -1 ;i++)
        {
                for(int j = i+1;j<size;j++)
                {
                        if(arr[i].score < arr[j].score)
                        {
                                tmp = arr[i];
                                arr[i] = arr[j];
                                arr[j] = tmp;
                        }
                }
        }
        print_ranking();
}

//ranking에 user 삽입
void insert_rank(User_data user)
{
        //ranking insert
        rank_arr->data[rank_arr->count] = user;
        rank_arr->count++;
        sort(rank_arr->data,rank_arr->count);
}

//ranking 매기는 thread function
void *ranking(void *data)
{
        char*  buf = (char*)data;

        char *ptr;

        char *pid;
        char *pscore;

        ptr = strtok(buf," ");
        pid = ptr;

        ptr = strtok(NULL,"\n");
        pscore = ptr;

        User_data us;
        us.id = (char*)malloc(sizeof(char)*MAXLINE);

        strcpy(us.id,pid);
        us.score = atoi(pscore);

        pthread_mutex_lock(&mutex);
        insert_rank(us);
        pthread_mutex_unlock(&mutex);
}



int main(int argc,char *argv[])
{
        rank_arr = (Rank*)malloc(sizeof(Rank));
        rank_arr->count = 0;

        pthread_mutex_init(&mutex,NULL);
        struct sockaddr_in servaddr,cliaddr;

        int s,nbyte,addrlen = sizeof(struct sockaddr);

        char buf[MAXLINE+1];
        pthread_t p_thread[MAX_RANK];
        int thread_no=0;

        if(argc!=2)
        {
                printf("usage : %s port\n",argv[0]);
                exit(0);
        }

        if((s=socket(PF_INET,SOCK_DGRAM,0))<0)
        {
                perror("socket fail\n");
                exit(0);
        }

        memset(&cliaddr,0,addrlen);
        memset(&servaddr,0,addrlen);

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(atoi(argv[1]));

        if(bind(s,(struct sockaddr*)&servaddr,addrlen)<0)
        {
                perror("bind fial\n");
                exit(0);
        }


        while(1)
        {
                char imsi[MAXLINE];
                memset(&buf,0,MAXLINE);
                nbyte = recvfrom(s,buf,MAXLINE,0,(struct sockaddr *)&cliaddr,&addrlen);

                if(nbyte<0)
                {
                        perror("recv from fail\n");
                        exit(1);

                }
                buf[nbyte] = 0;

                int thr_id;
                int status;

                strcpy(imsi,buf);
                thr_id = pthread_create(&p_thread[thread_no],NULL,ranking,(void*)imsi);

                pthread_join(p_thread[thread_no],NULL);
                memset(imsi,0,MAXLINE);
                pthread_detach(p_thread[thread_no]);
                if(thr_id<0)
                {
                        perror("thread create error:");
                        exit(0);
                }
                else
                        thread_no++;
        }
}

