#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 100010;
const int M = 4000010;
struct edge{
	int to, pre;
}e[M];
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
int vis[N], nex[N], pre[N];
int t[N], t1[N];
void del(int x){
	nex[pre[x]] = nex[x];
	pre[nex[x]] = pre[x];
}
int n, m, tmp, Ans[N];
void print(int x){
	for(int i = nex[0]; i<=n; i=nex[i]) cout <<i<<' ';
	cout <<endl;
}
int q[N];
void bfs(int x){
	int l = 0, r = 1;q[l] = x;del(x);
	while (l < r){
		int x = q[l++]; 
		vis[x] = 1, tmp++;

		reg(i,x) t[v] = 1;
		int a = nex[0];
		while (a <= n){
			if (!t[a])
				del(a), q[r++] = a;
			a = nex[a];
		}
		reg(i,x) t[v] = 0;
	}
}
int a1[N];
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m) {
		int x, y; scanf("%d%d",&x,&y);
		ins(x, y),ins(y, x);
	}
	int ans = 0;
	rep(i,0,n) nex[i] = i + 1;
	rep(i,1,n) pre[i] = i - 1;
	rep(i,1,n) t[i] = 0;
	rep(i,1,n) if (!vis[i]) tmp = 0, ans++, bfs(i), Ans[i] = tmp;
	printf("%d\n",ans);
	int tl = 0;
	rep(i,1,n) if (Ans[i]) a1[++tl] = Ans[i];
	sort(a1 + 1, a1 + tl + 1);
	rep(i,1,tl) printf("%d ",a1[i]);
	printf("\n");
	return 0;
}