#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <cctype>

using namespace std;

void find(const vector<string>&words, const string& search, int* count);
void wild(const vector<string>&words, const string& search);


int main(int argc, char* argv[]){
    ifstream infile;
    infile.open(argv[1]);
    if(!infile){
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }  

    unordered_set <string> uq;
    vector<string> words;
    string word="";
    char curr;
    while(infile.get(curr)){
        if(isalpha(curr))
            word += tolower(curr);
        else {
            if(!word.empty()) {
                words.push_back(word);
                uq.insert(word);
                word = "";
            }
        }
    }
    if(!word.empty()){
        words.push_back(word);
        uq.insert(word);
        word = "";
    }
    cout<<"The number of words found was "<<words.size()<<endl;
    cout<<"The number of distinct words was "<<uq.size()<<endl;
    infile.close();

    string search;
    cout<<"Enter a word:"<<endl;
    cin>>search;
    while(search!="STOP"){
    bool hard=0;
    for(char &c:search) {
        c=tolower(c);
        if(c=='?')
            hard=1;
    }
    if(!hard){
        int count=0;
        find(words, search, &count);
        cout<<"The word "<<search<<" appears "<<count<<" times"<<endl;
    }
    else
        wild(words, search);
    cout<<"Enter a word:"<<endl;
    cin>>search;
    }


 return 0;
}

void find(const vector<string>&words, const string& search, int* count){
    for(string w:words)
        if(w==search)
            (*count)++;
}

void wild(const vector<string>&words, const string& search){
    unordered_set<string> found;
    int nowildcount=0;
    string nowild="";
    for(char c:search){
        if(c!='?')
            nowild+=c;
    }
    find(words, nowild, &nowildcount);
    if(nowildcount!=0)
    cout<<"The word "<<nowild<<" appears "<<nowildcount<<" times"<<endl;

    for(string w:words){
        if(w.size()!=search.size()) continue;
        bool match=1;
        for(size_t i=0; i<search.size(); i++){
            if(search[i]!='?' && search[i]!=w[i]){
                match=0;
                break;
            }
        }
        if(match && found.find(w)==found.end()){
            found.insert(w);
            int count=0;
            find(words, w, &count);
            cout<<"The word "<<w<<" appears "<<count<<" times"<<endl;
        }
    }
    
    if(found.empty()&& nowildcount==0){
        cout<<"The word "<<search<<" appears 0 times"<<endl;
    }
}