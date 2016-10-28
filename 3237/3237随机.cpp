#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <bitset>
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N = 200010;
int M = 960;
using namespace std;
struct egde{int u, v, num;}e[N];
bitset<961> a[N], w, t;
int f[N];
inline int find(int x){
	return f[x] == x ? x : f[x] = find(f[x]);
}
int main(){
	srand(9167);
	int n,m; scanf("%d%d",&n,&m);
	if (M > n) M = n;
	rep(i,1,m) scanf("%d %d",&e[i].u, &e[i].v), e[i].num = i, a[i] = 0;
	rep(j,1,M){
		rep(i,1,n) f[i] = i;
		rep(i,1,m) {
			int fa = find(e[i].u), fb = find(e[i].v);
			if (fa != fb){
				a[e[i].num][j] = 1;
				f[fa] = fb;
			}
		}
		rep(i,1,m) swap(e[i], e[rand() % i + 1]);
		t[j] = 1;
	}
	int k; scanf("%d",&k);
	rep(i,1,k){
		int c;scanf("%d",&c);
		w = 0;
		rep(j,1,c){
			int t;
			scanf("%d",&t);
			w = w | a[t];
		}
		if (w != t) printf("Connected\n"); else printf("Disconnected\n");
	}
	return 0;
}