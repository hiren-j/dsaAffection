// Code to find the minimum number of elements to remove to make an array a mountain array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N)
    int minimumMountainRemovals(vector<int>& nums) {
        const int n = nums.size();
        
        vector<int> LIS(n, 1); 
        vector<int> LDS(n, 1); 
        
        for(int index = 0; index < n; ++index) 
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) 
                if(nums[index] > nums[prevIndex]) 
                    LIS[index] = max(LIS[index], LIS[prevIndex] + 1);
                    
        for(int index = n-1; index >= 0; --index) 
            for(int nextIndex = n-1; nextIndex > index; --nextIndex) 
                if(nums[index] > nums[nextIndex]) 
                    LDS[index] = max(LDS[index], LDS[nextIndex] + 1);
                    
        int maxLenBitonic = 0;
        
        for(int index = 0; index < n; ++index) 
            if(LIS[index] > 1 && LDS[index] > 1) 
                maxLenBitonic = max(maxLenBitonic, LIS[index] + LDS[index] - 1);
            
        return n - maxLenBitonic;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming | Greedy
Link  : https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/description/
