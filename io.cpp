//
// Created by zw on 17-9-27.
//
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include<iostream>
#include <sys/mman.h>
#include <cstring>
#include <sys/sendfile.h>
#include <sstream>

#define MSG_TRY "try again\n"
#define TESTOUTPATH "/home/zw/ClionProjects/XueXI2/opt.txt"
#define TESTPATH "/home/zw/ClionProjects/XueXI2/opt2.txt"
#define MSG_TIMEOUT "timeout\n"
using  namespace std;
int io1()
{
    FILE *fp = fopen("aaa", "r");
    //返回文件指针
    if (fp == NULL) {
        //返回null代表报错 errornumber 代表了某种错误
        //perror打印错误
        perror("error!!!!!");
        cout<<strerror(errno)<<"\t"<<errno<<endl;
//        cerr<<strerror(errno)<<"\t"<<errno<<endl;
        exit(2);
    }
    int res=fclose(fp);
    if(res<0){
        perror("error!!!!!");
        cout<<strerror(errno)<<"\t"<<errno<<endl;
        exit(2);
    }
    cout<<"ok"<<endl;
    return 0;
}
int dup1()
{
    int fd, save_fd;
    char msg[] = "This is a test\n";
    fd = open(TESTOUTPATH, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if(fd<0) {
        perror("open");
        exit(1);
    }
    save_fd = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    write(STDOUT_FILENO, msg, strlen(msg));
    dup2(save_fd, STDOUT_FILENO);
    write(STDOUT_FILENO, msg, strlen(msg));
    close(save_fd);
    return 0;
}
int fputcget(void)
{
    FILE *fp;
    int ch;
    if ( (fp = fopen(TESTOUTPATH, "w+")) == NULL) {
        perror("Open file file2\n");
        exit(1);
    }
//    while ( (ch = fgetc(stdin)) != '0'){
    while ( (ch = getchar()) != '0'){
        fputc(ch, fp);
    }
    rewind(fp);
    while ( (ch = fgetc(fp)) != EOF) {
//        putchar(ch);
        fputc(ch,stdout);
    }
    int res=fclose(fp);
    if(res<0){
        perror("error!!!!!");
        cout<<strerror(errno)<<"\t"<<errno<<endl;
        exit(1);
    }
    cout<<"ok"<<endl;
    return 0;
}
int fseek1()
{
    FILE* fp;
    if ( (fp = fopen(TESTPATH,"r+")) == NULL) {
        perror("Open file textfile");
        exit(1);
    }
    if (fseek(fp, 10, SEEK_SET)<0) {
        perror("Seek file textfile");
        exit(1);
    }
    fputc('K', fp);
    int res=fclose(fp);
    if(res<0){
        perror("error!!!!!");
        cout<<strerror(errno)<<"\t"<<errno<<endl;
        exit(1);
    }
    return 0;
}
int fputsfgets()
{
    //对字符串的操作
    FILE *fpSrc=NULL;
    FILE *fpDst=NULL;
    char str[11];
    if ((fpSrc=fopen(TESTPATH,"r"))==NULL)
    {
        perror("error!!!");
        exit(0);
    }
    if ((fpDst=fopen(TESTOUTPATH,"w"))==NULL)
    {
        perror("error!!!");
        exit(0);
    }
    /*
     *   原型  char *  fgets(char * s, int n,FILE *stream);

         参数：

         s: 字符型指针，指向存储读入数据的缓冲区的地址。

         n: 从流中读入n-1个字符

         stream ： 指向读取的流
     *
     * */
    while(fgets(str,10,fpSrc)!=NULL)
    {
        fputs(str,fpDst);
    }
    if (fpSrc!=NULL)
    {
        fclose(fpSrc);
    }
    if (fpDst!=NULL)
    {
        fclose(fpDst);
    }
    cout<<"ok"<<endl;
    return 0;
}
struct record {
    char name[10];
    int age;
};
int freadfwrite()
{
    //操作结构体
    struct record array[2] = {{"Ken", 24}, {"Knuth", 28}};
    FILE *fp = fopen(TESTOUTPATH, "w");
    if (fp == NULL) {
        perror("Open file recfile");
        exit(1);
    }
    fwrite(array, sizeof(struct record), 2, fp);
    //每个数据块的指针  每个数据的大小 数据个数 文件指针
    fclose(fp);
    struct record array1[2];
    FILE *fp1 = fopen(TESTOUTPATH, "r");
    if (fp1 == NULL) {
        perror("Open file recfile");
        exit(1);
    }
    fread(array1, sizeof(struct record), 2, fp1);
    //每个数据块的指针  每个数据的大小 数据个数 文件指针
    cout<<"Name1: "<<array1[0].name<<" Age1: "<<array1[0].age<<endl;
    cout<<"Name2: "<<array1[1].name<<" Age2: "<<array1[1].age<<endl;
    fclose(fp1);
    return 0;
}
int sysio()
{
    char buf[10];
    int fd, n;
    fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);//必须在真实终端运行，否则报错
    if(fd<0) {
        perror("error!!!");
        exit(1);
    }
    tryagain:
    n = read(fd, buf, 10);
    if (n < 0) {
        if (errno == EAGAIN) {
            sleep(1);
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            goto tryagain;
        }
        perror("read /dev/tty");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    close(fd);
    return 0;
}
int sysio2()
{
    char buf[10];
    int fd, n, i;
    fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);
    if(fd<0) {
        perror("open /dev/tty");
        exit(1);
    }
    for(i=0; i<5; i++) {
        n = read(fd, buf, 10);
        if(n>=0) {
            break;
        }
        if(errno!=EAGAIN) {
            perror("read /dev/tty");
            exit(1);
        }
        sleep(1);
        write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
    }
    if(i==5) {
        write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
    }else {
        write(STDOUT_FILENO, buf, n);
    }
    close(fd);
    return 0;
}
int sysstdio()
{
    char buf[10];
    int n;
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        perror("read STDIN_FILENO");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    return 0;
}
int fcntl1()
{
    char buf[10];
    int n;
    int flags;
    /*
     * int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd, struct flock *lock);
     *  fd：文件描述词。
        cmd：操作命令。
        arg：供命令使用的参数。
        lock：同上。
     */
    flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) {
        perror("fcntl");
        exit(1);
    }
    tryagain:
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        if (errno == EAGAIN) {
            sleep(1);
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            goto tryagain;
        }
        perror("read stdin");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    return 0;
}
int fcntl2()
{
    int val;
    if ((val = fcntl(0, F_GETFL)) < 0) {
        printf("fcntl error for fd %d\n", 0);
        exit(1);
    }
    switch(val & O_ACCMODE) {
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("read write");
            break;
        default:
            fputs("invalid access mode\n", stderr);
            exit(1);
    }
    if (val & O_APPEND)
        printf(", append");
    if (val & O_NONBLOCK)
        printf(", nonblocking");
    putchar('\n');
    return 0;
}
int ioctl1()//做服务端没啥用 ioctl一般做串口通信发布控制指令
{
    struct winsize size;
    if (isatty(STDOUT_FILENO) == 0) {// 检查设备
        exit(1);
    }
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size)<0) {//使用TIOCGWINSZ命令获得终端设备的窗口大小
        perror("error!!!");
        exit(1);
    }
    printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
    return 0;
}
int mmap1()
{
    char *p;
    int fd = open(TESTPATH, O_RDWR);
    if (fd < 0) {
        perror("open hello");
        exit(1);
    }
    p =(char *) mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);
    //将文件打开成了一块内存 系统对硬盘进行同步
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    close(fd);
    p[0] = 'z';
    cout<<p[4]<<'\t'<<p[0]<<'\t'<<p+1<<endl;
    munmap(p, 6);
    return 0;
}
int zerocopy(){
    //不走用户态
    int infd = open( TESTPATH, O_RDONLY );
    int outfd = open( TESTOUTPATH, O_WRONLY );
    struct stat stat_buf;
    fstat( infd, &stat_buf );
//    sendfile( outfd, infd, NULL, stat_buf.st_size );
    sendfile64( outfd, infd, NULL, stat_buf.st_size );//可传输大于2g的数据
    cout<<"ok!!"<<endl;
    return 0;
}
int writeSeq(){
//    stringstream ostr;
//    int a=100;
//    long ll = 123;
//    bool bb = true;
//    string str;
//    ostr<<a;
//    ostr>>str;
//    cout<<str<<endl;
    int fd;
    fd = open("/home/zw/ClionProjects/XueXI2/opt.txt",O_RDWR|O_CREAT|O_APPEND);
//    string str;
    char buf[10] = "123456\n";
    write(fd,buf,strlen(buf));
}