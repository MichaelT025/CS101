#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
int main() {
   vector <int>nums;
   int minone=INT_MAX;
   int mintwo=INT_MAX;
   int size;
   cin>>size;
   int num, idx;
   for(int i=0;i<size;i++){
      cin>>num;
      nums.push_back(num);
      if(num<minone){
         minone=num;
         idx=i;
      }
   }

   for(int i=0;i<size;i++){
      if(i==idx) continue;
      mintwo=min(mintwo, nums[i]);
   }
   cout<<minone<<" and "<<mintwo<<endl;

   

   return 0;
}
