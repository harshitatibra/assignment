#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];

int in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
for (int i = 0; i < NUM_ITEMS; i++)
{
sem_wait(&empty);
pthread_mutex_lock(&mutex);
buffer[in] = i;
printf("Produced : %d\n", i);
in = (in + 1) % BUFFER_SIZE;
pthread_mutex_unlock(&mutex);
sem_post(&full);
sleep(1);
}
return NULL;
}

void *consumer(void *arg)
{
for (int i = 0; i < NUM_ITEMS; i++)
{
sem_wait(&full);
pthread_mutex_lock(&mutex);
int item = buffer[out];
printf("Consumed: %d\n", item);
out = (out + 1) % BUFFER_SIZE;
pthread_mutex_unlock(&mutex);
sem_post(&empty);
sleep(1);
}
return NULL;
}

int main()
{
pthread_t prod_thread, cons_thread;

sem_init(&empty, 0, BUFFER_SIZE);
sem_init(&full, 0, 0);
pthread_mutex_init(&mutex, NULL);
pthread_create(&prod_thread, NULL, producer, NULL);
pthread_create(&cons_thread, NULL, consumer, NULL);
pthread_join(prod_thread, NULL);
pthread_join(cons_thread, NULL);
sem_destroy(&empty);
sem_destroy(&full);
pthread_mutex_destroy(&mutex);
return 0;
}
