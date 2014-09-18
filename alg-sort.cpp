/*
 * common used algorithm of sorting
 * date: 2014-09-18
 * author: qile68@163.com
 */

#include <iostream>
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

};



int main(){
    int n = 0;
    cout<<"Please input the length of array: ";
    cin>>n;
    Sort sort;

    // test insert sorting
    sort.fill(n);
    cout<<"-- before sort:"<<endl;
    sort.print();
    sort.insert_sorting();
    cout<<"-- After sort:"<<endl;
    sort.print();

    // test select sorting
    sort.clear();
    sort.fill(n);
    cout<<"-- before sort:"<<endl;
    sort.print();
    sort.select_sorting();
    cout<<"-- After sort:"<<endl;
    sort.print();

}

