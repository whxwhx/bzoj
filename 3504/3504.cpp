#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int inf = 1000000000, N = 52 * 52;
struct edge{
	int to, pre, w;
}e[N * 2];
int l = 1, u[N];//l=1!
void ins(int a, int b, int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
void insert(int a, int b, int c){
	ins(a, b, c), ins(b, a, 0);
}
#define reg(i,x) for(int i = u[x]; i; i = e[i].pre)
#define v e[i].to
#define ew e[i].w
#define min(a,b) ((a) < (b) ? (a) : (b))
int q[N], S, T, cur[N], h[N];
bool bfs(){
	rep(i,S,T) h[i] = -1;
	int l = 0, r = 1;
	q[h[S] = 0] = S;
	while (l < r){
		int x = q[l++];
		reg(i,x) if (ew && h[v] == -1)
			h[v] = h[x] + 1, q[r++] = v;
	}
	return h[T] != -1;
}
int dfs(int x, int f){
	if (x == T || f == 0) return f;
	int used = 0, w;
	for(int i = cur[x]; i; i = e[i].pre) if (h[v] == h[x] + 1 && ew){
		w = min(ew, f - used), w = dfs(v, w);
		ew -= w; if (ew) cur[x] = i;
		e[i ^ 1].w += w;
		used += w; if (used == f) break;
	}
	if (!used) h[x] = -1;
	return used;
}
int dinic(){
	int ans = 0;
	while (bfs()){
		rep(i,S,T) cur[i] = u[i];
		ans += dfs(S, inf);
	}
	return ans;
}
int main(){
	int n, a1, a2, an, b1, b2, bn; 
	while (scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn) == 7){
		a1++, a2++, b1++, b2++, an <<= 1, bn <<= 1;
		S = 0, T = n + 1;
		l = 1; rep(i,S,T) u[i] = 0;//l=1!
		rep(i,1,n) rep(j,1,n){
			char c = getchar();
			while (c != 'O' && c != 'N' && c != 'X') c = getchar();
			if (c == 'O'){
				if (i < j) ins(i,j,2), ins(j,i,2);
			}
			if (c == 'N'){
				if (i < j) ins(i,j,inf), ins(j,i,inf);
			}
		}
		insert(S, a1, an), insert(S, b1, bn), insert(a2, T, an), insert(b2, T, bn);
		int t1 = dinic();
		if (t1 < an + bn) {printf("No\n");continue;}
		l -= 8;
		rep(i,S,T) while (u[i] > l) u[i] = e[u[i]].pre;
		for(int i = 2; i < l; i += 2) ew = e[i ^ 1].w = (ew + e[i ^ 1].w) / 2;
		insert(S, a1, an), insert(b1, T, bn), insert(a2, T, an), insert(S, b2, bn);
		int t2 = dinic();
		if (t2 < an + bn) {printf("No\n");continue;}
		printf("Yes\n");
	}
	return 0;
}