#include <bits/stdc++.h>

#define base complex<double>
#define all(x) (x).begin(), (x).end()

using namespace std;

const int N = 1e3+5;
const int M = 1e9+7;
const double PI = 4*atan(1);

void fft(vector<base> &a) {
    int n = a.size(), L = 0;
    while((1 << L) < n) ++L;
    for(int i = 0, pos = 0; i < n; i++, pos = 0) {
        for(int j = 0; j < L; j++) pos |= (i & (1 << j)) << (L - j - 1);
        if(i < pos) swap(a[i], a[pos]);
    }
    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len;
        int half = len >> 1;
        base omega(cos(ang), sin(ang)), w(1);
        for(int i = 0; i < n; i += len, w = base(1)) for(int j = 0; j < half; j++, w *= omega) {
            base u = a[i + j], v = a[i + j + half] * w;
            a[i + j] = u + v;
            a[i + j + half] = u - v;
        }
    }
}

vector<int> fft_mul(vector<int> a, vector<int> b) {
    int n = 1;
    vector<base> fa(all(a)), fb(all(b));
    while(a.size() + b.size() > n) n <<= 1;
    fa.resize(n), fb.resize(n); fft(fa), fft(fb);
    for(int i = 0; i < n; i++) fa[i] = conj(fa[i] * fb[i]);
    fft(fa);
    vector<int> ret(n);
    for(int i = 0; i < n; i++) ret[i] = !!(int)(fa[i].real() / n + 0.5);
    while(!ret.empty() && !ret.back()) ret.pop_back();
    return ret;
}

int n, k;
vector<int> ans(1, 1), V(N);

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 1, a; i <= n; i++) scanf("%d", &a), V[a] = 1;
    for( ; k; k >>= 1) {
        if(k & 1) ans = fft_mul(ans, V);
        V = fft_mul(V, V);
    }
    for(int i = 0; i < ans.size(); i++) if(ans[i]) printf("%d ", i);
    printf("\n");

    return 0;
}