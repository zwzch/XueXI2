//
// Created by zw on 17-11-4.
//
#include <cstdlib>
#include <new>
#include <iostream>
#include<functional>
#include <vector>


#include<iomanip>
#include<queue>
using namespace std;

class test{
public:
    int a;
    double x;
    test() {
        a=0;
        x=0.0;
        cout<<"test()"<<endl;
    }
    test(int i,double m):a(i),x(m)
    {
        cout<<"test(int i,double m)"<<endl;
    };

    ~test()
    {
        cout<<"~test()"<<endl;
    }

    void* operator new(size_t sz)
    {
        cout<<"new"<<sz<<"\t"<<"sizeof(test): "<<sizeof(test)<<endl;
        void * p=malloc(sz);
        return p;
    }

    void* operator new[](size_t sz)
    {
        cout<<"new[]"<<sz<<"\t"<<"sizeof(test): "<<sizeof(test)<<endl;
        void * p=malloc(sz);
        return p;
    }

    void operator delete(void* p)
    {
        cout<<"delete"<<endl;
        free(p);
        p=0;
    }

    void operator delete[](void* p)
    {
        cout<<"delete[]"<<endl;
        free(p);
        p=0;
    }
};

int op8()
{
    test* te=new test(1,12);
    delete te;
    test* te1=new test(2,10);
    delete te1;
    test* te2 = new test[12];
    delete []te2;
    test* te3=new test[10];
    delete []te3;
    return 0;
}
double eval(std::function<double(double)> f, double x = 2.0) { return f(x); }
int cpp11ext1() {
    function<double(double)> f0 = [](double x) { return 1; };
    auto f1 = [](double x) { return x; };
    decltype(f0) fa[3] = {f0, f1, [](double x) { return x * x; }};
    vector<decltype(f0)> fv = {f0, f1};
    fv.push_back([](double x) { return x * x; });
    for (int i = 0; i < fv.size(); i++) {
        cout << fv[i](2.0) << endl;
    }
    for (int i = 0; i < 3; i++) {
        cout << fa[i](2.0) << endl;
    }
    for (auto &f : fv) {
        cout << f(2.0) << endl;
    }
    for (auto &f : fa){
        cout << f(2.0) << endl;
    }
    cout << eval(f0) << endl;
    cout << eval(f1) << endl;
    return 0;
}
//先序的顺序插成一棵树 先序中序推后序


class JCB
{
public:
    int start,end,arrive,runtime,zhou,weizhou;
    string name;
    void Show()
    {
        cout.width(9);    cout<<name;
        cout.width(9);    cout<<arrive;
        cout.width(11);   cout<<runtime;
        cout.width(13);   cout<<start;
        cout.width(10);   cout<<end;
        cout.width(10);   cout<<zhou;
        cout.width(9);    cout<<(double)zhou/runtime<<endl;
    }
};
int FCFS()
{
    queue<JCB>  jcbQue;
    int num;
    cout<<"(FCFS)请输入作业数目：";
    cin>>num;
    JCB jcb;
    cout<<"\n请输入作业名，到达时间，运行时间：";
    cin>>jcb.name>>jcb.arrive>>jcb.runtime;
    jcb.start=jcb.arrive;
    jcb.end=jcb.start+jcb.runtime;
    jcb.zhou=jcb.end-jcb.arrive;

    jcbQue.push(jcb);
    JCB jcb2;
    for(int i=2; i<=num; i++)
    {
        jcb2=jcbQue.back();
        cout<<"\n请输入作业名，到达时间，运行时间：";
        cin>>jcb.name>>jcb.arrive>>jcb.runtime;
        jcb.start=jcb2.end;
        jcb.end=jcb.start+jcb.runtime;
        jcb.zhou=jcb.end-jcb.arrive;
        jcbQue.push(jcb);
    }
    cout<<"\n作业名  到达时间  服务时间  开始执行时间  完成时间  周转时间  带权周转时间"<<endl;
    double sum=0;
    cout.setf(ios::left);
    while(!jcbQue.empty())
    {
        jcb=jcbQue.front();
        jcb.Show();
        sum+=(double)jcb.zhou/jcb.runtime;
        jcbQue.pop();
    }

    cout<<"\n先来先服务算法(FCFS)平均带权周转时间："<<sum/num<<endl;

    return 0;
}