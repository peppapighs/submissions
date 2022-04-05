#include <bits/stdc++.h>

#define long long long

using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert = false) {
    int n = a.size();

    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for( ; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len) {
            cd w(1);
            for(int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if(invert) for(cd &x : a)
        x /= n;
}

const int N = 1e6 + 5;

int n;
int cnt[N];
vector<cd> A;

int main() {
    scanf("%d", &n);

    for(int i = 1; i < n; i++)
        ++cnt[1ll * i * i % n];
    for(int i = 0; i < n; i++)
        A.emplace_back(cnt[i], 0);

    int sz = 1;
    while(sz < 2 * n) sz <<= 1;
    while((int)A.size() < sz) A.emplace_back(0);

    fft(A);
    for(cd &x : A) x = x * x;
    fft(A, true);

    long ans = 0;
    for(int i = 0; i < sz; i++)
        ans += (long)round(A[i].real()) * cnt[i % n];
    for(int i = 1; i < n; i++)
        ans += cnt[2ll * i * i % n];
    printf("%lld\n", ans >> 1);

    return 0;
}