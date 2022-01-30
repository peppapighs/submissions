#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 18;

vector<string> sub = {"a", "b", "c", "ab", "bc"};
int merged[1 << 5][1 << 5];

vector<string> from_mask(int mask) {
    vector<string> ret;
    for(int i = 0; i < 5; i++) if(mask >> i & 1)
        ret.emplace_back(sub[i]);
    return ret;
}

bool contains(string str, string pat) {
    int pos = 0;
    for(int i = 0; i < str.size(); i++)
        if(pos < pat.size() && str[i] == pat[pos])
            ++pos;
    return pos >= pat.size();
}

void find_merged() {
    for(int l = 0; l < 1 << 5; l++) for(int r = 0; r < 1 << 5; r++) {
        vector<string> vec_l = from_mask(l), vec_r = from_mask(r);
        for(string &s_l : vec_l) for(string &s_r : vec_r) {
            string now = s_l + s_r;
            if(contains(now, "abc")) merged[l][r] = -1;
            else for(int i = 0; i < 5; i++) if(contains(now, sub[i]))
                merged[l][r] |= (1 << i);
        }
    }
}

struct item {
    int dp[1 << 5];

    item() {}

    friend item operator+(const item &lhs, const item &rhs) {
        item ret;
        memset(ret.dp, -1, sizeof ret.dp);
        for(int i = 0; i < 1 << 5; i++) for(int j = 0; j < 1 << 5; j++) {
            int now = merged[i][j];
            if(now == -1 || lhs.dp[i] == -1 || rhs.dp[j] == -1) continue;
            if(ret.dp[now] == -1) ret.dp[now] = lhs.dp[i] + rhs.dp[j];
            else ret.dp[now] = min(ret.dp[now], lhs.dp[i] + rhs.dp[j]);
        }
        return ret;
    }
};

int n, q;
string S;
item t[N << 1];

void build(int p = 1, int l = 0, int r = n - 1) {
    if(l == r) {
        memset(t[p].dp, -1, sizeof t[p].dp);
        t[p].dp[1 << 0] = S[l] != 'a';
        t[p].dp[1 << 1] = S[l] != 'b';
        t[p].dp[1 << 2] = S[l] != 'c';
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build(p << 1 |  1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

void update(int x, int p = 1, int l = 0, int r = n - 1) {
    if(l == r) {
        memset(t[p].dp, -1, sizeof t[p].dp);
        t[p].dp[1 << 0] = S[l] != 'a';
        t[p].dp[1 << 1] = S[l] != 'b';
        t[p].dp[1 << 2] = S[l] != 'c';
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) update(x, p << 1, l, mid);
    else update(x, p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    find_merged();
    cin >> n >> q >> S;

    build();
    while(q--) {
        int pos;
        char c;
        cin >> pos >> c;
        S[pos - 1] = c;
        update(pos - 1);
        int ret = 1e9;
        for(int i = 0; i < 1 << 5; i++) if(t[1].dp[i] != -1)
            ret = min(ret, t[1].dp[i]);
        printf("%d\n", ret);
    }

    return 0;
}