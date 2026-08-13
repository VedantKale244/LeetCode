#include <bits/stdc++.h>
using namespace std;

struct Node {
    char leftChar, rightChar;
    int len;
    int prefix, suffix, best;

    Node() {
        leftChar = rightChar = '#';
        len = prefix = suffix = best = 0;
    }

    Node(char c) {
        leftChar = rightChar = c;
        len = prefix = suffix = best = 1;
    }
};

class SegmentTree {
private:
    int n;
    vector<Node> tree;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        // Initially take the best from either side
        res.prefix = a.prefix;
        res.suffix = b.suffix;
        res.best = max(a.best, b.best);

        if (a.rightChar == b.leftChar) {
            res.best = max(res.best, a.suffix + b.prefix);

            // Entire left segment is one character
            if (a.prefix == a.len) {
                res.prefix = a.len + b.prefix;
            }

            // Entire right segment is one character
            if (b.suffix == b.len) {
                res.suffix = b.len + a.suffix;
            }
        }

        return res;
    }

    void build(int node, int l, int r, const string& s) {
        if (l == r) {
            tree[node] = Node(s[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node] = Node(c);
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

public:
    SegmentTree(const string& s) {
        n = s.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, s);
    }

    void update(int idx, char c) {
        update(1, 0, n - 1, idx, c);
    }

    int getBest() {
        return tree[1].best;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s,
                                 string queryCharacters,
                                 vector<int>& queryIndices) {

        SegmentTree st(s);

        vector<int> lengths;

        for (int i = 0; i < queryIndices.size(); i++) {
            int index = queryIndices[i];
            char c = queryCharacters[i];

            st.update(index, c);

            lengths.push_back(st.getBest());
        }

        return lengths;
    }
};