#include <iostream>
using namespace std;

int fib_iterative(int n) {
    // Base cases
    if (n <= 1)
        return n;

    // Initialize first two Fibonacci numbers
    int prev2 = 0; // F(0)
    int prev1 = 1; // F(1)
    int curr = 0;

    // Compute Fibonacci values from 2 up to n
    for (int i = 2; i <= n; i++) {
        curr = prev1 + prev2; // F(n) = F(n-1) + F(n-2)
        prev2 = prev1;        // Shift window forward
        prev1 = curr;
    }

    return curr; // F(n)
}
int fib_recur(int n) {
    // Base cases
    if (n <= 1)
        return n;
    return fib_recur(n - 1) + fib_recur(n - 2);
}
// Recursive function
//Start recursive function here


int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    cout << "Fibonacci (Iterative) of " << n << " = " << fib_iterative(n) << endl;
    cout<< "Fibonacci (Recursive) of " << n << " = " << fib_recur(n) << endl;
    return 0;
}