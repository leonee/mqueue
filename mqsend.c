#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/stat.h>
typedef unsigned int  uint_t;

int main(int argc,char *argv[])
{
    mqd_t   mqd;
    // void    *ptr;
    // char str[30] = "いけい";
    // char str[30] = "りょうしゅう";
    char str[30] = "かいせき";
    size_t  len;
    uint_t  prio;
    if(argc != 3)
    {
        printf("usage: mqsend <name> <priority>\n");
        exit(0);
    }
    // len = atoi(argv[2]);
    // prio = atoi(argv[3]);
    prio = atoi(argv[2]);
    mqd = mq_open(argv[1],O_WRONLY);
    // ptr = calloc(len,sizeof(char));
    if(mq_send(mqd,str,30,prio) == -1)
    {
        perror("mq_send() error:");
        exit(-1);
    }
    exit(0);
}
