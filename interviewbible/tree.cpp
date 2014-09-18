/*
 * date: 2014-09-17
 * author: qile68@163.com
 *
 * 程序员面试宝典（第三版）题目
 *
 * Q1: 比较两个树是否相等
 *
 */

#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(){
        data = 0;
        left = NULL;
        right = NULL;
    }
    Node(int d){
        data = d;
        left = NULL;
        right = NULL;
    }
};

// Q1
bool compare_tree(Node* tree1,Node* tree2){
    // 如果两个节点都为NULL，则认为相等
    if(tree1 == NULL && tree2 == NULL)
        return true;
    // 如果一个节点为NULL，另一个不为NULL，则定不相等
    if(tree1 == NULL || tree2 == NULL)
        return false;
    // 当两个节点都不为NULL时，则比较其值是否等，如果相等，则比较子树是否相等
    if(tree1->data == tree2->data) {
        bool ll = compare_tree(tree1->left,tree2->left);
        bool rr = compare_tree(tree1->right,tree2->right);
        bool rl = compare_tree(tree1->right,tree2->left);
        bool lr = compare_tree(tree1->left,tree2->right);
        return (ll && rr) || (rl && lr);
    }
    return false;
}


// 中序遍历
void print_tree(Node* tree){
    if(!tree) return;
    print_tree(tree->left);
    cout<<tree->data<<" ";
    print_tree(tree->right);
}

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
    if(confire("Test Comapre tree")){
        //create trees
        Node* p = NULL;
        Node* tree1 = new Node(6);
        tree1->left = new Node(3);
        tree1->right = new Node(8);
        p = tree1->left;
        p->left = new Node(2);
        p = tree1->right;
        p->left = new Node(7);
        p->right = new Node(10);
        cout<<"print tree 1: "<<endl;
        print_tree(tree1);
        cout<<"  "<<endl;

        Node* tree2 = new Node(6);
        tree2->left = new Node(8);
        tree2->right = new Node(3);
        p = tree2->left;
        p->left = new Node(7);
        p->right = new Node(10);
        p = tree2->right;
        p->left = new Node(2);
        cout<<"print tree 2: "<<endl;
        print_tree(tree2);
        cout<<"  "<<endl;

        cout<<"compare_tree: "<<compare_tree(tree1,tree2)<<endl;
    }

    return 0;
}
