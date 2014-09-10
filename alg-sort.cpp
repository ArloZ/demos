/*
 * algorithm of inserting sort and merge sort
 * date: 2014-08-20
 * author: qile68@163.com
 */

#include <iostream>
using namespace std;


/*
 * fill array with rand value
 *
 * @buf: the array to be filled
 * @size: array size
 * return: 0 -- success
 *         other -- failed
 */
int rand_fill_array(int* buf,int size,int min=0, int max=100){
    srand(time(NULL));
    for(int i = 0;i < size; i++){
        buf[i] = min + rand()%max;
    }
    return 0;
}

/*
 * output all array elements
 *
 * @buf: the array to be output
 * @size: the array size
 * @width: num of element per line
 * return: none
 */
void output_array(int* buf,int size,int width=10){
    for(int i = 0;i < size; i++){
        cout<<buf[i]<<" ";
        if(i > 0 && 0 == i%width)
            cout<<endl;
    }
    cout<<endl;
}

/*
 * 插入排序(升序)
 */
void inser_sort(int* array, int size){
    int temp = 0;
    int j = 0;
    for(int i = 1;i < size;i ++){
        temp = array[i];
        for(j = 1; j <= i;j++){
            if(temp < array[i-j]){
                break;
            }
            array[i-j+1] = array[i-j];
        }
        array[i-j+1] = temp;
    }
}

int main(){
    int n = 0;
    cout<<"please input the length of array:"<<endl;
    cin>>n;
    int* array = new int[n];
    rand_fill_array(array,n);
    cout<<"source:"<<endl;
    output_array(array,n);

    inser_sort(array,n);

    cout<<"sorted:"<<endl;
    output_array(array,n);

    delete []array;
}

