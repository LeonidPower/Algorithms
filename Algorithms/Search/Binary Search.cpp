#include <iostream>
#include <vector>

// Function to perform binary search
int binarySearch(const std::vector<int>& arr, int key) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == key) {
            return mid;  // Return index of the key if found
        } else if (arr[mid] < key) {
            left = mid + 1;  // Search in the right half
        } else {
            right = mid - 1;  // Search in the left half
        }
    }
    
    return -1;  // Return -1 if key is not found
}

int main() {
    std::vector<int> arr = {10, 20, 30, 40, 50};
    int key = 30;
    
    int index = binarySearch(arr, key);
    
    if (index != -1) {
        std::cout << "Element found at index: " << index << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }
    
    return 0;
}
