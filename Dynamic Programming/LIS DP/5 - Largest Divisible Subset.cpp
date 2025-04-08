// Code to find the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies: answer[i] % answer[j] == 0, or answer[j] % answer[i] == 0 ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(N^2) & O(N^2)
    vector<int> solveBy2DTable(vector<int>& nums) {
        sort(begin(nums), end(nums));
        int n = nums.size();
        int maxLenLDS = 0;
        
        vector<int> LDS(n, 1);
        vector<vector<int>> divSubset(n);

        for(int j = 0; j < n; ++j) { // Find the length of longest divisible subset and the values of it
            divSubset[j].push_back(nums[j]);
            for(int i = 0; i < j; ++i) {
                if(nums[j] % nums[i] == 0) {
                    if(LDS[j] < LDS[i] + 1) {
                        LDS[j] = LDS[i] + 1;
                        divSubset[j] = divSubset[i]; 
                        divSubset[j].push_back(nums[j]);
                    }
                }
            }
            maxLenLDS = max(maxLenLDS, LDS[j]);
        }

        for(int j = 0; j < n; ++j) // Return the values of the longest divisible subset 
            if(LDS[j] == maxLenLDS) 
                return divSubset[j];
                        
        return {};
    }
    
    // O(N^2) & O(N)
    vector<int> solveBy1DTable(vector<int>& nums) {
        int n = nums.size();
        sort(begin(nums), end(nums));
        
        vector<int> LDS(n, 1);   // LDS[i] represents the length of the LDS ending at that ith index 
        vector<int> temp(n, -1); // temp[i] represents the index of the recently seen value which is considered as the part of the LDS ending at that ith index
        
        // Find the length of the (LDS) longest divisible subset ending at index i
        for(int i = 0; i < n; ++i) {
            temp[i] = i;
            for(int j = 0; j < i; ++j) {
                if(nums[i] % nums[j] == 0) {
                    if(1 + LDS[j] > LDS[i]) {
                        LDS[i]  = 1 + LDS[j];
                        temp[i] = j;
                    }
                }
            }
        }
        
        int maxLenLDS = -1;
        int maxLenIdx = -1;
        
        for(int i = 0; i < n; ++i) { // Find the length of the longest divisible subset
            if(LDS[i] > maxLenLDS) {
                maxLenLDS = LDS[i];
                maxLenIdx = i;
            }
        }
            
        vector<int> LDS;
        while(maxLenIdx != temp[maxLenIdx]) { // Store the result values
            LDS.push_back(nums[maxLenIdx]);
            maxLenIdx = temp[maxLenIdx];
        }
        LDS.push_back(nums[maxLenIdx]);
        
        reverse(begin(LDS), end(LDS)); // Reverse the result array to get the actual order
        return LDS;
    }
    
public:
    // Method to find the largest divisible subset, using tabulation :-
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        return solveBy1DTable(nums);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/largest-divisible-subset/description/
