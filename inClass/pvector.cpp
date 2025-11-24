#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> v={10,20,30,40};
    int *p=v.data();
    int *n=&v[4];
    *n=69;
    cout<<"first element: "<<*p<<endl;
    cout<<"second element: "<<*(p+1)<<endl;
    cout<<"third element: "<<p[2]<<endl;
    *(p+3)=99;
    cout<<"fourth element: "<<v[3]<<endl;
    cout<<*n<<endl;

    return 0;
}