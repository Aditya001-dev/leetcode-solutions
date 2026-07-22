class Group {
public:
    int start;
    int length;
};

class SparseTable {
public:
    int n;
    vector<vector<int>> st;

    SparseTable(const vector<int>& nums) {
        n = nums.size();

        if (n == 0) return;

        int LOG = 32 - __builtin_clz(n);
        st.assign(LOG, vector<int>(n));

        for (int i = 0; i < n; i++)
            st[0][i] = nums[i];

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = max(st[k - 1][i],
                               st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r) {
        if (l > r) return 0;
        int len = r - l + 1;
        int k = 31 - __builtin_clz(len);
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries) {

        int ones = 0;
        for (char c : s)
            if (c == '1')
                ones++;

        vector<Group> zeroGroups;
        vector<int> zeroIndex(s.size());

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0')
                    zeroGroups.back().length++;
                else
                    zeroGroups.push_back({i, 1});
            }
            zeroIndex[i] = (int)zeroGroups.size() - 1;
        }

        if (zeroGroups.empty())
            return vector<int>(queries.size(), ones);

        vector<int> merge;

        for (int i = 0; i + 1 < zeroGroups.size(); i++)
            merge.push_back(
                zeroGroups[i].length +
                zeroGroups[i + 1].length);

        SparseTable st(merge);

        vector<int> ans;

        for (auto& q : queries) {
            int l = q[0];
            int r = q[1];

            int left =
                zeroIndex[l] == -1
                    ? -1
                    : zeroGroups[zeroIndex[l]].length -
                          (l - zeroGroups[zeroIndex[l]].start);

            int right =
                zeroIndex[r] == -1
                    ? -1
                    : r - zeroGroups[zeroIndex[r]].start + 1;

            int start =
                zeroIndex[l] + 1;

            int end =
                (s[r] == '1')
                    ? zeroIndex[r]
                    : zeroIndex[r] - 1;

            int cur = ones;

            if (s[l] == '0' &&
                s[r] == '0' &&
                zeroIndex[l] + 1 ==
                    zeroIndex[r]) {

                cur = max(cur,
                          ones + left + right);

            } else if (start <= end - 1) {

                cur = max(cur,
                          ones +
                              st.query(start,
                                       end - 1));
            }

            if (s[l] == '0' &&
                zeroIndex[l] + 1 <= end) {

                cur = max(
                    cur,
                    ones +
                        left +
                        zeroGroups[zeroIndex[l] + 1]
                            .length);
            }

            if (s[r] == '0' &&
                zeroIndex[l] <
                    zeroIndex[r] - 1) {

                cur = max(
                    cur,
                    ones +
                        right +
                        zeroGroups[zeroIndex[r] - 1]
                            .length);
            }

            ans.push_back(cur);
        }

        return ans;
    }
};