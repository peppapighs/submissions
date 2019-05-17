#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

int n, k, ans;
char s[N];

int main() {
    scanf("%d %s", &k, s+1);
    n = strlen(s+1);
    for(int len = 2; len <= n; len += 2) {
        int half = len >> 1, cnt = 0;
        for(int i = 1; i <= half; i++) if(s[i] != s[half + i]) ++cnt;
        if(cnt <= k) ++ans;
        for(int i = 2, j = len+1; j <= n; i++, j++) {
            if(s[i-1] != s[half+i-1]) --cnt;
            if(s[half+i-1] != s[j]) ++cnt;
            if(cnt <= k) ++ans;
        }
    }
    printf("%d\n", ans);

    return 0;
}