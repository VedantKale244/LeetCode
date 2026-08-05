class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> dir(n), undirected(n);

        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            dir[u].push_back(v);
            undirected[u].push_back(v);
            undirected[v].push_back(u);
        }

        vector<bool> suspicious(n, false);

        auto dfs1 = [&](auto &&self, int u) -> void {
            suspicious[u] = true;
            for (int v : dir[u]) {
                if (!suspicious[v])
                    self(self, v);
            }
        };

        dfs1(dfs1, k);

        vector<bool> vis(n, false);

        auto dfs2 = [&](auto &&self, int u) -> void {
            vis[u] = true;
            for (int v : undirected[u]) {
                if (!vis[v]) {
                    suspicious[v] = false;
                    self(self, v);
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (!suspicious[i] && !vis[i])
                dfs2(dfs2, i);
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};