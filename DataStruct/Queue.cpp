#include<stdio.h>
#include<iostream>
using namespace std;
//dfs，每行只能放一个元素，遍历每行的每个位置，用一个一维数组记录，最后检查是否符合要求
int ans;
int vis[10];
int abs(int x){
    return x > 0 ? x : -x;
}
bool check(int r,int c){
    for(int i = 1;i<r;i++){
        if(vis[i] == c) return false;
        if(vis[i] - c == r - i || vis[i] - c == i - r) return false;
    }
    return true;
}
void dfs(int r){
    if(r > 8){
        ans++;
        return;
    }
    for(int i = 1;i<=8;i++){
        if(check(r,i)){
            vis[r] = i;
            dfs(r+1);
            vis[r] = 0;
        }
    }
}
void QueueTest(){
    dfs(1);
    cout<<ans<<endl;
}