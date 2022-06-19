#include <bits/stdc++.h>

#define base complex<double>
#define long long long
#define all(x) (x).begin(), (x).end()

using namespace std;

const int N = 1 << 10;
const double PI = 4 * atan(1);

void fft(vector<base> &a) {
    int n = a.size(), m = n >> 1;
    for (int i = 1, j = 0; i < n; i++) {
        int k = m;
        while (j >= k)
            j -= k, k >>= 1;
        j += k;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len;
        base omega(cos(ang), sin(ang));
        int half = len >> 1;
        vector<base> w(half);
        base w0(1);
        for (int i = 0; i < half; i++)
            w[i] = w0, w0 *= omega;
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < half; j++) {
                base u = a[i + j], v = a[i + j + half] * w[j];
                a[i + j] = u + v;
                a[i + j + half] = u - v;
            }
    }
}

vector<long> fft_mul(vector<long> a, vector<long> b) {
    vector<base> fa(all(a)), fb(all(b));
    int n = 1;
    while (a.size() + b.size() > n)
        n <<= 1;
    fa.resize(n), fb.resize(n);
    fft(fa), fft(fb);
    for (int i = 0; i < n; i++)
        fa[i] = conj(fa[i] * fb[i]);
    fft(fa);
    vector<long> ret(n);
    for (int i = 0; i < n; i++)
        ret[i] = min(1ll, (long)(fa[i].real() / n + 0.5));
    while (!ret.empty() && !ret.back())
        ret.pop_back();
    return ret;
}

int n, k;
vector<long> ans(1, 1), V(N);

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1, a; i <= n; i++)
        scanf("%d", &a), V[a] = 1;
    for (; k; k >>= 1) {
        if (k & 1)
            ans = fft_mul(ans, V);
        V = fft_mul(V, V);
    }
    for (int i = 0; i < ans.size(); i++)
        if (ans[i])
            printf("%d ", i);
    printf("\n");

    return 0;
}