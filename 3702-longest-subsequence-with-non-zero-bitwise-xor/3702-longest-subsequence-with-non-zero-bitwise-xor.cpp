class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int totalXor = 0;
        int nonZeroCount = 0;
        
        for (int num : nums) {
            totalXor ^= num;
            if (num != 0) {
                nonZeroCount++;
            }
        }
        
        // If no non-zero elements exist, max subsequence length is 0
        if (nonZeroCount == 0) {
            return 0;
        }
        
        // If the total XOR sum is non-zero, take the whole array
        if (totalXor != 0) {
            return nums.size();
        }
        
        // If total XOR sum is 0, excluding any single element makes it non-zero
        return nums.size() - 1;
    }
};