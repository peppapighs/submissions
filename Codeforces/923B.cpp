#include <bits/stdc++.h>

using namespace std;

int n;

void update(long long *tree,int k,int index) {
    index++;
    while(index<=n) {
        tree[index]+=k;
        index += index & (-index);
    }
}

long long sum(long long *tree,int index) {
    index++;
    long long res = 0;
    while(index > 0) {
        res += tree[index];
        index -= index & (-index);
    }
    return res;
}

int main()
{
    scanf("%d",&n);
    long long vol[n];
    long long t[n];
    long long prefix[n];
    long long f[n+1] = {0};
    long long m[n] = {0};
    for(int i=0;i<n;i++) {
        scanf("%lld",&vol[i]);
    }
    for(int i=0;i<n;i++) {
        scanf("%lld",&t[i]);
        if(i==0) {
            prefix[0] = t[0];
        }else{
            prefix[i] = prefix[i-1] + t[i];
        }
    }

    for(int i=0;i<n;i++) {
        int low = i, high = n-1;
        long long prev = i>0?prefix[i-1]:0;
        int j = n;
        while(low<=high) {
            int mid = (low+high)/2;
            if(vol[i]<=prefix[mid]-prev) {
                high = mid-1;
                j = mid;
            } else {
                low = mid+1;
            }
        }

        update(f,1,i);
        update(f,-1,j);
        if(j>0) {
            m[j] += (vol[i] - prefix[j-1] + prev);
        } else {
            m[j] += (vol[i] + prev);
        }
    }
    for(int i=0;i<n;i++) {
        printf("%lld ",(sum(f,i)*t[i])+m[i]);
    }

    return 0;
}
