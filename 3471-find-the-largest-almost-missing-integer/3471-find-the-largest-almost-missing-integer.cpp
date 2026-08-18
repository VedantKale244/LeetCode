#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        vector<int> count(51, 0);

        int n = nums.size();

        // Check every subarray of size k
        for (int i = 0; i <= n - k; i++) {
            set<int> seen;

            for (int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }

            // Each number is counted only once for this subarray
            for (int x : seen) {
                count[x]++;
            }
        }

        int ans = -1;

        // Find the largest number appearing in exactly one subarray
        for (int x = 0; x <= 50; x++) {
            if (count[x] == 1) {
                ans = max(ans, x);
            }
        }

        return ans;
    }
};