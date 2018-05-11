//
// Created by zw on 18-2-6.
//
//　IO多路复用是指内核一旦发现进程指定的一个或者多个IO条件准备读取，它就通知该进程。IO多路复用适用如下场合：
//
//　　（1）当客户处理多个描述字时（一般是交互式输入和网络套接口），必须使用I/O复用。
//
//　　（2）当一个客户同时处理多个套接口时，而这种情况是可能的，但很少出现。
//
//　　（3）如果一个TCP服务器既要处理监听套接口，又要处理已连接套接口，一般也要用到I/O复用。
//
//　　（4）如果一个服务器即要处理TCP，又要处理UDP，一般要使用I/O复用。
//
//　　（5）如果一个服务器要处理多个服务或多个协议，一般要使用I/O复用。
//
//　　  与多进程和多线程技术相比，I/O多路复用技术的最大优势是系统开销小，系统不必创建进程/线程，也不必维护这些进程/线程，从而大大减小了系统的开销。
#include <zconf.h>
#include <netinet/in.h>
#include <cstdio>
#include <errno.h>
#include <cstring>
#include <arpa/inet.h>
#include <assert.h>
#include <malloc.h>

#define IPADDR "127.0.0.1"
#define PORT 8787
#define MAXLINE 1024
#define LISTENQ 5
#define SIZE 10

