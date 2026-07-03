class Solution {
public:
    using ll = long long;
    const ll INF = 4e18;

    int findMaxPathScore(vector<vector<int>>& edges,
                         vector<bool>& online,
                         long long k) {

        int n = online.size();

        vector<vector<pair<int,int>>> g(n);
        vector<int> indeg(n, 0);

        int mxCost = 0;

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int c = e[2];

            g[u].push_back({v, c});
            indeg[v]++;
            mxCost = max(mxCost, c);
        }

        vector<int> topo;
        queue<int> q;

        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            topo.push_back(u);

            for (auto &[v, c] : g[u]) {
                if (--indeg[v] == 0)
                    q.push(v);
            }
        }

        auto can = [&](int limit) {
            vector<ll> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {
                if (dist[u] == INF)
                    continue;

                if (u != 0 && u != n - 1 && !online[u])
                    continue;

                for (auto &[v, c] : g[u]) {
                    if (c < limit)
                        continue;

                    if (v != n - 1 && !online[v])
                        continue;

                    dist[v] = min(dist[v], dist[u] + (ll)c);
                }
            }

            return dist[n - 1] <= k;
        };

        if (!can(0))
            return -1;

        int lo = 0, hi = mxCost;
        int ans = 0;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (can(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};