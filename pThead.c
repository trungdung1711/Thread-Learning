#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


/*This data is shared by the threads*/
int sum;
/*Threads call this function*/
void* runner(void* param);



int main(int argc, char** argv)
{
    /*The thread identifier*/
    pthread_t tid ;
    
    /*The thread attribute-stack size...*/
    pthread_attr_t attr;
    /*Initialise the attr with the default attributes*/
    pthread_attr_init(&attr);
    /*Creating the process*/
    pthread_create(&tid,&attr,&runner,argv[1]);
    /*Wait for the thread to exit*/
    pthread_join(tid,NULL);

    printf("sum = %d\n", sum);
}



/*The thread will execute from this function*/
void* runner(void* param)
{
    char* numStr = (char*)param;
    int upper = atoi(numStr);
    sum = 0;
    for (int i = 1 ; i <= upper ; ++i)
    {
        sum += i;
    }
    pthread_exit(NULL);
}