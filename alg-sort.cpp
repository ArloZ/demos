/*
 * common used algorithm of sorting
 * date: 2014-09-18
 * author: qile68@163.com
 */

//#include <unistd.h>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;


class Sort{
    int* _array;
    int _size;
public:
    Sort(){
        _size = 0;
        _array = NULL;
    }
    ~Sort(){
        if(_array != NULL)
            delete [] _array;
    }
    /*
     * fill array with rand value
     *
     * @buf: the array to be filled
     * @size: array size
     * return: 0 -- success
     *         other -- failed
     */
    int fill(int size,int min=0, int max=100){
        _array = new int[size];
        if(_array == NULL)
            return 0;
        _size = size;
        srand(time(NULL));
        for(int i = 0;i < size; i++){
            _array[i] = min + rand()%max;
        }
        return size;
    }
    /*
     * output all array elements
     *
     * @width: num of element per line
     * return: none
     */
    void print(int width=10){
        for(int i = 0;i < _size; i++){
            cout<<_array[i]<<" ";
            if(i > 0 && 0 == i%width)
                cout<<endl;
        }
        cout<<endl;
    }
    /*
     * clear the array
     */
    void clear(){
        if(_array != NULL){
            delete [] _array;
            _array = NULL;
        }
        _size = 0;
    }
    /*
     * check if array is empty
     * return: true if empty
     */
    bool is_empty(){
        if(_size <= 0 || _array == NULL)
            return true;
        return false;
    }
    /*
     * insert sorting (increase)
     */
    void insert_sorting(){
        if(is_empty()){
            cout<<"Array is empty!"<<endl;
            return;
        }
        int tmp = 0;
        for(int i = 1; i < _size; i ++){
            for(int j = 0; j < i; j++){
                if(_array[i] < _array[j]){
                    tmp = _array[i];
                    for(int k = i; k > j; k --){
                        _array[k] = _array[k-1];
                    }
                    _array[j] = tmp;
                    break;
                }
            }
        }
    }
    /*
     * select sorting(increase)
     */
    void select_sorting(){
        if(is_empty()){
            cout<<"Array is empty!"<<endl;
            return;
        }
        int least = 0;
        int tmp = 0;
        for(int i = 0; i < _size; i++){
            least = i;
            for(int j = i; j < _size; j++){
                if(_array[least] > _array[j]){
                    least = j;
                }
            }
            tmp = _array[i];
            _array[i] = _array[least];
            _array[least] = tmp;
        }
    }
    /*
     * bubble sorting(increase)
     */
    void bubble_sorting(){
        if(is_empty()){
            cout<<"Array is empty!"<<endl;
            return;
        }
        int tmp = 0;
        for(int i=0; i < _size; i++){
            for(int j = _size - 1; j > i; j--){
                if(_array[j] < _array[j-1]){
                    tmp = _array[j];
                    _array[j] = _array[j-1];
                    _array[j-1] = tmp;
                }
            }
        }
    }
    /*
     * Shell sorting(increase), use insert sort for each ht
     */
    void shell_sorting(){
        if(is_empty()){
            cout<<"Array is empty!"<<endl;
            return;
        }
        // generate ht
        vector<int> ht;
        int h = 1;
        do{
            ht.push_back(h);
            h = 3*h + 1;
        }while(h*3+1 < _size);
        int tmp = 0;
        int i,j,k;
        // for each ht
        for(i = (ht.size()-1); i >= 0; i --){
            h = ht[i];
            //cout<<"ht: "<<h<<endl;
            for(j = 0; j < h; j ++){
                for(k = h+j; k < _size; k += h){
                    // insert sort
                    tmp = _array[k];
                    int n = k;
                    while(n >= h && _array[n-h] > tmp){
                        _array[n] = _array[n-h];
                        n -= h;
                    }
                    _array[n] = tmp;
                }
            }
        }
    }
    /*
     * heap sorting(increase)
     */
    void heap_sorting(){
        if(is_empty()){
            cout<<"Array is empty!"<<endl;
            return;
        }
        // create a max heap
        // exchange all node except leaf nodes
        for(int i = _size/2-1; i >= 0; i--){
            move_down(i,_size);
        }
        // heap sort
        int tmp = 0;
        for(int i = _size-1; i > 0; i--){
            tmp = _array[i];
            _array[i] = _array[0];
            _array[0] = tmp;
            move_down(0,i);
        }
    }
    // use for heap sorting when create a heap
    void move_down(int i,int size){
        int maxid=0;
        int tmp=0;
        int leftchrild = i*2+1;
        int rightchrild = leftchrild + 1;
        while(leftchrild < size){
            if(rightchrild >= size)
                rightchrild = leftchrild;
            if(_array[i] > _array[leftchrild] && _array[i] > _array[rightchrild])
                break;
            maxid = leftchrild;
            if(_array[leftchrild] < _array[rightchrild])
                maxid = rightchrild;
            // exchange element i whith its bigest chirld
            tmp = _array[i];
            _array[i] = _array[maxid];
            _array[maxid] = tmp;
            i = maxid;
            leftchrild = i*2+1;
            rightchrild = leftchrild + 1;
        }
    }
    /*
     * Quick sorting (increase)
     */
    void quick_sorting(){
        if(is_empty()){
            cout<<"Array is empty!"<<endl;
            return;
        }
        quicksort(0,_size-1);
    }
    void quicksort(int first,int last){
        if(first < 0 || last >= _size || first >= last){
            return;
        }
        int tmp = 0;
        int key = _array[first];
        int lower = first;
        int upper = last;
        do{
            while(_array[upper] > key && upper > lower){
                upper --;
            }
            if(lower < upper){
                tmp = _array[lower];
                _array[lower] = _array[upper];
                _array[upper] = tmp;
                lower ++;
            }
            while(_array[lower] < key && upper > lower){
                lower ++;
            }
            if(lower < upper){
                tmp = _array[lower];
                _array[lower] = _array[upper];
                _array[upper] = tmp;
                upper --;
            }
        }while(lower != upper);
        _array[upper] = key;
        quicksort(first,upper - 1);
        quicksort(upper + 1,last);
        /*
        // use middle value have some bug
        if(first < 0 || last >= _size || (last - first) < 1){
            return;
        }
        int tmp = 0;
        int lower = first;
        int upper = last;
        int key = _array[(first+last)/2];
        _array[(first+last)/2] = _array[lower];
        _array[lower++] = key;

        while(lower <= upper){
            while(_array[lower] < key)
                lower ++;
            while(_array[upper] > key)
                upper --;
            if(lower <= last && lower < upper){
                tmp = _array[lower];
                _array[lower++] = _array[upper];
                _array[upper--] = tmp;
            }else{
                break;
            }
        }
        tmp = _array[upper];
        _array[upper] = _array[first];
        _array[first] = tmp;
        quicksort(first,upper - 1);
        quicksort(upper + 1,last);
        */
    }
    /*
     * Merge sorting(increase)
     */
    void merge_sorting(){
        if(is_empty()){
            cout<<"Array is empty!"<<endl;
            return;
        }
        mergesort(0,_size-1);
    }
    void mergesort(int first,int last){
        if(first >= last){
            return;
        }
        int middle = (first + last)/2;
        mergesort(first,middle);
        mergesort(middle+1,last);
        int length = last - first + 1;
        int* temp = new int(length);
        int i = 0;
        int j = first;
        int k = middle+1;
        while(j <= middle && k <= last){
            if(_array[j] > _array[k]){
                temp[i++] = _array[k++];
            }else{
                temp[i++] = _array[j++];
            }
        }
        if(j <= middle){
            while(i < length){
                temp[i++] = _array[j++];
            }
        }else if(k <= last){
            while(i < length){
                temp[i++] = _array[k++];
            }
        }
        for(int m = 0; m < length; m++){
            _array[first + m] = temp[m];
        }
        delete []temp;
    }
    /*
     * Radix sort(increase)
     */
    void radix_sorting(){
        if(is_empty()){
            cout<<"Array is empty!"<<endl;
            return;
        }
        queue<int> q[2];
        int width = sizeof(int) * 8;
        unsigned int mask = 0;
        for(int i  = 1; i < width; i++){
            mask = 1 << i;
            for(int j = 0;j < _size; j++){
                q[(_array[j]&mask)>>i].push(_array[j]);
            }
            int k = 0;
            while(!q[0].empty()){
                _array[k] = q[0].front();
                q[0].pop();
                k ++;
            }
            while(!q[1].empty()){
                _array[k] = q[1].front();
                q[1].pop();
                k ++;
            }
        }
    }
};



