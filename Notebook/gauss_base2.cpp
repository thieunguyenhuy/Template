struct GaussElimination {
    struct LinearEquation {
        bitset<N> lhs;
        bitset<T> rhs;

        LinearEquation() {
            lhs.reset(), rhs.reset();
        }

        void show() {
            cerr << lhs << ' ' << rhs << '\n';
        }
    };

    vector<LinearEquation> slae;
    vector<int> where;
    int n;

    void resize(int _n) {
        n = _n; slae.assign(n, LinearEquation()), where.assign(n, -1);
    }

    bool solve() {
        for (int row = 0; row < n; ++row) {
            if (!slae[row].lhs.any()) continue;
            int p = slae[row].lhs._Find_first();
            for (int i = 0; i < n; ++i) if (i != row && slae[i].lhs[p]) {
                slae[i].lhs ^= slae[row].lhs;
                slae[i].rhs ^= slae[row].rhs;
            }
            where[p] = row;
        }

        return true;
    }
} gauss;