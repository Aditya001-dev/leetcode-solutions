class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long,int> cnt;

        for (int x : nums) cnt[x]++;

        long long ans = 1;

        if (cnt.count(1)) {
            ans = max(ans,
                      (long long)(cnt[1] % 2 ?
                                  cnt[1] :
                                  cnt[1] - 1));
        }

        for (auto &[start, f] : cnt) {
            if (start == 1) continue;

            long long cur = start;
            long long len = 0;

            while (cnt.count(cur) && cnt[cur] >= 2) {
                len += 2;

                if (!cnt.count(cur * cur)) {
                    len--;          // use one current as center
                    break;
                }

                cur *= cur;
            }

            if (cnt.count(cur) && cnt[cur] == 1)
                len++;

            ans = max(ans, len);
        }

        return (int)ans;
    }
};