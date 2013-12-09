#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include<sys/stat.h>
#include <string.h>
#define GET_ARRAY_LEN(array,len) {len=(sizeof(array)/sizeof(array[0]));}
typedef unsigned int  uint_t;

struct strdata {
  char kana[30];
  char kouho[3][30];
}data[14]={
  {"いえん", {"胃炎", "以遠", ""}},
  {"いけい", {"畏敬", "異型", "異形"}},
  {"いんせき", {"隕石", "引責", "姻戚"}},
  {"うめがわ", {"梅川", "", ""}},
  {"えんちょう", {"延長", "園長", "円頂"}},
  {"おおいた", {"大分", "大板", ""}},
  {"おおいちょう", {"大銀杏", "", ""}},
  {"かいが", {"絵画", "怪訝", ""}},
  {"かいさん", {"解散", "海産", ""}},
  {"かいせき", {"解析", "会席", "懐石"}},
  {"かめ", {"亀", "瓶", "甕"}},
  {"かんさ", {"監査", "鑑査", "感作"}},
  {"かんにゅう", {"嵌入", "貫入", "陥入"}},
  {"がいはく", {"外泊", "該博", ""}}
};

int main(int argc,char *argv[])
{
    int     c,flags,i,len;
    mqd_t   mqd;
    ssize_t n;
    uint_t  prio;
    void *buff;
    char s[30];
    char *a;
    struct mq_attr attr;
    //printf("data.kana: %s \n", data[0].kana);
    printf("data.kouho: %s \n", data[0].kouho[1]);
    //printf("data.kouho: %s \n", data[0].kouho[0]);
   
    flags = O_RDONLY;
    while((c = getopt(argc,argv,"n")) != -1)
    {
        switch(c)
        {
            case 'n':
                flags |= O_NONBLOCK;  //设置为非阻塞
                break;
        }
    }
    if(optind != argc-1)
    {
        printf("usage: mqreceive [-n] <name>");
        exit(0);
    }
    mqd = mq_open(argv[optind],flags);
    //mqd = mq_open(argv[optind],flags);
    mq_getattr(mqd,&attr);
    buff = malloc(attr.mq_msgsize);
    if((n = mq_receive(mqd,buff,attr.mq_msgsize,&prio)) == -1) {
        perror("mq_receive error: ");
        exit(-1);
    }
    memcpy(s,buff,30);
    // printf("read %ld bytes,priority = %u\n",(long) n,prio);
    // printf("words %s \n\n", s);
    
    if (prio==0) {
        for (i=0; i<14; i++) {
            if (strcmp(s,data[i].kana)==0) {
                printf("data.kana1: %s \n", data[i].kana);
                printf("data.kana1: %s \n", data[i].kouho[1]);
                GET_ARRAY_LEN(data[i].kouho[1],len);
                a=data[i].kouho[1];
                //mq_send(mqd1,a,len,1);
                break;    
            }
        }
    } else {
        for (i=0; i<14; i++) {
            if (strcmp(s,data[i].kana)==0) {
                printf("data.kana2: %s \n", data[i].kana);
                printf("data.kana2: %s \n", data[i].kouho[1]);
                GET_ARRAY_LEN(data[i].kouho[1],len);
                a=data[i].kouho[1];
                //mq_send(mqd1,a,len,1);
                break;    
            }
        }

    }
        
    exit(0);
}
