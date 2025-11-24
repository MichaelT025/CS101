#include <iostream>
using namespace std;

int main(){
    int *p=new int (42);
    //new allocates memory on the heap
    //syntax new data_type (value);
    cout<<"Single value: "<<*p<<endl;
    delete p;
    //must free memory in heap after use
    p=nullptr; // good practice to avoid dangling pointers
    int *arr=new int[3] {76, 30, 5}; 
    //syntax(for array) new data_type[size] {values};
    cout<< "Array values are: ";
    for(int i=0;i<3;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    delete [] arr;
    arr=nullptr; // good practice to avoid dangling pointers
    int array[7]={10,20,30,40,50,60,70};
}