int main(){
    int n = 0;
    cout<<"Please input the length of array: ";
    cin>>n;
    Sort sort;

    // test Insert sorting
    sort.fill(n);
    cout<<"-- Insert sort:"<<endl;
    sort.print();
    sort.insert_sorting();
    cout<<"-- After sort:"<<endl;
    sort.print();

    // test Select sorting
    sort.clear();
    sort.fill(n);
    cout<<"-- Select sort:"<<endl;
    sort.print();
    sort.select_sorting();
    cout<<"-- After sort:"<<endl;
    sort.print();

    // test Bubble sorting
    sort.clear();
    sort.fill(n);
    cout<<"-- Bubble sort:"<<endl;
    sort.print();
    sort.bubble_sorting();
    cout<<"-- After sort:"<<endl;
    sort.print();

    // test Shell sorting
    sort.clear();
    sort.fill(n);
    cout<<"-- Shell sort:"<<endl;
    sort.print();
    sort.shell_sorting();
    cout<<"   After sort:"<<endl;
    sort.print();

    // test Heap sorting
    sort.clear();
    sort.fill(n);
    cout<<"-- Heap sort:"<<endl;
    sort.print();
    sort.heap_sorting();
    cout<<"   After sort:"<<endl;
    sort.print();

    // test Quick sorting
    sort.clear();
    sort.fill(n);
    cout<<"-- Quick sort:"<<endl;
    sort.print();
    sort.quick_sorting();
    cout<<"   After sort:"<<endl;
    sort.print();

    // test Merge sorting
    sort.clear();
    sort.fill(n);
    cout<<"-- Merge sort:"<<endl;
    sort.print();
    sort.merge_sorting();
    cout<<"   Merge sort:"<<endl;
    sort.print();

    // test Radix sorting
    sort.clear();
    sort.fill(n);
    cout<<"-- Radix sort:"<<endl;
    sort.print();
    sort.radix_sorting();
    cout<<"   Radix sort:"<<endl;
    sort.print();
}

