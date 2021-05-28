#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int saad = 0;
pthread_mutex_t mutex;
void    *myfunc(void *argv)
{
    int i = 0;
    while (i < 10000000)
    {
        pthread_mutex_lock(&mutex);
        saad++;
        i++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void    *myfunction(void *argv)
{
    static int i;
    i += 1;
    printf("Hello from thread : %d\n", i);
    return NULL;
}

int main()
{
    pthread_t t[4];
    int i = 0;

    pthread_mutex_init(&mutex, NULL);
    while (i < 4)
    {
        pthread_create(&t[i], NULL, &myfunc, NULL);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        pthread_join(t[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&mutex);
    printf("saad : %d\n", saad);
    return 0;
}