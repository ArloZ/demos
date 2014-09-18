/*
 * date: 2014-09-17
 * author: qile68@163.com
 *
 * 程序员面试宝典（第三版）题目
 *
 * Q1: 编程实现栈的入栈/出栈操作
 *
 * Q2: 用两个栈实现队列功能
 *
 */

#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* next;
    Node(){
        data = 0;
        next = NULL;
    }
    Node(int d,Node* n=NULL){
        data = d;
        next = n;
    }
};
class Stack{
    Node* top;
public:
    Stack(){
        top = NULL;
    }
    ~Stack(){
        Node* p = NULL;
        while(top != NULL){
            p = top;
            top = top->next;
            delete p;
        }
    }
    int length(){
        if(!top)
            return 0;
        int len = 0;
        Node* tmp = top;
        while(tmp != NULL){
            len ++;
            tmp = tmp->next;
        }
        return len;
    }
    void print(){
        if(!top){
            cout<<"(print)Stack is empty!"<<endl;
            return;
        }
        int len = 0;
        Node* tmp = top;
        cout<<"Print nodes: "<<endl;
        while(tmp != NULL){
            len ++;
            cout<<"node: "<<tmp->data<<endl;
            tmp = tmp->next;
        }
        cout<<"*********** Totle nodes: "<<len<<endl;
    }
    bool is_empty(){
        if(!top)
            return true;
        return false;
    }
    // for Q1
    Node* pop(){
        if(!top){
            cout<<"(pop)Stack is empty!"<<endl;
            return NULL;
        }
        Node* tmp = top;
        top = top->next;
        return tmp;
    }
    // for Q1
    void push(int val){
        if(!top){
            top = new Node(val);
            return;
        }
        Node* pre = top;
        top = new Node(val);
        top->next = pre;
    }
};

class StackQueue{
    Stack a;
    Stack b;
public:
    StackQueue(){
    }
    ~StackQueue(){
    }
    void insert(int val){
        a.push(val);
    }
    Node* front(){
        if(a.is_empty() && b.is_empty()){
            return NULL;
        }
        Node* p = NULL;
        if(b.is_empty()){
            while(!a.is_empty()){
                p = a.pop();
                if(p == NULL)
                    break;
                b.push(p->data);
            }
            return b.pop();
        }else{
            return b.pop();
        }
    }
    void print(){
        cout<<"---- stack a:"<<endl;
        a.print();
        cout<<"---- stack b:"<<endl;
        b.print();
    }
};

bool confire(char* msg=""){
    cout<<"Confire: "<<msg<<" [Y/N] (N) ?"<<endl;
    char buf[8];
    cin>>buf;
    if(buf[0] == 'Y' || buf[0] == 'y')
        return true;
    return false;
}

int main(){
    // test Q1
    if(confire("Test stack")){
        Stack stack;
        stack.pop();
        stack.push(3);
        stack.push(8);
        stack.print();

        stack.pop();
        stack.push(2);
        stack.pop();
        stack.push(4);
        stack.print();
    }

    //test Q2
    if(confire("Test stack queue")){
        StackQueue squeue;
        squeue.insert(2);
        squeue.insert(5);
        squeue.insert(3);
        squeue.print();
        cout<<"front: "<<squeue.front()->data<<endl;
        squeue.insert(8);
        squeue.print();
        cout<<"front: "<<squeue.front()->data<<endl;
        cout<<"front: "<<squeue.front()->data<<endl;
        squeue.insert(6);
        cout<<"front: "<<squeue.front()->data<<endl;
        cout<<"front: "<<squeue.front()->data<<endl;
    }


    return 0;
}
