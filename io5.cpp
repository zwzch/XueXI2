//
// Created by andilyliao on 16-11-23.
//

#include <fstream>
#include <iostream>
#include "../constutil.h"
using namespace std;
/*
goodbit 无错误
Eofbit 已到达文件尾
failbit 非致命的输入/输出错误
badbit 致使的输入/输出错误
 */
int cppio5()
{
    //试图打开一个不已存在的文件时会返回错误
    ofstream test("c:/",ios::out);

    //上一行将导致ios::failbit错误

    if(test.rdstate() == ios::failbit) {
        cout << "Error...!\n";
    }

    test.clear(ios::goodbit);//将当前状态重置为ios::goodbit

    if(test.rdstate() == ios::goodbit) {
        cout << "Fine!\n";
    }

    test.clear(ios::eofbit);//将状态标志设为ios::eofbit.无实际用途.

    if(test.rdstate() == ios::eofbit) {//检测是否已经正确地施行了设置
        cout << "EOF!\n";
        test.close();
    }
    return 0;
}
int cppio1(){

}