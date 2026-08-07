import math

class Solution:
    def smallestNumber(self, num: str, t: int) -> str:
        # Step 1: Check if 't' can be formed by digits 1-9
        # Allowed prime factors are 2, 3, 5, 7.
        temp = t
        for p in [2, 3, 5, 7]:
            while temp % p == 0:
                temp //= p
        if temp > 1:
            return "-1"

        # Step 2: Memoized DP to find the minimum number of digits needed
        # to get a product divisible by 'req'
        memo = {1: 0}
        def get_min_len(req: int) -> int:
            if req in memo:
                return memo[req]
            res = float('inf')
            for d in range(2, 10):
                g = math.gcd(req, d)
                if g > 1:
                    res = min(res, 1 + get_min_len(req // g))
            memo[req] = res
            return res

        get_min_len(t)

        N = len(num)
        
        # Step 3: Find the longest prefix without any '0'
        first_zero = -1
        for i in range(N):
            if num[i] == '0':
                first_zero = i
                break

        start_i = N if first_zero == -1 else first_zero

        # req_at[i] tracks the division requirement remaining after passing num[0...i-1]
        req_at = [1] * (start_i + 1)
        req_at[0] = t
        for i in range(1, start_i + 1):
            req_at[i] = req_at[i-1] // math.gcd(req_at[i-1], int(num[i-1]))

        # If num itself is already a zero-free number satisfying the condition
        if start_i == N and req_at[N] == 1:
            return num

        # Helper method to greedily form the lexicographically smallest suffix
        def build_suffix(req: int, length: int) -> str:
            res = []
            curr_req = req
            for j in range(length):
                for cd in range(1, 10):
                    cand_req = curr_req // math.gcd(curr_req, cd)
                    if length - 1 - j >= get_min_len(cand_req):
                        res.append(str(cd))
                        curr_req = cand_req
                        break
            return "".join(res)

        # Step 4: Traverse backward to find the optimal split point
        for i in range(start_i, -1, -1):
            if i < N:
                min_d = int(num[i]) + 1
            else:
                continue

            for d in range(min_d, 10):
                nxt_req = req_at[i] // math.gcd(req_at[i], d)
                if N - 1 - i >= get_min_len(nxt_req):
                    return num[:i] + str(d) + build_suffix(nxt_req, N - 1 - i)

        # Step 5: Fallback if no string of length N satisfies constraints.
        # FIXED: Ensure the new length is at least the minimum digits required by 't'.
        fallback_len = max(N + 1, get_min_len(t))
        return build_suffix(t, fallback_len)