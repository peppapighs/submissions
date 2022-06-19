#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e5 + 5;

int M;
int n, m;
int t[N + 1];
queue<int> mn[30];
char ls[N], pat[N];

void update(int x, int k) {
    for (int i = x; i < N; i += i & -i)
        t[i] += k;
}

int get(int x) {
    int ret = 0;
    for (int i = x; i; i -= i & -i)
        ret += t[i];
    return ret;
}

int main() {
    scanf("%d", &M);
    scanf(" %s", ls + 1);
    scanf(" %s", pat + 1);
    n = strlen(ls), m = strlen(pat);
    if (M == 0) {
        long ans = 0;
        for (int i = 1; ls[i]; i++)
            mn[ls[i] - 'a'].emplace(i);
        for (int i = 1; pat[i]; i++) {
            if (mn[pat[i] - 'a'].empty())
                return !printf("-1\n");
            ans += mn[pat[i] - 'a'].front();
            mn[pat[i] - 'a'].pop();
        }
        printf("%lld\n", ans);
    } else {
        long ans = 0;
        for (int i = 1; ls[i]; i++)
            update(i, 1);
        for (int i = 1; ls[i]; i++)
            mn[ls[i] - 'a'].emplace(i);
        for (int i = 1; pat[i]; i++) {
            if (mn[pat[i] - 'a'].empty())
                return !printf("-1\n");
            ans += get(mn[pat[i] - 'a'].front());
            update(mn[pat[i] - 'a'].front(), -1);
            mn[pat[i] - 'a'].pop();
        }
        printf("%lld\n", ans);
    }

    return 0;
}