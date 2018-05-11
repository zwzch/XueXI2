//
// Created by zw on 17-11-5.
//
#include <boost/thread.hpp>
#include <iostream>
using namespace std;
int bstatomic1()
{
    boost::atomic_int a(0);
    cout<<a<<endl;
    boost::thread t1([&](){
        for (int cnt=0;cnt<100000;cnt++)
        {
            a+=1;
        }
    });
    boost::thread t2([&](){
        for (int cnt=0;cnt<100000;cnt++)
        {
            a-=1;
        }
    });
    t1.join();
    t2.join();
    cout<<a<<endl;
    return 0;
}
