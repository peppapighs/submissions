#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<18;

#define var int p = 1, int l = 1, int r = n
#define mid (l + r >> 1)
#define lb p<<1, l, mid
#define rb p<<1|1, mid+1, r

int n;
long ans;
pii t[N<<1];

void update(int x, int y, int k, var) {
    if(x > r || l > y) return;
    if(x <= l && r <= y) {
        t[p].y += k;
        if(t[p].y) t[p].x = r - l + 1;
        else t[p].x = t[p<<1].x + t[p<<1|1].x;
        return;
    }
    update(x, y, k, lb), update(x, y, k, rb);
    if(t[p].y) t[p].x = r - l + 1;
    else t[p].x = t[p<<1].x + t[p<<1|1].x;
}

int main() {
    scanf("%d", &n);
    vector<deque<int> > pos(n);
    for(int i = 0; i < n; i++) pos[i].emplace_back(0);
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        if(pos[a].size() == 6) {
            update(pos[a][0] + 1, pos[a][1], -1);
            pos[a].pop_front();
        }
        pos[a].emplace_back(i);
        if(pos[a].size() == 6) update(pos[a][0] + 1, pos[a][1], 1);
        ans += t[1].x;
    }
    printf("%lld\n", ans);

    return 0;
}
