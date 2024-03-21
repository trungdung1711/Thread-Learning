#include <pthread.h>
#include <stdio.h>



void* add(void* param)
{
    int* value = (int*)param;
    *value = (*value)*2;
    return value;
}



int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int param = 100;


    pthread_create(&tid,&attr,&add,&param);

    /*doing the main thread works, and waiting for the result from the add thread*/
    for (int i = 0 ; i < 10 ; ++i)
    {
        printf("Doing\n");
        sleep(1);
    }

    void* result;
    void** resultPrime = &result;
    pthread_join(tid,resultPrime);
    printf("Value is %d", *((int*)result));

}