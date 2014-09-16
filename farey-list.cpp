/*
 * 链表：程序设计作业 Farey 分数
 * date: 2014-09-12
 * author: qile68@163.com
 */

#include <iostream>
using namespace std;

struct Node{
    int a;
    int b;
    Node(){
        a = 0;
        b = 1;
        pre = NULL;
        next = NULL;
    }
    Node(int i=0, int j=1,Node* p=NULL, Node* n=NULL){
        a = i;
        b = j;
        pre = p;
        next = n;
    }
    Node* next;
    Node* pre;
};

class FareyList{
public:
    Node* head;
    Node* tail;
    int order;
    FareyList(){
        head = NULL;
        tail = NULL;
        order = 0;
    }
    ~FareyList(){
        Node* p;
        while(head){
            p = head->next;
            delete []head;
            head = p;
        }
    }
    void calculate(Node* n1, Node* n2){
        if(order <= 0 || (n1->b + n2->b) > order)
            return ;
        Node* node = new Node(n1->a+n2->a,n1->b+n2->b);
        n1->next = node;
        node->next = n2;
        calculate(n1,node);
        calculate(node,n2);
    }
    int generate(int n){
        if(n < 1)
            return -1;
        order = n;
        cout<<"generate .."<<endl;
        head = new Node(0,1);
        tail = new Node(1,1);
        head->next = tail;
        calculate(head,tail);
        return 0;
    }
    void print(){
        cout<<"print farey list:"<<endl;
        Node* tmp = head;
        cout<<"(";
        while(tmp && tmp != tail){
            cout<<tmp->a<<"/"<<tmp->b<<", ";
            tmp = tmp->next;
        }
        if(tmp)
            cout<<tmp->a<<"/"<<tmp->b<<")"<<endl;
    }
    void printfloat(){
        cout<<"print farey list(float):"<<endl;
        Node* tmp = head;
        cout<<"(";
        while(tmp && tmp != tail){
            cout<<(float)tmp->a/tmp->b<<", ";
            tmp = tmp->next;
        }
        if(tmp)
            cout<<(float)tmp->a/tmp->b<<")"<<endl;
    }
};

int main(){
    int n;

    cout<<"Please input a order of farey"<<endl;
    cin>>n;

    FareyList flist;
    flist.generate(n);
    flist.print();
    flist.printfloat();
    return 0;
}

