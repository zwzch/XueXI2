//
// Created by zw on 17-11-18.
//

//#include <netinet/in.h>
//#include <sys/socket.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <sys/epoll.h>
//#include <time.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include <arpa/inet.h>
//
//#define MAXSIZE     1024
//#define IPADDRESS   "127.0.0.1"
//#define SERV_PORT   6666
//#define FDSIZE        1024
//#define EPOLLEVENTS 20
//#define LISTENQ     5
//void add_event(int epollfd,int fd,int state);//添加时间
//void delete_event(int epollfd,int fd,int state);//删除事件
//void modify_event(int epollfd,int fd,int state);//修改事件
//
//
//
//void handle_connection(int sockfd);//链接
//void handle_events(int epollfd,struct epoll_event *events,int num,int sockfd,char *buf);//执行读写操作
//void do_read(int epollfd,int fd,int sockfd,char *buf);//读方法
//void do_write(int epollfd,int fd,int sockfd,char *buf);//写
//
//int count=0;
//int clientepoll1(){
//    int                 sockfd;
//    struct sockaddr_in  servaddr;
//    sockfd = socket(AF_INET,SOCK_STREAM,0);
//    bzero(&servaddr,sizeof(servaddr));
//    servaddr.sin_family = AF_INET;
//    servaddr.sin_port = htons(SERV_PORT);
//    inet_pton(AF_INET,IPADDRESS,&servaddr.sin_addr);
//    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
//    /*处理连接*/
//    handle_connection(sockfd);
//    close(sockfd);
//    return 0;
//}
//
//void handle_connection(int sockfd){
//    int epollfd;
//    struct epoll_event events[EPOLLEVENTS];
//    char buf[MAXSIZE];
//    int ret;
//    epollfd = epoll_create(FDSIZE);
//    add_event(epollfd,STDIN_FILENO,EPOLLIN);
//    while (1 ) {
//        ret = epoll_wait(epollfd,events,EPOLLEVENTS,-1);
//        handle_events(epollfd,events,ret,sockfd,buf);
//    }
//    close(epollfd);
//}
//
//void handle_events(int epollfd,struct epoll_event *events,int num,int sockfd,char *buf){
//    int fd;
//    int i;
//    for (i = 0;i < num;i++){
//        fd = events[i].data.fd;
//        if (events[i].events & EPOLLIN)
//            do_read(epollfd,fd,sockfd,buf);
//        else if (events[i].events & EPOLLOUT)
//            do_write(epollfd,fd,sockfd,buf);
//    }
//}
//
//void do_read(int epollfd,int fd,int sockfd,char *buf){
//    int nread;
//    nread = read(fd,buf,MAXSIZE);
//    if (nread == -1){
//        perror("read error:");
//        close(fd);
//    }
//    else if (nread == 0){
//        fprintf(stderr,"server close.\n");
//        close(fd);
//    }
//    else{
//        if (fd == STDIN_FILENO)
//            add_event(epollfd,sockfd,EPOLLOUT);
//        else{
//            delete_event(epollfd,sockfd,EPOLLIN);
//            add_event(epollfd,STDOUT_FILENO,EPOLLOUT);
//        }
//    }
//}
//
//void do_write(int epollfd,int fd,int sockfd,char *buf){
//    int nwrite;
//    char temp[100];
//    buf[strlen(buf)-1]='\0';
//    snprintf(temp,sizeof(temp),"%s_%02d\n",buf,count++);
//    nwrite = write(fd,temp,strlen(temp));
//    if (nwrite == -1){
//        perror("write error:");
//        close(fd);
//    }
//    else{
//        if (fd == STDOUT_FILENO)
//            delete_event(epollfd,fd,EPOLLOUT);
//        else
//            modify_event(epollfd,fd,EPOLLIN);
//    }
//    memset(buf,0,MAXSIZE);
//}
//
//
////=============================================================================================
///*函数声明*/
///*创建套接字并进行绑定*/
//int socket_bind(const char* ip,int port);
///*IO多路复用epoll*/
//void do_epoll(int listenfd);
///*事件处理函数*/
//void handle_eventsserver(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf);
///*处理接收到的连接*/
//void handle_accpet(int epollfd,int listenfd);
///*读处理*/
//void do_readserver(int epollfd,int fd,char *buf);
///*写处理*/
//void do_writeserver(int epollfd,int fd,char *buf);
//
//int serverepoll1(){
//    int  listenfd;
//    listenfd = socket_bind(IPADDRESS,SERV_PORT);
//    listen(listenfd,LISTENQ);//backlog=5
//    do_epoll(listenfd);
//    return 0;
//}
//
//int socket_bind(const char* ip,int port){
//    int  listenfd;
//    struct sockaddr_in servaddr;
//    listenfd = socket(AF_INET,SOCK_STREAM,0);
//    if (listenfd == -1){
//        perror("socket error:");
//        exit(1);
//    }
//    bzero(&servaddr,sizeof(servaddr));
//    servaddr.sin_family = AF_INET;
//    inet_pton(AF_INET,ip,&servaddr.sin_addr);
//    servaddr.sin_port = htons(port);
//    if (bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1){
//        perror("bind error: ");
//        exit(1);
//    }
//    return listenfd;
//}
//
//void do_epoll(int listenfd){
//    int epollfd;
//    struct epoll_event events[EPOLLEVENTS];
//    int ret;
//    char buf[MAXSIZE];
//    memset(buf,0,MAXSIZE);
//    /*创建一个描述符*/
//    epollfd = epoll_create(FDSIZE);
//    /*添加监听描述符事件*/
//    add_event(epollfd,listenfd,EPOLLIN);
//    while(1){
//        /*获取已经准备好的描述符事件*/
//        ret = epoll_wait(epollfd,events,EPOLLEVENTS,-1);
//        handle_eventsserver(epollfd,events,ret,listenfd,buf);
//        //重点注意这个ret，它返回的是已经有事儿的fd的个数
//        //这样一会儿轮循的就不是所有的fd了
//    }
//    close(epollfd);
//}
//
//void handle_eventsserver(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf){
//    int i;
//    int fd;
//    /*进行选好遍历*/
//    for (i = 0;i < num;i++){
//        fd = events[i].data.fd;
//        /*根据描述符的类型和事件类型进行处理*/
//        if ((fd == listenfd) &&(events[i].events & EPOLLIN))
//            handle_accpet(epollfd,listenfd);
//        else if (events[i].events & EPOLLIN)
//            do_readserver(epollfd,fd,buf);
//        else if (events[i].events & EPOLLOUT)
//            do_writeserver(epollfd,fd,buf);
//    }
//}
//
//void handle_accpet(int epollfd,int listenfd){
//    int clifd;
//    struct sockaddr_in cliaddr;
//    socklen_t  cliaddrlen;
//    clifd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen);
//    if (clifd == -1)
//        perror("accpet error:");
//    else{
//        printf("accept a new client: %s:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
//        /*添加一个客户描述符和事件*/
//        add_event(epollfd,clifd,EPOLLIN);
//    }
//}
//
//void do_readserver(int epollfd,int fd,char *buf){
//    int nread;
//    nread = read(fd,buf,MAXSIZE);
//    if (nread == -1){
//        perror("read error:");
//        close(fd);
//        delete_event(epollfd,fd,EPOLLIN);
//    }
//    else if (nread == 0){
//        fprintf(stderr,"client close.\n");
//        close(fd);
//        delete_event(epollfd,fd,EPOLLIN);
//    }
//    else{
//        printf("read message is : %s",buf);
//        /*修改描述符对应的事件，由读改为写*/
//        modify_event(epollfd,fd,EPOLLOUT);
//    }
//}
//
//void do_writeserver(int epollfd,int fd,char *buf){
//    int nwrite;
//    nwrite = write(fd,buf,strlen(buf));
//    if (nwrite == -1){
//        perror("write error:");
//        close(fd);
//        delete_event(epollfd,fd,EPOLLOUT);
//    }
//    else
//        modify_event(epollfd,fd,EPOLLIN);
//    memset(buf,0,MAXSIZE);
//}
////====================================================================================
//
//void add_event(int epollfd,int fd,int state){
//    struct epoll_event ev;
//    ev.events = state;
//    ev.data.fd = fd;
//    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
//}
//
//void delete_event(int epollfd,int fd,int state){
//    struct epoll_event ev;
//    ev.events = state;
//    ev.data.fd = fd;
//    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
//}
//
//void modify_event(int epollfd,int fd,int state){
//    struct epoll_event ev;
//    ev.events = state;
//    ev.data.fd = fd;
//    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
//}
//
//int epoll1(){
//    clientepoll1();
////    serverepoll1();
//    return 0;
//}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define MAXBUF 1024
#define MAXEPOLLSIZE 10000

