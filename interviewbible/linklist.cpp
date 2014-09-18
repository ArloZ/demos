/*
 * date: 2014-09-16
 * author: qile68@163.com
 *
 * 程序员面试宝典（第三版）题目
 *
 * Q1: 编程实现单链表的建立、测长、打印
 *
 * Q2: 编程实现单链表删除节点
 *
 * Q3: 编程实现单链表的插入
 *
 * Q4: 编程实现单链表排序
 *
 * Q5: 编程实现单链表逆置
 *
 * Q6: 未知长度的单链表，如何遍历一次就求出其中间节点
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
class List{
    Node* head;
public:
    List(){
        head = NULL;
    }
    ~List(){
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
        Node* pre = NULL;
        Node* tmp = head;
        while(d != tmp->data){
            pre = tmp;
            tmp = tmp->next;
            if(!tmp) break;
        }
        if(tmp != NULL){
            if(!pre){
                head = tmp->next;
            }else{
                pre->next = tmp->next;
            }
            delete tmp;
        }else{
            cout<<"Can not find the node to remove!"<<endl;
        }
    }
    // for Q3
    void insert(int val){
        if(!head){
            head = new Node(val);
            return;
        }
        Node* pre = NULL;
        Node* tmp = head;
        while(val >= tmp->data){
            pre = tmp;
            tmp = tmp->next;
            if(!tmp->next) break;
        }
        if(pre == NULL){
            head = new Node(val);
            head->next = tmp;
        }else{
            if(!tmp->next){
                tmp->next = new Node(val);
            }else{
                pre->next = new Node(val);
                pre->next->next = tmp;
            }
        }
    }
    // for Q4: 冒泡排序
    void sort_pp(){
        if(!head){
            cout<<"List is empty!"<<endl;
            return;
        }
        Node* tmp = NULL;
        Node* p = NULL;
        int val = 0;
        while(head->next != tmp){
            p = head;
            while(p->next != tmp){
                if(p->data > p->next->data){
                    val = p->data;
                    p->data = p->next->data;
                    p->next->data = val;
                }
                p = p->next;
            }
            tmp = p;
        }
    }
    // Q5
    void reverse(){
        if(!head){
            cout<<"List is empty!"<<endl;
            return;
        }
        Node* p = head;
        Node* pre = NULL;
        Node* tmp = p->next;
        while(tmp != NULL){
            tmp = p->next;
            p->next = pre;
            pre = p;
            p = tmp;
        }
        head = pre;
    }
    // Q6
    Node* get_middle_node(){
        if(!head){
            cout<<"List is empty!"<<endl;
            return NULL;
        }
        Node* p1 = head;
        Node* p2 = head;
        while(p1->next != NULL && p1->next->next != NULL){
            p1 = p1->next->next;
            p2 = p2->next;
        }
        return p2;
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
    List list;
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

    // test Q3
    if(confire("Test insert node")){
        int value = 0;
        cout<<"---- Plese input a node value to insert"<<endl;
        cin>>value;
        list.insert(value);
        list.print();
    }

    // test Q4
    if(confire("Test sort list")){
        cout<<"---- Sort List with pop"<<endl;
        list.sort_pp();
        list.print();
    }
    // test Q5
    if(confire("Test reverse list")){
        cout<<"---- Reverse list"<<endl;
        list.reverse();
        list.print();
    }
    // test Q6
    if(confire("Test get middle node ")){
        Node* node = list.get_middle_node();
        if(node != NULL){
            cout<<"---- middle node is: "<<node->data<<endl;
            list.print();
        }
    }
    return 0;
}
