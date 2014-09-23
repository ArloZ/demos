/*
 * date: 2014-09-22
 * author: qile68@163.com
 *
 * 程序员面试宝典（第三版）题目
 *
 * Q1: 整数转化成字符串数，且不用内置函数itoa
 *
 * Q2: 字符串数转化成整数
 *
 * Q3: 编程实现 strcpy
 *
 * Q4: 编程实现把一个字符数组循环右移n位，如 'adlkfalkdf' n = 2，则结果为 'dfadlkfalk'
 *
 * Q5: 求一个字符串中连续出现次数最多的字串
 *
 * Q6: 找出一个字符串中重复出现的最长的子串及其位置
 *
 * Q7: 模拟C++中的strstr函数，该函数返回主串中子串位置以后的所有字符
 *
 * Q8: 将一个句子中的单词进行倒置，标点符号作为单词的一部分，如" I came from tianjin." -> "tianjin. from came I"
 *
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// for Q1
void int2str(char* buf,int i){
    stack<char> st;
    int pos = 0;
    if(i == 0){
        st.push('0');
    }else if(i < 0){
        i = 0 - i;
        buf[pos ++] = '-';
    }
    while(i > 0){
        st.push(i%10 + '0');
        i = i / 10;
    }
    while(!st.empty()){
        buf[pos ++] = st.top();
        st.pop();
    }
    buf[pos++] = '\0';
}

// for Q2
int str2int(char* buf){
    int i = 0;
    int val = 0;
    if(buf[i] == '-')
        i++;
    while(buf[i] != '\0'){
        val = val * 10 + (buf[i] - '0');
        i++;
    }
    if(buf[0] == '-')
        val = 0-val;
    return val;
}

// for Q3
char* _strcpy(char* src,char* dst){
    if(src == NULL || dst == NULL){
        return NULL;
    }
    char* address = src;
    while((*dst++ = *src++) != '\0');
    return address;
}

// for Q4
void loop_move(char* buf,int move){
    int n = strlen(buf) - move;
    char* tmp = new char(move);
    memcpy(tmp,buf+n,move);
    memcpy(buf+move,buf,n);
    memcpy(buf,tmp,move);
    /*
    int len = strlen(buf);
    move = move % len;
    char* tmp = new char(move);
    for(int i = 0; i < move; i++){
        tmp[i] = buf[len-move+i];
    }
    for(int i = len-1; i > 0; i--){
        buf[i] = buf[i - move];
    }
    for(int i = 0; i < move; i++){
        buf[i] = tmp[i];
    }
    delete []tmp;
    */
}

// for Q5
pair<int,string> find_substr(string& originstr){
    if(originstr.length() <= 0){
        return pair<int,string>(0,"");
    }
    int length = originstr.length();
    int max = 0,count = 0;
    string maxstr;
    vector<string> substrs;
    // suffix sub string of origin string
    for(int i = 0; i < length; i++){
        substrs.push_back(originstr.substr(i,length-i));
    }
    for(int i = 0; i < length; i++){
        for(int j = 1; j + i < length; j ++){
            if(substrs[i].substr(0,j) == substrs[i+j].substr(0,j)){
                count ++;
                for(int k = 0; (k + j) < substrs[i+j].length() && substrs[i].substr(0,j) == substrs[i+j].substr(k,j); k += j){
                    count ++;
                }
            }
            if(count > max){
                max = count;
                maxstr = substrs[i].substr(i,j);
            }
            count = 0;
        }
    }
    return pair<int,string>(max,maxstr);
}

