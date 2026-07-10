class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                   vector<vector<int>>& queries) {

        vector<pair<int,int>> arr;
        for (int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        sort(arr.begin(), arr.end());

        vector<int> values(n);
        vector<int> pos(n);

        for (int i = 0; i < n; i++) {
            values[i] = arr[i].first;
            pos[arr[i].second] = i;
        }

        vector<int> comp(n);
        int cid = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (values[i] - values[i - 1] > maxDiff)
                cid++;
            comp[i] = cid;
        }

        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {
            int j = upper_bound(values.begin(), values.end(),
                                values[i] + maxDiff) - values.begin() - 1;
            nxt[i] = j;
        }

        int LOG = 18; // since 2^17 > 1e5

        vector<vector<int>> up(LOG, vector<int>(n));

        up[0] = nxt;

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {

            int u = q[0];
            int v = q[1];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            if (nums[u] == nums[v]) {
                ans.push_back(1);
                continue;
            }

            int l = pos[u];
            int r = pos[v];

            if (l > r) swap(l, r);

            if (comp[l] != comp[r]) {
                ans.push_back(-1);
                continue;
            }

            int cur = l;
            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < r) {
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }

            if (cur < r) {
                cur = nxt[cur];
                steps++;
            }

            ans.push_back(cur >= r ? steps : -1);
        }

        return ans;
    }
};