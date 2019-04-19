#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int ask(int a, int b, int c, int d) {
    printf("? %d %d %d %d\n", a, b, c, d);
    fflush(stdout);
    int ret;
    scanf("%d", &ret);
    return ret;
}

int n;
vector<int> R, C;
vector<pii> ans;

int main() {
    scanf("%d", &n);
    int s_row = 0, s_col = 0;
    for(int i = 1; i < n; i++) {
        int a = ask(i, 1, i, n);
        int b = ask(1, i, n, i);
        s_row += a, s_col += b;
        if(a & 1) R.emplace_back(i);
        if(b & 1) C.emplace_back(i);
    }
    if(s_row & 1) R.emplace_back(n);
    if(s_col & 1) C.emplace_back(n);
    if(!R.empty()) for(int i : R) {
        int l = 1, r = n;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(ask(i, 1, i, mid) & 1) r = mid;
            else l = mid + 1;
        }
        ans.emplace_back(i, r);
    } else for(int i : C) {
        int l = 1, r = n;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(ask(1, i, mid, i) & 1) r = mid;
            else l = mid + 1;
        }
        ans.emplace_back(r, i);
    } 
    printf("! ");
    for(pii p : ans) printf("%d %d ", p.x, p.y);
    printf("\n");
    fflush(stdout);

    return 0;
}