class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> lg(n + 1);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;

        vector<vector<int>> stMax(K, vector<int>(n));
        vector<vector<int>> stMin(K, vector<int>(n));

        for (int i = 0; i < n; i++) {
            stMax[0][i] = nums[i];
            stMin[0][i] = nums[i];
        }

        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                stMax[j][i] = max(
                    stMax[j - 1][i],
                    stMax[j - 1][i + (1 << (j - 1))]
                );

                stMin[j][i] = min(
                    stMin[j - 1][i],
                    stMin[j - 1][i + (1 << (j - 1))]
                );
            }
        }

        auto value = [&](int l, int r) -> long long {
            int len = r - l + 1;
            int j = lg[len];

            int mx = max(
                stMax[j][l],
                stMax[j][r - (1 << j) + 1]
            );

            int mn = min(
                stMin[j][l],
                stMin[j][r - (1 << j) + 1]
            );

            return 1LL * mx - mn;
        };

        struct Node {
            long long val;
            int l, r;

            bool operator<(const Node& other) const {
                return val < other.val;
            }
        };

        priority_queue<Node> pq;

        for (int l = 0; l < n; l++) {
            pq.push({value(l, n - 1), l, n - 1});
        }

        long long ans = 0;

        while (k--) {
            auto cur = pq.top();
            pq.pop();

            ans += cur.val;

            if (cur.r > cur.l) {
                pq.push({
                    value(cur.l, cur.r - 1),
                    cur.l,
                    cur.r - 1
                });
            }
        }

        return ans;
    }
};