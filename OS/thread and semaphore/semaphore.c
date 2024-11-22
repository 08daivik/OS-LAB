#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

//PRODUCER CONSUMER

#define max 3
#define buffersize 3

int in=0;
int out=0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int buf[buffersize];

void *producer(void *pno)
{
    for(int i=0;i<max;i++)
    {
        int item=rand()%100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buf[in]=item;
        printf("Producer produces %d\n",item);
        in=(in+1)%buffersize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cno)
{
    for(int i=0;i<max;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item=buf[out];
        printf("Consumer consumed %d\n",item);
        out=(out+1)%buffersize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void main()
{
    pthread_t pro[3],con[3];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&empty,0,buffersize);
    sem_init(&full,0,0);
    int a[3]={1,2,3};

    for(int i=0;i<3;i++)
        pthread_create(&pro[i],NULL,(void *)producer,(void *)&a[i]);

    for(int i=0;i<3;i++)
        pthread_create(&con[i],NULL,(void *)consumer,(void *)&a[i]);

    for(int i=0;i<3;i++)
        pthread_join(pro[i],NULL);

    for(int i=0;i<3;i++)
        pthread_join(con[i],NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}


// READER WRITER

int cnt=1;
int numreader=0;
sem_t wrt;
pthread_mutex_t mutex;

void *writer(void *wno)
{
    sem_wait(&wrt);
    cnt=cnt*2;
    printf("Writer %d wrote %d\n",*((int *)wno),cnt);
    sem_post(&wrt);
}

void *reader(void *rno)
{
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    printf("Reader %d read %d",*((int *)rno),cnt);

    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader==0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
}

void main()
{
    pthread_t read[3],wrt[3];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&wrt,0,1);

    int a[3]={1,2,3};

    for(int i=0;i<3;i++)
        pthread_create(&read[i],NULL,(void *)reader,(void *)&a[i]);

    for(int i=0;i<3;i++)
        pthread_create(&wrt[i],NULL,(void *)writer,(void *)&a[i]);

    for(int i=0;i<3;i++)
        pthread_join(read[i],NULL);

    for(int i=0;i<3;i++)
        pthread_join(wrt[i],NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
}