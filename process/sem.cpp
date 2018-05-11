////
//// Created by andilyliao on 16-11-10.
////
//#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/sem.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/shm.h>
//#include <errno.h>
//#define SEM_KEY 4001
//#define SHM_KEY 5678
//#include <iostream>
//#include <fstream>
//#include <semaphore.h>
//#include <fcntl.h>
//#include<stdio.h>
//#include<signal.h>
//#include<sys/types.h>
//#include<unistd.h>
//using namespace std;
//
//#define SEM_NAME "/sem_name"
//union semun {
//    int val;
//};
///**
// * 信号量 Linux函数
// * semget();创建一个新的信号量或获取一个已经存在的信号量的键值
// * semctl();控制信号量的函数
// * semop();用户改变信号量的值。也就是使用资源还是释放资源使用权。
// */
//
//int reader(){
//    /*create a shm*/
//    int semid,shmid;
//    shmid = shmget(SHM_KEY,sizeof(int),IPC_CREAT|0666);
//    if(shmid<0){
//        printf("create shm error\n");
//        return -1;
//    }
//    void * shmptr;
//    shmptr =shmat(shmid,NULL,0);
//    if(shmptr == (void *)-1){
//        printf("shmat error:%s\n",strerror(errno));
//        return -1;
//    }
//    int * data = (int *)shmptr;
//    /*
//     * _key  为整型值，用户可以自己设定。有两种情况：
//        1.键值是IPC_PRIVATE，该值通常为0，意思就是创建一个仅能被进程进程给我的信号量。
//        2.键值不是IPC_PRIVATE，我们可以指定键值，例如1234；也可以一个ftok()函数来取得一个唯一的键值。
//_nsems 表示初始化信号量的个数。比如我们要创建一个信号量，则该值为1.,创建2个就是2。
//_semflg  ：信号量的创建方式或权限。有IPC_CREAT，IPC_EXCL。
//IPC_CREAT如果信号量不存在，则创建一个信号量，否则获取。
//IPC_EXCL只有信号量不存在的时候，新的信号量才建立，否则就产生错误。
//     */
//    semid = semget(SEM_KEY,2,IPC_CREAT|0666);/*这里是创建一个semid，并且有两个信号量*/
//    union semun semun1;/*下面这四行就是初始化那两个信号量，一个val=0,另一个val=1*/
//    semun1.val=0;
//    /**
//     * 参数：
//  _semid   信号量的标志码(ID)，也就是semget（）函数的返回值;
//_semnum,  操作信号在信号集中的编号。从0开始。
//_cmd    命令，表示要进行的操作。
//     参数cmd中可以使用的命令如下：
//IPC_STAT读取一个信号量集的数据结构semid_ds，并将其存储在semun中的buf参数中。
//IPC_SET设置信号量集的数据结构semid_ds中的元素ipc_perm，其值取自semun中的buf参数。
//IPC_RMID将信号量集从内存中删除。
//GETALL用于读取信号量集中的所有信号量的值。
//GETNCNT返回正在等待资源的进程数目。
//GETPID返回最后一个执行semop操作的进程的PID。
//GETVAL返回信号量集中的一个单个的信号量的值。
//GETZCNT返回这在等待完全空闲的资源的进程数目。
//SETALL设置信号量集中的所有的信号量的值。
//SETVAL设置信号量集中的一个单独的信号量的值。
//     */
//    semctl(semid,0,SETVAL,semun1);//第一个信号量值为0
//    semun1.val=1;
//    semctl(semid,1,SETVAL,semun1);//第二个信号量值为1
//    struct sembuf sembuf1;
//    while(1){
//        sembuf1.sem_num=0;/*sem_num=0指的是下面操作指向第一个信号量，上面设置可知其 val=0*/
//        sembuf1.sem_op=-1; /*初始化值为0，再-1的话就会等待*/
//        sembuf1.sem_flg=SEM_UNDO;
//        /*
//         *   _semid : 信号量的标识码。也就是semget（）的返回值。
// _sops是一个指向结构体数组的指针。
// struct   sembuf{
//     unsigned short  sem_num;//第几个信号量，第一个信号量为0；
//     short  sem_op;//对该信号量的操作。
//     short _semflg;
//};
//
//sem_num:  操作信号在信号集中的编号。第一个信号的编号为0；
//sem_op : 如果其值为正数，该值会加到现有的信号内含值中。通常用于释放所控资源的使用权；
//         如果sem_op的值为负数，而其绝对值又大于信号的现值，操作将会阻塞，
//         直到信号值大于或等于sem_op的绝对值。通常用于获取资源的使用权；
//         如果sem_op的值为0，则操作将暂时阻塞，直到信号的值变为0。
//_semflg IPC_NOWAIT //对信号的操作不能满足时，semop()不会阻塞，并立即返回，同时设定错误信息。
//        IPC_UNDO //程序结束时(不论正常或不正常)，保证信号值会被重设为semop()调用前的值。
//         这样做的目的在于避免程序在异常情况下结束时未将锁定的资源解锁，造成该资源永远锁定。
//
//nsops：操作结构的数量，恒大于或等于1。
//         */
//        semop(semid,&sembuf1,1);/*reader在这里会阻塞,直到收到信号*/
//        printf("the NUM:%d\n",*data);/*输出结果*/
//        sembuf1.sem_num=1;/*这里让writer再次就绪，就这样循环*/
//        sembuf1.sem_op=1;
//        sembuf1.sem_flg=SEM_UNDO;
//        semop(semid,&sembuf1,1);
//    }
//    return 0;
//}
//
//
//
//int writer(){
//    /*create a shm*/
//    int semid,shmid;
//    shmid = shmget(SHM_KEY,sizeof(int),IPC_CREAT|0666);
//    if(shmid<0){
//        printf("create shm error\n");
//        return -1;
//    }
//    void * shmptr;
//    shmptr =shmat(shmid,NULL,0);
//    if(shmptr == (void *)-1){
//        printf("shmat error:%s\n",strerror(errno));
//        return -1;
//    }
//    int * data = (int *)shmptr;
//    semid = semget(SEM_KEY,2,0666);
//    struct sembuf sembuf1;
//    union semun semun1;
//    while(1){
//        sembuf1.sem_num=1;/*这里指向第2个信号量（sem_num=1）*/
//        sembuf1.sem_op=-1;/*操作是-1，因为第2个信号量初始值为1，所以下面不会阻塞*/
//        sembuf1.sem_flg=SEM_UNDO;
//        semop(semid,&sembuf1,1);/*继续*/
//        scanf("%d",data);  /*用户在终端输入数据*/
//        sembuf1.sem_num=0;/*这里指向第一个信号量*/
//        sembuf1.sem_op=1;/*操作加1*/
//        sembuf1.sem_flg=SEM_UNDO;
//        semop(semid,&sembuf1,1);/*执行+1后，我们发现，reader阻塞正是由于第一个信号量为0，无法减一，而现在writer先为其加1，那reader就绪！writer继续循环，发现第二个信号量已经减为0，则阻塞了，我们回到reader*/
//    }
//    return 0;
//}
//
//int sem1(){
//    writer();
////    reader();
//}//
//// Created by zw on 17-10-16.
////
////
//// Created by andilyliao on 16-11-10.
////
//
//
////这个例子类似于java的信号量
////void semTest(int flag)
////{
////    sem_t *pSem;
////    pSem = sem_open(SEM_NAME, O_CREAT, 0666, 2);//打开信号量，初始值为2,只有两个进程可以进入
////    sem_wait(pSem);//信号量减1,如果小于0则阻塞
////    ofstream fileStream("/opt/testio-cpp/testfile/testdddd.txt", ios_base::app);
////    for (int i = 0; i < 5; ++i)
////    {
////        sleep(1);
////
////        fileStream<<flag;
////        fileStream<<" "<<flush;
////    }
////    sem_post(pSem);//信号量加1
////    sem_close(pSem);//关闭信号量
////}
//
////int sem2()
////{
////    for (int i = 1; i <= 3; ++i)
////    {
////        if (fork() == 0)
////        {
////            semTest(i);
////
////            sleep(1);
////            exit(0);
////        }
////    }
////}
//void SigRoutine(int iSignNum)
//{
//    switch(iSignNum)
//    {
//        case 1:
//            printf("capture SIGHUP signal, signal number is %d\n",iSignNum);
//            break;
//        case 2:
//            printf("capture SIGINT signal, signal number is %d\n",iSignNum);
//            break;
//        case 3:
//            printf("capture SIGINT signal, signal number is %d\n",iSignNum);
//            break;
//    }
//}
//
//int signal2()
//{
//    printf("process ID is %d\n",getpid());
//    if(signal(SIGHUP,SigRoutine) == SIG_ERR)
//    {
//        printf("coundn't register signal handler for SIGHUP");
//    }
//    if(signal(SIGINT,SigRoutine) == SIG_ERR)
//    {
//        printf("coundn't register signal handler for SIGINT");
//    } else{
//        printf("xxxxxxxxxxxxxxx\n");
//    }
//    if(signal(SIGQUIT,SigRoutine) == SIG_ERR)
//    {
//        printf("coundn't register signal handler for SIGQUIT");
//    }
//    while(1)
//        sleep(1);
//    return 0;
//}