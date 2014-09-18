/*
 * date: 2014-09-17
 * author: qile68@163.com
 *
 * 程序员面试宝典（第三版）题目
 *
 * Q1: 编程实现双链表的建立/测长/打印
 *
 * Q2: 编程实现双链表删除和插入
 *
 * Q3: 已知n个人（1，2，3 .... n）围在圆桌前，从变化为k的人开始报数，数到m的那个人出列，
 *     然后从出列的那个人的下一个开始重新报数，数到m的人出列，直到所有人都出列。
 *
 */

#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* next;
    Node* pre;
    Node(){
        data = 0;
        next = NULL;
        pre = NULL;
    }
    Node(int d,Node* n=NULL,Node* p=NULL){
        data = d;
        next = n;
        p = p;
    }
};
class DList{
    Node* head;
public:
    DList(){
        head = NULL;
    }
    ~DList(){
        Node* p = NULL;
        while(head != NULL){
            p = head;
            head = head->next;
            delete p;
        }
    }
    // for Q1
    void create(){
        int v = 1;
        Node* node = NULL;
        cout<<"Begin to create list, input '0' to complete create."<<endl;
        while(v != 0){
            cout<<"please input a node value: ";
            cin>>v;
            if(v == 0) break;
            if(!node){
                head = node = new Node(v);
            }else{
                node->next = new Node(v);
                node->next->pre = node;
                node = node->next;
            }
        }
    }
    // for Q1
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
    // for Q1
    void print(){
        if(!head){
            cout<<"List is empty!"<<endl;
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
    // for Q2
    void remove(int d){
        if(!head){
            cout<<"List is empty!"<<endl;
            return;
        }
        Node* tmp = head;
        while(d != tmp->data){
            tmp = tmp->next;
            if(!tmp) break;
        }
        if(tmp != NULL){
            if(!tmp->pre){
                head = tmp->next;
                head->pre = NULL;
            }else if(!tmp->next){
                tmp->pre->next = NULL;
            }else{
                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
            }
            delete tmp;
        }else{
            cout<<"Can not find the node to remove!"<<endl;
        }
    }
    // for Q2
    void insert(int val){
        if(!head){
            head = new Node(val);
            return;
        }
        Node* tmp = head;
        while(val >= tmp->data){
            tmp = tmp->next;
            if(!tmp->next) break;
        }
        if(!tmp->next){
            tmp->next = new Node(val);
            tmp->next->pre = tmp;
        }else if(!tmp->pre){
            head = new Node(val);
            head->next = tmp;
            tmp->pre = head;
        }else{
            tmp->pre->next = new Node(val);
            tmp->pre->next->next = tmp;
            tmp->pre = tmp->pre->next;
        }
    }
};

class Josephus{
    Node* head;
public:
    Josephus(){
        head = NULL;
    }
    void create(int n){
        if(n <= 0) return;
        head = new Node(1);
        Node* p = head;
        for(int i = 2; i <= n; i++){
            p->next = new Node(i);
            p->next->pre = p;
            p = p->next;
        }
        p->next = head;
        head->pre = p;
    }
    void print(){
        if(!head){
            cout<<"Josephus list is empty!"<<endl;
            return;
        }
        Node* p = head;
        do{
            cout<<"Node: "<<p->data<<endl;
            p = p->next;
        } while(p != head);
    }
    void count(int n,int m,int k){
        cout<<"count n: "<<n<<", m: "<<m<<", k:"<<k<<endl;
        create(n);
        print();
        if(!head){
            cout<<"Josephus list is empty!"<<endl;
            return;
        }
        Node* p = head;
        Node* tmp = NULL;
        while(p->data != k){
            p = p->next;
        }
        int i = 0;
        while(p != NULL){
            for(i = 0; i < m; i++){
                p = p->next;
            }
            cout<<"person: "<<p->data<<endl;
            if(p->next == p){
                delete p;
                break;
            }
            p->pre->next = p->next;
            p->next->pre = p->pre;
            tmp = p;
            p = p->next;
            delete tmp;
        }
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
    DList list;
    list.create();
    cout<<"list length is: "<<list.length()<<endl;
    list.print();

    // test Q2
    if(confire("Test remove node")){
        int value = 0;
        cout<<"---- Plese input a node value to remove"<<endl;
        cin>>value;
        list.remove(value);
        list.print();
    }

    // test Q2
    if(confire("Test insert node")){
        int value = 0;
        cout<<"---- Plese input a node value to insert"<<endl;
        cin>>value;
        list.insert(value);
        list.print();
    }
    // test Q3
    if(confire("Test Josephus")){
        Josephus jos;
        jos.count(8,3,3);
    }
    return 0;
}
