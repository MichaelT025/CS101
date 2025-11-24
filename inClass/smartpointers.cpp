#include <iostream>
#include <memory> // for unique and shared pointers
using namespace std;

int main() {
unique_ptr <int> uPtr=make_unique<int>(76);
//syntax: unique_ptr <data_type> [name]=make_unique<data_type>(value);
cout<<"Unique Pointer value: "<<*uPtr<<endl;
shared_ptr <int> sPtr=make_shared<int>(100);
//shared pointer is a pointer which can be shared among multiple owners
//syntax: shared_ptr <data_type> [name]=make_shared<data_type>(value);
shared_ptr <int> sPtr2=sPtr; //shared pointer can be copied
cout<<"Shared Pointer value: "<<*sPtr<<endl;
cout<<"Shared Pointer 2 value: "<<*sPtr2<<endl;
cout<<"Use count (number of owners):"<<sPtr.use_count()<<endl;
return 0;   
}
