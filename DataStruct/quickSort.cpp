////
//// Created by zw on 18-3-22.
////
///*
// * 递归实现的快速排序
// * */
//#include <iostream>
//
//using namespace std;
//int arrs[] = { 23, 65, 12, 3, 8, 76, 345, 90, 21, 75, 34, 61 };
//int arrLen = sizeof(arrs) / sizeof(arrs[0]);
//
//void quickSort(int * arrs, int left, int right){    //挖坑填坑法
//    int oldLeft = left;
//    int oldRight = right;
//    bool flag = true;
//    int baseArr = arrs[oldLeft];     // 先挑选一个基准元素
//    //从数组的右端开始向前找，一直找到比base小的数字为止(包括base同等数)
//    while (left < right){
//        while (left < right && arrs[right] >= baseArr){
//            right--;
//            flag = false;
//        }
//        arrs[left] = arrs[right];    //最终找到了比baseNum小的元素，要做的事情就是此元素放到base的位置
//        while (left < right && arrs[left] <= baseArr){  //从左端开始向后找，一直找到比base大的数字为止（包括base同等数）
//            left++;
//            flag = false;
//        }
//        arrs[right] = arrs[left];    //最终找到了比baseNum大的元素，要做的事情就是将此元素放到最后的位置
//    }
//    arrs[left] = baseArr;           //最后就是把baseNum放到该left的位置，最终，我们发现left位置的左侧数值部分比base小，
//    // left位置右侧数值比base大.至此，我们完成了第一篇排序
//    if (!flag){                     //如果在排序的过程中，发现存在需要交换的位置，则两边可能无序，继续对基准的左右分治处理
//        quickSort(arrs, oldLeft, left-1);
//        quickSort(arrs, left+1, oldRight);
//    }
//}
//
//int QuickSortTest()
//{
//    quickSort(arrs, 0, arrLen - 1);
//    for (int i = 0; i < arrLen; i++)
//        cout << arrs[i] << endl;
////    getch();
//    return 0;
//}