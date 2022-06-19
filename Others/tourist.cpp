#include <bits/stdc++.h>

using namespace std;

int t;

int main() {
    scanf("%d", &t);
    for (int q = 1; q <= t; q++) {
        long long n, k, v;
        map<string, int> rank;
        scanf("%lld%lld%lld", &n, &k, &v);
        vector<string> all;
        for (int i = 0; i < n; i++) {
            string str;
            cin >> str;
            all.emplace_back(str);
            rank[str] = i;
        }
        long long re = (k * (v - 1)) % n;
        vector<string> ans;
        for (int i = 0; i < k; i++)
            ans.emplace_back(all[(re + i) % n]);
        sort(ans.begin(), ans.end(), [&](const string &a, const string &b) {
            return rank[a] < rank[b];
        });
        printf("Case #%d: ", q);
        for (string tmp : ans)
            cout << tmp << " ";
        cout << endl;
    }

    return 0;
}