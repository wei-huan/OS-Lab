#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

// 互斥量实现
// 声明筷子互斥量
pthread_mutex_t Chopstick[5];

// 声明保护量,有哲学家在吃饭就不拿筷子
pthread_mutex_t SomeOneEating;

void Think(int i)
{
    printf("Philosopher%d is Thinking\n", i);
}

void Eat(int i)
{
    printf("Philosopher%d is Eating\n", i);
}

void Get_Chopsticks(int i)
{
    pthread_mutex_lock(&SomeOneEating);

    pthread_mutex_lock(&Chopstick[i]);
    printf("Philosopher%d got left\n", i);

    pthread_mutex_lock(&Chopstick[(i+1)%5]);
    printf("Philosopher%d got right\n", i);
}

void Drop_Chopsticks(int i)
{
    pthread_mutex_unlock(&Chopstick[i]);
    pthread_mutex_unlock(&Chopstick[(i+1)%5]);
    pthread_mutex_unlock(&SomeOneEating);
}

void Philosopher_Dining(int i)
{
    while(1)
    {   
        sleep(2);
        Think(i);
        Get_Chopsticks(i);
        Eat(i);
        Drop_Chopsticks(i);
        sleep(2);
    }
}

int main()
{
    pthread_t p1_tid[5];

    printf("Create Chopsticks\n");
    for(int i=0; i<5; i++)
        pthread_mutex_init(&Chopstick[i], NULL);

    printf("Create DinningFlag\n");
    pthread_mutex_init(&SomeOneEating, NULL);

    printf("Create Philosopher_thread\n");
    for(int i=0; i<5; i++)
        pthread_create(&p1_tid[i], NULL, (void*)Philosopher_Dining, i);

    printf("Delete Philosopher_thread\n");
    for(int i=0; i<5; i++)
        pthread_join(p1_tid[i], NULL);

    printf("Delete DinningFlag\n");
    pthread_mutex_destroy(&SomeOneEating);

    printf("Delete Chopsticks\n");
    for(int i=0; i<5; i++)
        pthread_mutex_destroy(&Chopstick[i]);

    return 0;
}
