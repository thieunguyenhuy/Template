struct AhoCorasick {
    struct Node {
        int fail, output;
        int child[2], nxt[2];

        Node() {
            fail = output = 0;
            child[0] = child[1] = -1;
            nxt[0] = nxt[1] = -1;
        }
    };

    vector<Node> nodes;
    vector<string> all;

    void reset() {
        nodes.clear(), nodes.emplace_back(Node());
        all.clear();
    }

    void add(string &s) {
        int v = 0; all.emplace_back(s);
        for (char ch : s) {
            int c = ch - '0';
            if (nodes[v].child[c] == -1) {
                nodes[v].child[c] = nodes.size();
                nodes.emplace_back(Node());
            }
            v = nodes[v].child[c];
        }
        ++nodes[v].output;
    }

    void build() {
        nodes[0].fail = 0;
        for (int i = 0; i < 2; ++i)
            nodes[0].nxt[i] = (nodes[0].child[i] == -1 ? 0 : nodes[0].child[i]);
    
        queue<int> q; q.emplace(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
 
            for (int c = 0; c < 2; ++c) if (nodes[u].child[c] != -1) {
                int v = nodes[u].child[c];
                nodes[v].fail = (u == 0 ? 0 : nodes[nodes[u].fail].nxt[c]);
                for (int d = 0; d < 2; ++d)
                    nodes[v].nxt[d] = (nodes[v].child[d] == -1 ? nodes[nodes[v].fail].nxt[d] : nodes[v].child[d]);
                nodes[v].output += nodes[nodes[v].fail].output;
                q.emplace(v);
            }
        }
    }

    int query(string &x) {
        ll ans = 0; int p = 0;
        for (auto ch : x) {
            int c = ch - '0', nxt = nodes[p].nxt[c];
            ans += nodes[nxt].output, p = nxt;
        }
        return ans;
    }
} aho;