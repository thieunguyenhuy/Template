#include <bits/stdc++.h>
using namespace std;

#define popcount(n) (__builtin_popcountll((n)))
#define clz(n) (__builtin_clzll((n)))
#define ctz(n) (__builtin_ctzll((n)))
#define lg(n) (63 - __builtin_clzll((n)))
#define BIT(n, i) (((n) >> (i)) & 1ll)
#define MASK(i) (1ll << (i))
#define FLIP(n, i) ((n) ^ (1ll << (i)))
#define ON(n, i) ((n) | MASK(i))
#define OFF(n, i) ((n) & ~MASK(i))

#define Int __int128
#define fi first
#define se second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef pair<long long, int> pli;
typedef pair<int, long long> pil;
typedef vector<pair<int, int>> vii;
typedef vector<pair<long long, long long>> vll;
typedef vector<pair<long long, int>> vli;
typedef vector<pair<int, long long>> vil;

template <class T1, class T2>
bool maximize(T1 &x, T2 y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
}
template <class T1, class T2>
bool minimize(T1 &x, T2 y) {
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}

template <class T>
void remove_duplicate(vector<T> &ve) {
    sort (ve.begin(), ve.end());
    ve.resize(unique(ve.begin(), ve.end()) - ve.begin());
}

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
template <class T> T random(T l, T r) {
    return uniform_int_distribution<T>(l, r)(rng);
}
template <class T> T random(T r) {
    return rng() % r;
}

const int N = 1e5 + 5, LG = 18, lim = 10 * N * LG;
const int MOD = 1e9 + 7;
const int inf = 1e9;
const ll INF = 1e18;

int n, m, len = 0;
int heavy[N], head[N], par[N], dep[N], pos[N];
vector<int> adj[N];

int numNode = 0, root = 0;
vector<int> version, le, ri;
vector<ll> nodes, lazy1, lazy2;
vector<bool> hasLazy;

void TLE() {
    for (; ; ) {}
}

void addNode() {
    le.emplace_back(0), ri.emplace_back(0);
    nodes.emplace_back(0), lazy1.emplace_back(0), lazy2.emplace_back(0);
    hasLazy.emplace_back(false);
}

struct PersistentIT {
    ll f(int n) {
        return 1ll * n * (n + 1) / 2;
    }

    ll f(int l, int r) {
        return f(r) - f(l - 1);
    }

    int newlazykid(ll x, ll y, int l, int r, int oldId) {
        int id = ++numNode; 
        addNode();
        le[id] = le[oldId], ri[id] = ri[oldId];
        nodes[id] = nodes[oldId], lazy1[id] = lazy1[oldId], lazy2[id] =  lazy2[oldId];
        hasLazy[id] = true;

        nodes[id] += 1ll * x * (r - l + 1);
        nodes[id] += 1ll * f(l, r) * y;
        lazy1[id] += x, lazy2[id] += y;

        return id;
    }

    int newparent(int l, int r) {
        int id = ++numNode; addNode();
        le[id] = l, ri[id] = r;
        nodes[id] = nodes[l] + nodes[r];
        return id;
    }

    void push(int id, int l, int r) {
        if (!hasLazy[id]) return;

        if (l != r) {
            int mid = l + r >> 1;
            le[id] = newlazykid(lazy1[id], lazy2[id], l, mid, le[id]);
            ri[id] = newlazykid(lazy1[id], lazy2[id], mid + 1, r, ri[id]);
        }

        lazy1[id] = lazy2[id] = 0;
        hasLazy[id] = false;
    }

    int update(int u, int v, int A, int B, int l, int r, int oldId) {
        if (l > v || r < u) return oldId;
        if (u <= l && r <= v) return newlazykid(0ll + A - 1ll * u * B, B, l, r, oldId);
        push(oldId, l, r); int mid = l + r >> 1;
        int left = update(u, v, A, B, l, mid, le[oldId]),
            right = update(u, v, A, B, mid + 1, r, ri[oldId]);
        return newparent(left, right);
    }

