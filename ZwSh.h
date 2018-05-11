//
// Created by zw on 17-10-15.
//
#include "iostream"
#include <stdio.h>
#include <vector>
#include "stdlib.h"
#include <list>
#include <numeric>
#include <algorithm>
#include <wait.h>

using  namespace std;
class Task{
public:
    int setArgs(string ss){
    }
    void begin(){
        while(true) {
            string order;
            cout << "ZwSh ====== >>>";
            cin >> order;
            pid_t pid;
            pid = fork();
            if (pid < 0) {
                perror("fail to fork");
                exit(-1);
            } else if (pid == 0) {
                /*子进程*/
//            printf("Sub-process, PID: %u, PPID: %u\n", getpid(), getppid());
//            sleep(20);
                test(order);
            }
            else {/*父进程*/
//                sleep(2);
                wait(NULL);
//                waitpid(pid,NULL,NULL);
                continue;

//                printf("Parent, PID: %u, Sub-process PID: %u\n", getpid(), pid);
//            sleep(20);
            }
        }
//        this->test(order);
    }
    void test(string order){
        std::vector<std::string> result=split(order," ");
        std::cout<<"The result:"<<std::endl;
        int length = result.size();
        char *argv[length];
        string ordername;
        for(int i=0; i<result.size(); i++)
        {
            if(result[i]==""){
                continue;
            }
            if(i==0){
                ordername=result[i];
            }

//            std::cout<<result[i]<<std::endl;
            const char *t = result[i].c_str();
            char *temp=(char*)malloc(sizeof(char)*20);;
            strcpy(temp,t);
//            AddItem(*argv[i],temp);
//            argv[i] = (char*)malloc(sizeof(char)*20);
            argv[i]=temp;
//            printf("%s",argv[i]);
//            const char *p = result[i].c_str();
//            cout<<*p<<endl;
//            cout<<args[i]<<endl;
        }
        argv[length] = NULL;
        char *envp[]={0,NULL};
        string path = "/bin/"+ordername;
        if(  execve(path.data(),argv,envp) == -1) {
            perror ("execve");
            exit(EXIT_FAILURE);
        }
    }
protected:
    std::vector<std::string> split(std::string str,std::string pattern)
    {
        std::string::size_type pos;
        std::vector<std::string> result;
        str+=pattern;//扩展字符串以方便操作
        int size=str.size();

        for(int i=0; i<size; i++)
        {
            pos=str.find(pattern,i);
            if(pos<size)
            {
                std::string s=str.substr(i,pos-i);
                result.push_back(s);
                i=pos+pattern.size()-1;
            }
        }
        return result;
    }
};