struct GaussElim {
    struct LinearEquation {
        vector<int> lhs;
        int rhs;
 
        LinearEquation(int n = 0) {
            lhs.assign(n, 0), rhs = 0;
        }
 
        LinearEquation operator+ (const LinearEquation &other) {
            LinearEquation res(lhs.size()); res.rhs = (rhs + other.rhs) % 3;
            for (int i = 0; i < lhs.size(); ++i) res.lhs[i] = (lhs[i] + other.lhs[i]) % base;
            return res;
        }
 
        LinearEquation operator- (const LinearEquation &other) {
            LinearEquation res(lhs.size()); res.rhs = (rhs - other.rhs + 3) % 3;
            for (int i = 0; i < lhs.size(); ++i) res.lhs[i] = (lhs[i] - other.lhs[i] + base) % base;
            return res;
        }
    };
 
    vector<int> vars, where;
    vector<LinearEquation> slae;
    int n;
 
    void resize(int _n) {
        n = _n; slae.assign(n, LinearEquation(n));
        vars.assign(n, -1), where.assign(n, -1);
    }
 
    bool solve() {
        for (int col = 0, row = 0; col < n && row < n; ++col) {
            for (int i = row; i < n; ++i) if (slae[i].lhs[col]) {
                swap(slae[i], slae[row]);
                break;
            }
            if (!slae[row].lhs[col]) continue;
            where[col] = row;
 
            for (int i = 0; i < n; ++i) if (i != row && slae[i].lhs[col]) {
                if (slae[i].lhs[col] + slae[row].lhs[col] == 3) slae[i] = slae[i] + slae[row];
                else slae[i] = slae[i] - slae[row];
            }
            ++row;
        }
 
        for (int i = 0; i < n; ++i) {
            bool flag = true;
            for (auto &x : slae[i].lhs) if (x > 0) {
                flag = false;
                break;
            }
            if (flag && slae[i].rhs != 0) return false;
        }
 
        for (int i = 0; i < n; ++i) if (where[i] != -1) {
            int row = where[i];
            if (slae[row].lhs[i] == 1) vars[i] = slae[row].rhs;
            else vars[i] = (3 - slae[row].rhs) % 3;
        }
 
        return true;
    }
} gauss;