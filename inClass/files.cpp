#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char* argv[]){
    if(argc < 2){
        std::cerr<<"Usage: "<<argv[0]<<" <filename>"<<std::endl;
        return 1;
    }
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1]);
    outfile.open(argv[2]);
    if(!infile){
        cout<<"File could not be opened!"<<endl;
        return 1;
    }
    if(!outfile){
        cout<<"File could not be opened!"<<endl;
        return 1;
    }
    string line;
    while(getline(infile, line)){
        outfile<<line<<endl;
    }
    infile.close();
    outfile.close();

    return 0;
}