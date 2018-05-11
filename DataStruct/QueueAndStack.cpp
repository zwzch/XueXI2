//
// Created by zw on 18-4-19.
//

#include <stack>
#include <clocale>
#include <iostream>
#include <queue>

class MyStack{
    //队列实现栈
private:
   std::queue<int > _data;
public:
    MyStack (){}
    void push(int x){
        std::queue<int > temp_queue;
        temp_queue.push(x);
        while (!_data.empty()){
            temp_queue.push(_data.front());
            _data.pop();
        }
        while (!temp_queue.empty()){
            _data.push(temp_queue.front());
            temp_queue.pop();
        }
    }
    int  pop(){
        int  x = _data.front();
        _data.pop();
        return  x;
    }
    int  top(){
        return _data.front();
    }
    bool empty(){
        return _data.empty();
    }
};

class MinStack{
    //包含最小值的栈 O1
private:
    std::stack<int > _data ;
    std::stack<int >  _min;
public:
    MinStack() {}
    void push(int x){
        _data.push(x);
        if (_min.empty()){
            _min.push(x);
        } else{
            if (x > _min.top()){
                x = _min.top();
            }
            _min.push(x);
        }
    }
    void pop(){
        _data.pop();
        _min.pop();
    }
};
class MyQueue {
    //使用栈实现队列
private: std::stack <int > _data;
public:
    MyQueue() {}
    void push(int x){
        std::stack<int > temp_stack;
        while (!_data.empty()){
            temp_stack.push(_data.top());
            temp_stack.pop();
        }
        temp_stack.push(x);
        while (!temp_stack.empty()){
            _data.push(temp_stack.top());
            temp_stack.pop();
        }
    }
    int  pop(){
        int  x = _data.top();
        _data.pop();
        return  x;
    }
    int peek (){
        return  _data.top();
    }
    bool empty(){
        return  _data.empty();
    }
};


bool check_is_vaild_order(std::queue<int > &order){
    //整体算法复杂度On
    std::stack<int >S;
    //模拟栈
    int  n = order.size();
    for (int i=1;i<=n;i++){
        S.push(i);
        while (!S.empty()&&order.front()==S.top()){
            S.pop();
            order.pop();
        }
    }
    if (!S.empty()){
        return false;
    }
    return true;
}
using namespace   std;


class Solution {
public:
    int calculate(std::string s) {
        static const int STATE_BEGIN = 0;
        static const int NUMBER_STATE = 1;
        static const int OPERATION_STATE = 2;
        std::stack<int> number_stack;
        std::stack<char> operation_stack;
        int number = 0;
        int STATE = STATE_BEGIN;
        int compuate_flag = 0;
        for (int i = 0; i < s.length(); i++){
            if (s[i] == ' '){
                continue;
            }
            switch(STATE){
                case STATE_BEGIN:
                    if (s[i] >= '0' && s[i] <= '9'){
                        STATE = NUMBER_STATE;
                    }
                    else{
                        STATE = OPERATION_STATE;
                    }
                    i--;
                    break;
                case NUMBER_STATE:
                    if (s[i] >= '0' && s[i] <= '9'){
                        number = number * 10 + s[i] - '0';
                    }
                    else{
                        number_stack.push(number);
                        if (compuate_flag == 1){
                            compute(number_stack, operation_stack);
                        }
                        number = 0;
                        i--;
                        STATE = OPERATION_STATE;
                    }
                    break;
                case OPERATION_STATE:
                    if (s[i] == '+' || s[i] == '-'){
                        operation_stack.push(s[i]);
                        compuate_flag = 1;
                    }
                    else if (s[i] == '('){
                        STATE = NUMBER_STATE;
                        compuate_flag = 0;
                    }
                    else if (s[i] >= '0' && s[i] <= '9'){
                        STATE = NUMBER_STATE;
                        i--;
                    }
                    else if (s[i] == ')'){
                        compute(number_stack, operation_stack);
                    }
                    break;
            }
        }
        if (number != 0){
            number_stack.push(number);
            compute(number_stack, operation_stack);
        }
        if (number == 0 && number_stack.empty()){
            return 0;
        }
        return number_stack.top();
    }
private:
    void compute(std::stack<int> &number_stack,
                 std::stack<char> &operation_stack){
        if (number_stack.size() < 2){
            return;
        }
        int num2 = number_stack.top();
        number_stack.pop();
        int num1 = number_stack.top();
        number_stack.pop();
        if (operation_stack.top() == '+'){
            number_stack.push(num1 + num2);
        }
        else if(operation_stack.top() == '-'){
            number_stack.push(num1 - num2);
        }
        operation_stack.pop();
    }
};

