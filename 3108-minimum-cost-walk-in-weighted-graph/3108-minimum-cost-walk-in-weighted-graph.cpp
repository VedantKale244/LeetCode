class Solution {
public:
    vector<int> parent, compAnd;

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;
    }

    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);

        for (auto &edge : edges) {
            unite(edge[0], edge[1]);
        }

        compAnd.assign(n, -1);

        for (auto &edge : edges) {
            int root = find(edge[0]);
            compAnd[root] &= edge[2];
        }

        vector<int> ans;

        for (auto &q : query) {
            int u = q[0], v = q[1];

            if (find(u) != find(v)) {
                ans.push_back(-1);
            } else {
                ans.push_back(compAnd[find(u)]);
            }
        }

        return ans;
    }
};