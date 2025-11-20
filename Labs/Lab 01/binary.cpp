#include <iostream>
using namespace std;

string IntToReverseBinary(int num){
    string binary="";
    int bin;
    while(num>0){
        bin=num%2;
        if(bin==1) binary+="1";
        else binary+="0";
        num/=2;
    }
    return binary;
}
string StringReverse(string str){
    string rbinary="";
    for(int i=str.length()-1;i>=0;i--){
        rbinary+=str[i];
    }
    return rbinary;
}
int main(){
    int val;
    cin>>val;
    string binary=IntToReverseBinary(val);
    string reversed=StringReverse(binary);
    cout<<reversed<<endl;
    return 0;
}
    