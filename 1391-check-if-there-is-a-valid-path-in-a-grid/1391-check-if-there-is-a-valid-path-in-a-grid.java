import java.util.*;

class Solution {
    int[][][] dirs = {
        {},
        {{0,-1},{0,1}},     // 1 left right
        {{-1,0},{1,0}},     // 2 up down
        {{0,-1},{1,0}},     // 3 left down
        {{0,1},{1,0}},      // 4 right down
        {{0,-1},{-1,0}},    // 5 left up
        {{0,1},{-1,0}}      // 6 right up
    };

    public boolean hasValidPath(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        boolean[][] vis = new boolean[m][n];

        Queue<int[]> q = new LinkedList<>();
        q.offer(new int[]{0,0});
        vis[0][0] = true;

        while(!q.isEmpty()) {
            int[] cur = q.poll();
            int x = cur[0], y = cur[1];

            if(x == m-1 && y == n-1) return true;

            int type = grid[x][y];

            for(int[] d : dirs[type]) {
                int nx = x + d[0];
                int ny = y + d[1];

                if(nx < 0 || ny < 0 || nx >= m || ny >= n || vis[nx][ny])
                    continue;

                int nextType = grid[nx][ny];

                for(int[] back : dirs[nextType]) {
                    if(nx + back[0] == x && ny + back[1] == y) {
                        vis[nx][ny] = true;
                        q.offer(new int[]{nx, ny});
                        break;
                    }
                }
            }
        }
        return false;
    }
}