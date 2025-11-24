#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //for reverse()

using namespace std;

int main(){
    
    string name;
    cout<< "Enter your name"<<endl;
    cin>>name;
    string rname=name;
    reverse(rname.begin(),rname.end());
    /*for(int i=0;i<(name.size())/2;i++){
        rname.at(i)=name.at(name.size()-1-i);
        rname.at(name.size()-1-i)=name.at(i);
    }*/
    cout<<"Reversed name is: "<<rname<<endl;
    
    cout<<"What is your name?"<< endl;
    return 0;

}


