class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();

        vector<bool> reachable(n, false);
        reachable[0] = true;

        int count = 0;

        for (int i = 1; i < n; i++) {

            // Add positions entering the window
            if (i - minJump >= 0 && reachable[i - minJump]) {
                count++;
            }

            // Remove positions leaving the window
            if (i - maxJump - 1 >= 0 && reachable[i - maxJump - 1]) {
                count--;
            }

            // Current position can be reached
            if (s[i] == '0' && count > 0) {
                reachable[i] = true;
            }
        }

        return reachable[n - 1];
    }
};