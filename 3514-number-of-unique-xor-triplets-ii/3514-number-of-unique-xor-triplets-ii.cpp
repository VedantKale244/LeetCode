class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int v : nums) {
            auto ndp = dp;

            for (int taken = 0; taken <= 3; taken++) {
                for (int xr = 0; xr < MAXX; xr++) {
                    if (!dp[taken][xr]) continue;

                    if (taken + 1 <= 3)
                        ndp[taken + 1][xr ^ v] = true;

                    if (taken + 2 <= 3)
                        ndp[taken + 2][xr] = true;

                    if (taken + 3 <= 3)
                        ndp[taken + 3][xr ^ v] = true;
                }
            }

            dp = move(ndp);
        }

        int ans = 0;
        for (bool ok : dp[3])
            if (ok) ans++;

        return ans;
    }
};