#include <iostream>
#include <vector>
using namespace std;

int main(){
    int total;
    cin>>total;
    vector<int> vals;
    for(int i=0;i<total;i++){
        int val;
        cin>>val;
        vals.push_back(val);
    }
    int lb;
    int ub;
    cin>>lb>>ub;
    for(int i=0;i<total;i++){
        if(vals.at(i)>=lb && vals.at(i)<=ub){
            cout<<vals.at(i)<<",";
        }
    }
    cout<<endl;


    return 0;
}