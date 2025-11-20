#include <iostream>
#include <string>

using namespace std;

int main() {
   string phoneNumber;
   
   cin >> phoneNumber;
   
   for(int i=0;i<10;i++){
      if(i==0) cout<<"(";
      cout<<phoneNumber[i];
      if(i==2)cout<<") ";
      if(i==5)cout<<"-";   
   }
   cout<<endl;

   
   return 0;
}
