class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);

        for (int x : nums)
            freq[x]++;

        vector<long long> cntDiv(mx + 1, 0);

        for (int d = 1; d <= mx; d++) {
            for (int m = d; m <= mx; m += d) {
                cntDiv[d] += freq[m];
            }
        }

        vector<long long> exactPairs(mx + 1, 0);

        for (int d = mx; d >= 1; d--) {
            long long k = cntDiv[d];
            exactPairs[d] = k * (k - 1) / 2;

            for (int m = 2 * d; m <= mx; m += d) {
                exactPairs[d] -= exactPairs[m];
            }
        }

        vector<long long> prefix(mx + 1, 0);

        for (int d = 1; d <= mx; d++) {
            prefix[d] = prefix[d - 1] + exactPairs[d];
        }

        vector<int> ans;

        for (long long q : queries) {
            int g = lower_bound(prefix.begin() + 1, prefix.end(), q + 1) - prefix.begin();
            ans.push_back(g);
        }
        return ans;
    }
};