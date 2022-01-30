#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 5;

struct Fenwick {
    long t1[N], t2[N];

    void upd(long t[], int x, int k) {
        for(int i = x; i < N; i += i & -i)
            t[i] += k;
    }

    long que(long t[], int x, long ret = 0) {
        for(int i = x; i; i -= i & -i)
            ret += t[i];
        return ret;
    }

    void update(int x, int k) {
        upd(t1, x, k);
        upd(t2, x, 1ll * k * (x - 1));
    }

    long query(int x) {
        return que(t1, x) * x - que(t2, x);
    }
};

int main() {

    return 0;
}