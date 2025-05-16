namespace FFT {
	const ld pi = atan2(1, 1) * 4;

	struct cmplx {
	    ld a, b;

	    cmplx() {
	        a = 0, b = 0;
	    }

	    cmplx(ld a1, ld b1) {
	        a = a1, b = b1;
	    }
	};

	inline cmplx sum(cmplx& c1, cmplx& c2) {
	    return {c1.a + c2.a, c1.b + c2.b};
	}

	inline cmplx sub(cmplx& c1, cmplx& c2) {
	    return {c1.a - c2.a, c1.b - c2.b};
	}

	inline cmplx mult(cmplx& c1, cmplx& c2) {
	    return {c1.a * c2.a - c1.b * c2.b, c1.a * c2.b + c1.b * c2.a};
	}

	void fft(vector<cmplx> &a, int n) {
	    for (int i = 1, j = 0; i < n; ++i) {
	        int bit = n >> 1;
	        for (; j >= bit; bit >>= 1) j -= bit;
	        j += bit;
	        if (i < j) swap(a[i], a[j]);
	    }

	    for (int k = 1; k < n; k <<= 1) {
	        ld phi = pi / k;
	        cmplx wt(cos(phi), sin(phi));
	        for (int i = 0; i < n; i += 2 * k) {
	            cmplx w(1, 0);
	            for (int j = 0; j < k; ++j) {
	                cmplx u = a[i + j], v = mult(a[i + j + k], w);
	                a[i + j] = sum(u, v);
	                a[i + j + k] = sub(u, v);
	                w = mult(w, wt);
	            }
	        }
	    }
	}

	vector<int> multiply(vector<int> &s, vector<int> &t) {
	    int need = (int) s.size() + t.size() - 1, sz = 1;
	    while (sz < need) sz <<= 1;
	    
	    vector<cmplx> a(sz), b(sz);
	    for (int i = 0; i < sz; ++i) {
	        if(i < (int)s.size()) a[i] = cmplx(s[i], 0);
	        else a[i] = cmplx(0, 0);
	        if(i < (int)t.size()) b[i] = cmplx(t[i], 0);
	        else b[i] = cmplx(0, 0);
	    }
	    
	    fft(a, sz);
	    fft(b, sz);
	    
	    for (int i = 0; i < sz; ++i) {
	        a[i] = mult(a[i], b[i]);
	    }

	    fft(a, sz);
	    reverse(a.begin() + 1, a.end());

	    vector<int> ans(need);
	    for (int i = 0; i < need; ++i) ans[i] = round(a[i].a / sz);
	    return ans;
	}

	vector<int> operator * (vector<int> &s, vector<int> &t) {
		return multiply(s, t);
	}
}