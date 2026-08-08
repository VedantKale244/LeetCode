class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[i] = first index of word2 that cannot be matched
        // exactly using word1[i ... n-1].
        vector<int> suf(n + 1);

        suf[n] = m;

        int j = m - 1;

        // Build suffix feasibility information.
        for (int i = n - 1; i >= 0; --i) {
            if (j >= 0 && word1[i] == word2[j]) {
                --j;
            }

            suf[i] = j + 1;
        }

        vector<int> ans;

        j = 0;
        bool mismatchUsed = false;

        // Greedily choose the earliest possible index.
        for (int i = 0; i < n && j < m; ++i) {

            // Case 1: Exact match.
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                ++j;
            }

            // Case 2: Use our one allowed mismatch.
            else if (!mismatchUsed && suf[i + 1] <= j + 1) {
                ans.push_back(i);
                ++j;
                mismatchUsed = true;
            }
        }

        // Couldn't construct a complete sequence.
        if (j != m) {
            return {};
        }

        return ans;
    }
};