#include <bits/stdc++.h>

using namespace std;

const int N = 1<<17;
const int M = 1e9+7;

struct Matrix {
    int m[2][2];

    Matrix() { m[0][0] = 1, m[0][1] = 1, m[1][0] = 1, m[1][1] = 0; }

    friend Matrix operator+(const Matrix &a, const Matrix &b) {
        Matrix c;
        memset(c.m, 0, sizeof c);
        for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) c.m[i][j] = (a.m[i][j] + b.m[i][j]) % M;
        return c;
    }

    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        Matrix c;
        memset(c.m, 0, sizeof c);
        for(int k = 0; k < 2; k++) for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) {
            c.m[i][j] += a.m[i][k] * b.m[k][j];
            c.m[i][j] %= M;
        }
        return c;
    }

    friend bool operator!=(const Matrix &a, const Matrix &b) {
        for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) if(a.m[i][j] != b.m[i][j]) return true;
        return false;
    }
};

int n, q;
Matrix base, iden, zero;
Matrix t[N<<1], lz[N<<1], pre[70];

void build(int p = 1, int l = 1, int r = n) {
    if(l == r) return;
    int m = (l + r) >> 1;
    build(p<<1, l, m), build(p<<1|1, m+1, r);
    t[p] = t[p<<1] + t[p<<1|1];
}

void apply(int p, int l, int r) {
    if(lz[p] != iden) {
        t[p] = lz[p] * t[p];
        if(l != r) {
            lz[p<<1] = lz[p<<1] * lz[p];
            lz[p<<1|1] = lz[p<<1|1] * lz[p];
        }
        lz[p] = iden;
    }
}

template<typename T>
void travel(int x, int y, const T &f, int p = 1, int l = 1, int r = n) {
    apply(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) return f(p, l, r);
    int m = (l + r) >> 1;
    travel(x, y, f, p<<1, l, m), travel(x, y, f, p<<1|1, m+1, r);
    t[p] = t[p<<1] + t[p<<1|1];
}

int main() {
    iden.m[0][1] = iden.m[1][0] = 0, iden.m[1][1] = 1;
    zero.m[0][0] = zero.m[0][1] = zero.m[1][0] = zero.m[1][1] = 0;
    fill_n(lz, N<<1, iden);
    for(int i = 2; i < 70; i++) pre[i] = pre[i-1] * base;

    scanf("%d %d", &n, &q);
    build(); 

    while(q--) {
        int T, a, b, c;
        scanf("%d %d %d", &T, &a, &b);
        if(T == 0) {
            scanf("%d", &c);
            travel(a, b, [&](int p, int l, int r) {
                lz[p] = lz[p] * pre[c];
                apply(p, l, r);
            });
        } else {
            Matrix ret = zero;
            travel(a, b, [&](int p, int l, int r) {
               ret = ret + t[p];
            });
            printf("%d\n", ret.m[0][0]);
        }
    }

    return 0;
}
