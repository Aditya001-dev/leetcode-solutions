class Solution:
    def winnerSquareGame(self, n: int) -> bool:
        # dp[i] will be True if the current player can win with i stones
        dp = [False] * (n + 1)
        
        for i in range(1, n + 1):
            # Check all possible square numbers we can remove
            k = 1
            while k * k <= i:
                # If removing k*k stones leaves the opponent in a losing state,
                # then i is a winning state for the current player.
                if not dp[i - k * k]:
                    dp[i] = True
                    break  # We found a winning strategy, no need to check further
                k += 1
                
        return dp[n]