#include <pthread.h>
#include <stdio.h>
#include <malloc.h>



/*shared memory*/
int arr[20] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};



/*struct used for passing*/
typedef struct
{
    /*begin*/
    int i;
    /*end*/
    int j;
} arguments;



/*THREAD starts*/
void* Sum(void* param)
{
    arguments* indices = (arguments*)(param);

    /*length of subarr*/
    int num = indices->j-indices->i+1;

    /*pointer to save result*/
    int* result = malloc(sizeof(int));

    /*initilised to be 0*/
    *result = 0;
    /*small enough*/
    if (num <= 2)
    {
        for (int index = indices->i ; index <= indices->j ; ++index)
        {
            *result += arr[index];
        }
        /*because the memory that result points to is in the heap (shared between threads)
        the ending of the thread won't destroy this memory*/
        return result;
    }
    /*large need divide and conquer*/
    else 
    {
        int m = (indices->i+indices->j)/2;

        pthread_t tid1, tid2;
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        /*arguments preparing*/
        arguments* a1 = malloc(sizeof(arguments));
        arguments* a2 = malloc(sizeof(arguments));
        a1->i = indices->i;
        a1->j = m;
        /*i--------m---------j*/
        a2->i = m+1;
        a2->j = indices->j;

        /*used to get returned value*/
        void *s1;
        void *s2;

        pthread_create(&tid1,&attr,&Sum,a1);
        pthread_create(&tid2,&attr,&Sum,a2);

        pthread_join(tid1,&s1);
        pthread_join(tid2,&s2);

        *result = *(int*)s1 + *(int*)s2;

        /*free unused resources */
        free(a1);
        free(a2);
        free(s1);
        free(s2);
        return result;
    }
}



int main(int argc, char** argv)
{
    arguments* arg = malloc(sizeof(arguments));
    arg->i = 0;
    arg->j = 19;

    /*first thread */
    pthread_t tid ;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    /*pointer used for result*/
    void* RESULT;
    pthread_create(&tid,&attr,&Sum,arg);
    pthread_join(tid,&RESULT);
    printf("The sum of the array is %d\n",*(int*)RESULT);
    
    free(RESULT);
    free(arg);

    return 0;
}