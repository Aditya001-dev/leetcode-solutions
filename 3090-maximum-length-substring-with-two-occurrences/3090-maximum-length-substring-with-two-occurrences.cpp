class Solution {
public:
    int maximumLengthSubstring(string s) {
        int left = 0, right = 0;
        int max_len = 0;
        int count[26] = {0}; // Frequency array for lowercase English letters

        while (right < s.length()) {
            int char_idx = s[right] - 'a';
            count[char_idx]++;
            
            // If any character occurs more than 2 times, shrink the window from the left
            while (count[char_idx] > 2) {
                count[s[left] - 'a']--;
                left++;
            }
            
            // Update the maximum length found so far
            max_len = max(max_len, right - left + 1);
            right++;
        }

        return max_len;
    }
};