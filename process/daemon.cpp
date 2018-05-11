//
// Created by zw on 17-10-21.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fstream>
#include <iostream>
#include <sys/msg.h>

#define P_FIFO "/tmp/p_fifo"
#define P_FIFO2 "/tmp/p_fifo2"
#define MAXFILE 65535
#define OPT2PATH "/home/zw/ClionProjects/XueXI2/opt2.txt"
#define DAEMONLOG "/home/zw/ClionProjects/XueXI2/process/daemon_log.txt"
using namespace std;
volatile sig_atomic_t _running = 1;
#define INPUT 0
#define OUTPUT 1
struct msg_st{
    long int msg_type;
    char text[BUFSIZ];
};
#define MAX_TEXT 512
int pipe_w(char* path,char *argv[]){
    int fd;
    fd= open(path,O_WRONLY|O_NONBLOCK); /*非阻塞方式*/
    write(fd,argv[0], 100); /*将argv[1]写道fd里面去*/
    close(fd);
    exit(0);
    return 0;
}


void sigterm_handler(int arg)
{
    char*args[] = {"diediedie"};
    pipe_w(P_FIFO,args);
//    pid_t new_p;
//    new_p = fork();
//    if(new_p<0){
//        printf("error fork\n");
//        exit(1);
//    }else if(new_p>0){
//        exit(0);//杀死父进程
//    }
//    _running = 0;
}
void setStatus(char a){
    ofstream file(OPT2PATH,ios::ate);
    file<<a<<endl;
}
char getStatus (){
    fstream file2(OPT2PATH,ios::out | ios::in | ios::binary);
    char ch;
    file2.get(ch);
//    cout<<ch<<endl;
    file2.close();
    return ch;
}
void sig2(int arg){
    ofstream file(DAEMONLOG, ios::app);
    file<<"i am dead"<<"   currentPid:"<<getpid()<<endl;
    //            write(fd,buf,len+1);
    int running = 1;
    struct msg_st data;
//    char buffer[BUFSIZ];
    int msgid = -1;
    /*建立消息队列*/
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid == -1){
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    data.msg_type = 1;
    strcpy(data.text, "die");
    if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1){
        fprintf(stderr, "msgsnd failed\n");
        exit(EXIT_FAILURE);
    }
    setStatus('b');
    exit(0);
}
int DameonThread();
int Sp();
int daemon1(){
    pid_t pc;
    int i,fd,len;
    /* 屏蔽一些有关控制终端操作的信号
     * 防止在守护进程没有正常运转起来时，因控制终端受到干扰退出或挂起
     * */
    signal(SIGINT,  SIG_IGN);// 终端中断
    signal(SIGHUP,  SIG_IGN);// 连接挂断
    signal(SIGQUIT, SIG_IGN);// 终端退出
    signal(SIGPIPE, SIG_IGN);// 向无读进程的管道写数据
    signal(SIGTTOU, SIG_IGN);// 后台程序尝试写操作
    signal(SIGTTIN, SIG_IGN);// 后台程序尝试读操作
    signal(SIGTERM, SIG_IGN);// 终止
    pc = fork(); /*第一步 分离子进程，干掉父进程*/
    if(pc<0){
        printf("error fork\n");
        exit(1);
    }else if(pc>0){
        exit(0);//杀死父进程
    }
    else{
        int flag=0;
        char stat = getStatus();
        if(stat!='a')
        {
            flag=1;
        }
        ofstream file(DAEMONLOG, ios::app);
        file<<"current_id"<<getpid()<<" currentFlag"<<flag<<endl;
        switch (flag){
            case 1:
                Sp();
                break;
            case 0:
                int fd[2];
                pipe(fd);
                char * buf="daemon dead\n";
                int len = strlen(buf);
                setsid();
                /*第二步 创建一个新的会话，并担任该会话组的组长*/
                //创建一个新的会话
                /**
                 *    (a) 让进程摆脱原会话的控制；
                      (b) 让进程摆脱原进程组的控制；
                      (c) 让进程摆脱原控制终端的控制；
                 */
                chdir("/"); /*第三步 设置目录为根目录*/
                umask (0); /*第四步 讲权限掩码设置为不屏蔽任何权限*/
                int i;
                for(i=0;i<MAXFILE;i++) /*第五步 关掉所有的设备*/
                    close(i);
                //将文件描述符和io关掉
                /*第六步 设置关闭信号*/
                //    signal(SIGTERM, sigterm_handler);//kill -15 pid
                signal(31, sigterm_handler);//kill -31 pid
                while(_running){
                    //写个日志 守护进程死亡时的记录
                    //        if((fd=open("/home/zw/ClionProjects/XueXI2/process/daemon_log.txt",O_CREAT|O_WRONLY|O_APPEND,0600))<0){
                    //            perror("open");
                    //            exit(1);
                    //        }
                    ofstream file(DAEMONLOG, ios::app);
                    file<<"currentPid: "<<getpid() <<" parentPid: "<<getppid()<<endl;
                    //            write(fd,buf,len+1);
                    sleep(10);
                }
                break;
        }
    }
    return 0;
}

