#include <iostream>
using namespace std;


int main(){
    int numbrers[5];
    cout<<"enter 5 numbers: ";
    for (int i=0;i<5;i++){
        cin>>numbrers[i];
    }
    for(int i=0;i<5;i++){
        cout<<numbrers[i]<<endl;
    }
    return 0;
}