class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> best(m, vector<int>(n, -1));

        priority_queue<vector<int>> pq;

        int startHealth = health - grid[0][0];

        if (startHealth <= 0) return false;

        pq.push({startHealth, 0, 0});
        best[0][0] = startHealth;

        vector<pair<int,int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            int h = cur[0];
            int x = cur[1];
            int y = cur[2];

            if (x == m - 1 && y == n - 1)
                return true;

            if (h < best[x][y]) continue;

            for (auto &[dx, dy] : dir) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;

                int nh = h - grid[nx][ny];

                if (nh > 0 && nh > best[nx][ny]) {
                    best[nx][ny] = nh;
                    pq.push({nh, nx, ny});
                }
            }
        }

        return false;
    }
};