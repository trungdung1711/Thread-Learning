#include <pthread.h>
#include <stdio.h>



void* routine1(void* param)
{
    for (int i = 0 ; i < 5 ; ++i)
    {
        printf("THREAD 1\n");
        sleep(4);
    }
}



void* routine2(void* param)
{
    for (int i = 0 ; i < 20 ; ++i)
    {
        printf("THREAD 2\n");
        sleep(4);
    }
}



int main()
{
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0 ; i < 2 ; ++i)
    {
        pthread_create(&tid[i],&attr,&routine1,NULL);
    }

    for (int i = 0 ; i < 2 ; ++i)
    {
        pthread_join(tid[i],NULL);
    }
    return 0;
}