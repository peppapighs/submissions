#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

long long r[N], perf;

int n;
int seq[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vector<char> t;
        for (int j = 0; j < s.length(); j++) {
            if (t.empty()) {
                t.push_back(s[j]);
            } else {
                if (s[j] == ')' && t.back() == '(') {
                    t.pop_back();
                } else {
                    t.push_back(s[j]);
                }
            }
        }
        int lt = 0, rt = 0;
        for (char c : t) {
            if (c == '(') {
                lt++;
            } else {
                rt++;
            }
        }
        if (lt && rt) {
            continue;
        } else if (!lt && !rt) {
            perf++;
        } else {
            seq[i] = lt;
            r[rt]++;
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (seq[i]) {
            ans += r[seq[i]];
        }
    }
    printf("%lld", ans + (perf * perf));

    return 0;
}