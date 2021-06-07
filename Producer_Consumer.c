#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// POSIX 信号量实现

// 定义队列
sem_t empty,full;
sem_t mutex;

// 定义缓冲区容量
#define FIFO_MAX_NUM 10

FILE *fp;

// 定义缓冲区
struct FIFO
{
    char buffer[FIFO_MAX_NUM+1];
    int readindex, writeindex;
}fifo;

void Produce(int id)
{
    char product = fgetc(fp);
    fifo.buffer[fifo.writeindex++] = product;
    printf("生产者生产了%c\n",product);
}

void Producer(int id)
{
    sleep(1);
    sem_wait(&full);
    sem_wait(&mutex);
    Produce(id);
    sem_post(&mutex);
    sem_post(&empty);
}

void Consume(int id)
{
    char product = fifo.buffer[fifo.readindex++];
    printf("消费者消费了%c\n", product);
}

void Consumer(int id)
{
    sleep(1);
    sem_wait(&empty);
    sem_wait(&mutex);
    Consume(id);
    sem_post(&mutex);
    sem_post(&full);
}

int main()
{   
    int Producer_Num = 4;
    int Consumer_Num = 3;
    fp = fopen("Product.txt","r");
    pthread_t Producer_tid[Producer_Num];
    pthread_t Consumer_tid[Consumer_Num];

    printf("Sem Mutex Init\n");
    sem_init(&mutex, 0, 1);

    printf("Sem Empty Init\n");
    sem_init(&empty, 0, 0);

    printf("Sem Full Init\n");
    sem_init(&full, 0, FIFO_MAX_NUM);

    printf("Create Producer_thread\n");
    for(int i=0; i<Producer_Num; i++)
        pthread_create(&Producer_tid[i], NULL, (void*)Producer, &i);

    printf("Create Consumer_thread\n");
    for(int i=0; i < Consumer_Num; i++)
        pthread_create(&Consumer_tid[i], NULL, (void*)Consumer, &i);

    printf("Delete Producer_thread\n");
    for(int i=0; i < Producer_Num; i++)
        pthread_join(Producer_tid[i], NULL);

    printf("Delete Consumer_thread\n");
    for(int i=0; i < Consumer_Num; i++)
        pthread_join(Consumer_tid[i], NULL);

    printf("Delete Sem full\n");
    sem_destroy(&full);

    printf("Delete Sem empty\n");
    sem_destroy(&empty);

    printf("Delete Sem mutex\n");
    sem_destroy(&mutex);

    return 0;
}
