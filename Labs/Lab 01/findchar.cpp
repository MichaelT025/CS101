#include <iostream>
#include <vector>
using namespace std;

int main(){
    int words;
    cin>>words;
    vector<string> strings;
    for(int i=0;i<words;i++){
        string word;
        cin>>word;
        strings.push_back(word);
    }
    char find;
    cin>>find;
    for(int i=0;i<words;i++){
        for(int j=0;j<strings[i].size();j++){
            if(strings[i][j]==find){
                cout<<strings[i]<<",";
                break;
            }
        }
    }
    cout<<endl;



    return 0;
}