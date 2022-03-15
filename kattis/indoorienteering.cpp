#include <bits/stdc++.h>

#define long long long

using namespace std;

int n;
long l, A[15][15];
unordered_set<long> st;

int main() {
    scanf("%d %lld", &n, &l);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
        scanf("%lld", A[i] + j);

    for(int mid = 0; mid < n - 1; mid++) for(int mask = 0; mask < 1 << (n - 1); mask++) {
        if((mask >> mid & 1) || __builtin_popcount(mask) != n / 2 - 1)
            continue;
        vector<int> L, R;
        for(int i = 0; i < n - 1; i++) if(i != mid) {
            if(mask >> i & 1) L.emplace_back(i);
            else R.emplace_back(i);
        }
        st.clear();
        if(!R.empty()) {
            do {
                long dist = A[n - 1][R[0]] + A[R.back()][mid];
                for(int i = 0; i < (int)R.size() - 1; i++)
                    dist += A[R[i]][R[i + 1]];
                st.emplace(dist);
            } while(next_permutation(R.begin(), R.end()));
        } else st.emplace(A[n - 1][mid]);
        if(!L.empty()) {
            do {
                long dist = A[n - 1][L[0]] + A[L.back()][mid];
                for(int i = 0; i < (int)L.size() - 1; i++)
                    dist += A[L[i]][L[i + 1]];
                if(st.count(l - dist))
                    return !printf("possible\n");
            } while(next_permutation(L.begin(), L.end()));
        } else if(st.count(l - A[n - 1][mid]))
            return !printf("possible\n");
    }
    
    printf("impossible\n");

    return 0;
}