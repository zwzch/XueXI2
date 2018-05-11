//
// Created by zw on 18-4-21.
//
#include "iostream"
#include <stdio.h>
#include <vector>
int equation(int n, int m){
    if (n==1||m==1){
        return 1;
    } else if (n<m)
        return equation(n,n);
    else if(n==m)
        return 1+equation(n,n-1);
    else
        return equation(n-m,m)+equation(n,m-1);
}
//void split(int n, int k){
//
//    int  i;
//    if (n==0)
//
//}
//void display(int k){
//    int  i;
//    for ( i=0;i<k;i++){
//        cout<<x[i]<<endl;
//    }
//}
//using namespace std;
//vector<int> twoSum(vector<int>& nums, int target) {
//    int size = nums.size();
//    int i =0;
//    for (;i<nums.size();i++)
//}