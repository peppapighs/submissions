#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e5 + 5;

int n;
int d1[N], d2[N], chk[N];
vector<iii> E;
map<int, int> mp;

int main() {
    scanf("%d", &n);
    for(int i = 2; i < n; i++) scanf("%d", d1 + i);
    for(int i = 2; i < n; i++) scanf("%d", d2 + i);

    int len = 1e9, dif = -1;
    bool valid = true;
    vector<pii> path;
    for(int i = 2; i < n; i++) {
        len = min(len, d1[i] + d2[i]);
        if(dif == -1) dif = abs(d1[i] - d2[i]);
        else if(dif != abs(d1[i] - d2[i])) 
            valid = false;
    }

    if(valid && dif > 0) {
        E.emplace_back(1, n, dif);
        for(int i = 2; i < n; i++) {
            if(min(d1[i], d2[i]) == 0) return !printf("NIE\n");
            if(d1[i] > d2[i]) E.emplace_back(i, n, d2[i]);
            else E.emplace_back(i, 1, d1[i]);
        }
    } else {
        for(int i = 2; i < n; i++) if(d1[i] + d2[i] == len)
            path.emplace_back(d1[i], i), chk[i] = true;
        sort(path.begin(), path.end());

        path.insert(path.begin(), pii(0, 1)), path.emplace_back(len, n);
        for(int i = 0; i < path.size(); i++) {
            if(i < path.size() - 1) {
                if(path[i].x == path[i + 1].x) return !printf("NIE\n");
                E.emplace_back(path[i].y, path[i + 1].y, path[i + 1].x - path[i].x);
            }
            if(mp.count(path[i].x)) return !printf("NIE\n");
            mp[path[i].x] = path[i].y;
        }

        for(int i = 2; i < n; i++) if(!chk[i]) {
            int d = (d1[i] + d2[i] - len) / 2;
            if(!mp.count(d1[i] - d) || d == 0 || d1[i] + d2[i] - 2 * d != len)
                return !printf("NIE\n");
            E.emplace_back(mp[d1[i] - d], i, d);
        }
    }

    printf("TAK\n");
    for(iii e : E) {
        int a, b, c; tie(a, b, c) = e;
        printf("%d %d %d\n", a, b, c);
    }

    return 0;
}