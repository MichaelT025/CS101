#include <vector>
#include <string>
#include <iostream>

using namespace std;

// TODO: Write function to create and output all permutations of the list of names.
void PrintAllPermutations(const vector<string> &permList, const vector<string> &nameList) {
   if(nameList.empty()){
      for(int i=0;i<permList.size()-1;i++){
         cout<<permList[i]<<", ";
      }
      cout<<permList.back()<<endl;
      return;
   }
   for(int i=0;i<nameList.size();i++){
      vector<string> newPermList=permList;
      newPermList.push_back(nameList[i]);
      vector<string>remaining=nameList;
      remaining.erase(remaining.begin()+i);
      PrintAllPermutations(newPermList,remaining);
   }

   
}

int main() {
   vector<string> nameList;
   vector<string> permList;
   string name;

   // TODO: Read a list of names into nameList; stop when -1 is read. Then call recursive function.
   cin>>name;
   while(name!="-1"){
      nameList.push_back(name);
      cin>>name;
   }
   PrintAllPermutations(permList, nameList);

   return 0;
}