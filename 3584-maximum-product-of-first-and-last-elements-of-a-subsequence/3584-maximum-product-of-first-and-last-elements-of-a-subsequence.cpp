class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        int n = nums.size();

        // Special case: subsequence contains one element.
        if (m == 1) {
            long long ans = 0;

            for (long long x : nums) {
                ans = max(ans, x * x);
            }

            return ans;
        }

        long long mn = LLONG_MAX;
        long long mx = LLONG_MIN;

        long long ans = LLONG_MIN;

        for (int j = m - 1; j < n; j++) {
            // This index can now be the first element.
            int i = j - m + 1;

            mn = min(mn, (long long)nums[i]);
            mx = max(mx, (long long)nums[i]);

            long long x = nums[j];

            ans = max({
                ans,
                x * mn,
                x * mx
            });
        }

        return ans;
    }
};