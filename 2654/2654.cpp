#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a, _b = b; i <= _b; i++)
using namespace std;
int n, m, k;
const int N = 100100, inf = 110;
struct edge{ int a, b, c, d; }e[N];
inline bool operator < (const edge &a, const edge &b) { 
	return a.d < b.d || (a.d == b.d && a.c < b.c);
}
int f[N], ans, L = 1;
inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
bool merge(int a, int b){
	int fa = find(a), fb = find(b); return fa == fb ? false : (f[fa] = fb, true);
}
bool check(int K){
	int cnt = 0;
	rep(i,1,n) f[i] = i; int t1 = 1, t2 = L; ans = 0;
	while (t1 <= L - 1 || t2 <= m){
		if (t1 > L - 1)  
			(ans += merge(e[t2].a, e[t2].b) ? e[t2].c : 0) , t2++;
		else if (t2 > m) 
			(ans += merge(e[t1].a, e[t1].b) ? (cnt++, e[t1].c + K) : 0), t1++;
		else if (e[t1].c + K < e[t2].c) 
			(ans += merge(e[t1].a, e[t1].b) ? (cnt++, e[t1].c + K) : 0), t1++;
		else 
			(ans += merge(e[t2].a, e[t2].b) ? e[t2].c : 0), t2++;
	}
	return cnt <= k;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,m) { scanf("%d%d%d%d",&e[i].a,&e[i].b,&e[i].c,&e[i].d), e[i].a++, e[i].b++; }
	sort(e + 1, e + m + 1); while (L <= m && e[L].d == 0) L++;
	int l = -inf, r = inf; 
	while (l + 1 < r){ int mid = (l + r) >> 1; if (check(mid)) r = mid; else l = mid; }
	check(r); printf("%d\n",ans - r * k);//因为不是恰好k个，所以必须在最后再减去
	return 0;
}