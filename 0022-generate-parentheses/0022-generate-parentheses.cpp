#include <vector>
#include <string>

class Solution {
public:
    void backtrack(std::vector<std::string>& result, std::string current_string, int open_count, int close_count, int max_pairs) {
        // Base case: string length is exactly 2 * n
        if (current_string.length() == max_pairs * 2) {
            result.push_back(current_string);
            return;
        }
        
        // If we can still add open parentheses
        if (open_count < max_pairs) {
            backtrack(result, current_string + "(", open_count + 1, close_count, max_pairs);
        }
        
        // If we can add a close parenthesis (must have an unmatched open parenthesis)
        if (close_count < open_count) {
            backtrack(result, current_string + ")", open_count, close_count + 1, max_pairs);
        }
    }

    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }
};