//
// Created by zw on 18-3-20.
//
//冒泡、选择、插入、希尔、归并、快排、堆排、桶排、基数的原理、平均时间复杂度、最坏时间复杂度、空间复杂度、是否稳定
#include "iostream"
using namespace std;
int a[101],n;
void quicksort(int left, int right){
    int  i,j,t,temp;
    if (left>right)
        return;
    temp = a[left];//temp是基准数
    i = left;
    j = right;
    while (i!=j){
        while (a[j]>=temp&&i<j)
            j--;
        while (a[i]<=temp)
            i++;
        if (i<j){
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    a[left] = a[i];
    a[i] = temp;
    quicksort(left,i-1);
    quicksort(i+1,right);
}
int MaoPao(){
    int a[] = {1,3,24,23,543,32423,222};
    int i,j;
    for ( i = 0;i < 7; i++){
        for (j = 0 ; j < 7-i ; j++){
            if (a[j]<a[j+1]){
                int t;
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
    int t;
    for (t=0;t<7;t++){
      cout<<a[t]<<endl;
    }
}
void shellsort1(int a[], int n)
{
    int i, j, gap;

    for (gap = n / 2; gap > 0; gap /= 2)   //步长
        for (i = 0; i < gap; i++)         //按组排序
        {
            for (j = i + gap; j < n; j += gap)
            {
                if (a[j] < a[j - gap])
                {
                    int temp = a[j];
                    int k = j - gap;
                    while (k >= 0 && a[k] > temp)
                    {
                        a[k + gap] = a[k];
                        k -= gap;
                    }
                    a[k + gap] = temp;
                }
            }
        }
}
void SelectionSort(int *num,int n)
{


    int i = 0;
    int min = 0;
    int j = 0;
    int tmp = 0;
    for(i = 0;i < n-1;i++)
    {
        min = i;//每次讲min置成无序组起始位置元素下标
        for(j = i;j < n;j++)//遍历无序组，找到最小元素。
        {
            if(num[min]>num[j])
            {
                min = j;
            }
        }
        if(min != i)//如果最小元素不是无序组起始位置元素，则与起始元素交换位置
        {
            tmp = num[min];
            num[min] = num[i];
            num[i] = tmp;
        }
    }
}
void InsertSort(int *num,int n){
    int i = 0;
    int j = 0;
    int temp;
    for (i = 1;i<n;i++){
        temp = num[i];//从待插入组取出第一个元素。
        j = i-1;//i-1即为有序组最后一个元素（与待插入元素相邻）的下标
        while (j>=0 && temp<num[j]){
            num[j+1] = num[j];//若不是合适位置，有序组元素向后移动
            j--;
        }
        num[j+1]=temp;

    }
}
void orderTest(){
    /*
     * 选择排序
     * */
//    int  num[6] = {5,4,3,2,6,9};
//    SelectionSort(num,6);
     /*
      * 插入排序
      * */
//    InsertSort(num,6);

    //希尔排序

//    shellsort1(num,6);

//    int  i;
//    for (i = 0;i<6;i++){
//        cout<<num[i]<<endl;
//    }

    /*
     * 快速排序
     * */
//    int i,j,t;
//    scanf("%d",&n);
//    for (i = 1;i<=n;i++){
//        scanf("%d",&a[i]);
//    }
//    quicksort(1,n);
//
//    for (i=1;i<=n;i++){
//        cout<<a[i]<<endl;
//    }

    /*
     * 归并排序
     * */
    return;
}
