
#include <iostream>
#include <string>
#include <X11/Xlib.h>

using namespace std;

void get_next(string t, int *next);
int Index_KMP(string s, string t);

int StringTest(){
/*
 * KMP
 * */
    string s = "ababadeababaaabadf";
    string t = "ababaaaba";
    int pos = Index_KMP(s, t);
    if (pos != -1){
        cout << "find " << t << " at the index " << pos << " of " << s << endl;
    }
    else{
        cout << "can't find " << t << " in " << s << endl;
    }


    return 0;
}
/*
功能:由串S复制得串T
*/
Status StrCopy(string S, string T)
{
    int i;
    for (i = 0; i <= S[0]; i++)
        T[i] = S[i];           //将S串的字符依次赋给T串
    return 0;
}
int Index_KMP(string s, string t){
    int lens = s.length();
    int lent = t.length();
    int *next = new int[lent];
    get_next(t, next); //对子串t作分析，得到next数组
    cout << "next: ";    //输出next测试而已
    for (int i = 0; i < lent; ++i){
      cout << next[i];
    }
    cout << endl;

    int i = 0;
    int j = 0;
    while (i < lens&&j < lent){//两字母相等则继续，与朴素算法增加了j==0的判断
        if (j == 0 || t[j] == s[i]){
            ++i;
            ++j;
        }
        else{
            j = next[j-1];//j退回合适位置，i值不变
        }
    }
    if (j == lent){//如果最j和lent的大小一样，证明找到了，返回子串在主串中的索引
        return i - lent;
    }
    else{//否则返回-1
        return -1;
    }
}

void get_next(string t, int *next){
    int lent = t.length();
    int i = 0;
    int j = 0;
    next[0] = 0;
    while (i < lent){//i小于t的长度
        if (j == 0 || t[i] == t[j - 1]){//t[i]表示后缀的单个字符
            ++i;                      //t[j]表示前缀的单个字符
            ++j;
            next[i] = j;
        }
        else{
            j = next[j - 1];   //若字符不相同，则j值回溯
        }
    }
}