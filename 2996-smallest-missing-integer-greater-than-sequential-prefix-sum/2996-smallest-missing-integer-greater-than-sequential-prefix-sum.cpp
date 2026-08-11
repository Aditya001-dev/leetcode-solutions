#include <vector>
#include <unordered_set>

class Solution {
public:
    int missingInteger(std::vector<int>& nums) {
        // Step 1: Find the sum of the longest sequential prefix
        int sum = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break; 
            }
        }
        
        // Step 2: Store numbers in a set for O(1) lookups
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        
        // Step 3: Find the smallest missing integer >= sum
        while (numSet.count(sum)) {
            sum++;
        }
        
        return sum;
    }
};