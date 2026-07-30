class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        return min(n, 8)
             + max(0, min(n - 8, 8)) * 2
             + max(0, min(n - 16, 8)) * 3
             + max(0, n - 24) * 4;
    }
};