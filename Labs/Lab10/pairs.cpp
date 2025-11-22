#include <iostream>
#include <string>
using namespace std;

/*** Template class Pair ***/
template<typename TheType> class Pair {
   public:
      void Input();
      void Output();
      char CompareWith(Pair<TheType>* otherPair) ;
      void ShowComparison(Pair<TheType>* otherPair);

   private:
      TheType firstVal;
      TheType secondVal;
};

// Return '<', '=', or '>' according to whether the Pair is less than,
// equal to, or greater than the argument Pair
template<typename TheType>
char Pair<TheType>::CompareWith(Pair<TheType>* otherPair) {
   if(this->firstVal<otherPair->firstVal) return '<';
   else if(this->firstVal>otherPair->firstVal) return '>';
   else{
      if(this->secondVal<otherPair->secondVal) return '<';
      else if(this->secondVal>otherPair->secondVal) return '>';
      else return '=';
   }
}

// Input values into a pair
template<typename TheType>
void Pair<TheType>::Input() {
   cin>>this->firstVal>>this->secondVal;
   /* Type your code here. */
}

// Output a Pair 
template<typename TheType>
void Pair<TheType>::Output() {
   cout<<"["<<this->firstVal<<", "<<this->secondVal<<"]";
   /* Type your code here. */
}

// Output both pairs with a comparison symbol in between
template<typename TheType>
void Pair<TheType>::ShowComparison(Pair<TheType>* otherPair) {
   this->Output();
   cout<<" "<<this->CompareWith(otherPair)<<" ";
   otherPair->Output();
   cout<<endl;
}
/*** End template class Pair ***/

int main() {
   Pair<int> intPair;
   Pair<int> intOtherPair;
   intPair.Input();
   intOtherPair.Input();
   intPair.ShowComparison(&intOtherPair);

   Pair<double> doublePair;
   Pair<double> doubleOtherPair;
   doublePair.Input();
   doubleOtherPair.Input();
   doublePair.ShowComparison(&doubleOtherPair);

   Pair<string> wordPair;
   Pair<string> wordOtherPair;
   wordPair.Input();
   wordOtherPair.Input();
   wordPair.ShowComparison(&wordOtherPair);

   return 0;
}
