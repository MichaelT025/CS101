#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;


int GetWordFrequency(const vector<string> &words, string currword){
    int count=0;
    string lowerword=currword;
    for(int i=0;i<currword.length();i++){
        lowerword[i]=tolower(currword[i]);
    }
    vector<string> words_lower=words;
    for(int i=0;i<words.size();i++){
        for(int j=0;j<words[i].length();j++){
            words_lower[i][j]=tolower(words[i][j]);
        }
        if(words_lower[i]==lowerword) count++;
    }
    
    return count;
}
int main(){
    int count;
    cin>>count;
    vector<string> words(count);
    for(int i=0; i<count; i++){
        cin>>words[i];
    }

    for(int i=0;i<count;i++){
        string currword = words[i];
        int found = GetWordFrequency(words, currword);
        cout<<words[i]<<" "<<found<<endl;
    }
    return 0;
}