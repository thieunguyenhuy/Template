struct LichaoTree {
    struct Line {
        ll a, b;
 
        Line(ll _a = 0, ll _b = INF) {
            a = _a, b = _b;
        }
 
        ll operator() (ll x) {
            return a * x + b;
        }
    };
 
    struct Node {
        Node *le, *ri;
        Line ln;
 
        Node() {
            le = ri = nullptr;
            ln = Line();
        }
    };
 
    Node *root;
 
    LichaoTree() {
        root = nullptr;
    }
 
    Node *add(Node *root, int l, int r, Line ln) {
        if (root == nullptr) {
            root = new Node();
            root->ln = ln;
            return root;
        }
        int mid = (l + r) >> 1;
        if (root->ln(mid) > ln(mid)) swap(root->ln, ln);
        if (l == r) return root;
        if (root->ln.a < ln.a) root->le = add(root->le, l, mid, ln);
        else root->ri = add(root->ri, mid + 1, r, ln);
        return root;
    }
 
    void add(ll a, ll b) {
        root = add(root, -inf, inf, Line(a, b));
    }
 
    ll query(Node *root, int l, int r, ll x) {
        if (root == nullptr) return INF;
        int mid = (l + r) >> 1; ll ret = root->ln(x);
        if (x <= mid) minimize(ret, query(root->le, l, mid, x));
        else minimize(ret, query(root->ri, mid + 1, r, x));
        return ret;
    }
 
    ll query(ll x) {
        return query(root, -inf, inf, x);
    }
} cht;