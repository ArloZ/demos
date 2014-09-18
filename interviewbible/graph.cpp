/*
 * date: 2014-09-17
 * author: qile68@163.com
 *
 * 程序员面试宝典（第三版）题目
 *
 * Q1: 编程实现移除"死代码"的功能，如下：
 *      b = a+c;
 *      d = a+f;
 *      d = d*c;
 *      d = d*a;
 *      return d;
 *      其中b = a+c;对求d没有任何贡献，被称为"死代码"
 *
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


bool confire(string msg){
    cout<<"Confire: "<<msg<<" [Y/N] (N) ?"<<endl;
    char buf[8];
    cin>>buf;
    if(buf[0] == 'Y' || buf[0] == 'y')
        return true;
    return false;
}

class Expression{
public:
    string result;
    vector<string> ops;
    vector<string> exp;

    string get_result(){
        return result;
    }
    vector<string> get_ops(){
        return ops;
    }
    vector<string> get_exps(){
        return exp;
    }
    string get_exp(){
        string str = result + " = ";
        for(int i = 0; !ops[i].empty(); i++) {
            if(exp[i].empty()){
                str += ops[i] + ";";
                break;
            }else{
                str += ops[i] + exp[i];
            }
        }
        return str;
    }
    void parse_exp(string expstr){
        string str;
        for(int i = 0; i < expstr.length(); i++) {
            if(expstr[i] == ' ') {
                continue;
            }
            switch(expstr[i]){
                case '=':
                    result = str;
                    str = "";
                    continue;
                case '*':
                case '/':
                case '-':
                case '+':
                    ops.push_back(str);
                    exp.push_back(expstr.substr(i,1));
                    str = "";
                    continue;
                case ';':
                    ops.push_back(str);
                    str = "";
                    continue;
                default:
                    break;
            }
            str += expstr[i];
        }
    }
};

class Graph{
    struct Node{
        string value;
        Node* next;
        Node(string v){
            value = v;
            next = NULL;
        }
    };
    map<string,string> livemap;
    map<string,Node*> vmap;
public:
    Graph(){
        livemap.clear();
        vmap.clear();
    }
    ~Graph(){
        map<string,Node*>::iterator iter;
        Node* p = NULL;
        for(iter = vmap.begin(); iter != vmap.end(); iter ++){
            while(iter->second != NULL){
                p = iter->second->next;
                delete iter->second;
                iter->second = p;
            }
        }
    }
    void print(){
        map<string,Node*>::iterator iter;
        Node* p = NULL;
        for(iter = vmap.begin(); iter != vmap.end(); iter ++){
            cout<<iter->first<<": ";
            p = iter->second;
            while(p != NULL){
                cout<<p->value<<" ";
                p = p->next;
            }
            cout<<endl;
        }
    }
    // save graph use linklist
    void create1(vector<Expression> &explist){
        string res;
        Node* p = NULL;
        for(int i = 0; i < explist.size(); i++){
            res = explist[i].get_result();
            if(vmap.find(res) == vmap.end()){
                vmap.insert(pair<string,Node*>(res,new Node(res)));
            }
            p = vmap[res];
            vector<string> ops = explist[i].get_ops();
            for(int j = 0; j < ops.size();j ++){
                while(p->next != NULL){
                    if(ops[j] == p->value)
                        break;
                    p = p->next;
                }
                if(!p->next){
                    p->next = new Node(ops[j]);
                }
            }
        }
    }
    void get_code(Node* node){
        if(!node){
            //cout<<"return get_code"<<endl;
            return;
        }
        //cout<<"get_code:"<<node->value<<endl;
        while(node != NULL){
            if(livemap.find(node->value) == livemap.end()) {
                livemap.insert(pair<string,string>(node->value,""));
                //cout<<"insert : "<<node->value<<endl;
            }
            node = node->next;
            if(node == NULL)
                break;
            //cout<<"node:"<<node->value<<endl;
            if(vmap.find(node->value) != vmap.end()) {
                //cout<<"recu: "<<node->value<<endl;
                get_code(vmap[node->value]);
            }
        }
        //cout<<"return from recu.."<<endl;
    }
    void death_code(string retvar){
        if(vmap.find(retvar) == vmap.end()){
            cout<<"return variable is invalid !"<<endl;
            return;
        }
        Node* p = vmap[retvar];
        get_code(p);

        cout<<"livemap:"<<endl;
        map<string,string>::iterator it;
        for(it = livemap.begin(); it != livemap.end(); it ++) {
            cout<<it->first<<" ";
        }
        cout<<endl;

        cout<<"Death: ";
        map<string,Node*>::iterator iter;
        for(iter = vmap.begin(); iter != vmap.end(); iter ++){
            p = iter->second;
            if(livemap.find(p->value) != livemap.end())
                continue;
            cout<<p->value<<" ";
        }
        cout<<endl;
    }
};

int main(){
    // test Q1
    if(confire("Test Death code")){
        string expstr;
        vector<Expression> explist;
        cout<<"Please input a expression: [q] to exit"<<endl;
        while(true){
            getline(cin,expstr);
            //cout<<"read in:"<<expstr.size()<<endl;
            if(expstr == "q")
                break;
            if(expstr.size() <= 1)
                continue;
            Expression exp;
            exp.parse_exp(expstr);
            explist.push_back(exp);
        }
        string retvar;
        cout<<"Please input your return variable:";
        cin>>retvar;
        cout<<"Your input: "<<endl;
        for(int i = 0; i < explist.size();i ++){
            cout<<explist[i].get_exp()<<endl;
        }

        Graph graph;
        graph.create1(explist);
        graph.print();
        graph.death_code(retvar);
    }

    return 0;
}
