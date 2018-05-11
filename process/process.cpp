//
// Created by zw on 17-10-15.
//
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <iostream>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <semaphore.h>
#include <fstream>
#define MAXFILE 65535

using namespace std;

//int fork1(){
//    sem_t *pSem;
//    pSem = sem_open(SEM_NAME, O_CREAT, 0666, 2);
//    pid_t pid;
//    pid = fork();
//    if (pid < 0){
//        perror("fail to fork");
//        exit(-1);
//    }
//    else if (pid == 0){
//        /*子进程*/
//        printf("Sub-process, PID: %u, PPID: %u\n", getpid(), getppid());
//        sleep(20);
//    }
//    else{/*父进程*/
//        printf("Parent, PID: %u, Sub-process PID: %u\n", getpid(), pid);
//        sleep(20);
//    }
//    return 0;
//}
////子进程有独立的栈和堆
//int global = 1; /*初始化的全局变量，存在data段*/
//int forkshare(){
//    pid_t pid;/*存储进程id*/
//    int   stack = 1;/*局部变量，存在栈中*/
//    int  *heap;/*指向堆变量的指针*/
//    heap = (int *)malloc(sizeof(int));
//    *heap = 3;/*设置堆中的值是3*/
//    pid = fork();/*创建一个新的进程*/
//    if (pid < 0){
//        perror("fail to fork");
//        exit(-1);
//    }
//    else if (pid == 0){
//        /*子进程，改变变量的值*/
//        global++;
//        stack++;
//        (*heap)++;
//        /*打印出变量的值*/
//        printf("In sub-process, global: %d, stack: %d, heap: %d\n", global, stack, *heap);
//        exit(0);
//    }
//    else{
//        /*父进程*/
//        sleep(2);/*休眠2秒钟，确保子进程已执行完毕，再执行父进程*/
//        printf("In parent-process, global: %d, stack: %d, heap: %d\n", global, stack, *heap);
//    }
//    return 0;
//}
//int execve1()
//{
//    char *args[] = {"/bin/ls", NULL};
//
//    if(execve ("/bin/ls", args, NULL) == -1) {
//        perror ("execve");
//        exit(EXIT_FAILURE);
//    }
//    cout<<"这句是打印不出来的！！！！！！"<<endl;
//}
//int execve2(){
//    char *argv[]={"ping", "127.0.0.1", NULL};
//
//    char *envp[]={0,NULL}; //传递给执行文件新的环境变量数组
//
//    execve("/bin/ping",argv,envp);
//}
/*
 * daemon1
 *
 * */
//volatile sig_atomic_t _running = 1;
//void sigterm_handler(int arg)
//{
//    _running = 0;
//}
//int daemon1(){
//    pid_t pc;
//    int i,fd,len;
//    char *buf="this is a Dameon\n";
//    len = strlen(buf);
//    /* 屏蔽一些有关控制终端操作的信号
//     * 防止在守护进程没有正常运转起来时，因控制终端受到干扰退出或挂起
//     * */
//    signal(SIGINT,  SIG_IGN);// 终端中断
//    signal(SIGHUP,  SIG_IGN);// 连接挂断
//    signal(SIGQUIT, SIG_IGN);// 终端退出
//    signal(SIGPIPE, SIG_IGN);// 向无读进程的管道写数据
//    signal(SIGTTOU, SIG_IGN);// 后台程序尝试写操作
//    signal(SIGTTIN, SIG_IGN);// 后台程序尝试读操作
//    signal(SIGTERM, SIG_IGN);// 终止
//    pc = fork(); /*第一步 分离子进程，干掉父进程*/
//    if(pc<0){
//        printf("error fork\n");
//        exit(1);
//    }else if(pc>0){
//        exit(0);//杀死父进程
//    }
//    setsid(); /*第二步 创建一个新的会话，并担任该会话组的组长*/
//    //创建一个新的会话
//    /**
//     *    (a) 让进程摆脱原会话的控制；
//          (b) 让进程摆脱原进程组的控制；
//          (c) 让进程摆脱原控制终端的控制；
//     */
//    chdir("/"); /*第三步 设置目录为根目录*/
//    umask(0); /*第四步 讲权限掩码设置为不屏蔽任何权限*/
//
//    for(i=0;i<MAXFILE;i++) /*第五步 关掉所有的设备*/
//        close(i);
//    //将文件描述符和io关掉
//
//    /*第六步 设置关闭信号*/
////    signal(SIGTERM, sigterm_handler);//kill -15 pid
//    signal(31, sigterm_handler);//kill -31 pid
//    while(_running){
//        //写个日志 守护进程死亡时的记录
//        if((fd=open("/tmp/dameon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0){
//            perror("open");
//            exit(1);
//        }
//        write(fd,buf,len+1);
//        close(fd);
//        sleep(10);
//    }
//    return 0;
//}
/*
 * execve1
 * */
