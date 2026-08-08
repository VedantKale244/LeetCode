class Solution {
public:

    vector<int> bfs(int src, vector<vector<int>>& graph) {
        int n = graph.size();

        vector<int> dist(n, -1);
        queue<int> q;

        dist[src] = 0;
        q.push(src);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (dist[v] != -1)
                    continue;

                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

        return dist;
    }

    int specialNodes(
        int n,
        vector<vector<int>>& edges,
        int x,
        int y,
        int z
    ) {
        // Build tree
        vector<vector<int>> graph(n);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // Distances from the three target nodes
        vector<int> distX = bfs(x, graph);
        vector<int> distY = bfs(y, graph);
        vector<int> distZ = bfs(z, graph);

        int answer = 0;

        for (int u = 0; u < n; u++) {
            long long a = distX[u];
            long long b = distY[u];
            long long c = distZ[u];

            // Sort the three distances
            if (a > b)
                swap(a, b);

            if (b > c)
                swap(b, c);

            if (a > b)
                swap(a, b);

            // Pythagorean condition
            if (a * a + b * b == c * c)
                answer++;
        }

        return answer;
    }
};