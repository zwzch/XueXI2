////
//// Created by zw on 17-10-29.
////
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<errno.h>
//#include<sys/types.h>
//#include<sys/socket.h>
//#include<netinet/in.h>
//#include<arpa/inet.h>
//#include<unistd.h>
//#define MAXLINE 4096
//int server1(){
//    int  listenfd, connfd;
//    struct sockaddr_in  servaddr;
//    char  buff[4096];
//    int  n;
//
//    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
//        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
//        return 0;
//    }
//
//    memset(&servaddr, 0, sizeof(servaddr));
//    servaddr.sin_family = AF_INET;//协议只占了一个字节
//    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//将主机的无符号长整形数转换成网络字节顺序。 不管大端小端都转大端
//    servaddr.sin_port = htons(6666);//将一个无符号短整型数值转换为网络字节序，即大端模式(big-endian)　
//    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
//        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
//        return 0;
//    }
//    if( listen(listenfd, 10) == -1){
//        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
//        return 0;
//    }
//    printf("======waiting for client's request======\n");
//    while(1){
//        //返回一个socket的fd
//        if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
//            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
//            continue;
//        }
//        n = recv(connfd, buff, MAXLINE, 0);
//        buff[n] = '\0';
//        printf("recv msg from client: %s\n", buff);
//        close(connfd);
//    }
//    close(listenfd);
//    return 0;
//}
//int client1(){
//    int   sockfd, n;
//    char  recvline[4096], sendline[4096];
//    struct sockaddr_in  servaddr;
////Type就是socket的类型，对于AF_INET协议族而言有流套接字(SOCK_STREAM)、数据包套接字(SOCK_DGRAM)、原始套接字(SOCK_RAW)
//    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
//        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
//        return 0;
//    }
//    memset(&servaddr, 0, sizeof(servaddr));
//    servaddr.sin_family = AF_INET;
//    servaddr.sin_port = htons(6666);
//    //inet_pton是一个IP地址转换函数，
//    // 可以在将IP地址在“点分十进制”和“二进制整数”之间转换而且，
//    // inet_pton和inet_ntop这2个函数能够处理ipv4和ipv6。
//    if( inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
//        printf("inet_pton error for 127.0.0.1");
//        return 0;
//    }
//    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
//        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
//        return 0;
//    }
//    printf("send msg to server: \n");
//    fgets(sendline, 4096, stdin);
//    if( send(sockfd, sendline, strlen(sendline), 0) < 0){
//        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
//        return 0;
//    }
//    close(sockfd);
//    return 0;
//}
//int cs1(){
////    server1();
//    client1();
//    return 0;
//}
//int server2(){
//    int    listenfd, acceptfd;
//    struct sockaddr_in     servaddr;
//    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
//        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
//        return -1;
//    }
//    memset(&servaddr, 0, sizeof(servaddr));
//    servaddr.sin_family = AF_INET;
//    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//    servaddr.sin_port = htons(6666);
//    if( bind(listenfd, (struct sockaddr*) & servaddr, sizeof (servaddr)) == -1){
//        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
//        return -1;
//    }
//    if( listen(listenfd, 10) == -1){
//        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
//        return -1;
//    }
//    printf("======waiting for client's request======\n");
//    if( (acceptfd = accept(listenfd, (struct sockaddr*) NULL, NULL)) == -1){
//        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
//    }
//    char recvMsg[100];
//
//    ssize_t readLen = read(acceptfd, recvMsg, sizeof(recvMsg));
//    if (readLen < 0) {
//        printf("read error: %s(errno: %d)\n",strerror(errno),errno);
//        return -1;
//    }
//    recvMsg[9] = '\0';
//    printf("readLen:%d, recvMsg:%s\n" ,readLen,recvMsg);
//    sleep(5);
//    recvMsg[1]='9';
//    ssize_t writeLen = write(acceptfd, recvMsg, sizeof(recvMsg));
//    printf("writeLen:%d, sendMsg:%s\n" ,writeLen,recvMsg);
//    if (writeLen < 0) {
//        printf("writeLen error: %s(errno: %d)\n",strerror(errno),errno);
//        return -1;
//    }
//    close(acceptfd);
//    return 0;
//}
//int client2(){
//    int   connfd, n;
//    char  recvline[4096], sendline[4096];
//    struct sockaddr_in  servaddr;
//    if( (connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
//        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
//        return 0;
//    }
//    memset(&servaddr, 0, sizeof(servaddr));
//    servaddr.sin_family = AF_INET;
//    servaddr.sin_port = htons(6666);
//    if( inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
//        printf("inet_pton error for 127.0.0.1\n");
//        return 0;
//    }
//    if(connect(connfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
//        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
//        return 0;
//    }
//    //基本的传入参数的结构体
//    struct timeval stTimeValStruct;
//    stTimeValStruct.tv_sec = 2;
//    stTimeValStruct.tv_usec = 0;
//    /**
//     * level:(级别)： 指定选项代码的类型。
//        SOL_SOCKET: 基本套接口
//        IPPROTO_IP: IPv4套接口
//        IPPROTO_IPV6: IPv6套接口
//        IPPROTO_TCP: TCP套接口
//     */
//    if(setsockopt(connfd, SOL_SOCKET, SO_SNDTIMEO , &stTimeValStruct, sizeof(stTimeValStruct))){
//        printf("setsockopt error: %s(errno: %d)\n", strerror(errno),errno);
//        return 0;
//    }
//    if(setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO , &stTimeValStruct, sizeof(stTimeValStruct))){
//        printf("setsockopt error: %s(errno: %d)\n", strerror(errno),errno);
//        return 0;
//    }
//    ssize_t writeLen;
//    char sendMsg[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '\0'};
//    int count = 0;
//    writeLen = write(connfd, sendMsg, sizeof(sendMsg));
//    if (writeLen < 0) {
//        printf("write error: %s(errno: %d)\n", strerror(errno),errno);
//        close(connfd);
//        return 0;
//    }
//    else{
//        printf("write sucess, writelen :%d, sendMsg:%s\n",writeLen,sendMsg);
//    }
//    char readMsg[10]={0};
//    int readlen= read(connfd,readMsg,sizeof(readMsg));
//    if (readlen < 0) {
//        printf("read error: %s(errno: %d)\n", strerror(errno),errno);
//        close(connfd);
//        return 0;
//    }
//    else{
//        readMsg[9]= '\0';
//        printf("read sucess, readlen :%d, readMsg:%s\n",readlen,readMsg);
//    }
//    close(connfd);
//    return 0;
//}
//int propercs1(){
////    server2();
//    client2();
//    return 0;
//}