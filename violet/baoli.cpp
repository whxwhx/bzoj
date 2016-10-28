#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a; i<=b; i++)
using namespace std;
int main(){
	int a, b; scanf("%d%d",&a,&b);
	int ans = 0;
	rep(i,a,b){
		for(int j = 1; j * j <= i; j++)if (i % j == 0){
			int k = j, t = 1, tmp = k;
			while (tmp) t *= tmp % 10, tmp /= 10;
			if (k * t == i) ans++;
			if (j * j < i) {
				int k = i / j, t = 1, tmp = k;
				while (tmp) t *= tmp % 10, tmp /= 10;
				if (k * t == i) ans++;
				if (j == 14) cout <<i<<' '<<j<<' '<<k<<' '<<t<<endl;
			}
		}
	}
	printf("%d\n",ans);
}