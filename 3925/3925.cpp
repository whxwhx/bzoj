#include <iostream>
#include <cstdio>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
//typedef __float128 db;
typedef double db;
struct ply{
	int l;
	db a[61];
}f[1024], c, ans, I, g;
#define a(i) (i > a.l ? 0 : a.a[i])
#define b(i) (i > b.l ? 0 : b.a[i])
ply operator + (const ply &a, const ply &b){
	c.l = max(a.l, b.l);
	rep(i,0,c.l) c.a[i] = a(i) + b(i);
	return c;
}
ply operator - (const ply &a, const ply &b){
	c.l = max(a.l, b.l);
	rep(i,0,c.l) c.a[i] = a(i) - b(i);
	return c;
}
int d[1024], cnt[1024], e[1024], pre[1024];
//void print(ply a){
//	rep(i,0,a.l) cout <<a.a[i]<<' ';
//	cout <<endl;
//}
int main(){
	int n, m; scanf("%d%d",&n,&m);
	int U = (1 << n) - 1;
	cnt[0] = 0;
	rep(i,1,U) cnt[i] = cnt[i ^ ((-i) & i)] + 1;
	rep(i,1,m){
		int a, b; scanf("%d%d",&a,&b);
		d[1 << (a - 1)] |= 1 << (b - 1), d[1 << (b - 1)] |= 1 << (a - 1);
	}

	f[0].a[0] = 1;
	I.l = 0, I.a[0] = 1;
	rep(i,1,U){
		f[i] = I;
		int t = i & (-i);
		
		e[0] = 0;
		for(int j = (i - 1) & i; j; j = (j - 1) & i) e[j] = 0, pre[(j - 1) & i] = j;
		for(int j = pre[0]; j; j = pre[j]){
			int t = j & (-j);
			e[j] = e[j ^ t] - cnt[j & d[t]] + cnt[d[t] & (i ^ j)];
		}
		
		for(int j = (i - 1) & i; j; j = (j - 1) & i) if (j & t){
			g = f[j];
			int cnt = e[j];
			dep(i,g.l,0) g.a[i + cnt] = g.a[i];
			rep(i,0,cnt - 1) g.a[i] = 0;
			g.l += cnt;
			f[i] = f[i] - g;
		}
		while (f[i].l && f[i].a[f[i].l] == 0) f[i].l--;
	}	
	ans = I - f[U];


	db Ans = 0;
	rep(i,0,ans.l) Ans += ans.a[i] / (i + 1);
	printf("%.6lf\n",(double)Ans);
}