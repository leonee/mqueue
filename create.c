#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc,char *argv[])
{
    int     c,flags;
    mqd_t   mqd;
    struct mq_attr  attr;

    flags = O_RDWR|O_CREAT;
    printf("create mqueue.\n");
    while((c = getopt(argc,argv,"e")) != -1)
    {
        switch(c)
        {
            case 'e':
                flags |= O_EXCL;
                break;
        }
    }
    if(optind != argc-1)
    {
        perror("usage: mqcreate [-e] <name>");
        exit(0);
    }
    if((mqd = mq_open(argv[optind],flags,FILE_MODE,NULL)) == -1)
    {
        perror("mq_open() error");
        exit(-1);
    }
    mq_getattr(mqd,&attr);
    printf("max #msgs = %ld,max #bytes/msg = %ld,#currently on queue = %ld\n",
           attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);
    mq_close(mqd);
    exit(0);
}