/*
 * 设置句柄为非阻塞方式
 */
int setnonblocking(int sockfd)
{
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1)
    {
        return -1;
    }
    return 0;
}

/*********************************************************************
* filename: epoll-server.c
* 演示epoll接受海量socket并进行处理响应的方法
*********************************************************************/

int epoll_server(int argc, char **argv)
{
    int listenfd, connfd, epfd, sockfd, nfds, n, curfds;
    socklen_t len;
    struct sockaddr_in my_addr, their_addr;
    unsigned int myport, lisnum;
    char buf[MAXBUF + 1];
    // 声明epoll_event结构体的变量，ev用于注册事件，events数组用于回传要处理的事件
    struct epoll_event ev;
    struct epoll_event events[MAXEPOLLSIZE];
    if (argv[1])
        myport = atoi(argv[1]);
    else
        myport = 7838;
    if (argv[2])
        lisnum = atoi(argv[2]);
    else
        lisnum = 2;
    // 开启 socket 监听
    if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    } else
        printf("socket 创建成功！\n");
    // 把socket设置为非阻塞方式
    setnonblocking(listenfd);
    bzero(&my_addr, sizeof(my_addr));//清空我地址的内存
    my_addr.sin_family = PF_INET;
    my_addr.sin_port = htons(myport);
    if (argv[3])
        my_addr.sin_addr.s_addr = inet_addr(argv[3]);
    else
        my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    } else
        printf("IP 地址和端口绑定成功\n");

    if (listen(listenfd, lisnum) == -1)
    {
        perror("listen");
        exit(1);
    } else
        printf("开启服务成功！\n");

    // 创建 epoll句柄，把监听 socket 加入到 epoll 集合里 */
    epfd = epoll_create(MAXEPOLLSIZE); /*epoll专用的文件描述符*/
    len = sizeof(struct sockaddr_in);
    ev.events = EPOLLIN|EPOLLET;
    ev.data.fd = listenfd;
    // 将listenfd注册到epoll事件
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) < 0)
    {
        fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
        return -1;
    } else
        printf("监听 socket 加入 epoll 成功！\n");
    curfds = 1;
    while (1)
    {
        // 等待有事件发生
        nfds = epoll_wait(epfd, events, curfds, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            break;
        }
        // 处理所有事件
        for (n = 0; n < nfds; ++n)
        {
            // 如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接
            if (events[n].data.fd == listenfd)
            {
                len = sizeof(struct sockaddr);
                connfd = accept(listenfd, (struct sockaddr *) &their_addr, &len);
                if (connfd < 0)
                {
                    perror("accept");
                    continue;
                }
                else
                    printf("有连接来自于： %s:%d， 分配的 socket 为:%d\n", inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port), connfd);

                setnonblocking(connfd);
                // 设置用于注册的 读操作 事件
                ev.events = EPOLLIN | EPOLLET;
                // 设置用于读操作的文件描述符
                ev.data.fd = connfd;
                //注册ev
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
                curfds ++;
            }
            else if (events[n].events & EPOLLIN) // 如果是已经连接的用户，并且收到数据，那么进行读入
            {
                printf("EPOLLIN\n");
                if ((sockfd = events[n].data.fd) < 0)
                    continue;
                int len;
                bzero(buf, MAXBUF + 1);
                /* 接收客户端的消息 */
                /*len = read(sockfd, buf, MAXBUF);*/
                len = recv(sockfd, buf, MAXBUF, 0);
                if (len > 0)
                    printf("%d接收消息成功:'%s'，共%d个字节的数据\n", sockfd, buf, len);
                else
                {
                    if (len < 0)
                    {
                        printf("消息接收失败！错误代码是%d，错误信息是'%s'\n", errno, strerror(errno));
                        epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, &ev);
                        curfds--;
                        continue;
                    }
                }
                // 设置用于写操作的文件描述符
                ev.data.fd = sockfd;
                // 设置用于注册的写操作事件
                ev.events = EPOLLOUT | EPOLLET;
                /*修改sockfd上要处理的事件为EPOLLOUT*/
                epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev); //修改标识符，等待下一个循环时发送数据，异步处理的精髓!!!!! ?????
            }
            else if (events[n].events & EPOLLOUT) // 如果有数据发送
            {
                printf("EPOLLOUT\n");
                sockfd = events[n].data.fd;
                bzero(buf, MAXBUF + 1);
                strcpy(buf, "Server already processes!");
                send(sockfd, buf, strlen(buf), 0);
                // 设置用于读操作的文件描述符
                ev.data.fd = sockfd;
                // 设置用于注册的读操作事件
                ev.events = EPOLLIN | EPOLLET;
                // 修改sockfd上要处理的事件为EPOLIN
                epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
            }
        }
    }
    close(listenfd);
    return 0;
}