#define PATH "/home/zw/ClionProjects/XueXI2/opt.txt"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include "DataType.h"
#include "LogUtil.h"
#include "ZwSh.h"
using  namespace std;
#define OPT2PATH "/home/zw/ClionProjects/XueXI2/opt.txt"
static int req_key;
static int req_value;

typedef struct seq{
    map< string,int > back_map;
} Seq;
static Seq ss;

int Init_Seq(int d_key, int d_value,string url){
    int  fd;
    ss.back_map.insert(pair<string,int >( "back_key",d_key));
    ss.back_map.insert(pair<string,int >( "back_value",d_value));
    map<string, int >::iterator iter;
    for(iter = ss.back_map.begin(); iter != ss.back_map.end(); iter++){
        cout<<iter->first<<" "<<iter->second<<endl;
    }
    const char * _url = url.c_str();
    fd = open(_url,O_RDWR|O_CREAT|O_APPEND);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }
    return fd;
}
template <typename T,typename Y>
int Add_data( S_node<T> key, S_node<Y> value, int fd){
    map<string, int >::iterator iter=ss.back_map.begin();
    if (key.getFlag()!=iter->second){
        cout<<"key数据类型错误"<<endl;
        return 1;
    }
    iter++;
    if (value.getFlag()!=iter->second){
        cout<<"value数据类型错误"<<endl;
        return 2;
    }
//    cout<<"key--->"<<key.getValue()<<"    value----->"<<value.getValue()<<endl;
    stringstream ostr;
    string str;
    ostr<<"key--->";
    ostr<<key.getValue();
    ostr<<"    value----->";
    ostr<<value.getValue();
    ostr>>str;
    cout<<str<<endl;
    char c[100] ;
    strcpy(c,str.c_str());
//    char buf[10] = "123456\n";
    write(fd,c,str.length());
    return 0;
}
void Seqtest(){
    int  fd = Init_Seq(d_string,d_string,"/home/zw/ClionProjects/XueXI2/opt.txt");
//    writeSeq();
    S_node<char> * node = new S_node<char> ('a',d_char);
    S_node<double> *double1 = new S_node< double > (1.1,d_double);
    cout<<double1->getValue()<<"    "<<double1 -> getFlag()<<endl;
    S_node<string> * string_test = new S_node<string>("aaaa",d_string);
    cout<<string_test->getValue()<<endl;
    Add_data(*string_test,*string_test,fd);
}
void logTest(){
    Logger logger;
    logger.Init();
    logger.Debug(AT,"debug");
    logger.Info(AT,"info");
    logger.Warning(AT,"warning");
    logger.Error(AT,"error");
    logger.close();
}
//extern int signal2();

void SmallAndBig(){
    short int x;
    char x0,x1;
    x=0x1122;
    x0=((char *)&x)[0];  //低地址单元
    x1=((char *)&x)[1];  //高地址单元
    printf("x0=0x%x,x1=0x%x",x0,x1);// 若x0=0x11,则是大端; 若x0=0x22,则是小端......
}
int My_Shell(){
    Task task;
    task.test("more /home/zw/ClionProjects/XueXI2/LogConf.xml");
    task.begin();
}
int add(int a, int b){
    return a+b;
}
typedef int  (*fun)(int , int );
//函数数据类型
struct person{
    int  id;
    char * name;

};
void dis(person person1){
    cout<<person1.name<<person1.id<<endl;
}
struct opt{
    int a[10];
    void init(int b[]){
        for (int i=0;i<10;i++){
            a[i]=b[i];
        }
    }
    opt map (fun f, int j){

        opt o1;
        for (int i=0;i<10;i++){
            o1.a[i]= f( this->a[i], j);
        }
        return o1;
    }
    void dis(){
        for(int i=0;i<10;i++){
            cout<<this->a[i]<<" ";
        }
        cout<<endl;
    }
};

int main1(){
//    person p;
//    p.id = 1;
//    p.name = "heihei";
//    dis(p);
//    int (*fun) (int, int)=add;//函数指针
//    cout<<fun(1,2)<<endl;
//    int a=1;
//    int b = 3;
//    fun  ptr=add;
//    cout<<add(&a,&b)<<endl;
//   char a[]="abcde";
//    char *str = (char *)malloc(sizeof(char)*100);
//    memset(str,0,100);
//    strcpy(str,"abcde");
//    cout<<str<<endl;
    return 0;
}
int test1(){
//    ofstream file(OPTPATH,ios::ate);
//    file<<'b'<<endl;
    fstream file2(OPT2PATH,ios::out | ios::in | ios::binary);
    char ch;
    file2.get(ch);
    cout<<ch<<endl;
    file2.close();
}