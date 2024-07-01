#include <iostream>
#include <vector>

// Function to perform linear search
int linearSearch(const std::vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == key) {
            return i;  // Return index of the key if found
        }
    }
    return -1;  // Return -1 if key is not found
}

int main() {
    std::vector<int> arr = {10, 20, 30, 40, 50};
    int key = 30;
    
    int index = linearSearch(arr, key);
    
    if (index != -1) {
        std::cout << "Element found at index: " << index << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }
    
    return 0;
}
