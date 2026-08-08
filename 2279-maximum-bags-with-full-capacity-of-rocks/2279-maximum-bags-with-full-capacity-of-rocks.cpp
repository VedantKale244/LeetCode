class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        int n = capacity.size();
        vector<long long> need;

        int ans = 0;

        for (int i = 0; i < n; i++) {
            long long required = capacity[i] - rocks[i];

            if (required == 0) {
                ans++;
            } else {
                need.push_back(required);
            }
        }

        sort(need.begin(), need.end());

        for (long long required : need) {
            if (additionalRocks < required)
                break;

            additionalRocks -= required;
            ans++;
        }

        return ans;
    }
};