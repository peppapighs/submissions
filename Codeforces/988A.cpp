#include <bits/stdc++.h>

using namespace std;

int num[101];

int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	int cnt=0;
	for(int i=1;i<=n;i++) {
		int x;
		scanf("%d",&x);
		if(num[x]==0) {
			cnt++;
		}
		num[x]=i;
	}
	if(cnt<k) {
		printf("NO");
	} else {
		printf("YES\n");
		int c = 0;
		for(int i=1;i<=100;i++) {
			if(c==k) {
				break;
			} else {
				if(num[i]) {
					printf("%d ",num[i]);
					c++;
				}
			}
		}
	}

	return 0;
}