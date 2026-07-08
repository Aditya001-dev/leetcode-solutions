class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        int n = s.size();

        vector<long long> pow10(n + 1, 1);
        for (int i = 1; i <= n; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<long long> prefNum(n + 1, 0);
        vector<int> prefCnt(n + 1, 0);
        vector<int> prefSum(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefNum[i + 1] = prefNum[i];
            prefCnt[i + 1] = prefCnt[i];
            prefSum[i + 1] = prefSum[i];

            if (s[i] != '0') {
                int d = s[i] - '0';
                prefNum[i + 1] = (prefNum[i] * 10 + d) % MOD;
                prefCnt[i + 1]++;
                prefSum[i + 1] += d;
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int cnt = prefCnt[r + 1] - prefCnt[l];
            int sum = prefSum[r + 1] - prefSum[l];

            long long x =
                (prefNum[r + 1] -
                 prefNum[l] * pow10[cnt] % MOD +
                 MOD) % MOD;

            ans.push_back((x * sum) % MOD);
        }

        return ans;
    }
};