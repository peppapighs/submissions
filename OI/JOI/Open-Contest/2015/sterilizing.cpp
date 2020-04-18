#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1 << 17;

int n, q, k;

struct node {
    vector<long> vec;
    node() {}
    node(int x) {
        if(k == 1) vec.emplace_back(x);
        else while(x) {
            vec.emplace_back(x);
            x /= k;
        }
    }
    friend node operator+(const node &a, const node &b) {
        node ret;
        ret.vec = a.vec;
        for(int i = 0; i < b.vec.size(); i++) {
            if(ret.vec.size() <= i) ret.vec.emplace_back(b.vec[i]);
            else ret.vec[i] += b.vec[i];
        }
        while(!ret.vec.empty() && !ret.vec.back()) 
            ret.vec.pop_back();
        return ret;
    }

    void shift(int x) {
        reverse(vec.begin(), vec.end());
        while(!vec.empty() && x--) 
            vec.pop_back();
        reverse(vec.begin(), vec.end());
    }

    long get() { return vec.empty() ? 0 : vec.front(); }
} t[N << 1];

int lz[N << 1], A[N];

void build(int p = 1, int l = 1, int r = n) {
    if(l == r) return void(t[p] = node(A[l]));
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

void push(int p, int l, int r) {
    if(lz[p]) {
        t[p].shift(lz[p]);
        if(l != r) {
            lz[p << 1] += lz[p];
            lz[p << 1 | 1] += lz[p];
        }
        lz[p] = 0;
    }
}

void update(int x, int _k, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if(x < l || r < x) return;
    if(l == r) return void(t[p] = node(_k));
    int mid = (l + r) >> 1;
    update(x, _k, p << 1, l, mid), update(x, _k, p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

void spray(int x, int y, int p = 1, int l = 1, int r = n) {
    if(k == 1) return;
    push(p, l, r);
    if(x > r || l > y) return;
    if(x <= l && r <= y) {
        ++lz[p], push(p, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    spray(x, y, p << 1, l, mid), spray(x, y, p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

long query(int x, int y, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if(x > r || l > y) return 0;
    if(x <= l && r <= y) return t[p].get();
    int mid = (l + r) >> 1;
    return query(x, y, p << 1, l, mid) + query(x, y, p << 1 | 1, mid + 1, r);
}

int main() {
    scanf("%d %d %d", &n, &q, &k);
    for(int i = 1; i <= n; i++) scanf("%d", A + i);

    build();
    for(int i = 1, T, a, b; i <= q; i++) {
        scanf("%d %d %d", &T, &a, &b);
        if(T == 1) update(a, b);
        else if(T == 2) spray(a, b);
        else printf("%lld\n", query(a, b));
    }

    return 0;
}