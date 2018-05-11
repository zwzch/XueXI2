#include <atomic>
#include <sstream>
#include "iostream"
//
// Created by zw on 18-4-22.
//

using  namespace std;
string LeftRotateString(string str, int n) {
//        const char * ss = str.c_str();
        stringstream sb;

        sb<<str.substr(n,str.size());
        sb<<str.substr(0,n);
//        cout<<sb.str()<<endl;
        return sb.str();
}

    int StrToInt(string str) {
            int sum=0;
            int orm=1;
            int  len = str.length();
            const char * xxx = str.c_str();
            for (int i = len-1;i>=0;i--){
                    if (xxx[i]=='+')
                            continue;
                    else if (xxx[i]=='-'){
                            sum=0-sum;
                            continue;
                    }
                    int x = (int)xxx[i];
                    if (x<48||x>57){
                            return 0;
                    }
                    sum+=(x-48)* orm;
                    orm*=10;
            }
            return sum;
    }
