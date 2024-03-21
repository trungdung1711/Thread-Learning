#include <pthread.h>
#include <stdio.h>



int value = 0;
/*The start of the thread*/
void* runner(void* param);



int main(int argc, char** argv)
{
    /*id of the process*/
    pid_t pid;
    /*id of the thread*/
    pthread_t tid;
    /*thread attribute*/
    pthread_attr_t attr;

    /*fork new process*/
    pid = fork();
    if (pid == 0)
    {
        /*child process*/
        /*initialise the process attribute with the default attribute*/
        pthread_attr_init(&attr);
        /*create the new thread*/
        pthread_create(&tid,&attr,&runner,NULL);
        /*this thread will wait for the completion for the new one*/
        pthread_join(tid,NULL);

        printf("CHILD: value = %d\n",value);

    }
    else if (pid > 0)
    {
        /*parent process*/
        /*wait for the children to complete*/
        wait(NULL);
        printf("PARENT: value = %d\n", value);

    }
}



void* runner(void* param)
{
    value = 5;
    pthread_exit(0);
}