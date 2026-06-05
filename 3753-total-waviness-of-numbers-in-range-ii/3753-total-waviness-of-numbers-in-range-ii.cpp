class Solution {
public:
    struct Node {
        long long cnt;
        long long wav;
        Node(long long c = 0, long long w = 0) : cnt(c), wav(w) {}
    };

    string s;
    Node dp[20][11][11][2][2];
    bool vis[20][11][11][2][2];

    Node dfs(int pos, int prev1, int prev2, bool started, bool tight) {
        if (pos == s.size()) {
            return Node(1, 0);
        }

        if (vis[pos][prev1][prev2][started][tight])
            return dp[pos][prev1][prev2][started][tight];

        vis[pos][prev1][prev2][started][tight] = true;

        Node res(0, 0);

        int lim = tight ? (s[pos] - '0') : 9;

        for (int d = 0; d <= lim; d++) {
            bool ntight = tight && (d == lim);

            if (!started && d == 0) {
                Node nxt = dfs(pos + 1, 10, 10, false, ntight);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else {
                int add = 0;

                if (started && prev2 != 10) {
                    if ((prev1 > prev2 && prev1 > d) ||
                        (prev1 < prev2 && prev1 < d))
                        add = 1;
                }

                int nprev2, nprev1;

                if (!started) {
                    nprev2 = 10;
                    nprev1 = d;
                } else {
                    nprev2 = prev1;
                    nprev1 = d;
                }

                Node nxt = dfs(pos + 1, nprev1, nprev2, true, ntight);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav + nxt.cnt * add;
            }
        }

        return dp[pos][prev1][prev2][started][tight] = res;
    }

    long long solve(long long x) {
        if (x <= 0) return 0;

        s = to_string(x);
        memset(vis, 0, sizeof(vis));

        return dfs(0, 10, 10, false, true).wav;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};