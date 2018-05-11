//
// Created by zw on 18-4-21.
//

#include <vector>
#include "algorithm"
#include "iostream"
using namespace std;
int findContent(std::vector <int > &g, std::vector<int > &S){
    //分糖果
    //需求因子g 糖果的大小 S
    std::sort(g.begin(),g.end());
    std::sort(S.begin(),S.end());
    int child = 0;
    int cookie = 0;
    while (child<g.size() && cookie<S.size()){
        if (g[child]<=S[cookie]){
            child++;
            continue;
        }
        cookie++;
    }
    return child;
}

int wiggleMaxLength(std::vector<int > & nums){
    //求最长摇摆子序列
    //有限状态自动机
    if (nums.size()<2){
        return nums.size();
    }
    static const int  BEGIN = 0;
    static const int  UP = 1;
    static const int  DOWN = 2;
    int  STATE = BEGIN;
    int  max_length = 1;
    //数组的最大长度为1

    for (int i=1;i<nums.size();i++){
        switch(STATE){
            case BEGIN:
                if (nums[i]>nums[i-1]){
                    STATE = UP;
                    max_length++;
                } else if (nums[i]<nums[i-1]){
                    STATE = DOWN;
                    max_length++;
                }
                break;
            case UP:
                if (nums[i]<nums[i-1]){
                    STATE = DOWN;
                    max_length++;
                }
                break;
            case DOWN:
                if (nums[i]>nums[i-1]){
                    STATE = UP;
                    max_length++;
                }
                break;
        }

    }
    return max_length;

}

std::string removeKdigits(std::string num, int k){
    std::vector<int  > S;//vector当作栈
    std::string result = "";//储存最终结果
    for (int i=0;i<num.length();i++){
        int  number = num[1]-'0';
        while (S.size() !=0 &&S[S.size()-1]>number&&k>0){
            S.pop_back();
            k--;
        }
        if (number!=0||S.size()!=0){
            S.push_back(number);
        }
        while(S.size() !=0 && k>0){
            S.pop_back();
            k--;
        }
        for (int i=0;i<S.size();i++){
            result.append(1,'0'+S[i]);
        }
        if (result == "")
            return "0";

        cout<<result<<endl;
        return result;
    }
}
void GreedyTest(){
    removeKdigits("14221239",3);
}