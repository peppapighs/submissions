#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;
const int M = 1e6 + 7;

string a, b;
int res;
long long hsh[26];

int main() {
    cin >> a >> b;
    hsh[0] = 69LL;
    for (int i = 1; i < 26; i++)
        hsh[i] = (hsh[i - 1] * 69LL);
    for (int ans = 1; ans <= min(a.length(), b.length()); ans++) {
        set<long long> lib;
        long long win = 0;
        for (int i = 0; i < ans; i++) {
            win = (win + hsh[a[i] - 'A']);
        }
        lib.insert(win);
        for (int i = ans; i < a.length(); i++) {
            win -= hsh[a[i - ans] - 'A'];
            win += hsh[a[i] - 'A'];
            lib.insert(win);
        }
        win = 0;
        for (int i = 0; i < ans; i++) {
            win = (win + hsh[b[i] - 'A']);
        }
        if (lib.find(win) != lib.end()) {
            res = max(res, ans);
            continue;
        }
        for (int i = ans; i < b.length(); i++) {
            win -= hsh[b[i - ans] - 'A'];
            win += hsh[b[i] - 'A'];
            if (lib.find(win) != lib.end()) {
                res = max(res, ans);
                break;
            }
        }
    }

    printf("%d", res);

    return 0;
}