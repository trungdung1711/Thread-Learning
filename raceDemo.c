#include <pthread.h>
#include <stdio.h>



/*SHARED MEMORY BETWEEN THREADS*/
int shared_memory = 0;
int NUM = 1000000;



void* routine(void* param)
{
    for (int i = 0 ; i < NUM ; ++i)
    {
        ++shared_memory;
    }
}



int main(int argc, char** argv)
{
    pthread_t tid1,tid2;
    pthread_attr_t attr1,attr2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    pthread_create(&tid1,&attr1,&routine,NULL);
    pthread_create(&tid2,&attr2,&routine,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    printf("The value of shared_memory is %d",shared_memory);
    return 0;
}