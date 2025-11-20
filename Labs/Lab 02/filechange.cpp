#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    string filename="";
    cout<<"Enter the inputfile name: ";
    cin>>filename;
    ifstream infile;
    infile.open(filename);
    if(!infile){
        cout<<"Error in opening the file"<<endl;
        return 1;
    }
    string photo="photo.jpg";
    string info="info.txt";
    string line;
    int pos;
    while(getline (infile, line)){
        pos=line.find(photo,0);
        line.replace(pos,9,info);
        cout<<line<<endl;

    }
}