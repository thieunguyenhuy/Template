struct FenwickTree {
    using T = int;
    vector<T> bit;

    FenwickTree() {}

    void resize(int n) {
        bit.assign(n + 1, 0);
    }

    void update(int p, T val) {
        for (; p < int(bit.size()); p += p & -p) bit[p] += val;
    }

    T get(int p) {
        T ans = 0;
        for (; p > 0; p -= p & -p) ans += bit[p];
        return ans;
    }
} fen;