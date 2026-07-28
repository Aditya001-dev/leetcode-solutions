class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        string first = "";
        string mid = "";

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 == 1)
                mid = char('a' + i);

            first += string(freq[i] / 2, char('a' + i));
        }

        string second = first;
        reverse(second.begin(), second.end());

        return first + mid + second;
    }
};