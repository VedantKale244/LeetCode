class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {};

        for (int x : stones) {
            ++cnt[x % 3];
        }

        if (cnt[1] == 0 && cnt[2] == 0) {
            return false;
        }

        int mn = min(cnt[1], cnt[2]);
        int mx = max(cnt[1], cnt[2]);

        if (cnt[0] % 2 == 0) {
            return mn > 0;
        }

        return mx - mn > 2;
    }
};