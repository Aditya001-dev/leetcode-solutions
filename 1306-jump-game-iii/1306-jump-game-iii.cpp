class Solution {
public:
    bool dfs(vector<int>& arr, int start, vector<bool>& visited) {
        
        // Out of bounds or already visited
        if(start < 0 || start >= arr.size() || visited[start])
            return false;

        // Found zero
        if(arr[start] == 0)
            return true;

        visited[start] = true;

        // Jump forward or backward
        return dfs(arr, start + arr[start], visited) ||
               dfs(arr, start - arr[start], visited);
    }

    bool canReach(vector<int>& arr, int start) {
        vector<bool> visited(arr.size(), false);
        return dfs(arr, start, visited);
    }
};