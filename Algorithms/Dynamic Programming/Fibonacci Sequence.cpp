#include <iostream>
#include <unordered_map>

// Memoization: Use a map to store computed Fibonacci numbers
std::unordered_map<int, int> fibMemo;

// Function to compute Fibonacci number using memoization
int fibonacciMemoization(int n) {
    if (n <= 1) {
        return n;
    }
    
    // Check if value already computed
    if (fibMemo.find(n) != fibMemo.end()) {
        return fibMemo[n];
    }
    
    // Compute and store the value
    fibMemo[n] = fibonacciMemoization(n - 1) + fibonacciMemoization(n - 2);
    return fibMemo[n];
}

int main() {
    int n = 10; // Example: Compute the 10th Fibonacci number
    
    std::cout << "Fibonacci number at position " << n << " (Memoization): " << fibonacciMemoization(n) << std::endl;
    
    return 0;
}
