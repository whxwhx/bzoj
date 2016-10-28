#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n, m;
const int N = 200000 + 10;

int c[N], q[N][6], cnt = 0;
bool vis[N];

struct edge{int a, b;}e[N];
int f[N], h[N];
int tl = 0;
int find(int x){return f[x] == x ? x : find(f[x]);}
struct node{
	int fa, fb, ha;
}st[20 * N];
void ins(int a, int b){
	int fa = find(a), fb = find(b);
	if (fa != fb){
		if (h[fa] < h[fb]) swap(fa, fb);
		st[++tl] = (node){fa, fb, h[fa]};
		f[fb] = fa; if (h[fa] == h[fb]) h[fa] = h[fb] + 1;
		cnt--;
	}
}
void resume(){
	node x = st[tl--];
	f[x.fb] = x.fb;
	h[x.fa] = x.ha;
	cnt++;
}
void cdq(int l, int r){
	if (!cnt){
		rep(i,l,r) printf("Connected\n");
		return;
	}
	if (l == r) {if (!cnt) printf("Connected\n"); else printf("Disconnected\n");return;}
	
	int mid = (l + r) >> 1;

	int cur = tl + 1;
	rep(i,l,r) rep(j,1,c[i]) vis[q[i][j]] = 0;
	rep(i,l,mid) rep(j,1,c[i]) vis[q[i][j]] = 1;
	rep(i,mid + 1, r) rep(j,1,c[i]) if (!vis[q[i][j]]) ins(e[q[i][j]].a, e[q[i][j]].b), vis[q[i][j]] = 1;
	
	cdq(l, mid);
	int tmp = tl;//resume will modify tl!
	rep(i,cur,tmp) resume();


	cur = tl + 1; 
	rep(i,l,r) rep(j,1,c[i]) vis[q[i][j]] = 0;
	rep(i,mid + 1, r) rep(j,1,c[i]) vis[q[i][j]] = 1;
	rep(i,l,mid) rep(j,1,c[i]) if (!vis[q[i][j]]) ins(e[q[i][j]].a, e[q[i][j]].b), vis[q[i][j]] = 1;
	
	cdq(mid + 1, r);
	tmp = tl;//resume will modify tl!
	rep(i,cur,tmp) resume();
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d", &e[i].a, &e[i].b);
	int Q; scanf("%d",&Q);
	rep(i,1,Q) {
		scanf("%d", &c[i]);
		rep(j,1,c[i]) scanf("%d",&q[i][j]), vis[q[i][j]] = 1;
	}
	rep(i,1,n) f[i] = i, h[i] = 1;
	cnt = n - 1;
	rep(i,1,m) if (!vis[i]) ins(e[i].a, e[i].b); else vis[i] = 0;
	cdq(1,Q);
	return 0;
}

//教训：小心for循环rep(I,A,B)的时候 循环内的语句会不会更改a和b的值