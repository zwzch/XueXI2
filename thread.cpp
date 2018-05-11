////
//// Created by zw on 17-10-29.
////
//
#include <stdio.h>
#include <pthread.h>
#include <cstdlib>
#include <string.h>
#include <zconf.h>
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>
using namespace std;
//gcc main.cpp thread.cpp -o thread -lpthread

//void* say_hello(void* args){
//    /*线程的运行函数，必须void*，没说的表示返回通用指针、输入通用指针*/
//    printf("hello from thread\n");
//    while(1);
//    pthread_exit((void*)1);
//}
//int thread1111(){
//    pthread_t tid;
//    int iRet = pthread_create(&tid, NULL, say_hello, NULL);
//    /*参数依次是：创建的线程id，线程参数，调用函数名，传入的函数参数*/
//    if (iRet){
//        printf("error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    void *retval;
//    iRet=pthread_join(tid,&retval);
//    if (iRet){
//        printf("error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    printf("retval=%ld\n",(long)retval);
////    exit(0);
//    return 0;
//}
//class Hello{
//public:
//    static void* say_hello(void* args){
//        /*线程的运行函数，必须void*，没说的表示返回通用指针、输入通用指针*/
//        printf("hello from thread\n");
//        pthread_exit((void*)1);
//    }
//};
//int thread2(){
//    pthread_t tid;
//    int iRet = pthread_create(&tid, NULL, Hello::say_hello, NULL);
//    /*参数依次是：创建的线程id，线程参数，调用函数名，传入的函数参数*/
//    if (iRet){
//        printf("error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    void *retval;
//    iRet=pthread_join(tid,&retval);
//    if (iRet){
//        printf("error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    printf("retval=%ld\n",(long)retval);
//    return 0;
//}
//void* say_hello3(void* args){
//    int i=*(int*)args;
//    printf("hello from thread,i=%d\n",i);
//    pthread_exit((void*)1);
//}
//int thread3(){
//    pthread_t tid;
//    int para=10;
//    int iRet = pthread_create(&tid, NULL, say_hello3, &para);
//    if (iRet){
//        printf("error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    void *retval;
//    iRet=pthread_join(tid,&retval);
//    if (iRet){
//        printf("error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    printf("retval=%ld\n",(long)retval);
//    return 0;
//}
//
//struct arg_type{
//    int a;
//    char b[100];
//};
//void* say_hello(void* args){
//    arg_type arg_temp=*(arg_type*)args;
//    printf("hello from thread,arg_temp.a=%d, arg_temp.b=%s\n",arg_temp.a,arg_temp.b);
//    pthread_exit((void*)1);
//}
//int thread4(){
//    pthread_t tid;
//    arg_type arg_temp;
//    arg_temp.a=10;
//    char temp[100]="I am number one.";
//    strncpy(arg_temp.b,temp,sizeof(temp));
//    int iRet = pthread_create(&tid, NULL, say_hello, &arg_temp);
//    if (iRet){
//        printf("error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    void *retval;
//    iRet=pthread_join(tid,&retval);
//    if (iRet){
//        printf("error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    printf("retval=%ld\n",(long)retval);
//    return 0;
//}
//void* thrd_start_routine(void* v)
//{
//    sleep(10);
//    cout<<"created thread"<<endl;
//}
//
//int thread5()
//{
//    pthread_t thrdid;
//
//    pthread_create(&thrdid, NULL, &thrd_start_routine, NULL);
//
//    sleep(5);
//    cout<<"main thread"<<endl;
//    pthread_exit(NULL);
//    return  0;
//}
//int volitaletest1()
//{
//    struct timeval start,end;
//    gettimeofday( &start, NULL );  /*测试起始时间*/
//    double  timeuse;
//    int volatile j;
////    int j;
//    for(j=0;j<10000000;j++)
//        ;
//    gettimeofday( &end, NULL );   /*测试终止时间*/
//    timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
//    timeuse /= 1000000;
//    printf("运行时间为：%f\n",timeuse);
//
//    int ar[10];
//    int* __restrict restar = (int*)malloc(10*sizeof(int));
//    int*  par = ar;
//
//    return 0;
//
//}
//int total_ticket_num=20;
//void *sell_ticket(void *arg){
//    for(int i=0;i<20;i++){
//        if(total_ticket_num>0){
//            sleep(1);
//            printf("sell the %dth ticket\n",20-total_ticket_num+1);
//            total_ticket_num--;
//        }
//    }
//    return (void *) 1;
//}
//int sync1(){
//    int iRet;
//    pthread_t tids[4];
//    int i=0;
//    for(i=0;i<4;i++){
//        int iRet = pthread_create(&tids[i], NULL, &sell_ticket, NULL);
//        if(iRet){
//            printf("pthread_create error, iRet=%d\n",iRet);
//            return iRet;
//        }
//    }
////    sleep(20);
//    void *retval;
//    for(i=0;i<4;i++){
//        iRet=pthread_join(tids[i], &retval);
//        if(iRet){
//            printf("tid=%d join error, iRet=%d\n",tids[i],iRet);
//            return iRet;
//        }
//        printf("retval=%ld\n",(long*)retval);
//    }
//    return 0;
//}

