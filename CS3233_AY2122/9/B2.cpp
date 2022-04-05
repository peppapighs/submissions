#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int P = 98765431;

long pw[N];
long hsh[N];

void solve() {
    string s;
    cin >> s;
    for(int i = 1; i <= s.size(); i++) {
        hsh[i] = hsh[i - 1] * P + s[i - 1]; 
    }

    int l = 0, r = s.size();
    int ans = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;

        map<long, pii> cnt;
        for(int i = 1; i <= s.size() - mid + 1; i++) {
            long h = hsh[i + mid - 1] - hsh[i - 1] * pw[mid];
            if(!cnt.count(h)) cnt[h] = pii(i, i);
            else cnt[h] = pii(min(cnt[h].x, i), max(cnt[h].y, i));
        }

        bool valid = false;
        for(auto &p : cnt) {
            if(p.y.y - p.y.x >= mid) {
                valid = true;
                break;
            }
        }

        if(valid) {
            l = mid + 1;
            ans = mid;
        } else r = mid - 1;
    }

    cout << ans << "\n";
}

int T;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    
    pw[0] = 1;
    for(int i = 1; i < N; i++) pw[i] = pw[i - 1] * P;
    
    cin >> T;
    while(T--) solve();

    return 0;
}