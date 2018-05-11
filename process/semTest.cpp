//
// Created by zw on 17-11-14.
//
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include <atomic>
#include <iostream>

#define SEM_KEY 4001
#define SHM_KEY 5678
using namespace std;
union semun{
    int val;
};
int test_r(){
    int semid,shmid;
    shmid = shmget(SHM_KEY,sizeof(int),IPC_CREAT|0666);
    //建立shm的共享内存 大小int
    if(shmid<0){
        printf("create shm error\n");
        return -1;
    }
    void * shmptr;
    //建立void*指针
    shmptr =shmat(shmid,NULL,0);
    //指向共享内存
    if(shmptr == (void *)-1){
        printf("shmat error:%s\n",strerror(errno));
        return -1;
    }
    //错误处理
    int *data = (int *) shmptr;
    //data指向shmptr
    semid = semget(SEM_KEY,2,IPC_CREAT|0666);
    union semun semun1;

    semun1.val=0;
    semctl(semid,0,SETVAL,semun1);
    //第一个信号量为0
    semun1.val=1;
    semctl(semid,1,SETVAL,semun1);
    struct sembuf sembuf1;
    cout<<"########"<<endl;
    while(1){
        cout<<"+++++"<<endl;
        sembuf1.sem_num=0;
        sembuf1.sem_op=-1;
        //等待条件
        sembuf1.sem_flg = SEM_UNDO;
        semop(semid,&sembuf1,1);/*reader在这里会阻塞,直到收到信号*/
        printf("the NUM:%d\n",*data);/*输出结果*/
        sembuf1.sem_num=1;/*这里让writer再次就绪，就这样循环*/
        sembuf1.sem_op=1;
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);
    }

}
int test_w(){
    /*create a shm*/
    int semid,shmid;

    shmid = shmget(SHM_KEY,sizeof(int),IPC_CREAT|0666);
    if(shmid<0){
        printf("create shm error\n");
        return -1;
    }

    void * shmptr;
    shmptr =shmat(shmid,NULL,0);
    if(shmptr == (void *)-1){
        printf("shmat error:%s\n",strerror(errno));
        return -1;
    }
  cout<<"++++++"<<endl;
    int * data = (int *)shmptr;
    semid = semget(SEM_KEY,2,0666);
    struct sembuf sembuf1;
    union semun semun1;
    while(1){
        sembuf1.sem_num=1;/*这里指向第2个信号量（sem_num=1）*/
        sembuf1.sem_op=-1;/*操作是-1，因为第2个信号量初始值为1，所以下面不会阻塞*/
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);/*继续*/
        cout<<"input something\n"<<endl;
        scanf("%d",data);  /*用户在终端输入数据*/
        sembuf1.sem_num=0;/*这里指向第一个信号量*/
        sembuf1.sem_op=1;/*操作加1*/
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);/*执行+1后，我们发现，reader阻塞正是由于第一个信号量为0，无法减一，而现在writer先为其加1，那reader就绪！writer继续循环，发现第二个信号量已经减为0，则阻塞了，我们回到reader*/
    }
    return 0;
}
int sem1(){

    test_w();
//   test_r();
}

int  WaitTest(int shmkey, int semkey){
    int semid,shmid;
    shmid = shmget(shmkey,sizeof(int),IPC_CREAT|0666);
    //建立shm的共享内存 大小int
    if(shmid<0){
        printf("create shm error\n");
        return -1;
    }
    cout<<"init shm"<<endl;
    void * shmptr;
    //建立void*指针
    shmptr =shmat(shmid,NULL,0);
    //指向共享内存
    if(shmptr == (void *)-1){
        printf("shmat error:%s\n",strerror(errno));
        return -1;
    }

    //错误处理
    int *data = (int *) shmptr;
    //data指向shmptr
    semid = semget(semkey,2,IPC_CREAT|0666);
    union semun semun1;
    semun1.val=0;
    semctl(semid,0,SETVAL,semun1);
    //第一个信号量为0
    semun1.val=1;
    semctl(semid,1,SETVAL,semun1);
    struct sembuf sembuf1;
    sembuf1.sem_num=0;
    sembuf1.sem_op=-1;
    //等待条件
    sembuf1.sem_flg = SEM_UNDO;
    cout<<"i am wait "<<endl;
    semop(semid,&sembuf1,1);/*reader在这里会阻塞,直到收到信号*/
    printf("the NUM:%d\n",*data);/*输出结果*/
}
int NotifyTest(int shmkey, int semkey){
    int semid,shmid;

    shmid = shmget(shmkey,sizeof(int),IPC_CREAT|0666);
    if(shmid<0){
        printf("create shm error\n");
        return -1;
    }

    void * shmptr;
    shmptr =shmat(shmid,NULL,0);
    if(shmptr == (void *)-1){
        printf("shmat error:%s\n",strerror(errno));
        return -1;
    }
    cout<<"++++++"<<endl;
    int * data = (int *)shmptr;
    semid = semget(semkey,2,0666);
    struct sembuf sembuf1;
    union semun semun1;
//    cout<<"input something\n"<<endl;
//    scanf("%d",data);  /*用户在终端输入数据*/
    sembuf1.sem_num=0;/*这里指向第一个信号量*/
    sembuf1.sem_op=1;/*操作加1*/
    sembuf1.sem_flg=SEM_UNDO;
    semop(semid,&sembuf1,1);
    return 0;
}