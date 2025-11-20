#include <iostream>
#include <string>

using namespace std;

int main() {
   string* enrollment;
   int classSize=0;
   cin>>classSize;
   enrollment= new string[classSize];

   for(int i=0;i<classSize;i++){
      cin>>enrollment[i];
   }

   for(int j = 0; j < classSize; j++) {
     cout << enrollment[j] << endl;
   }
   cout << "Class Size: " << classSize << endl;
   delete[]enrollment;

   return 0;
}