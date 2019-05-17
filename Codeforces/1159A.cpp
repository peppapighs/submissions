#include <bits/stdc++.h>

using namespace std;

int n;
char s[105];

int main() {
    scanf("%d %s", &n, s+1);
    int cnt = 0, mn = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '-') --cnt;
        else ++cnt;
        mn = min(mn, cnt);
    }
    printf("%d\n", -mn + cnt);

    return 0;
}