//
// Created by zw on 17-11-15.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define MAXLINE 4096
#define DEFAULT_PORT 6666
int server3(){
    int   listenfd, acceptfd;
    struct sockaddr_in   servaddr;
    //socket结构体
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    //结构体内存置为0
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//大小端转换
    //INADDR_ANY表示所有地址 服务器默认绑定ip地址
    servaddr.sin_port = htons(6666);//大小端转换 绑定端口
    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }

    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }
    //第二个参数backlog
    printf("======waiting for client's request======\n");
    if( (acceptfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
    }else{
        printf("accept succ\n");
        int rcvbuf_len;
        socklen_t len = sizeof(rcvbuf_len);
        if( getsockopt(acceptfd, SOL_SOCKET, SO_RCVBUF, (void *)&rcvbuf_len, &len ) < 0 ){
            //获取socket并且操作
            perror("getsockopt: " );
        }
        printf("the recv buf len: %d\n" , rcvbuf_len );
    }
    char recvMsg[246988]={0};
    ssize_t totalLen = 0;
    while (1) {
        sleep(1);
        ssize_t readLen = read(acceptfd, recvMsg, sizeof(recvMsg));
        printf("readLen:% ld\n",readLen);
        if (readLen < 0) {
            perror("read: ");
            return -1;
        }
        else if (readLen == 0) {
            printf("read finish: len = % ld\n",totalLen);
            close(acceptfd);
            return 0;
        }
        else{
            totalLen += readLen;
        }
    }
    close(acceptfd);
    return 0;
}
int MySend( int iSock, char * pchBuf, size_t tLen){
    int iThisSend;
    unsigned int iSended=0;
    if(tLen == 0)
        return(0);
    while(iSended < tLen){
        do{
            iThisSend = send(iSock, pchBuf, tLen-iSended, 0);
        } while((iThisSend<0) && (errno==EINTR));
        if(iThisSend < 0){
            return(iSended);
        }
        iSended += iThisSend;
        pchBuf += iThisSend;
    }
    return(tLen);
}
int client4(){
    int connfd = 0;
    int cLen = 0;
    struct sockaddr_in client;

    client.sin_family = AF_INET;
    client.sin_port = htons(DEFAULT_PORT);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    connfd = socket( AF_INET , SOCK_STREAM , 0);
    if(connfd < 0){
        printf ("socket() failure!\n" );
        return -1;
    }

    if(connect(connfd, (struct sockaddr*)&client, sizeof(client)) < 0){
        printf("connect() failure!\n" );
        return -1;
    }
    ssize_t writeLen;
    char *sendMsg = "0123456789";
    int tLen=strlen(sendMsg);
    printf("tLen:%d\n" ,tLen);
    int iLen=0;
    char * pBuff= new char [100];
    //将tlen作为前4个字节添加到buf中
    //字符串不需要转网络字节序，但是int需要
    //最终发送的数据是：htonl（4字节长度）+字符串
    *(int*)(pBuff+iLen)= htonl(tLen);//host to net long
    iLen+=sizeof( int);
    memcpy(pBuff+iLen,sendMsg,tLen);
    iLen+=tLen;
    writeLen= MySend(connfd, pBuff, iLen);
    if (writeLen < 0) {
        printf("write failed\n" );
        close(connfd);
        return 0;
    }
    else{
        printf("write sucess, writelen :%d, sendMsg:%s\n",writeLen,sendMsg);
    }
    close(connfd);
    return 0;
}
//=============================================================================================
int MyRecv( int iSock, char * pchBuf, size_t tCount){
    size_t tBytesRead=0;
    int iThisRead;
    while(tBytesRead < tCount){
        do{
            iThisRead = read(iSock, pchBuf, tCount-tBytesRead);
        } while((iThisRead<0) && (errno==EINTR));
        if(iThisRead < 0){
            return(iThisRead);
        }else if (iThisRead == 0)
            return(tBytesRead);
        tBytesRead += iThisRead;
        pchBuf += iThisRead;
    }
}
int server4(){
    int sockfd,acceptfd; /* 监听socket: sock_fd,数据传输socket: acceptfd */
    struct sockaddr_in my_addr; /* 本机地址信息 */
    struct sockaddr_in their_addr; /* 客户地址信息 */
    unsigned int sin_size, myport=6666, lisnum=10;
    if ((sockfd = socket(AF_INET , SOCK_STREAM, 0)) == -1) {
        perror("socket" );
        return -1;
    }
    printf("socket ok \n");
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(DEFAULT_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero), 0);
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr )) == -1) {
        perror("bind" );
        return -2;
    }
    printf("bind ok \n");
    if (listen(sockfd, lisnum) == -1) {
        perror("listen" );
        return -3;
    }
    printf("listen ok \n");
    char recvMsg[1024];
    sin_size = sizeof(my_addr);
    acceptfd = accept(sockfd,(struct sockaddr *)&my_addr,&sin_size);
    if (acceptfd < 0) {
        close(sockfd);
        printf("accept failed\n" );
        return -4;
    }
    ssize_t readLen = MyRecv(acceptfd, recvMsg, sizeof( int));
    if (readLen < 0) {
        printf("read failed\n" );
        return -1;
    }
    int len=( int)ntohl(*( int*)recvMsg);//net to host long
    printf("len:%d\n",len);
    readLen = MyRecv(acceptfd, recvMsg, len);
    if (readLen < 0) {
        printf("read failed\n" );
        return -1;
    }
    recvMsg[len]='\0';
    printf("recvMsg:%s\n" ,recvMsg);
    close(acceptfd);
    return 0;
}
int stringcs1(){
//    client4();
    server4();
    return 0;
}
