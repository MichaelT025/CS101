#include <iostream>
#include <vector>
#include <string>
using namespace std;

void ReadSentences(vector<string>& first, vector<string>& second, int count) {
   for (int i = 0; i < count; i++) {
      cin >> first[i];
   }
   for (int i = 0; i < count; i++) {
      cin >> second[i];
   }
}
int main() {
   vector<string> firstSentence(20);
   vector<string> secondSentence(20);
   int wordCount;
   int i;
   
   cin >> wordCount;
   // Call ReadSentences() to populate vectors
   ReadSentences(firstSentence, secondSentence, wordCount);
   
   for(int i=0;i<wordCount;i++){
    if(firstSentence[i]!=secondSentence[i]){
        cout<<firstSentence[i]<<" "<<secondSentence[i]<<endl;
    }
   }

   return 0;
}
