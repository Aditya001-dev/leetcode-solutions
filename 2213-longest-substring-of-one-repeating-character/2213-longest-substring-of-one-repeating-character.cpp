#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int maxLen;
    int prefixLen;
    int suffixLen;
    int len;
    char prefixChar;
    char suffixChar;
};

class Solution {
    vector<Node> tree;
    string str;

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.len = left.len + right.len;
        res.prefixChar = left.prefixChar;
        res.suffixChar = right.suffixChar;

        // Calculate new prefix
        res.prefixLen = left.prefixLen;
        if (left.prefixLen == left.len && left.prefixChar == right.prefixChar) {
            res.prefixLen = left.len + right.prefixLen;
        }

        // Calculate new suffix
        res.suffixLen = right.suffixLen;
        if (right.suffixLen == right.len && right.suffixChar == left.suffixChar) {
            res.suffixLen = right.len + left.suffixLen;
        }

        // Calculate new max length
        res.maxLen = max(left.maxLen, right.maxLen);
        if (left.suffixChar == right.prefixChar) {
            res.maxLen = max(res.maxLen, left.suffixLen + right.prefixLen);
        }

        return res;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, 1, str[start], str[start]};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, char c) {
        if (start == end) {
            tree[node] = {1, 1, 1, 1, c, c};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, c);
        } else {
            update(2 * node + 1, mid + 1, end, idx, c);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        str = s;
        int n = s.length();
        tree.resize(4 * n);
        
        build(1, 0, n - 1);
        
        int k = queryCharacters.length();
        vector<int> ans(k);
        
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            // The root of the segment tree always contains the max length for the whole string
            ans[i] = tree[1].maxLen; 
        }
        
        return ans;
    }
};