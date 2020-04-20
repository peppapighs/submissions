#include <bits/stdc++.h>

#define long long long

using namespace std;

int x, y;
vector<char> ans;

void solve(int idx) {
    ans.clear();

    scanf("%d %d", &x, &y);
    printf("Case #%d: ", idx);

    long sum = abs(x) + abs(y);
    if(sum % 2 == 0) {
        printf("IMPOSSIBLE\n");
        return;
    }

    bool valid = false;
    long all = (1ll << 31) - 1, a = 0, b = 0;

    for(int i = 30; ~i; i--) {
        int now = 1 << i;
        all -= now;
        if(all < sum) {
            long na = a + now, nb = b;
            if(abs(a + now - x) + abs(b - y) <= all) {
                a += now;
                ans.emplace_back('E');
            } else if(abs(a - now - x) + abs(b - y) <= all) {
                a -= now;
                ans.emplace_back('W');
            } else if(abs(a - x) + abs(b + now - y) <= all) {
                b += now;
                ans.emplace_back('N');
            } else {
                b -= now;
                ans.emplace_back('S');
            }
        }
    }
    reverse(ans.begin(), ans.end());
    for(int c : ans) printf("%c", c);
    printf("\n");
}

int T;

int main() {
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve(i);

    return 0;
}