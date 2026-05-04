#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;  // track number of items

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Produced: %d | Buffer count: %d\n", item, count);

        if (count == BUFFER_SIZE) {
            printf(">>> BUFFER FULL <<<\n");
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumed: %d | Buffer count: %d\n", item, count);

        if (count == 0) {
            printf(">>> BUFFER EMPTY <<<\n");
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1);
    }
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
