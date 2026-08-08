class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        int n = nums.size() / 2;

        unordered_map<int, int> freq;

        for (int x : nums) {
            freq[x]++;

            if (freq[x] == n)
                return x;
        }

        return -1;
    }
};