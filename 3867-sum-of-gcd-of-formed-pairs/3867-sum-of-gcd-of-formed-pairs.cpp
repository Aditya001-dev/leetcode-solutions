class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();

        vector<int> pref(n);
        int mx = 0;

        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            pref[i] = gcd(nums[i], mx);
        }

        sort(pref.begin(), pref.end());

        long long ans = 0;
        int l = 0, r = n - 1;

        while (l < r) {
            ans += gcd(pref[l], pref[r]);
            l++;
            r--;
        }

        return ans;
    }
};