class Fenwick {
public:
    vector<int> bit;
    int n;

    Fenwick(int n) : n(n) {
        bit.assign(n + 1, 0);
    }

    void add(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    long long sum(int idx) {
        long long res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }
};

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        vector<int> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (nums[i] == target ? 1 : -1);
        }

        vector<int> vals = pref;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        Fenwick bit(vals.size());

        long long ans = 0;

        for (int x : pref) {
            int pos = lower_bound(vals.begin(), vals.end(), x) - vals.begin();

            ans += bit.sum(pos - 1);

            bit.add(pos, 1);
        }

        return ans;
    }
};