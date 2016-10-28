#include <iostream>
#include <cstdio>
#include <bitset>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 30005, M = 100010;

int d[N];
struct edge{ int to, pre; }e[M]; int u[N], l = 0;
void ins(int a, int b){ e[++l] = (edge){b, u[a]}, u[a] = l; d[b]++; }
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

int q[N], rk[N], n;
void DAGsort(){
	int l = 0, r = 0; rep(i,1,n) if (!d[i]) q[r++] = i;
	while (l < r){
		int x = q[l++];
		reg(i,x) { d[v]--; if (!d[v]) q[r++] = v;}
	}
	dep(i,n,1) q[i] = q[i - 1];
	rep(i,1,n) rk[q[i]] = i;
}

bitset<N> b[N];
int to[N], tl;

inline bool cmp(const int &a, const int &b){ return rk[a] < rk[b]; }

int main(){
	int m; scanf("%d%d",&n,&m);
	rep(i,1,m){ int a, b; scanf("%d%d",&a,&b); ins(a, b); }
	DAGsort();
	rep(i,1,n) b[i][i] = 1;
	int ans = 0;
	dep(j,n,1){
		int x = q[j]; b[x][x] = 1; 
		tl = 0; reg(i,x) to[++tl] = v; sort(to + 1, to + tl + 1, cmp);
		rep(i,1,tl){
			int v1 = to[i];
			if (!b[x][v1]){ ans++; b[x] |= b[v1]; }
		}
	}
	printf("%d\n",m - ans);
	return 0;
}