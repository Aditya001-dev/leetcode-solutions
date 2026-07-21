class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        int ones = 0;
        int preZero = INT_MIN;
        int bestMerge = 0;

        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;

            int len = j - i;

            if (s[i] == '1') {
                ones += len;
            } else {
                bestMerge = max(bestMerge, preZero + len);
                preZero = len;
            }

            i = j;
        }

        return ones + bestMerge;
    }
};