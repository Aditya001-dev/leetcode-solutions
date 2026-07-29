import math
from collections import Counter

class Solution(object):
    def smallestPalindrome(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        n = len(s)
        cnt = Counter(s)
        
        mid = ''
        half_counts = {}
        for ch, c in cnt.items():
            if c % 2 == 1:
                mid = ch
            if c // 2 > 0:
                half_counts[ch] = c // 2
        
        half_len = n // 2
        cap = k
        
        def nCr(a, b):
            b = min(b, a - b)
            if b == 0:
                return 1
            result = 1
            for i in range(b):
                result = result * (a - i) // (i + 1)
                if result > cap:
                    return cap + 1
            return result
        
        def count_perms(counts_dict):
            result = 1
            remaining = sum(counts_dict.values())
            for c in counts_dict.values():
                if c == 0:
                    continue
                result *= nCr(remaining, c)
                remaining -= c
                if result > cap:
                    return cap + 1
            return result
        
        total = count_perms(half_counts)
        if total < k:
            return ""
        
        chars = sorted(half_counts.keys())
        remaining_counts = dict(half_counts)
        remaining_k = k
        half_result = []
        
        for _ in range(half_len):
            for ch in chars:
                if remaining_counts.get(ch, 0) == 0:
                    continue
                remaining_counts[ch] -= 1
                block = count_perms(remaining_counts)
                if remaining_k <= block:
                    half_result.append(ch)
                    break
                else:
                    remaining_k -= block
                    remaining_counts[ch] += 1
        
        half_str = ''.join(half_result)
        return half_str + mid + half_str[::-1]