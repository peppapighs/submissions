#include <bits/stdc++.h>

#define base complex<double>
#define all(x) (x).begin(), (x).end()

using namespace std;

const int N = 1e3+5;
const int M = 1e9+7;
const double PI = 4*atan(1);

void fft(vector<base> &a) {
    int n = a.size();
    for(int i = 1, j = 0; i < n; i++) {
        int k = n >> 1;
        while(j >= k) j -= k, k >>= 1;
        j += k;
        if(i < j) swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len;
        int half = len >> 1;
        base omega(cos(ang), sin(ang)), w0(1);
        vector<base> w(half);
        for(int i = 0; i < half; i++) w[i] = w0, w0 *= omega;
        for(int i = 0; i < n; i += len) for(int j = 0; j < half; j++) {
            base u = a[i + j], v = a[i + j + half] * w[j];
            a[i + j] = u + v;
            a[i + j + half] = u - v;
        }
    }
}

vector<int> fft_mul(vector<int> a, vector<int> b) {
    int n = 1;
    vector<base> fa(all(a)), fb(all(b));
    while(a.size() + b.size() > n) n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa), fft(fb);
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