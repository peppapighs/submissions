#include <bits/stdc++.h>

#define long long long

using namespace std;

void induced_sort(vector<int> &vec, int range, vector<int> &SA, vector<bool> &sl, vector<int> &lms_idx) {
    vector<int> l(range, 0), r(range, 0);
    for(int &c : vec) {
        if(c + 1 < range)
            ++l[c + 1];
        ++r[c];
    }
    partial_sum(l.begin(), l.end(), l.begin());
    partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for(int i = (int)lms_idx.size() - 1; ~i; i--)
        SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for(int &i : SA) if(i >= 1 && sl[i - 1])
        SA[l[vec[i - 1]]++] = i - 1;
    fill(r.begin(), r.end(), 0);
    for(int &c : vec) ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for(int k = (int)SA.size() - 1, i = SA[k]; k >= 1; k--, i = SA[k])
        if(i >= 1 && !sl[i - 1])
            SA[--r[vec[i - 1]]] = i - 1;
}

vector<int> SA_IS(vector<int> &vec, int range) {
    int n = (int)vec.size();
    vector<int> SA(n), lms_idx;
    vector<bool> sl(n);
    sl[n - 1] = 0;
    for(int i = n - 2; ~i; i--) {
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if(sl[i] && !sl[i + 1])
            lms_idx.emplace_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end());
    induced_sort(vec, range, SA, sl, lms_idx);
    vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for(int i = 0, k = 0; i < n; i++)
        if(!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1])
            new_lms_idx[k++] = SA[i];
    int cur = 0;
    SA[n - 1] = cur;
    for(int k = 1; k < (int)new_lms_idx.size(); k++) {
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if(vec[i] != vec[j]) {
            SA[j] = ++cur;
            continue;
        }
        bool flag = 0;
        for(int a = i + 1, b = j + 1; ; a++, b++) {
            if(vec[a] != vec[b]) {
                flag = 1;
                break;
            }
            if((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
                flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
                break;
            }
        }
        SA[j] = (flag ? ++cur : cur);
    }
    for(int i = 0; i < (int)lms_idx.size(); i++)
        lms_vec[i] = SA[lms_idx[i]];
    if(cur + 1 < (int)lms_idx.size()) {
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        for(int i = 0; i < (int)lms_idx.size(); i++)
            new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
    induced_sort(vec, range, SA, sl, new_lms_idx);
    return SA;
}

vector<int> suffix_array(string &s, int first = 'a', int last = 'z') {
    vector<int> vec(s.size() + 1);
    copy(s.begin(), s.end(), vec.begin());
    for(int &x : vec) x -= first - 1;
    vec.back() = 0;
    auto ret = SA_IS(vec, last - first + 2);
    ret.erase(ret.begin());
    return ret;
}

vector<int> LCP(string &s, vector<int> &sa) {
    int n = s.size();
    vector<int> lcp(n), rank(n);
    for(int i = 0; i < n; i++)
        rank[sa[i]] = i;
    for(int i = 0, k = 0; i < n; i++) if(rank[i] != n - 1) {
        for(int j = sa[rank[i] + 1]; s[i + k] == s[j + k]; k++);
        lcp[rank[i]] = k;
        if(k) --k;
    }
    return lcp;
}

const int N = 1e5 + 5;
const int M = 998244353;

int n;
int cnt[30][N];
long dp[N], sum[30];
string S;

void solve() {
    cin >> S;

    n = S.size();
    {
        vector<int> sa = suffix_array(S);
        vector<int> lcp = LCP(S, sa);

        for(int i = n - 1; ~i; i--) for(int j = 'a'; j <= 'z'; j++) {
            cnt[j - 'a'][i] = (S[i] == j);
            if(i != n - 1) cnt[j - 'a'][i] += cnt[j - 'a'][i + 1];
        }

        long ans = 0;
        for(int i = 0; i < n; i++) {
            int l = i == 0 ? 1 : max(1, lcp[i - 1]);
            if(sa[i] + l < n) ans = (ans + cnt[S[sa[i]] - 'a'][sa[i] + l]) % M;
        }
        cout << ans << " ";
    }
    {
        long ans = 0;
        for(int c = 'a'; c <= 'z'; c++) {
            memset(dp, 0, sizeof dp);
            memset(sum, 0, sizeof sum);

            long total = 0, ret = 0, flag = 0;
            for(int i = 0; i < n; i++) {
                dp[i] = (total - sum[S[i] - 'a'] + M) % M;
                if(S[i] == c) {
                    dp[i] = (dp[i] + 1) % M;
                    ret = (ret + dp[i]) % M;
                    flag = 1;
                }

                sum[S[i] - 'a'] = (sum[S[i] - 'a'] + dp[i]) % M;
                total = (total + dp[i]) % M;
            }
            ans = (ans + ret - flag + M) % M;
        }

        cout << ans << "\n";
    }
}

int T;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> T;
    while(T--) solve();

    return 0;
}