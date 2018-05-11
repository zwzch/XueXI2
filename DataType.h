//
// Created by zw on 17-9-29.
//

#ifndef XUEXI2_DATATYPE_H
#define XUEXI2_DATATYPE_H
#endif //XUEXI2_DATATYPE_H
#include <map>
#include <string>
#include <iostream>
#define d_char 0
#define d_int  1
#define d_short 2
#define d_long 3
#define d_string 4
#define d_float 5
#define d_double 6
#define d_bool 7
using namespace std;
template <class T>
class S_enity{
public:
    S_enity (){}
    T getValue() {
        return  value;
    };
    void setValue(T value){
        this->value = value;
    }
    int flag;
    T value;
};

//template <typename T>
//class S_char:public S_node<T>{
//public:
//    S_char(T value){
//        innerchar.setValue(value);
//    }
//    char getValue (){
//        return  this->innerchar.getValue();
//    }
//    int  getFlag(){
//        return this->flag;
//    }
//protected:
//    S_enity <char> innerchar;
//    int flag = d_char;
//};
template <typename T>
class S_node{
public:
    S_node( T value, int flag){
        innerchar.setValue(value);
        this->flag = flag;
    }
    S_node() {

    }
    virtual T getValue(){
        return this->innerchar.getValue();
    }
    virtual int getFlag(){
        return this->flag;
    }
    virtual void setFlag(int flag){
        this->flag = flag;
    }
    protected:
    S_enity <T> innerchar;
    int flag = d_char;
};
