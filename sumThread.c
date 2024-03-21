#include <pthread.h>
#include <stdio.h>
#include <malloc.h>



/*shared memory*/
int arr[20] = {11,12,13,14,15,16,17,18,19,20
,21,22,23,24,25,26,27,28,29,30};



typedef struct
{
    int i;
    int j;
} arguments;




void* Sum(void* param)
{
    arguments* indices = (arguments*)(param);
    int i = indices->i;
    int j = indices->j;
    int num = j-i+1;
    int sum = 0;
    if (num <= 2)
    {
        for (int index = i ; index <= j ; ++index)
        {
            sum += arr[index];
        }
        int* result = malloc(sizeof(int));
        *result = sum;
        return result;
    }
    else 
    {
        int m = (i+j)/2;

        pthread_t tid1, tid2;
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        arguments* a1 = malloc(sizeof(arguments));
        arguments* a2 = malloc(sizeof(arguments));
        a1->i = i;
        a1->j = m;

        a2->i = m+1;
        a2->j = j;

        void *s1;
        void *s2;

        pthread_create(&tid1,&attr,&Sum,a1);
        pthread_create(&tid2,&attr,&Sum,a2);

        pthread_join(tid1,&s1);
        pthread_join(tid2,&s2);

        int sum = *(int*)s1 + *(int*)s2;
        int* s = malloc(sizeof(int));
        *s = sum;
        free(a1);
        free(a2);
        free(s1);
        free(s2);
        return s;
    }
}



int main()
{
    arguments* arg = malloc(sizeof(arguments));
    arg->i = 0;
    arg->j = 19;

    pthread_t tid ;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    void* RESULT;
    pthread_create(&tid,&attr,&Sum,arg);
    pthread_join(tid,&RESULT);
    printf("The sum is %d",*(int*)RESULT);
    free(RESULT);
    free(arg);

    return 0;
}