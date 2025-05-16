struct SuffixArray {
    string str;
    vector<int> sa, lcp, order, rank;
    vector<ll> weight;
    int n;
 
    SuffixArray(string _str = "") {
        str = _str, n = str.size();
        sa.assign(n, 0), lcp.assign(n, 0), order.assign(n, 0);
        rank.assign(n, 0), weight.assign(n, 0);
        get(), getLCP();
    }
 
    void getSA() {
        for (int i = 0; i < n; ++i) {
            sa[i] = i;
            weight[i] = int(str[i]);
        }
 
        auto cmp = [&](int x, int y) {
            return weight[x] < weight[y];
        };
 
        sort (sa.begin(), sa.end(), cmp);
 
        for (int len = 1; len <= n; len <<= 1) {
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                if (i > 0 && weight[sa[i]] == weight[sa[i - 1]]) order[sa[i]] = order[sa[i - 1]];
                else order[sa[i]] = ++cnt;
            }
            if (cnt == n) break;
            for (int i = 0; i < n; ++i) {
                weight[i] = 1ll * order[i] * (n + 1) + (i + len < n ? order[i + len] : 0);
            }
            for (int i = 0, j = 0; i < n; i = j) {
                while (j < n && order[sa[j]] == order[sa[i]]) ++j;
                sort (sa.begin() + i, sa.begin() + j, cmp);
            }
        }
    }
 
    void getLCP() {
        for (int i = 0; i < n; ++i) rank[sa[i]] = i;
        for (int i = 0, k = 0; i < n; lcp[rank[i++]] = k) {
            if (rank[i] > 0) {
                int j = sa[rank[i] - 1];
                if (k > 0) --k;
                while (str[i + k] == str[j + k]) ++k;
            }
            else k = 0;
        }
    }
} T;