#include <iostream>
#include<vector>
using namespace std;

void printvect(vector<int> v){
    for(int n:v)cout<<n<<endl;
}
int sumvectors(vector <int> v, int& avg){
    int sum=0;

for(int n:v)sum+=n; //range based for-loop, runs through each element in v.
//for(declaration:container)
    avg=sum/v.size();
return sum;
}

int main(){
    vector<int> nums;
    nums.push_back(5);
    nums.push_back(10);
    nums.push_back(44);
    nums.push_back(4);
    printvect(nums);
    int avg=0;
    int sum=sumvectors(nums, avg);
    cout<<"Sum is: "<<sum<<endl<<"Average is: "<<avg <<endl;

}