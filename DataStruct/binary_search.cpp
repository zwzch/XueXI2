//
// Created by zw on 18-3-23.
//
# include "iostream"
using namespace std;
int  binarySearch(int *num , int target, int length){
    int low = 0, high = length-1;
    while (low<=high){
        int mid = low+(high-low)/2;
        if (num[mid]<target){low = mid+1;}
        if (num[mid]>target){high = mid-1;}
        if (num[mid]==target){ return mid;}
    }
    return low;
}
int lower_bound(int A[], int n, int key){
    if (A[n-1]<key) return n;
    int lo = 0, hi = n -1;
    while (lo <hi){
        int  mid = (lo + hi) /2;
        if (A[mid] < key) lo = mid + 1;
        else hi = mid;

    }
    return lo;
}
void BSTest(){
    int xxx[6] = {1,2,3,4,5};
    cout<<binarySearch(xxx,5,5)<<endl;
}
