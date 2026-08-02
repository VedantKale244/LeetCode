class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {

        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);

        // Build graph and indegree
        for (auto &p : prerequisites) {
            int course = p[0];
            int prereq = p[1];

            graph[prereq].push_back(course);
            indegree[course]++;
        }

        queue<int> q;

        // Push all nodes with indegree 0
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        vector<int> order;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            order.push_back(node);

            for (int neighbor : graph[node]) {
                indegree[neighbor]--;

                if (indegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }

        if (order.size() != numCourses)
            return {};

        return order;
    }
};