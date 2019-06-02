/*
 Sliding Maximum Subarray problem
 Inspired on the GeeksforGeeks article
 Link: https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/
*/


#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

vector<int> max_size_k(const vector<int> & arr, int k){
        int n = arr.size();
        vector<int> result;
        //let's create a deque, in which its size will be the subarray size
        deque<int> d(k);
        //this deque will contain indexes of the necessary elements in the range 

        //first, let's loop through the first subarray (range [0..k) )
        int i;
        for (i = 0; i < k; i++){
                //for every integer we read, the ones smaller than it will be removed
                //from the deque

                while (not d.empty() && arr[i] >= arr[d.back()]){
                        d.pop_back();
                }

                d.push_back(i); //for every element, we remove the ones smaller than it and place it in the deque
        }
        //the max number in the subarray is in the front of the deque
        result.push_back(arr[d.front()]);

        //now we need to go from [k, n) 

        for (; i < n; i++){
                //first, we'll remove all the indexes that don't belong in the range
                //anymore

                //given a array with for integers [4, 3, 2, 1] and k = 2
                //the indexes we need to remove are less or equal than i-k

                while(not d.empty() && d.front() <= i-k)
                        d.pop_front();

                //after that, we do the same thing as we did in the first for loop
                while (not d.empty() && arr[i] >= arr[d.back()])
                        d.pop_back();

                d.push_back(i);
                //the max element in the range will be again in the front of the deque
                result.push_back(arr[d.front()]);

        }

        return result;
}

int main() {
        vector<int> arr = {3,9,5,8,1,7,4,10,16,2};
        int subarr_size = 4;

        vector<int> result = max_size_k(arr, subarr_size);
        vector<int> correct_answer = {9,9,8,8,10,16,16};

        assert(result == correct_answer);

        for (auto elem : result){
                cout << elem << " ";
        }

        cout << endl;
    
    return 0;
}
