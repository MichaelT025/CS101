#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <iomanip>

using namespace std;

vector<string> identifiers;
unordered_map<string, int> indexedID;
vector<vector<int>> bw;

void upper(string &str) {
    for (char &i:str)
        i = toupper(i);
}

int find(const string &id){
    if(indexedID.find(id) != indexedID.end()) 
        return indexedID.at(id);
    return -1;
}


void insert(string &id, int check, int band){
    upper(id);
    int found=find(id);
    if(found != -1){
        bw[found][check]+=band;
        return;
    }
    if(found == -1){
        int x = indexedID.size();
        indexedID[id] = x;
        identifiers.push_back(id);
        bw.push_back({0,0});
        bw[x][check]+=band;
    }
}

void printIDs(ofstream &outfile){
    for(auto &id: identifiers)
        outfile << id << endl;
}

void nonleaf(ofstream &outfile){
    for(int i=0; i<(int)identifiers.size(); i++){
        if(bw[i][0] == 0 || bw[i][1] == 0)
            continue;
        outfile<< identifiers[i]<<" "<<bw[i][0]<<" "<<bw[i][1]<<" "<<fixed<<setprecision(2)<<(double)bw[i][1]/bw[i][0]<<endl;
    }

}






int main(int argc, char* argv[]){
    string inputfile, outputfile;
    if(argc != 3){
        cout << "Usage: " << argv[0] << " <inputfile> <outputfile>" << endl;
        return 1;
    }
    inputfile = argv[1];
    outputfile = argv[2];
    ifstream infile(inputfile);
    ofstream outfile(outputfile);
    if(!infile){
        cout << "Error: Could not open input file " << inputfile << endl;
        return 1;
    }

    string line;

    while(getline(infile, line)){
        istringstream iss(line);
        string source, dest;
        int band;
        if(!(iss >> source >> dest >> band)){
            cout << "Error: Invalid line format: " << line << endl;
            continue;
        }
        insert(source, 0, band);//0 for source
        insert(dest, 1, band);//  1 for dest
    }
    printIDs(outfile);
    outfile<<endl;
    nonleaf(outfile);


    infile.close();
    outfile.close();


}