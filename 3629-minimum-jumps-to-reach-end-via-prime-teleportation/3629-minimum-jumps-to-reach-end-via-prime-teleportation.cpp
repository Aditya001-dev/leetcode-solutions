class Solution {
public:
    bool isPrime(int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    }

    int minJumps(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int, vector<int>> mp;

        // Store indices divisible by each prime
        for (int i = 0; i < n; i++) {
            int x = nums[i];

            for (int p = 2; p * p <= x; p++) {
                if (x % p == 0) {
                    mp[p].push_back(i);

                    while (x % p == 0)
                        x /= p;
                }
            }

            if (x > 1)
                mp[x].push_back(i);
        }

        vector<int> dist(n, -1);
        queue<int> q;

        q.push(0);
        dist[0] = 0;

        unordered_set<int> usedPrime;

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            if (i == n - 1)
                return dist[i];

            // adjacent left
            if (i - 1 >= 0 && dist[i - 1] == -1) {
                dist[i - 1] = dist[i] + 1;
                q.push(i - 1);
            }

            // adjacent right
            if (i + 1 < n && dist[i + 1] == -1) {
                dist[i + 1] = dist[i] + 1;
                q.push(i + 1);
            }

            // teleport
            if (isPrime(nums[i]) && !usedPrime.count(nums[i])) {
                usedPrime.insert(nums[i]);

                for (int nxt : mp[nums[i]]) {
                    if (dist[nxt] == -1) {
                        dist[nxt] = dist[i] + 1;
                        q.push(nxt);
                    }
                }
            }
        }

        return -1;
    }
};