//pthread_mutex_t mutex_x= PTHREAD_MUTEX_INITIALIZER;
//int total_ticket_num=20;
//void *sell_ticket1(void *arg){
//    for(int i=0;i<20;i++){
//        pthread_mutex_lock(&mutex_x);
//        if(total_ticket_num>0){
//            printf("thread1 sell the %dth ticket\n",20-total_ticket_num+1);
//            total_ticket_num--;
//        }
//        sleep(1);
//        pthread_mutex_unlock(&mutex_x);
//        sleep(1);
//    }
//    return 0;
//}
//void *sell_ticket2(void *arg){
//    int iRet=0;
//    for(int i=0;i<10;i++){
//        iRet=pthread_mutex_trylock(&mutex_x);
//        if(iRet==EBUSY){
//            printf ("sell_ticket2:the variable is locked by sell_ticket1.\n");
//        }else if(iRet==0){
//            if(total_ticket_num>0){
//                printf("thread2 sell the %dth ticket\n",20-total_ticket_num+1);
//                total_ticket_num--;
//            }
//            pthread_mutex_unlock(&mutex_x);
//        }
//        sleep(1);
//    }
//    return 0;
//}
//
//int sync3(){
//    pthread_t tids[2];
//    int iRet = pthread_create(&tids[0], NULL, &sell_ticket1, NULL);
//    if(iRet){
//        printf("pthread_create error, iRet=%d\n",iRet);
//        return iRet;
//    }
//    iRet = pthread_create(&tids[1], NULL, &sell_ticket2, NULL);
//    if(iRet){
//        printf("pthread_create error, iRet=%d\n",iRet);
//        return iRet;
//    }
//    sleep(30);
//    void *retval;
//    iRet=pthread_join(tids[0], &retval);
//    if(iRet){
//        printf("tid=%d join error, iRet=%d\n",tids[0],iRet);
//    }else{
//        printf("retval=%ld\n",(long*)retval);
//    }
//    iRet=pthread_join(tids[1], &retval);
//    if(iRet){
//        printf("tid=%d join error, iRet=%d\n",tids[1],iRet);
//    }else{
//        printf("retval=%ld\n",(long*)retval);
//    }
//    return 0;
//}
/*
 * 4
 * */
//pthread_cond_t qready = PTHREAD_COND_INITIALIZER;    /*初始构造条件变量*/
//pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;    /*初始构造锁*/
//int x = 10;
//int y = 20;
//void *func1(void *arg){
//    cout<<"func1 start"<<endl;
//    pthread_mutex_lock(&qlock);
//    while(x<y)
//    {
//        pthread_cond_wait(&qready,&qlock);
//    }
//    pthread_mutex_unlock(&qlock);
//    sleep(3);
//    cout<<"func1 end"<<endl;
//}
//void *func2(void *arg){
//    cout<<"func2 start"<<endl;
//    pthread_mutex_lock(&qlock);
//    x = 20;
//    y = 10;
//    cout<<"has change x and y"<<endl;
//    pthread_mutex_unlock(&qlock);
//    if(x > y){
//        pthread_cond_signal(&qready);
//    }
//    cout<<"func2 end"<<endl;
//}
//int sync4(){
//    pthread_t tid1,tid2;
//    int iRet;
//    iRet = pthread_create(&tid1,NULL,func1,NULL);
//    if(iRet){
//        cout<<"pthread 1 create error"<<endl;
//        return iRet;
//    }
//    sleep(2);
//    iRet = pthread_create(&tid2,NULL,func2,NULL);
//    if(iRet){
//        cout<<"pthread 2 create error"<<endl;
//        return iRet;
//    }
//    sleep(5);
//    return 0;
//}


/*
 * 5
 * */
