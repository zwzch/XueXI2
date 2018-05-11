#include <pthread.h>
#include <zconf.h>

//
// Created by zw on 17-11-14.
//
int Flag=1;
pthread_mutex_t mutex_nor= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_try= PTHREAD_MUTEX_INITIALIZER;
int IsTry(){
    while (true){
        sleep(15);
        break;
    }
    Flag=0;
    return Flag;
}
int Sync_Beg(){
    int it1=0;
    int it2=0;
    it1 =pthread_mutex_trylock(&mutex_try);
    IsTry();
    pthread_mutex_unlock(&mutex_try);

    return  0;
}
int Sync_End(){
    int it1=0;
    int it2=0;
    return  0;
}
