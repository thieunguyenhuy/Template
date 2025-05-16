namespace TwoSat {
    const int N = 1e6 + 5;
    vector<int> adj[N], rev_adj[N], order;
    int ans[N], vis[N], comp[N];
    vii edges;
    int n;
 
    void resize(int _n) {
        n = _n;
        for (int i = 0; i < 2 * n; ++i) {
            comp[i] = -1, vis[i] = 0;
            adj[i].clear(), rev_adj[i].clear();
        }
        edges.clear();
    }
 
    int NOT(int x) {
        return (x < n ? x + n : x - n);
    }
 
    void add(int u, int v) { // u -> v, if u then v
        edges.emplace_back(u, v);
        adj[u].emplace_back(v), rev_adj[v].emplace_back(u);
    }
 
    void add_or(int u, int v) { // u or v = true
        add(NOT(u), v), add(NOT(v), u);
    }
 
    void dfs1(int u) {
        vis[u] = true;
        for (auto v : adj[u]) if (!vis[v]) {
            dfs1(v);
        }
        order.emplace_back(u);
    }
 
    void dfs2(int u, int cnt) {
        comp[u] = cnt;
        for (auto v : rev_adj[u]) if (comp[v] == -1) {
            dfs2(v, cnt);
        }
    }
 
    bool solve() {
        for (int i = 0; i < 2 * n; ++i) if (!vis[i]) {
            dfs1(i);
        }
 
        reverse(order.begin(), order.end());
        int cnt = 0;
        for (auto u : order) if (comp[u] == -1) {
            dfs2(u, ++cnt);
        }
  
        for (int i = 0; i < n; ++i) if (comp[i] == comp[NOT(i)]) {
            return false;
        }
        for (int i = 0; i < n; ++i) ans[i] = comp[i] > comp[NOT(i)];
        return true;
    }
}