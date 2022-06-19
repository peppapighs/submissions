#include "dna.h"
#include <bits/stdc++.h>

using namespace std;

string analyse(int n, int t) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (make_test(string(m, '0')))
            l = m;
        else
            r = m - 1;
    }

    string ret(l, '0');
    auto zero = [&](string a) {
        int ret = 0;
        while (a.back() == '0')
            ++ret, a.pop_back();
        return ret;
    };
    while (zero(ret) <= l) {
        if (make_test(ret + '1'))
            ret += '1';
        else
            ret += '0';
    }

    l = 0, r = n;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (make_test(ret.substr(0, m)))
            l = m;
        else
            r = m - 1;
    }
    ret = ret.substr(0, l);
    while (ret.length() != n) {
        if (make_test('1' + ret))
            ret = '1' + ret;
        else
            ret = '0' + ret;
    }
    return ret;
}