/*提示出租车到达的条件变量*/
//pthread_cond_t taxiCond = PTHREAD_COND_INITIALIZER;
///*同步锁*/
//pthread_mutex_t taxiMutex = PTHREAD_MUTEX_INITIALIZER;
//
//void * traveler_arrive(void * name){
//    cout<<"Traveler: "<<(char *)name<<" needs a taxi now!"<<endl;
//    pthread_mutex_lock(&taxiMutex);
//    pthread_cond_wait(&taxiCond,&taxiMutex);
//    pthread_mutex_unlock(&taxiMutex);
//    cout<<"Traveler: "<<(char *)name<<" now got a taxi!"<<endl;
//    pthread_exit((void*)0);
//}
//
//void * taxi_arrive(void * name){
//    cout<<"Taxi: "<<(char *)name<<" arrives."<<endl;
//    pthread_cond_signal(&taxiCond);
//    pthread_exit((void*)0);
//}
//
//int sync5(){
//    pthread_t tids[3];
//    int iRet = pthread_create(&tids[0],NULL,taxi_arrive,(void*)(" Jack "));
//    if(iRet){
//        printf("pthread_create error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    printf("Time passing by.\n");
//    sleep(1);
//    iRet = pthread_create(&tids[1],NULL,traveler_arrive,(void*)(" Susan "));
//    if(iRet){
//        printf("pthread_create error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    printf("Time passing by.\n");
//    sleep(1);
//    iRet = pthread_create(&tids[2],NULL,taxi_arrive,(void*)(" Mike "));
//    if(iRet){
//        printf("pthread_create error: iRet=%d\n",iRet);
//        return iRet;
//    }
//    printf("Time passing by.\n");
//    sleep(1);
//    void *retval;
//    for(int i=0;i<3;i++){
//        iRet=pthread_join(tids[i],&retval);
//        if (iRet){
//            printf("pthread_join error: iRet=%d\n",iRet);
//            return iRet;
//        }
//        printf("retval=%ld\n",(long)retval);
//    }
//    return 0;
//}

/*
 * 7
 * */
//#define THREADNUM 5
//pthread_rwlock_t rwlock;
//void *readers(void *arg){
//    pthread_rwlock_rdlock(&rwlock);
//    printf("reader %ld got the lock\n", (long)arg);
//
//    pthread_rwlock_unlock(&rwlock);
//    pthread_exit((void*)0);
//}
//void *writers(void *arg){
//    pthread_rwlock_wrlock(&rwlock);
//    printf("writer %ld got the lock\n", (long)arg);
//
//    pthread_rwlock_unlock(&rwlock);
//    pthread_exit((void*)0);
//}
//int sync7(){
//    int iRet, i;
//    pthread_t writer_id, reader_id;
//    pthread_attr_t attr;
//    int nreadercount = 1, nwritercount = 1;
//    iRet = pthread_rwlock_init(&rwlock, NULL);
//    if (iRet) {
//        fprintf(stderr, "init lock failed\n");
//        return iRet;
//    }
//    pthread_attr_init(&attr);
//    /*pthread_attr_setdetachstate用来设置线程的分离状态
//    也就是说一个线程怎么样终止自己，状态设置为PTHREAD_CREATE_DETACHED
//    表示以分离状态启动线程*/
//    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//    for (i = 0; i < THREADNUM; i++){
//        if (i % 3) {
//            pthread_create(&reader_id, &attr, readers, (void *)nreadercount);
//            printf("create reader %d\n", nreadercount++);
//        } else {
//            pthread_create(&writer_id, &attr, writers, (void *)nwritercount);
//            printf("create writer %d\n", nwritercount++);
//        }
//    }
//    sleep(5);/*sleep是为了等待另外的线程的执行*/
//    return 0;
//}

/*
 * 8
 * */
//#define CUSTOMER_NUM 10
////posix 函数
///* @Scene: 某行业营业厅同时只能服务两个顾客。
// * 有多个顾客到来，每个顾客如果发现服务窗口已满，就等待，
// * 如果有可用的服务窗口，就接受服务。 */
///* 将信号量定义为全局变量，方便多个线程共享 */
//sem_t sem;
///* 每个线程要运行的例程 */
//void * get_service(void *thread_id){
///* 注意：立即保存thread_id的值，因为thread_id是对主线程中循环变量i的引用，它可能马上被修改*/
//    int customer_id = *((int *)thread_id);
//    if(sem_wait(&sem) == 0) {
//        usleep(100); /* service time: 100ms */
//        printf("customer %d receive service ...\n", customer_id);
//        sem_post(&sem);
//    }
//}
//int sync8(){
//    /*初始化信号量，初始值为2，表示有两个顾客可以同时接收服务 */
//    sem_init(&sem,0,2);
//    /*为每个顾客定义一个线程id*/
//    pthread_t customers[CUSTOMER_NUM];
//    int i, iRet;
//    /* 为每个顾客生成一个线程 */
//    for(i = 0; i < CUSTOMER_NUM; i++){
//        int customer_id = i;
//        iRet = pthread_create(&customers[i], NULL, get_service, &customer_id);
//        if(iRet){
//            perror("pthread_create");
//            return iRet;
//        }
//        else{
//            printf("Customer %d arrived.\n", i);
//        }
//        usleep(10);
//    }
//    /* 等待所有顾客的线程结束 */
//    /* 注意：这地方不能再用i做循环变量，因为可能线程中正在访问i的值 */
//    int j;
//    for(j = 0; j < CUSTOMER_NUM; j++) {
//        pthread_join(customers[j], NULL);
//    }
//    /*销毁信号量*/
//    sem_destroy(&sem);
//    return 0;
//}
/*
 * atomic
 * */
