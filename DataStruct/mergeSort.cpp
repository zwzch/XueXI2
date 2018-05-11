//
// Created by zw on 18-3-22.
//


#include<stdio.h>
#include<stdlib.h>
#define INFINITE 1000

//对两个序列进行合并,数组从mid分开
//对a[start...mid]和a[start+1...end]进行合并
void merge(int *a,int start,int mid,int end)
{
    int i,j,k;
    //申请辅助数组
    int *array1=(int *)malloc(sizeof(int)*(mid-start+2));
    int *array2=(int *)malloc(sizeof(int)*(end-mid+1));

    //把a从mid分开分别赋值给数组
    for(i=0;i<mid-start+1;i++)
        *(array1+i)=a[start+i];
    *(array1+i)=INFINITE;//作为哨兵
    for(i=0;i<end-mid;i++)
        *(array2+i)=a[i+mid+1];
    *(array2+i)=INFINITE;
    //有序的归并到数组a中
    i=j=0;
    for(k=start;k<=end;k++){
        if(*(array1+i) > *(array2+j)){
            a[k]=*(array2+j);
            j++;
        }
        else{
            a[k]=*(array1+i);
            i++;
        }
    }
    free(array1);
    free(array2);
}

//归并排序
void mergeSort(int *a,int start,int end)
{
    int mid=(start+end)/2;
    if(start<end){
        //分解
        mergeSort(a,start,mid);
        mergeSort(a,mid+1,end);
        //合并
        merge(a,start,mid,end);
    }
}

int Merge()
{
    int i;
    int a[7]={0,3,5,8,9,1,2};//不考虑a[0]
    mergeSort(a,1,6);
    for(i=1;i<=6;i++)
        printf("%-4d",a[i]);
    printf("\n");
}
/*
 * 对冒泡排序和快速排序的改进
 * */
/*
 *  1 问题降到一定规模时，改用插入排序

    2 中轴元素的选取

    3 分成3堆，一方面避免相同元素这种情况，另一方面也可以降低子问题的规模。这个感觉有点想DFS中寻找剪枝条件来降低搜索规模一样。
 * */
//如果上面代码中，里面一层循环在某次扫描中没有执行交换，则说明此时数组已经全部有序列，无需再扫描了。
// 因此，增加一个标记，每次发生交换，就标记，如果某次循环完没有标记，则说明已经完成排序。
void BubbleSort_3(int a[], int size)
{
    int lastSwapPos = 0,lastSwapPosTemp = 0;
    for (int i = 0; i < size - 1; i++)
    {
        lastSwapPos = lastSwapPosTemp;
        for (int j = size - 1; j >lastSwapPos; j--)
        {
            if (a[j - 1] > a[j])
            {
                int temp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = temp;

                lastSwapPosTemp = j;
            }
        }
        if (lastSwapPos == lastSwapPosTemp)
            break;

    }
}