// for Q6
pair<int,string> find_longest_repeat_substr(string& originstr){
    if(originstr.length() <= 0){
        return pair<int,string>(0,"");
    }
    int idx = 0;
    int max = 0;
    string longeststr = "";
    int length = originstr.length();
    vector<string> substrs;
    // suffix sub string of origin string
    for(int i = 0; i < length; i++){
        substrs.push_back(originstr.substr(i,length-i));
    }
    for(int i = 0; i < length; i++){
        for(int j = 1; j < length; j++){
            for(int k = i+1; k < length; k++){
                if(substrs[i].substr(0,j) == substrs[k].substr(0,j)){
                    cout<<"sub: i="<<i<<" j="<<j<<" k="<<k<<" max="<<max<<endl;
                    if(j > max){
                        max = j;
                        longeststr = substrs[i].substr(0,j);
                        idx = i;
                    }
                }
            }
        }
    }

    return pair<int,string>(idx,longeststr);
}

// for Q7
string _strstr(string& origin,string& sub){
    int length = origin.length();
    int len = sub.length();
    for(int i = 0; i < length - len; i++){
        if(origin.substr(i,len) == sub){
            return origin.substr(i,length - i);
        }
    }
    return "";
}

// for Q8
void revert(char* buf, int size){
    char tmp;
    for(int i = 0; i < size/2+1; i++){
        tmp = buf[i];
        buf[i] = buf[size - i];
        buf[size - i] = tmp;
    }
}
void revert_sentence(char* sentence){
    int idx = 0;
    int len = 0;
    while(sentence[len++] != '\0');
    len --;
    revert(sentence,len-1);
    for(int i = 0; i < len; i++){
        if(sentence[i] == ' '){
            revert(sentence + idx,i - idx-1);
            idx = i + 1;
        }
    }
}

bool confire(string msg=""){
    cout<<"Confire: "<<msg<<" [Y/N] (N) ?"<<endl;
    char buf[8];
    cin>>buf;
    if(buf[0] == 'Y' || buf[0] == 'y')
        return true;
    return false;
}

int main(){
    // for Q1
    int n = 0;
    cout<<"Please input a num for convert to string: ";
    cin >> n;
    char buf[33];
    int2str(buf,n);
    cout<<"num: "<<n<<" convert to string: "<<buf<<endl;

    // for Q2
    cout<<"str: "<<buf<<" convert to num: "<<str2int(buf)<<endl;

    // for Q3
    char buf2[33];
    _strcpy(buf,buf2);
    cout<<"custom str copy: "<<buf<<" to: "<<buf2<<endl;

    // for Q4
    char buf3[] = {'j','a','e','o','u','i','b','\0'};
    int m = 3;
    cout<<"str: "<<buf3<<" move: "<<m<<" to: ";
    loop_move(buf3,m);
    cout<<buf3<<endl;

    // for Q5
    if(confire("Test find sub string repeat most time")){
        cout<<"Please input a string: ";
        string org;
        cin>>org;
        pair<int,string> maxstr = find_substr(org);
        cout<<"String: "<<org<<" find:"<<maxstr.second<<" is max: "<<maxstr.first<<endl;
    }

    // for Q6
    if(confire("Test find repeat sub string which is longest")){
        cout<<"Please input a string: ";
        string org;
        cin>>org;
        pair<int,string> longeststr = find_longest_repeat_substr(org);
        cout<<"String: "<<org<<" find:"<<longeststr.second<<" is longest at: "<<longeststr.first<<endl;
    }

    // for Q7
    if(confire("Test strstr")){
        string org;
        string sub;
        cout<<"Please input a string: ";
        cin>>org;
        cout<<"Please input a sub string: ";
        cin>>sub;
        cout<<"String: "<<org<<" Sub string: "<<sub<<" _strstr: "<<_strstr(org,sub)<<" strstr: "<<strstr(org.c_str(),sub.c_str())<<endl;
    }

    // for Q8
    if(confire("Test revert sentence")){
        string org;
        cout<<"Please input a string: ";
        while(org.length() <= 0)
            getline(cin,org);

        char* a = strdup(org.c_str());
        cout<<"Input is:"<<a<<endl;
        revert_sentence(a);
        cout<<"Revert is:"<<a<<endl;
    }


}

