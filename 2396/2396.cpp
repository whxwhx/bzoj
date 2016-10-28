#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 1000;
int a[N][N], b[N][N], c[N][N], T[N], BT[N], ABT[N], CT[N];
int main(){
	int n;
	while (scanf("%d",&n) == 1){
		rep(i,1,n) rep(j,1,n) scanf("%d",&a[i][j]);
		rep(i,1,n) rep(j,1,n) scanf("%d",&b[i][j]);
		rep(i,1,n) rep(j,1,n) scanf("%d",&c[i][j]);
		bool flag;
		rep(t,1,10){
			rep(i,1,n) T[i] = rand();
			rep(i,1,n){
				BT[i] = 0;
				rep(j,1,n) BT[i] += b[i][j] * T[j];
			}
			rep(i,1,n){
				ABT[i] = 0;
				rep(j,1,n) ABT[i] += a[i][j] * BT[j];
			}
			rep(i,1,n){
				CT[i] = 0;
				rep(j,1,n) CT[i] += c[i][j] * T[j];
			}
			flag = true;
			rep(i,1,n) if (ABT[i] != CT[i]) {flag = false;break;}
			if (!flag) break;
		}
		if (!flag) printf("No\n"); else printf("Yes\n");
	}
	return 0;
}