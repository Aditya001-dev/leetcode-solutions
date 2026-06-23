class Solution {
public:
    static const int MOD = 1000000007;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<int> up(m, 1), down(m, 1);
        vector<int> newUp(m), newDown(m);
        vector<int> pref(m + 1);

        for (int len = 2; len <= n; len++) {

            pref[0] = 0;
            for (int i = 0; i < m; i++) {
                pref[i + 1] = pref[i] + up[i];
                if (pref[i + 1] >= MOD) pref[i + 1] -= MOD;
            }

            for (int i = 0; i < m; i++) {
                newDown[i] = pref[i];
            }

            pref[0] = 0;
            for (int i = 0; i < m; i++) {
                pref[i + 1] = pref[i] + down[i];
                if (pref[i + 1] >= MOD) pref[i + 1] -= MOD;
            }

            int total = pref[m];

            for (int i = 0; i < m; i++) {
                newUp[i] = total - pref[i + 1];
                if (newUp[i] < 0) newUp[i] += MOD;
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;

        for (int i = 0; i < m; i++) {
            ans += up[i];
            ans += down[i];
        }

        return (int)(ans % MOD);
    }
};