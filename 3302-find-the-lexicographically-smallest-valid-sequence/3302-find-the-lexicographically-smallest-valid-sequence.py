from typing import List

class Solution:
    def validSequence(self, word1: str, word2: str) -> List[int]:
        n = len(word1)
        m = len(word2)
        
        # suf[k] will store the maximum starting index in word1 to exactly match word2[k...m-1]
        suf = [-1] * (m + 1)
        suf[m] = n  # Base case: empty suffix can be matched starting at length n
        
        # Precompute right-to-left exact matches
        curr = n - 1
        for k in range(m - 1, -1, -1):
            while curr >= 0 and word1[curr] != word2[k]:
                curr -= 1
            if curr < 0:
                break
            suf[k] = curr
            curr -= 1
            
        ans = []
        k = 0
        mismatches = 1
        
        # Greedily match left-to-right to construct the lexicographically smallest sequence
        for j in range(n):
            if k == m:
                break
            
            if word1[j] == word2[k]:
                # Exact Match
                ans.append(j)
                k += 1
            elif mismatches == 1:
                # Mismatch - Validate if we can exact match the rest of word2 
                if suf[k + 1] != -1 and j + 1 <= suf[k + 1]:
                    ans.append(j)
                    mismatches = 0
                    k += 1
                    
        # Check if we were able to successfully form a full sequence for word2
        if k == m:
            return ans
        return []