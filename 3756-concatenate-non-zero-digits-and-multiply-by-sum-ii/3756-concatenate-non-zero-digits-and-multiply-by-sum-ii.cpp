#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> pos;
        vector<int> digit;

        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                digit.push_back(s[i] - '0');
            }
        }

        int k = digit.size();

        vector<long long> pow10(k + 1, 1);
        for (int i = 1; i <= k; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<long long> hash(k + 1, 0);
        for (int i = 0; i < k; i++)
            hash[i + 1] = (hash[i] * 10 + digit[i]) % MOD;

        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + (s[i] - '0');

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            auto it1 = lower_bound(pos.begin(), pos.end(), l);
            auto it2 = upper_bound(pos.begin(), pos.end(), r);

            if (it1 == it2) {
                ans.push_back(0);
                continue;
            }

            int L = it1 - pos.begin();
            int R = (it2 - pos.begin()) - 1;
            int len = R - L + 1;

            long long x = (hash[R + 1] - hash[L] * pow10[len]) % MOD;
            if (x < 0) x += MOD;

            long long sum = pref[r + 1] - pref[l];

            ans.push_back((x * (sum % MOD)) % MOD);
        }

        return ans;
    }
};