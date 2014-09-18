/*
 * date: 2014-09-17
 * author: qile68@163.com
 *
 * 程序员面试宝典（第三版）题目
 *
 * Q1: 编程实现队列的入队/出队操作
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
class Queue{
    Node* head;
    Node* tail;
public:
    Queue(){
        head = NULL;
        tail = NULL;
    }
    ~Queue(){
        Node* p = NULL;
        while(head != NULL){
            p = head;
            head = head->next;
            delete p;
        }
    }
    int length(){
        if(!head)
            return 0;
        int len = 0;
        Node* tmp = head;
        while(tmp != NULL){
            len ++;
            tmp = tmp->next;
        }
        return len;
    }
    void print(){
        if(!head){
            cout<<"Queue is empty!"<<endl;
            return;
        }
        int len = 0;
        Node* tmp = head;
        cout<<"Print nodes: "<<endl;
        while(tmp != NULL){
            len ++;
            cout<<"node: "<<tmp->data<<endl;
            tmp = tmp->next;
        }
        cout<<"*********** Totle nodes: "<<len<<endl;
    }
    // for Q1
    Node* front(){
        if(!head){
            cout<<"Queue is empty!"<<endl;
            return NULL;
        }
        Node* tmp = head;
        if(head == tail){
            head = NULL;
            tail = NULL;
        }else{
            head = head->next;
        }
        return tmp;
    }
    // for Q1
    void insert(int val){
        if(!head){
            head = new Node(val);
            tail = head;
            return;
        }
        tail->next = new Node(val);
        tail = tail->next;
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
    Queue queue;
    queue.insert(1);
    queue.insert(5);
    queue.insert(8);
    queue.insert(3);
    cout<<"front: "<<queue.front()->data<<endl;
    queue.insert(2);
    cout<<"list length is: "<<queue.length()<<endl;
    queue.print();
    cout<<"front: "<<queue.front()->data<<endl;
    cout<<"front: "<<queue.front()->data<<endl;
    cout<<"front: "<<queue.front()->data<<endl;
    cout<<"front: "<<queue.front()->data<<endl;

    return 0;
}
