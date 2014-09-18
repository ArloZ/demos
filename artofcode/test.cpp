#include <iostream>

using namespace std;

int main(){
    unsigned int i = 81;
    // 通过除法和取余实现双重循环
    while(i --){
        if(i/9%3 == i%9%3)
            continue;
        cout<<"A="<<i/9+1<<" B="<<i%9+1<<endl;
    }
}