typedef struct server_context_st
{
    int  cli_cnt;//客户端个数
    int clifds[SIZE];
    fd_set allfds;//描述符集合
    int maxfd;//句柄最大值
} server_context_st;
static server_context_st * s_srv_ctx = NULL;
/*===========================================================================
* ==========================================================================*/
static int  create_server_proc(const char * ip, int port)
{
    int fd;
    struct sockaddr_in servaddr;//socket结构体
    fd = socket(AF_INET,SOCK_STREAM,0);
    //获得socket的文件描述符
    if (fd == -1){
        fprintf(stderr, "create socket fail,erron:%d,reason:%s\n", errno, strerror(errno));
                 return -1;
    }
    /*一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。*/
    int reuse =1;
    if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&reuse, sizeof(reuse)) == -1){
        //对socket进行设置操作 对他设置可复用的参数
        return -1;
    }
    bzero(&servaddr, sizeof(servaddr));
    //对缓冲区进行清空
    servaddr.sin_family = AF_INET;
    //TCP协议
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
//    将IP地址从字符串格式转换成网络地址格式
    servaddr.sin_port = htons(port);

    if (bind(fd,(struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        //开始绑定端口
        perror("bind error");
        return -1;
    }
    listen(fd,LISTENQ);
    //开始监听
    return fd;
    //返回生成的fd
}
static int  accept_client_proc(int srvfd)
{
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    int clifd = -1;
    printf("accpet clint proc is called.\n");
    ACCEPT:
        clifd = accept(srvfd,(struct sockaddr*)&cliaddr,&cliaddrlen);

    if (clifd == -1){
            if (errno == EINTR){
//                慢系统调用(slow system call)：此术语适用于那些可能永远阻塞的系统调用。永远阻塞的系统调用是指调用有可能永远无法返回，多数网络支持函数都属于这一类。如：若没有客户连接到服务器上，那么服务器的accept调用就没有返回的保证。
//
//                EINTR错误的产生：当阻塞于某个慢系统调用的一个进程捕获某个信号且相应信号处理函数返回时，该系统调用可能返回一个EINTR错误。例如：在socket服务器端，设置了信号捕获机制，有子进程，当在父进程阻塞于慢系统调用时由父进程捕获到了一个有效信号时，内核会致使accept返回一个EINTR错误(被中断的系统调用)。
//
//                当碰到EINTR错误的时候，可以采取有一些可以重启的系统调用要进行重启，而对于有一些系统调用是不能够重启的。例如：accept、read、write、select、和open之类的函数来说，是可以进行重启的。不过对于套接字编程中的connect函数我们是不能重启的，若connect函数返回一个EINTR错误的时候，我们不能再次调用它，否则将立即返回一个错误。针对connect不能重启的处理方法是，必须调用select来等待连接完成。
                goto ACCEPT;
            } else {
                fprintf(stderr, "accept fail,error:%s\n", strerror(errno));
                        return -1;
            }
        }
    fprintf(stdout, "accept a new client: %s:%d\n",
            inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
    //把新的连接描述符添加到数组中
    int  i =0;
    for (i = 0;i<SIZE;i++){
        if (s_srv_ctx->clifds[i]<0){
            s_srv_ctx->clifds[i] = clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }
    if (i==SIZE){
        fprintf(stderr,"too many clients.\n");
            return -1;
    }
}
static int handle_client_msg(int fd, char *buf)
{
    assert(buf);
    //断言测试
    printf("recv buf is :%s\n", buf);
    write(fd,buf,strlen(buf)+1);
    return 0;
}
static void  recv_client_msg(fd_set *readfds)
{
    int  i =0,n =0;
    int clifd;
    char buf[MAXLINE] = {0};
    for (i =0;i <= s_srv_ctx->cli_cnt;i++){
        clifd = s_srv_ctx->clifds[i];
        if (clifd<0){
            continue;
        }
        /*判断客户端套接字是否有数据*/
        if (FD_ISSET(clifd,readfds)){
            //接收客户端发送的信息
            n = read(clifd,buf,MAXLINE);
            if (n<=0){
                /*n==0表示读取完成，客户都关闭套接字*/
                FD_CLR(clifd,&s_srv_ctx->allfds);
                close(clifd);
                s_srv_ctx ->clifds[i] = -1;
                continue;
            }
            handle_client_msg(clifd,buf);
        }
    }
}
static void handle_client_proc(int srvfd){
    int clifd = -1;
    int retval = 0;
    fd_set *readfds = &s_srv_ctx->allfds;
    struct timeval tv;
    int i = 0;
    while (1){
        /*每次调用select前都要重新设置文件描述符和时间，因为事件发生后，文件描述符和时间都被内核修改啦*/
        FD_ZERO(readfds);
        //添加监听套接字
        FD_SET(srvfd,readfds);
        s_srv_ctx ->maxfd = srvfd;
        tv.tv_sec = 30;
        tv.tv_usec = 0;
        for (i = 0; i<s_srv_ctx->cli_cnt;i++){
            clifd = s_srv_ctx->clifds[i];
            if(clifd != -1){
                FD_SET(clifd,readfds);
            }
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd : s_srv_ctx->maxfd);
        }
        retval = select(s_srv_ctx->maxfd +1,readfds,NULL,NULL,&tv);
        if (retval == -1) {
                       fprintf(stderr, "select error:%s.\n", strerror(errno));
                         return;
                     }
                if (retval == 0) {
                         fprintf(stdout, "select is timeout.\n");
                         continue;
                     }
                if (FD_ISSET(srvfd, readfds)) {
                         /*监听客户端请求*/
                         accept_client_proc(srvfd);
                     } else {
                         /*接受处理客户端消息*/
                         recv_client_msg(readfds);
                     }
    }
}
static void server_uninit(){
    if (s_srv_ctx){
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
}
static int server_init(){
    s_srv_ctx = (server_context_st *)malloc(sizeof(server_context_st));
    if (s_srv_ctx == NULL){
        return -1;
    }
    memset(s_srv_ctx,0,sizeof(server_context_st));
    int  i =0;
    for (;i<SIZE;i++){
        s_srv_ctx->clifds[i] = -1;
    }
    return 0;
}
int SelectServer(){
    int srvfd;

    if (server_init()<0){
        return -1;
    }
    srvfd = create_server_proc(IPADDR,PORT);
    if (srvfd <0){
        fprintf(stderr,"sock create or bind fail.\n");
        goto err;
    }
    handle_client_proc(srvfd);
    server_uninit();
    return 0;
    err:
        server_uninit();
        return -1;
}