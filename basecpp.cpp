/*
 * OOP with C++
 * date: 2014-09-09
 * author: qile68@163.com
 */

#include <iostream>
using namespace std;


/*
 * 定义一个类
 */
class A{
private:
    char name[32];
    int age;
public:
    A(char *s="",int i=0){
        strcpy(name,s);
        age = i;
    }
    void hello(){
        cout<<name<<" is "<<age<<" years old."<<endl;
    }
};


/*
 * 类的继承关系
 */
class Base{
private:
    int id;
protected:
    int age;
public:
    char name[32];
public:
    Base(){}
    Base(char* s="", int i=0,int ii=1){
        strcpy(name,s);
        age = i;
        id = ii;
        cout<<"Base construct"<<endl;
    }
    void hello(){
        cout<<"Base hello: "<<name<<" is "<<age<<" years old."<<endl;
    }
};

class Student:protected Base{
private:
    char school[32];
public:
    Student(char* s="",int i=0, int ii=1,char* sch=""):Base(s,i,ii){
        strcpy(school,sch);
        cout<<"Student construct"<<endl;
        Base::hello();
    }
    void hello(){
        cout<<"Student hello: "<<name<<" is "<<age<<" years old.";
        cout<<" in school: "<<school<<endl;
        //cout<<"the id is: "<<id<<endl; // ERROR: id is a private member of Base
    }
};

class Worker:public Base{
private:
    char companay[64];
public:
    Worker(char* s="",int i=0, int ii=1,char* com=""):Base(s,i,ii){
        strcpy(companay,com);
        cout<<"Worker construct"<<endl;
    }

    void hello(){
        cout<<"Worker hello: "<<name<<" is "<<age<<" years old.";
        cout<<" in companay: "<<companay<<endl;
    }
};

/*
 * 指针和复制构造函数
 */
struct Node{
    char *name;
    int age;
    Node(char* s="",int a=0){
        name = strdup(s);
        age = a;
    };
    Node(const Node &n){
        name = strdup(n.name);
        age = n.age;
    };
    // 指针数据成员的赋值操作
    Node& operator=(const Node& n){
        if (this != &n){ // no assignment to it self
            if(name != NULL)
                delete [] name;
            name = strdup(n.name);
            age = n.age;
        }
        return *this;
    };
};

/*
 * 多态性
 */
class ClassA{
public:
    virtual void hello(){
        cout<<"hello in ClassA"<<endl;
    }
    void bye(){
        cout<<"bye in ClassA"<<endl;
    }
};
class ClassB{
public:
    virtual void hello(){
        cout<<"hello in ClassB"<<endl;
    }
    void bye(){
        cout<<"bye in ClassB"<<endl;
    }
};
class ClassC{
public:
    void hi(){
        cout<<"hi in ClassC"<<endl;
    }
};

int main(){
    // 定义类的对象实例
    A obj1("Bob",12),obj2("Lucy",13);
    // 调用类方法
    obj1.hello();
    obj2.hello();
    cout<<"--------"<<endl;

    // 类的继承
    Student s("studentA",23,10000,"tju");
    Worker w("workerB",32,10001,"baidu");
    w.hello();
    s.hello();
    cout<<w.name<<endl;
    //cout<<s.name<<endl;// ERROR: Student is protected extend from Base class

    // 指针和复制构造函数
    Node node1("kobe",20),node2(node1);
    cout<<"node1 "<<node1.name<<" "<<node1.age<<endl;
    cout<<"node2 "<<node2.name<<" "<<node2.age<<endl;
    strcpy(node1.name,"john");
    node1.age = 23;
    cout<<"node1 "<<node1.name<<" "<<node1.age<<endl;
    cout<<"node2 "<<node2.name<<" "<<node2.age<<endl;

    // 多态性
    ClassA obja,*p;
    ClassB objb;
    ClassC objc;

    p = &obja;
    p->hello();
    p->bye();

    p = (ClassA*) &objb;
    p->hello();
    p->bye();

    p = (ClassA*) &objc;
    //p->hello(); // ERROR: segmentation fault
    p->bye();
    //p->hi();// ERROR: no member named 'hi' in ClassA

}
