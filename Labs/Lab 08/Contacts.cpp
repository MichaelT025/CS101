//contacts linked list
#include <iostream>
using namespace std;
class ContactNode{
    public:
        ContactNode(string name, string number){
            contactName=name;
            contactPhoneNumber=number;
            nextNodePtr=nullptr;
        }
        string GetName(){
            return contactName;
        }
        string GetPhoneNumber(){
            return contactPhoneNumber;
        }
        void InsertAfter(ContactNode* newNode){
            newNode->nextNodePtr=nextNodePtr;
            nextNodePtr=newNode;
        }
        ContactNode* GetNext(){
            return nextNodePtr;
        }
        void PrintContactNode(){
            cout<<"Name: "<<contactName<<endl;
            cout<<"Phone number: "<<contactPhoneNumber<<endl;
        }
    private:
        string contactName;
        string contactPhoneNumber;
        ContactNode* nextNodePtr;

};
int main(){
    string name, number;
    getline(cin, name);
    getline(cin, number);
    ContactNode* p1=new ContactNode(name, number);
    cout<<"Person 1: "<<name<<", "<<number<<endl;
    getline(cin, name);
    getline(cin, number);
    ContactNode* p2=new ContactNode(name, number);
    p1->InsertAfter(p2);
    cout<<"Person 2: "<<name<<", "<<number<<endl;
    getline(cin, name);
    getline(cin, number);
    ContactNode* p3=new ContactNode(name, number);
    p2->InsertAfter(p3);
    cout<<"Person 3: "<<name<<", "<<number<<endl;
    ContactNode* head=p1;
    cout<<endl<<"CONTACT LIST"<<endl;
    while(head){
        head->PrintContactNode();
        cout<<endl;
        head=head->GetNext();
    }

}