//int execve1()
//{
//    char *args[] = {"/bin/ls", NULL};
//
//    if(execve ("/bin/ls", args, NULL) == -1) {
//        perror ("execve");
//        exit(EXIT_FAILURE);
//    }
//    cout<<"这句是打印不出来的！！！！！！"<<endl;
//}

/*
 * fork1
 * */
//int fork1(){
//    pid_t pid;
//    pid = fork();
//    if (pid < 0){
//        perror("fail to fork");
//        exit(-1);
//    }
//    else if (pid == 0){
//        /*子进程*/
//        printf("Sub-process, PID: %u, PPID: %u\n", getpid(), getppid());
//        sleep(5);
//        cout<<"fin"<<endl;
//    }
//    else{/*父进程*/
//        printf("Parent, PID: %u, Sub-process PID: %u\n", getpid(), pid);
//        sleep(10);
//        exit(0);
//    }
//    return 0;
//}
//int global = 1; /*初始化的全局变量，存在data段*/
//int forkshare(){
//    pid_t pid;/*存储进程id*/
//    int   stack = 1;/*局部变量，存在栈中*/
//    int  *heap;/*指向堆变量的指针*/
//    heap = (int *)malloc(sizeof(int));
//    *heap = 3;/*设置堆中的值是3*/
//    pid = fork();/*创建一个新的进程*/
//    if (pid < 0){
//        perror("fail to fork");
//        exit(-1);
//    }
//    else if (pid == 0){
//        /*子进程，改变变量的值*/
//        global++;
//        stack++;
//        (*heap)++;
//        /*打印出变量的值*/
//        printf("In sub-process, global: %d, stack: %d, heap: %d\n", global, stack, *heap);
//        exit(0);
//    }
//    else{
//        /*父进程*/
//        sleep(2);/*休眠2秒钟，确保子进程已执行完毕，再执行父进程*/
//        printf("In parent-process, global: %d, stack: %d, heap: %d\n", global, stack, *heap);
//    }
//    return 0;
//}
//struct msg_st{
//    long int msg_type;//类型
//    char text[BUFSIZ];//char数组
//};
//#define MAX_TEXT 512
//
//int msg_res(){
//    int running = 1;
//    int msgid = -1;
//    struct msg_st data;
//    long int msgtype = 0;
//
//    /*建立消息队列*/
//    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
//    if(msgid == -1){
//        fprintf(stderr, "msgget failed with error: %d\n", errno);
//        exit(EXIT_FAILURE);
//    }
//    /*从队列中获取消息，直到遇到end消息为止*/
//    while(running){
//        /*
//         * msgtyp:  信息类型。 取值如下：
//            msgtyp = 0 ，不分类型，直接返回消息队列中的第一项
//            msgtyp > 0 ,返回第一项 msgtyp与 msgbuf结构体中的mtype相同的信息
//            msgtyp <0 , 返回第一项 mtype小于等于msgtyp绝对值的信息
//
//           msgflg:取值如下：
//            IPC_NOWAIT ,不阻塞
//            IPC_NOERROR ，若信息长度超过参数msgsz，则截断信息而不报错。
//         */
//        if(msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1){
//            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
//            exit(EXIT_FAILURE);
//        }
//        printf("You wrote: %s\n",data.text);
//        /*遇到end结束*/
//        if(strncmp(data.text, "end", 3) == 0){
//            running = 0;
//        }
//    }
//    /*删除消息队列*/
//    if(msgctl(msgid, IPC_RMID, 0) == -1){
//        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
//        exit(EXIT_FAILURE);
//    }
//    exit(EXIT_SUCCESS);
//}
//
//
//
//int msg_send(){
//    int running = 1;
//    struct msg_st data;//数据结构体
//    char buffer[BUFSIZ];
//    int msgid = -1;
//    /*建立消息队列*/
//    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
//    if(msgid == -1){
//        fprintf(stderr, "msgget failed with error: %d\n", errno);
//        exit(EXIT_FAILURE);
//    }
//    /*向消息队列中写消息，直到写入end*/
//    while(running){
//        /*输入数据*/
//        printf("Enter some text: ");
//        fgets(buffer, BUFSIZ, stdin);
//        data.msg_type = 1;
//        strcpy(data.text, buffer);//向数据结构体拷贝数据
//        /*向队列发送数据*/
//        if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1){
//            //发送数据
//            fprintf(stderr, "msgsnd failed\n");
//            exit(EXIT_FAILURE);
//        }
//        /*输入end结束输入*/
//        if(strncmp(buffer, "end", 3) == 0)
//            running = 0;
//        sleep(1);
//    }
//    exit(EXIT_SUCCESS);
//}
//int msg1(){
////    msg_send();
//    msg_res();
//}
//
//#define INPUT 0
//#define OUTPUT 1
//int pipe1() {
//    int fd[2];
//    /*定义子进程号 */
//    pid_t pid;
//    char buf[256];
//    int returned_count;
//    /*创建无名管道*/
//    pipe(fd);
//    /*创建子进程*/
//    pid=fork();
//    if(pid<0) {
//        printf("Error in fork\n");
//        exit(1);
//    }else if(pid == 0) { /*执行子进程*/
//        printf("in the child process...\n");
//        /*子进程向父进程写数据，关闭管道的读端*/
//        close(fd[INPUT]);
//        write(fd[OUTPUT], "hello world", strlen("hello world"));
//        exit(0);
//    }else { /*执行父进程*/
//        printf("in the parent process...\n");
//        /*父进程从管道读取子进程写的数据，关闭管道的写端*/
//        close(fd[OUTPUT]);
//        returned_count = read(fd[INPUT], buf, sizeof(buf));
//        printf("%d bytes of data received from child process: %s\n", returned_count, buf);
//    }
//    return 0;
//}
//#define P_FIFO "/home/zw/temp/p_fifo"
//int pipe_r(){
//    char cache[100];
//    int fd;
//    memset(cache,0, sizeof(cache));   /*初始化内存*/
//    if(access(P_FIFO,F_OK)==0){  /*管道文件存在   F_OK判断文件是否存在*/
//        execlp("rm","-f", P_FIFO, NULL);  /*删掉*/
//        printf("access.\n");
//    }
//    if(mkfifo(P_FIFO, 0777) < 0){
//        printf("createnamed pipe failed.\n");
//    }
//    fd= open(P_FIFO,O_RDONLY|O_NONBLOCK); /*非阻塞方式打开，只读*/
//    while(1){
//        memset(cache,0, sizeof(cache));
//        if((read(fd,cache, 100)) == 0 ){ /*没有读到数据*/
//            printf("nodata:\n");
//        }
//        else{
//            printf("getdata:%s\n", cache); /*读到数据，将其打印*/
//        }
//        sleep(3);/*休眠1s*/
//    }
//    close(fd);
//    return 0;
//}
//
//int pipe_w(char *argv[]){
//    int fd;
//    fd= open(P_FIFO,O_WRONLY|O_NONBLOCK); /*非阻塞方式*/
//    write(fd,argv[0], 100); /*将argv[1]写道fd里面去*/
//    close(fd);
//    return 0;
//}
//int pipe2(){
//    char *argv[]={"aaaa"};
//    pipe_w(argv);
////    pipe_r();
//}
//#define SEM_KEY 4001
//#define SHM_KEY 5678
//
//union semun {
//    int val;
//};
////两个值 0 或者非0
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
//    struct sembuf sembuf1; //信号量的方法
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
//        //semop哪个信号量的值减一
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
//
////    writer();
//    reader();
//}
//#define SEM_NAME "/sem_name"
//void semTest(int flag)
//{
//    sem_t *pSem;
//    pSem = sem_open(SEM_NAME, O_CREAT, 0666, 2);//打开信号量，初始值为2,只有两个进程可以进入
//    sem_wait(pSem);//信号量减1,如果小于0则阻塞
//    ofstream fileStream("/home/zw/ClionProjects/XueXI2/test/test.txt", ios_base::app);
//    for (int i = 0; i < 5; ++i)
//    {
//        sleep(1);
//
//        fileStream<<flag;
//        fileStream<<" "<<flush;
//    }
//    sem_post(pSem);//信号量加1
//    sem_close(pSem);//关闭信号量
//}
//
//int sem2()
//{
//    for (int i = 1; i <= 3; ++i)
//    {
//        if (fork() == 0)
//        {
//            semTest(i);
//
//            sleep(1);
//            exit(0);
//        }
//    }
//}
//typedef struct{
//
//    char name[8];
//
//    int age;
//
//} people;
//
//int write(int argc, char** argv)
//{
//    int shm_id,i;
//    key_t key;
//    char temp[8];
//    people *p_map;
//    char pathname[30] ;
//    strcpy(pathname,"/tmp") ;
//    key = ftok(pathname,0x03);
//    if(key==-1)
//    {
//        perror("ftok error");
//        return -1;
//    }
//    printf("key=%d\n",key) ;
//    shm_id=shmget(key,4096,IPC_CREAT|IPC_EXCL|0600);
//    if(shm_id==-1)
//    {
//        perror("shmget error");
//        return -1;
//    }
//    printf("shm_id=%d\n", shm_id) ;
//    p_map=(people*)shmat(shm_id,NULL,0);
//    memset(temp, 0x00, sizeof(temp)) ;
//    strcpy(temp,"test") ;
//    temp[4]='0';
//    for(i = 0;i<3;i++)
//    {
//        temp[4]+=1;
//        strncpy((p_map+i)->name,temp,5);
//        (p_map+i)->age=0+i;
//    }
//    shmdt(p_map) ;
//    return 0 ;
//}
//int read(int argc, char** argv)
//{
//
//    int shm_id,i;
//
//    key_t key;
//
//    people *p_map;
//
//    char pathname[30] ;
//
//
//
//    strcpy(pathname,"/tmp") ;
//
//    key = ftok(pathname,0x03);
//
//    if(key == -1)
//
//    {
//
//        perror("ftok error");
//
//        return -1;
//
//    }
//
//    printf("key=%d\n", key) ;
//
//    shm_id = shmget(key,0, 0);
//
//    if(shm_id == -1)
//
//    {
//
//        perror("shmget error");
//
//        return -1;
//
//    }
//
//    printf("shm_id=%d\n", shm_id) ;
//
//    p_map = (people*)shmat(shm_id,NULL,0);
//
//    for(i = 0;i<3;i++)
//
//    {
//
//        printf( "name:%s\n",(*(p_map+i)).name );
//
//        printf( "age %d\n",(*(p_map+i)).age );
//
//    }
//
//    if(shmdt(p_map) == -1)
//
//    {
//
//        perror("detach error");
//
//        return -1;
//
//    }
//
//    return 0 ;
//
//}
//void SignalHandler(int iSignNum)
//{
//    printf("capture signal number:%d\n",iSignNum);
//    _exit(0);
//}
//
//int signal1()
//{   // 程序运行Ctrl+c将不能终止，因为“Ctrl+c”产生的信号SIGINT
////将交给已经注册的自定义函数处理，“Ctrl+\”终止是因为它产生的SIGQUIT尚未在程序中注册
//    signal(SIGINT,SignalHandler);
//    while(1)
//        sleep(1);
//    return 0;
//}
/*
 * signal2
 * */
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
//    }
//    if(signal(SIGQUIT,SigRoutine) == SIG_ERR)
//    {
//        printf("coundn't register signal handler for SIGQUIT");
//
//    while(1)
//        sleep(1);
//    return 0;
//}
//

