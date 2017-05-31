#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

//int	pthread_cond_wait(pthread_cond_t *cv,pthread_mutex_t *mutex);
int i;
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t count_mutex1     = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t  condition_var2   = PTHREAD_COND_INITIALIZER;
pthread_cond_t  condition_var1   = PTHREAD_COND_INITIALIZER;

pthread_t tid[2];

void* doSomeThing(void *arg)
{

int i=0,err1;
while(1){  


   pthread_t id = pthread_self();


if(pthread_equal(id,tid[0]))                       {
//scanf("%d",&i);
//if(i==1){
//break;
//}
pthread_mutex_lock( &count_mutex );

printf("A");


pthread_mutex_unlock( &count_mutex1 );
//pthread_cond_signal( &condition_var1 );

//pthread_cond_wait( &condition_var2,&count_mutex ); 


                                                    }



   
 


 id = pthread_self();


if(pthread_equal(id,tid[1])){
pthread_mutex_lock( &count_mutex1);

//pthread_cond_wait( &condition_var1,&count_mutex );
//pthread_mutex_unlock( &count_mutex1 );
printf("B");
pthread_mutex_unlock( &count_mutex);




//pthread_cond_signal( &condition_var2 );


                                                    }
      

                                                    






}

}

int main(void)
{
    int k;
    int err;
while(k<2){
       err = pthread_create(&(tid[k]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");
k++;
}

    
sleep(15);
 
    return 0;
}
