class Solution {
public:

    struct TrieNode {

        int bestIdx;
        map<char, TrieNode*> child;

        TrieNode() {
            bestIdx = -1;
        }
    };

    TrieNode* root = new TrieNode();

    int better(vector<string>& words, int a, int b) {

        if(a == -1)
            return b;

        if(words[b].size() < words[a].size())
            return b;

        if(words[b].size() == words[a].size() && b < a)
            return b;

        return a;
    }

    void insert(string &word, int idx, vector<string>& words) {

        TrieNode* node = root;

        node->bestIdx = better(words, node->bestIdx, idx);

        for(int i = word.size() - 1; i >= 0; i--) {

            char c = word[i];

            if(node->child.count(c) == 0) {
                node->child[c] = new TrieNode();
            }

            node = node->child[c];

            node->bestIdx = better(words, node->bestIdx, idx);
        }
    }

    int query(string &word) {

        TrieNode* node = root;

        int ans = node->bestIdx;

        for(int i = word.size() - 1; i >= 0; i--) {

            char c = word[i];

            if(node->child.count(c) == 0)
                break;

            node = node->child[c];

            ans = node->bestIdx;
        }

        return ans;
    }

    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        for(int i = 0; i < wordsContainer.size(); i++) {
            insert(wordsContainer[i], i, wordsContainer);
        }

        vector<int> ans;

        for(auto &q : wordsQuery) {
            ans.push_back(query(q));
        }

        return ans;
    }
};