//void Handler(int i)
//{
//    printf("signal handler ..\n");
//}
//
//int signal3()
//{
//    int i;
//    signal(SIGALRM,Handler);
//    //SIGNALRM 时钟触发器
//    // alarm专门为SIGALRM信号而设，使系统在一定时间后发送信号
//    alarm(5);
//    for(i=1;i<=10;i++)
//    {
//        sleep(1);
//        printf("sleep %ds\n",i);
//    }
//    return 0;
//}
//void SigHandler(int iSignNum)
//{
//    printf("signal:%d\n",iSignNum);
//}
//
//int signal4()
//{
//    signal(SIGALRM,SigHandler);
//    alarm(5);
//    printf("before pause \n");
//    /*
//     * 当程序运行时，pause会使当前的进程挂起（进入睡眠状态），
//     * 直到我们向该进程发送SIGINT中断信号，进程才会被唤醒，
//     * 并处理信号，处理完信号后pause函数才返回，并继续运行该程序。
//
//      任何信号都可使pause唤醒。
//     */
//    pause();
//    printf("after pause \n");
//    return 0;
//}
//
//int wait1(){
//    /*fork一个子进程*/
//    pid_t pid = fork();
//    if(pid<0){
//        perror("fork error\n");
//        return 0;
//    }else if(pid > 0){/*父进程*/
//        printf("Parent process\n");
//        pid_t pr=wait(NULL);
//        printf("Parent process, I catched a child process with pid of %d\n",pr);
//    }else if(pid == 0){
//        printf("Sub-process, PID: %u, PPID: %u\n", getpid(), getppid());
//        exit(0);
//    }
//    return 0;
//}

int zombie(){
    /*fork一个子进程*/
    pid_t pid = fork();
    if (pid > 0){/*父进程*/
        printf("in parent process, sleep for one miniute...zZ...\n");
        sleep(60);
        printf("after sleeping, and exit!\n");
    }
    else if(pid == 0){
        /*子进程退出，成为一个僵死进程*/
        sleep(3);
        printf("in child process, and exit!\n");
        exit(0);
    }
    return 0;
}