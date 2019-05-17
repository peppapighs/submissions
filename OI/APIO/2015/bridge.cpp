#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

long suml, sumr;
priority_queue<long> L;
priority_queue<long, vector<long>, greater<long> > R;

void add(long x) {
    if(L.empty() || x <= L.top()) {
        L.emplace(x), suml += x;
        int now = L.size() + R.size();
        if(L.size() > (now + 1) / 2) {
            long t = L.top(); L.pop();
            suml -= t;
            R.emplace(t), sumr += t;
        } 
    } else {
        R.emplace(x), sumr += x;
        int now = L.size() + R.size();
        if(R.size() > (now + 1) / 2) {
            long t = R.top(); R.pop();
            sumr -= t;
            L.emplace(t), suml += t;
        } 
    }
}

int k, n;
long ans, dpl[N], dpr[N];
vector<pii> v;

int main() {
    scanf("%d %d", &k, &n);
    for(int i = 1; i <= n; i++) {
        char a, c; int b, d;
        scanf(" %c %d %c %d", &a, &b, &c, &d);
        if(b > d)  swap(b, d);
        if(a == c) ans += d - b;
        else v.emplace_back(b, d);
    }
    n = v.size(), ans += n;
    if(!v.empty()) {
        sort(v.begin(), v.end(), [&](const pii &a, const pii &b) {
            return a.x + a.y < b.x + b.y;
        });
        for(int i = 1; i <= n; i++) {
            add(v[i-1].x), add(v[i-1].y);
            int now = L.size() + R.size();
            long b = L.size() == (now + 1) / 2 ? L.top() : R.top();
            dpl[i] = (b * L.size() - suml) + (sumr - b * R.size());
        }
        L = priority_queue<long>();
        R = priority_queue<long, vector<long>, greater<long> >();
        suml = sumr = 0;
        for(int i = n; i; i--) {
            add(v[i-1].x), add(v[i-1].y);
            int now = L.size() + R.size();
            long b = L.size() == (now + 1) / 2 ? L.top() : R.top();
            dpr[i] = (b * L.size() - suml) + (sumr - b * R.size());
        }
        if(k == 1) ans += dpl[n];
        else {
            long tmp = 2e18;
            for(int i = 0; i <= n; i++) tmp = min(tmp, dpl[i] + dpr[i+1]);
            ans += tmp;
        }
    }
    printf("%lld\n", ans);

    return 0;
}