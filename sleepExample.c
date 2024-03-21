#include <pthread.h>
#include <stdio.h>


void* routine(void* param)
{
    printf("Text from threads\n");
    sleep(20);
    printf("Ending thread\n");    
}



int main(int argc, char**argv)
{
    /*The id for the thread*/
    pthread_t tid;
    /*The thread attribute*/
    pthread_attr_t attr ;
    /*initialise the default attributes*/
    pthread_attr_init(&attr);
    /*Create the thread*/
    pthread_create(&tid,&attr,&routine,NULL);

    /*The main thread and the routine thread will be e
    executed in paralell because of multiple cores
    */
    for (int i = 0 ; i < 10 ; ++i)
    {
        printf("Main thread\n");
        sleep(1);
    }

}