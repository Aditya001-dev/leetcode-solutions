class Solution:
    def stoneGameII(self, piles: list[int]) -> int:
        n = len(piles)
        
        # suffix_sums[i] stores the sum of piles from index i to the end
        suffix_sums = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            suffix_sums[i] = suffix_sums[i + 1] + piles[i]
            
        memo = {}
        
        def dp(i, m):
            # If all piles have been taken
            if i >= n:
                return 0
                
            # Return cached result if already computed
            if (i, m) in memo:
                return memo[(i, m)]
                
            # If the current player can take all remaining piles
            if i + 2 * m >= n:
                return suffix_sums[i]
                
            max_stones = 0
            
            # Try taking X piles, where 1 <= X <= 2M
            for x in range(1, 2 * m + 1):
                # The current player's score is the total remaining stones 
                # minus the maximum stones the opponent can get from the rest.
                current_score = suffix_sums[i] - dp(i + x, max(m, x))
                max_stones = max(max_stones, current_score)
                
            memo[(i, m)] = max_stones
            return max_stones
            
        return dp(0, 1)