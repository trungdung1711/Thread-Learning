#include <pthread.h>
#include <stdio.h>


void* routine(void* param)
{
    printf("Text from thread1 1\n");
    sleep(20);
    printf("Ending thread 1\n");    
}



void* routine2(void* param)
{
    printf("Text from thread 2\n");
    sleep(30);
    for (int i = 0 ; i < 10 ; ++i)
    {
        printf("Value: %d\n",i);
        sleep(1);
    }
    printf("Ending thread 2\n");
}



int main(int argc, char**argv)
{
    /*The id for the thread*/
    pthread_t tid,tid2;
    /*The thread attribute*/
    pthread_attr_t attr ;
    /*initialise the default attributes*/
    pthread_attr_init(&attr);
    /*Create the thread*/
    pthread_create(&tid,&attr,&routine,NULL);
    pthread_create(&tid2,&attr,&routine2,NULL);
    /*The main thread and the routine thread will be e
    executed in paralell because of multiple cores
    */
    for (int i = 0 ; i < 10 ; ++i)
    {
        printf("Main thread\n");
        sleep(1);
    }
    pthread_join(tid,NULL);

}