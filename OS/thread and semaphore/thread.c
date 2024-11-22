#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int s=0;
int p=1;

void *sum(void *parm)
{
    int i,n;
    n=atoi(parm);
    printf("Entered sum thread\n");
    for(i=1;i<=n;i++)
        s+=i;
    printf("Sum completed\n");
}

void *mul(void *parm)
{
    int i,n;
    n=atoi(parm);
    printf("Entered mul thread\n");
    for(i=2;i<=n;i++)
        p=p*i;
    printf("multiply completed\n");
}

void main(int argc,char *argv[])
{
    pthread_t t1,t2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&t1,&attr,sum,argv[1]);
    pthread_create(&t2,&attr,mul,argv[1]);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("Sum=%d\n",s);
    printf("Product=%d\n",p);
}