int Sp(){
    int fd[2];
    pipe(fd);
    pid_t mange_pc = fork();//fork出管理 进程
    if(mange_pc<0){
        printf("error fork\n");
        exit(1);
    }
    else if(mange_pc==0)/*分离子进程*/
    {
       DameonThread();
    }
    else{
        char * buf="daemon dead\n";
        int len = strlen(buf);
        setsid();
        /*第二步 创建一个新的会话，并担任该会话组的组长*/
        //创建一个新的会话
        /**
         *    (a) 让进程摆脱原会话的控制；
              (b) 让进程摆脱原进程组的控制；
              (c) 让进程摆脱原控制终端的控制；
         */
        chdir("/"); /*第三步 设置目录为根目录*/
        umask(0); /*第四步 讲权限掩码设置为不屏蔽任何权限*/
        int i;
        for(i=0;i<MAXFILE;i++) /*第五步 关掉所有的设备*/
            close(i);
        //将文件描述符和io关掉
        /*第六步 设置关闭信号*/
        //    signal(SIGTERM, sigterm_handler);//kill -15 pid
        signal(31, sigterm_handler);//kill -31 pid
        ofstream file(DAEMONLOG, ios::app);
            file<<"currentPid: "<<getpid() <<" parentPid: "<<getppid()<<endl;
//进程之间通信
        int running = 1;
        int msgid = -1;
        struct msg_st data;
        long int msgtype = 0;

        /*建立消息队列*/
        msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
        if(msgid == -1){
            fprintf(stderr, "msgget failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        /*从队列中获取消息，直到遇到end消息为止*/
        while(running){
            if(msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1){
                fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }
//            printf("You wrote: %s\n",data.text);
            /*遇到end结束*/
            if(strncmp(data.text, "die", 3) == 0){
                ofstream file(DAEMONLOG, ios::app);
                file<<"received : "<<data.text<<endl;
                pid_t resurgence;
                resurgence = fork();
                if(resurgence==0) //复活的进程
                {
                    ofstream file(DAEMONLOG, ios::app);
                    file<<"DaemonThreadresurgence "<<getpid() <<" parentPid: "<<getppid()<<endl;
                    DameonThread();
                }
//                running = 0;
            }
            sleep(2);
        }
//        while(_running){
//            写个日志 守护进程死亡时的记录
//                if((fd=open("/home/zw/ClionProjects/XueXI2/process/daemon_log.txt",O_CREAT|O_WRONLY|O_APPEND,0600))<0){
//                       perror("open");
//                       exit(1);
//                 }
//            ofstream file(DAEMONLOG, ios::app);
//            file<<"currentPid: "<<getpid() <<" parentPid: "<<getppid()<<endl;
//            //            write(fd,buf,len+1);
//            sleep(10);
//        }
    }
    return 0;
}
int DameonThread(){
    signal(31,sig2);
    setStatus('a');
    char buf[256];
    ofstream file(DAEMONLOG, ios::app);
    file<<"new_currentPid: "<<getpid() <<" parentPid: "<<getppid()<<endl;
    char cache[100];
    int fd;
    memset(cache,0, sizeof(cache));   /*初始化内存*/
    file<<"================"<<endl;
//    if(access(P_FIFO,F_OK)==0){  /*管道文件存在   F_OK判断文件是否存在*/
//        execlp("rm","-f", P_FIFO, NULL);  /*删掉*/
////        printf("access.\n");
//        file<<"access\n"<<endl;
//    }
    file<<"****************"<<endl;
    if(mkfifo(P_FIFO, 0777) < 0){
        file<<"createnamed pipe failed."<<endl;
        printf("createnamed pipe failed.\n");
    }

    fd= open(P_FIFO,O_RDONLY|O_NONBLOCK); /*非阻塞方式打开，只读*/
    while(1){
        file<<"wait"<<endl;
        memset(cache,0, sizeof(cache));
        if((read(fd,cache, 100)) == 0 ){ /*没有读到数据*/
//                    printf("nodata:\n");
        }else{
//                    printf("getdata:%s\n", cache); /*读到数据，将其打印*/
            file<<cache<<endl;
            pid_t resurgence;
            resurgence = fork();
            if(resurgence==0) //复活的进程
            {

                file<<"resurgence_currentPid: "<<getpid() <<" parentPid: "<<getppid()<<endl;
                daemon1();
            }
        }
        sleep(3);/*休眠1s*/
    }
    close(fd);
    return 0;
}
