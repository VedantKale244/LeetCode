class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int ones = 0;
        for (char c : s) {
            if (c == '1') ones++;
        }

        string t = "1" + s + "1";

        vector<pair<char, int>> runs;
        int i = 0, m = t.size();

        while (i < m) {
            int j = i;
            while (j < m && t[j] == t[i]) j++;
            runs.push_back({t[i], j - i});
            i = j;
        }

        int ans = ones;

        for (int k = 1; k + 1 < (int)runs.size(); k++) {
            if (runs[k].first == '1') {
                int leftZeros = runs[k - 1].second;
                int rightZeros = runs[k + 1].second;
                ans = max(ans, ones + leftZeros + rightZeros);
            }
        }

        return ans;
    }
};