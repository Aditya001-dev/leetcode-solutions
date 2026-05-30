class Fenwick {
public:
    vector<int> bit;
    int n;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void update(int idx, int val) {
        idx++;
        while (idx <= n) {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        idx++;
        int res = 0;
        while (idx > 0) {
            res = max(res, bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int MAXX = 50000;

        set<int> pos;
        pos.insert(0);
        pos.insert(MAXX);

        for (auto &q : queries) {
            if (q[0] == 1)
                pos.insert(q[1]);
        }

        Fenwick fw(MAXX + 1);

        vector<int> pts(pos.begin(), pos.end());

        for (int i = 1; i < pts.size(); i++) {
            fw.update(pts[i], pts[i] - pts[i - 1]);
        }

        vector<bool> ans;

        for (int i = queries.size() - 1; i >= 0; i--) {
            auto &q = queries[i];

            if (q[0] == 1) {
                int x = q[1];

                auto it = pos.find(x);

                int l = *prev(it);
                int r = *next(it);

                pos.erase(it);

                fw.update(r, r - l);
            }
            else {
                int x = q[1];
                int sz = q[2];

                auto it = pos.upper_bound(x);

                int l = *prev(it);

                int best = fw.query(x);

                ans.push_back(max(best, x - l) >= sz);
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};