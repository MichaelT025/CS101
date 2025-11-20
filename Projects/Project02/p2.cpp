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
    auto matchesPattern = [&](const string& word) -> bool {
        size_t m = search.size();
        size_t n = word.size();
        vector<vector<char>> dp(m + 1, vector<char>(n + 1, 0));
        dp[m][n] = 1;

        for(int i = static_cast<int>(m) - 1; i >= 0; --i){
            for(int j = static_cast<int>(n); j >= 0; --j){
                if(search[i] == '?'){
                    char zero = dp[i + 1][j];
                    char one = (j < static_cast<int>(n)) ? dp[i + 1][j + 1] : 0;
                    dp[i][j] = zero || one;
                }
                else if(j < static_cast<int>(n) && search[i] == word[j]){
                    dp[i][j] = dp[i + 1][j + 1];
                }
                else{
                    dp[i][j] = 0;
                }
            }
        }
        return dp[0][0];
    };

    unordered_map<string, int> counts;
    vector<string> order;

    for(const string& word : words){
        if(matchesPattern(word)){
            if(!counts.count(word)){
                order.push_back(word);
            }
            counts[word]++;
        }
    }

    if(order.empty()){
        cout << "The word " << search << " appears 0 times" << endl;
        return;
    }

    for(const string& matched : order){
        cout << "The word " << matched << " appears " << counts[matched] << " times" << endl;
    }
}
