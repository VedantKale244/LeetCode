#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;

    ll lcmLimited(ll a, ll b, ll limit) {
        ll g = gcd(a, b);
        ll x = a / g;

        // If LCM would be greater than limit,
        // we don't need to calculate it exactly.
        if (x > limit / b)
            return limit + 1;

        return x * b;
    }

    ll countAmounts(ll x, const vector<int>& coins) {
        int n = coins.size();
        ll total = 0;

        // Enumerate all non-empty subsets
        for (int mask = 1; mask < (1 << n); mask++) {
            ll lcm = 1;
            int bits = 0;
            bool tooLarge = false;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    lcm = lcmLimited(lcm, coins[i], x);

                    if (lcm > x) {
                        tooLarge = true;
                        break;
                    }
                }
            }

            if (tooLarge)
                continue;

            ll cnt = x / lcm;

            if (bits % 2 == 1)
                total += cnt;
            else
                total -= cnt;
        }

        return total;
    }

    long long findKthSmallest(vector<int>& coins, long long k) {
        ll low = 1;
        ll high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            ll mid = low + (high - low) / 2;

            if (countAmounts(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};