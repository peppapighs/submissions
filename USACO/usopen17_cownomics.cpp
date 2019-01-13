#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 505;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

pii iden(69, 6969);

int n, k;
pii hpow[N];
vector<string> spt, pln;

bool f(int m) {
    set<pii> S;
    queue<pii> Q1, Q2;
    for(string &s : spt) {
        pii hsh(0, 0);
        for(int i = 0; i < m; i++) hsh = add(mul(hsh, iden), pii(s[i], s[i]));
        Q1.emplace(hsh);
    }
    for(string &s : pln) {
        pii hsh(0, 0);
        for(int i = 0; i < m; i++) hsh = add(mul(hsh, iden), pii(s[i], s[i]));
        Q2.emplace(hsh);
    }
    for(int i = m-1; i < k; i++) {
        bool invalid = false;
        S.clear();
        for(string &s : spt) {
            pii hsh = Q1.front(); Q1.pop();
            S.emplace(hsh);
            if(i == k-1) continue;
            hsh = add(mul(hsh, iden), pii(s[i+1], s[i+1]));
            hsh = sub(hsh, mul(pii(s[i-m+1], s[i-m+1]), hpow[m]));
            Q1.emplace(hsh);
        }
        for(string &s : pln) {
            pii hsh = Q2.front(); Q2.pop();
            if(S.find(hsh) != S.end()) invalid = true;
            if(i == k-1) continue;
            hsh = add(mul(hsh, iden), pii(s[i+1], s[i+1]));
            hsh = sub(hsh, mul(pii(s[i-m+1], s[i-m+1]), hpow[m]));
            Q2.emplace(hsh);
        }
        if(!invalid) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> k;
    hpow[0] = pii(1, 1);
    for(int i = 1; i < N; i++) hpow[i] = mul(hpow[i-1], iden);
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        spt.emplace_back(s);
    }
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        pln.emplace_back(s);
    }
    int l = 1, r = k;
    while(l < r) {
        int m = (l + r) >> 1;
        if(f(m)) r = m;
        else l = m+1;
    }
    cout << r << endl;

    return 0;
}
