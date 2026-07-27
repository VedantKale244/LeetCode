class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> first, last, freq;

        for (int i = 0; i < nums.size(); i++) {
            if (!first.count(nums[i])) {
                first[nums[i]] = i;
            }
            last[nums[i]] = i;
            freq[nums[i]]++;
        }

        int degree = 0;
        for (auto &it : freq) {
            degree = max(degree, it.second);
        }

        int ans = nums.size();
        for (auto &it : freq) {
            if (it.second == degree) {
                ans = min(ans, last[it.first] - first[it.first] + 1);
            }
        }

        return ans;
    }
};