//static int count = 0;
//
//void *test_func(void *arg)
//{
//    int i=0;
//    for(i=0;i<20000;++i){
//        __sync_fetch_and_add(&count,1);
//    }
//    return NULL;
//}
//
//int atomic1()
//{
//    pthread_t id[20];
//    int i = 0;
//
//    for(i=0;i<20;++i){
//        pthread_create(&id[i],NULL,test_func,NULL);
//    }
//
//    for(i=0;i<20;++i){
//        pthread_join(id[i],NULL);
//    }
//
//    cout<<count<<endl;
//    return 0;
//}
pthread_mutex_t mutex_x= PTHREAD_MUTEX_INITIALIZER;
int total_ticket_num=20;
void *sell_ticket(void *arg){
    for(int i=0;i<20;i++){
        pthread_mutex_lock(&mutex_x);
        if(total_ticket_num>0){
            sleep(1);
            printf("sell the %dth ticket\n",20-total_ticket_num+1);
            total_ticket_num--;
        }
        pthread_mutex_unlock(&mutex_x);
    }
    return 0;
}

int sync2(){
    int iRet;
    pthread_t tids[4];
    int i=0;
    for(i=0;i<4;i++){
        int iRet = pthread_create(&tids[i], NULL, &sell_ticket, NULL);
        if(iRet){
            printf("pthread_create error, iRet=%d\n",iRet);
            return iRet;
        }
    }
    sleep(30);
    void *retval;
    for(i=0;i<4;i++){
        iRet=pthread_join(tids[i], &retval);
        if(iRet){
            printf("tid=%d join error, iRet=%d\n",tids[i],iRet);
            return iRet;
        }
        printf("retval=%ld\n",(long*)retval);
    }
    return 0;
}


/*
 * affinity
 * */
/*线程亲和性的设置和获取主要通过下面两个函数来实现：
int pthread_setaffinity_np(pthread_t thread, size_t cpusetsize，
const cpu_set_t *cpuset);
int pthread_getaffinity_np(pthread_t thread, size_t cpusetsize,
                           cpu_set_t *cpuset);
//初始化，设为空
void CPU_ZERO (cpu_set_t *set);
//将某个cpu加入cpu集中
void CPU_SET (int cpu, cpu_set_t *set);
//将某个cpu从cpu集中移出
void CPU_CLR (int cpu, cpu_set_t *set);
//判断某个cpu是否已在cpu集中设置了
int CPU_ISSET (int cpu, const cpu_set_t *set);
*/
void * myfun(void *arg)
{
    cpu_set_t mask;
    cpu_set_t get;
    char buf[256];
    int i;
    int j;
    int num = sysconf(_SC_NPROCESSORS_CONF);//返回系统可以使用的核数
    printf("system has %d processor(s)\n", num);

    for (i = 0; i < num; i++) {
        CPU_ZERO(&mask);
        CPU_SET(i, &mask);
        if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
            fprintf(stderr, "set thread affinity failed\n");
        }
        CPU_ZERO(&get);
        if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) < 0) {
            fprintf(stderr, "get thread affinity failed\n");
        }
        for (j = 0; j < num; j++) {
            if (CPU_ISSET(j, &get)) {
                printf("thread %d is running in processor %d\n", (int)pthread_self(), j);
            }
        }
        j = 0;
        while (j++ < 900000000) {
            memset(buf, 0, sizeof(buf));
        }
    }
    pthread_exit(NULL);
}

int affinity1()
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, myfun, NULL) != 0) {
        fprintf(stderr, "thread create failed\n");
        return -1;
    }
    pthread_join(tid, NULL);
    return 0;
}
