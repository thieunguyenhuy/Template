struct SegmentTree {
    vector<ll> nodes, lazy;
    int n;

    SegmentTree() {}

    void resize(int _n) { // 1-index
        n = _n; nodes.assign(4 * n + 5, 0), lazy.assign(4 * n + 5, 0);
        build(1, 1, n);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            nodes[id] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        nodes[id] = nodes[id << 1] + nodes[id << 1 | 1];
    }

    void apply(int id, int l, int r, int val) {
        nodes[id] += 1ll * (r - l + 1) * val;
        lazy[id] += val;
    }

    void push_down(int id, int l, int r) {
        if (lazy[id] == 0) return;
        int mid = (l + r) >> 1;
        apply(id << 1, l, mid, lazy[id]);
        apply(id << 1 | 1, mid + 1, r, lazy[id]);
        lazy[id] = 0;
    }

    void update(int id, int l, int r, int u, int v, int val) {
        if (l > v || r < u) return;
        if (u <= l && r <= v) {
            apply(id, l, r, val);
            return;
        }
        push_down(id, l, r); int mid = (l + r) >> 1;
        update(id << 1, l, mid, u, v, val);
        update(id << 1 | 1, mid + 1, r, u, v, val);
        nodes[id] = nodes[id << 1] + nodes[id << 1 | 1];
    }

    void update(int u, int v, int val) {
        update(1, 1, n, u, v, val);
    }

    ll get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (u <= l && r <= v) return nodes[id];
        push_down(id, l, r); int mid = (l + r) >> 1;
        return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
    }

    ll get(int u, int v) {
        return get(1, 1, n, u, v);
    }
} mytree;