int  findKthLargest(std::vector<int >&nums, int k){
    //优先级队列的构造函数是nlogn  最小堆实现top k
    std::priority_queue<int ,std::vector <int > ,std::greater<int >> small_heap;
    for (int i=0;i<nums.size();i++){
        if (small_heap.size()<k){
            small_heap.push(nums[i]);
        }
        else if (small_heap.top()<nums[i])
        {
            small_heap.pop();
            small_heap.push(nums[i]);
        }
    }
    return small_heap.top();
}

class MedianFinder {
    //维护两个堆 最大堆 最小堆 两个堆中间相差不过1
public:
    MedianFinder() {
    }
    void addNum(int num) {
        if (big_queue.empty()){
            big_queue.push(num);
            return;
        }
        if (big_queue.size() == small_queue.size()){
            if (num < big_queue.top()){
                big_queue.push(num);
            }
            else{
                small_queue.push(num);
            }
        }
        else if(big_queue.size() > small_queue.size()){
            if (num > big_queue.top()){
                small_queue.push(num);
            }
            else{
                small_queue.push(big_queue.top());
                big_queue.pop();
                big_queue.push(num);
            }
        }
        else if(big_queue.size() < small_queue.size()){
            if (num < small_queue.top()){
                big_queue.push(num);
            }
            else{
                big_queue.push(small_queue.top());
                small_queue.pop();
                small_queue.push(num);
            }
        }
    }
    double findMedian(){
        if (big_queue.size() == small_queue.size()){
            return (big_queue.top() + small_queue.top()) / 2;
        }
        else if (big_queue.size() > small_queue.size()){
            return big_queue.top();
        }
        return small_queue.top();
    }
private:
    std::priority_queue<double> big_queue;
    std::priority_queue<double, std::vector<double>,
            std::greater<double> > small_queue;
};

int stackTest(){
//    std::stack<int> S;
//    if (S.empty()){
//        cout<<"empty"<<endl;
//    }
//    S.push(5);
//    S.push(6);
//    S.push(10);
//
//    cout<<S.top()<<endl;
//    S.pop();
//    S.pop();
//    cout<<S.top()<<endl;
//
//    cout<<S.size()<<endl;

//    std::string s = "12345";
//    int  number = 0;
//    for (int i=0;i<s.length();i++){
////        number =
//        number = number* 10 + s[i] - '0';
//    }
//    cout<<"number = "<<number<<endl;



//
//std::priority_queue <int> big_heap;
//    //优先级队列 默认构造最大堆
//    std::priority_queue<int ,std::vector <int > ,std::greater<int >> small_heap;
//    std::priority_queue<int ,std::vector <int > ,std::less<int >> big_heap2;
//    //最小堆 最大堆构造
//    int test[] = {6,10,1,7,99,4,33};
//    for (int i=0;i<7;i++){
//        big_heap.push(test[i]);
//    }
//    cout<<big_heap.top()<<endl;
//    big_heap.push(1000);
//    cout<<big_heap.top()<<endl;
//    for (int i=0;i<3;i++){
//        big_heap.pop();
//    }
//    cout<<big_heap.top()<<endl;
}
