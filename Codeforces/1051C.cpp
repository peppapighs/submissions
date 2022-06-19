#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int n;
int n1, nn;
int A[105];
map<int, int> mp;
char s[105];

int main() {
    fill(begin(s), end(s), 'A');
    scanf("%d", &n);
    for (int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        A[i] = a;
        mp[a]++;
    }
    s[n + 1] = 0;
    for (pii p : mp) {
        if (p.y == 1)
            n1++;
        if (p.y > 2)
            nn++;
    }
    if (n1 % 2 == 0) {
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (cnt == n1 / 2)
                break;
            if (mp[A[i]] == 1)
                s[i] = 'B', cnt++;
        }
        printf("YES\n%s\n", s + 1);
    } else if (nn) {
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (cnt == n1 / 2)
                break;
            if (mp[A[i]] == 1)
                s[i] = 'B', cnt++;
        }
        for (int i = 1; i <= n; i++) {
            if (mp[A[i]] > 2) {
                s[i] = 'B';
                break;
            }
        }
        printf("YES\n%s\n", s + 1);
    } else {
        printf("NO\n");
    }

    return 0;
}