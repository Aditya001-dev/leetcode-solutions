class Solution {
public:
    long long sumAndMultiply(int n) {
        string s = to_string(n);

        long long x = 0;

        for (char c : s) {
            if (c != '0') {
                x = x * 10 + (c - '0');
            }
        }

        long long sum = 0;
        long long temp = x;

        while (temp > 0) {
            sum += temp % 10;
            temp /= 10;
        }

        return x * sum;
    }
};