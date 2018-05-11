#include <cstdlib>
#include "iostream"
using namespace std;
typedef struct DataResource{
    int Data;
    int Index;
}Data;
void  StackInit(int );

void AddStack(int);

Data* stack[10];
//
// Created by zw on 18-3-18.
//
void display(int length){
    length--;
    int j=0;
    for(;length-j>=0;j++){
        cout<<stack[length-j]->Data<<endl;
    }
}
void StackTest(){
//    AddData();
    StackInit(10);
//    for(int j=0;j<10;j++){
//       cout<<stack[j]->Index<<endl;
//    }
    AddStack(10);
    AddStack(11);
    AddStack(12);
    display(3);

}

void AddStack(int data) {
    int j=0;
    while(true){
        if(stack[j]->Data==0)
            break;
    j++;
    }
    stack[j]->Data = data;
}

void StackInit(int n) {

    int j;
    for (j=0;j<10;j++){
        stack[j] = (Data *) malloc(sizeof(Data));
        stack[j]->Index = j;
    }
}