    ll get(int u, int v, int l, int r, int id) {
        if (l > v || r < u) return 0;
        if (u <= l && r <= v) return nodes[id];
        push(id, l, r); int mid = l + r >> 1;
        return get(u, v, l, mid, le[id]) + get(u, v, mid + 1, r, ri[id]);
    }
} mytree;

int dfs(int u, int fa) {
    int ma = -1, sz = 1; heavy[u] = -1;
    for (auto v : adj[u]) {
        if (v == fa) continue;
        par[v] = u, dep[v] = dep[u] + 1;
        int tmp = dfs(v, u); sz += tmp;
        if (maximize(ma, tmp)) heavy[u] = v;
    }
    return sz;
}

void hld(int u, int uhead) {
    head[u] = uhead, pos[u] = ++len;
    if (heavy[u] != -1) hld(heavy[u], uhead);
    for (auto v : adj[u])
        if (v != heavy[u] && v != par[u]) hld(v, v);
}

int lca(int u, int v) {
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
    }
    if (dep[u] > dep[v]) swap(u, v);
    return u;
}

void update(int u, int v, int A, int B, int start) {
    int cur = start;
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        if (start > 0) {
            cur -= pos[v] - pos[head[v]] + 1;
            root = mytree.update(pos[head[v]], pos[v], 0ll + A + 1ll * cur * B, B, 1, len, root);
        }
        else {
            root = mytree.update(pos[head[v]], pos[v], 0ll + A + 1ll * cur * B + 1ll * (pos[v] - pos[head[v]]) * B, -B, 1, len, root);
            cur += pos[v] - pos[head[v]] + 1;
        }
    }
    if (dep[u] > dep[v]) swap(u, v);
    if (start > 0) {
        cur -= pos[v] - pos[u] + 1;
        root = mytree.update(pos[u], pos[v], 0ll + A + 1ll * cur * B, B, 1, len, root);
    }
    else {
        root = mytree.update(pos[u], pos[v], 0ll + A + 1ll * cur * B + 1ll * (pos[v] - pos[u]) * B, -B, 1, len, root);
        cur += pos[v] - pos[u] + 1;
    }
}

void update(int u, int v, int A, int B) {
    int p = lca(u, v);
    update(u, p, A, B, 0);
    update(p, v, A, B, dep[u] - dep[p] + dep[v] - dep[p] + 1);
    update(p, p, -A, -B, dep[u] - dep[p] + 1);
    version.emplace_back(root);
}

ll query(int u, int v) {
    ll ans = 0;
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        ans += mytree.get(pos[head[v]], pos[v], 1, len, root);
    }
    if (dep[u] > dep[v]) swap(u, v);
    ans += mytree.get(pos[u], pos[v], 1, len, root);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    // n = m = 1e5;

    for (int i = 1; i < n; ++i) {
        // int u = i, v = i + 1;
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v), adj[v].emplace_back(u);
    }

    dfs(1, -1), hld(1, 1);

    version.emplace_back(root = numNode);
    addNode();
    ll lastans = 0;
    for (int i = 1; i <= m; ++i) {
        char type; cin >> type;
        // char type = 'c';
        if (type == 'l') {
            int q; cin >> q;
            q = (0ll + q + lastans) % version.size();
            root = version[q];
        }
        else {
            // int u = i, v = (i + 2) % n + 1;
            int u, v; cin >> u >> v;
            u = (0ll + u + lastans) % n + 1, v = (0ll + v + lastans) % n + 1;
            // cout << "Real = " << u << ' ' << v << '\n';
            if (type == 'c') {
                // int A = random(1, 1000), B = random(1, 1000);
                int A, B; cin >> A >> B;
                update(u, v, A, B);
                // cout << "Sum = " << mytree.get(1, n, 1, n, root) << '\n';
                // for (int x = 1; x <= n; ++x)
                //     cout << mytree.get(pos[x], pos[x], 1, n, root) << ' ';
                // cout << '\n';
            }
            else cout << (lastans = query(u, v)) << '\n';
        }
    }
    cerr << '\n'; return 0;
}