ll binpow(ll x, ll y, ll p) {
    ll ans = 1;
    while (y > 0) {
        if (y & 1) ans = (Int)ans * x % p;
        x = (Int)x * x % p, y >>= 1;
    }
    return ans;
}

ll sqrt(ll a, ll p) {
    a %= p; if (a < 0) a += p;
    if (a == 0) return 0;

    assert(binpow(a, (p - 1) / 2, p) == 1);
    if (p % 4 == 3) return binpow(a, (p + 1) / 4, p);

    ll s = p - 1, n = 2;
    int r = 0, m;
    while (s % 2 == 0)
        ++r, s >>= 1;
    
    while (binpow(n, (p - 1) / 2, p) != p - 1) ++n;
    ll x = binpow(a, (s + 1) / 2, p);
    ll b = binpow(a, s, p), g = binpow(n, s, p);
    for (; ; r = m) {
        ll t = b;
        for (m = 0; m < r && t != 1; ++m)
            t = (Int)t * t % p;
        if (m == 0) return x;
        ll gs = binpow(g, 1LL << (r - m - 1), p);
        g = (Int)gs * gs % p;
        x = (Int)x * gs % p;
        b = (Int)b * g % p;
    }

    return -1;
}