// Solve max weighted matching
struct Hungarian {
    using T = long long;
    const T INF = 2e18;

    vector<vector<T>> a;
    vector<T> u, v, p, way, where;
    int n, m;

    Hungarian(int _n = 0, int _m = 0) {
        resize(_n, _m);
    }

    void resize(int _n, int _m) {
        n = _n, m = _m; a.assign(n + 1, vector<T>(m + 1, 0));
        u.assign(n + 1, 0), v.assign(n + 1, 0), p.assign(n + 1, 0), way.assign(n + 1, 0), where.assign(n + 1, -1);
    }

    T solve() {
        for (int i = 1; i <= n; ++i) {
            p[0] = i; int j0 = 0;
            vector<T> minv(m+1, INF);
            vector<bool> used(m+1, false);
            do {
                used[j0] = true;
                int i0 = p[j0], j1 = -1; T delta = INF;
                for (int j = 1; j <= m; ++j) if (!used[j]) {
                    T cur = a[i0][j] - u[i0] - v[j];
                    if (minimize(minv[j], cur)) way[j] = j0;
                    if (minimize(delta, minv[j])) j1 = j;
                }
                for (int j = 0; j <= m; ++j) {
                    if (used[j]) u[p[j]] += delta,  v[j] -= delta;
                    else minv[j] -= delta;
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        for (int j = 1; j <= m; ++j) where[p[j]] = j;

        T ans = 0;
        for (int i = 1; i <= n; ++i) ans += a[i][where[i]];
        return ans;
    }
} solver;