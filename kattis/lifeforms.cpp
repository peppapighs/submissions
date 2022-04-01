#include <bits/stdc++.h>

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

vector<int> suffix_array(vector<int> &s, int first = 'a', int last = 'z') {
    vector<int> vec(s.size() + 1);
    copy(s.begin(), s.end(), vec.begin());
    for(int &x : vec) x -= first - 1;
    vec.back() = 0;
    auto ret = SA_IS(vec, last - first + 2);
    ret.erase(ret.begin());
    return ret;
}

vector<int> LCP(vector<int> &s, vector<int> &sa) {
    int n = (int)s.size(), k = 0;
    vector<int> lcp(n), rank(n);
    for(int i = 0; i < n; i++)
        rank[sa[i]] = i;
    for(int i = 0; i < n; i++, k ? k-- : 0) {
        if(rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while(i + k < n && j + k < n && s[i + k] == s[j + k])
            ++k;
        lcp[rank[i]] = k;
    }
    lcp[n - 1] = 0;
    return lcp;
}

template<typename T>
class SegmentTree {
private:
    int n;
    function<T(T, T)> f;
    vector<T> t;
public:
    SegmentTree(int _n, function<T(T, T)> _f) : n(_n), f(_f) {
        t.resize(n << 1);
    }

    void update(int x, T k) {
        for(t[x += n] = k; x != 1; x >>= 1)
            t[x >> 1] = f(t[x], t[x ^ 1]);
    }

    T query(int l, int r, T ret) {
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret = f(ret, t[l++]);
            if(r & 1) ret = f(ret, t[--r]);
        }
        return ret;
    }
};

int n;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    while(cin >> n, n != 0) {
        vector<int> idx;
        vector<int> str;
        int max_l = 0;

        for(int i = 1; i <= n; i++) {
            string s;
            cin >> s;
            for(int j = 0; j < (int)s.size(); j++) {
                idx.emplace_back(i);
                str.emplace_back((int)s[j]);
            }
            idx.emplace_back(0);
            str.emplace_back(127 + i);
            max_l = max(max_l, (int)s.size());
        }

        vector<int> sa = suffix_array(str, 0, 255);
        vector<int> lcp = LCP(str, sa);

        int s = str.size();
        int ans = 0;

        int l = 1, r = max_l;
        while(l <= r) {
            int mid = (l + r) / 2;

            int cnt = 1, book = 1;
            vector<int> sel(n + 1);
            sel[idx[sa[0]]] = book;
            for(int i = 1; i < s; i++) {
                if(lcp[i - 1] < mid) {
                    ++book;
                    cnt = 0;
                }
                if(sel[idx[sa[i]]] != book) {
                    sel[idx[sa[i]]] = book;
                    ++cnt;
                    if(cnt > n / 2) break;
                }
            }

            if(cnt > n / 2)
                ans = mid, l = mid + 1;
            else r = mid - 1; 
        }

        if(ans == 0) cout << "?\n";
        else {
            vector<string> vec;

            int cnt = 1, book = 1;
            vector<int> sel(n + 1);
            sel[idx[sa[0]]] = book;
            for(int i = 1; i < s; i++) {
                if(lcp[i - 1] < ans) {
                    if(cnt > n / 2) {
                        vec.emplace_back("");
                        for(int j = sa[i - 1]; j < sa[i - 1] + ans; j++)
                            vec.back() += (char)str[j];
                    }
                    ++book;
                    cnt = 0;
                }
                if(sel[idx[sa[i]]] != book) {
                    sel[idx[sa[i]]] = book;
                    ++cnt;
                }
            }
            if(cnt > n / 2) {
                vec.emplace_back("");
                for(int j = sa[s - 2]; j < sa[s - 2] + ans; j++)
                    vec.back() += (char)str[j];
            }
            vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
            for(string &x : vec) cout << x << "\n";
        }

        cout << "\n";
    }

    return 0;
}