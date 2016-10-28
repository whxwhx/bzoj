#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N = 300000 + 10;
struct edge{
	int to, pre;
}e[N * 2];
#define reg(i,a) for(int i=u[a]; i; i = e[i].pre)
#define v e[i].to
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
int fa[N], s[N], son[N], dep[N];
void dfs(int x, int f){
	s[x] = 1, son[x] = 0;
	reg(i,x) if (v != f){
		dep[v] = dep[x] + 1;
		fa[v] = x;
		dfs(v, x);
		s[x] += s[v];
		if (s[v] > s[son[x]]) son[x] = v;
	}
}
int pre[N], dfs_clock = 0, top[N], ed[N];
void dfs1(int x, int f){
	pre[x] = ++dfs_clock;
	if (son[x]) top[son[x]] = top[x], dfs1(son[x], x);
	reg(i,x) if (v != f && v != son[x]) 
		top[v] = v, dfs1(v, x);
	ed[x] = dfs_clock;
}

int S[N * 4], tag[N * 4];
#define mid ((l + r) >> 1)
#define lc  (x << 1)
#define rc  (lc + 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
void push(int x, int l, int r){
	if (tag[x]){
		if (l < r) tag[lc] += tag[x], tag[rc] += tag[x];
		S[x] += (r - l + 1) * tag[x], tag[x] = 0;	
	}
}
void upd(int x){
	S[x] = S[lc] + S[rc];
}
void add(int x, int l, int r, int a, int b, int d){
	if (a <= l && r <= b) {tag[x] += d, push(x, l, r);return;}
	push(x, l, r);
	if (a <= mid) add(lcq, a, b, d); else push(lcq);
	if (b >  mid) add(rcq, a, b, d); else push(rcq);
	upd(x);
}
int qry(int x, int l, int r, int a, int b){
	push(x, l, r);
	if (a <= l && r <= b) return S[x];
	int ans = 0;
	if (a <= mid) ans += qry(lcq, a, b);
	if (b >  mid) ans += qry(rcq, a, b);
	return ans;
}
typedef pair<int, int> node;
node q[N];
#define mp(a,b) make_pair(a,b)
int ql, ans = 0;
void Qry(int a, int b){
	int ta = top[a], tb = top[b];
	while (ta != tb){
		if (dep[ta] < dep[tb]) swap(a,b), swap(ta, tb);
		q[++ql] = mp(pre[ta], pre[a]);
		a = fa[ta], ta = top[a];
	}
	if (dep[a] > dep[b]) swap(a, b);
	q[++ql] = mp(pre[a], pre[b]);
}
int n;
void calc(){
	ans = 0;
	sort(q + 1, q + ql + 1);
	int t = q[1].first, mx = q[1].second;
	rep(i,2,ql) if (q[i].first > mx + 1){
		ans += qry(1, 1, n, t, mx);
		t = q[i].first, mx = q[i].second;
	}else mx = max(q[i].second, mx);
	ans += qry(1, 1, n, t, mx);
	//cout <<ql<<endl;
	//rep(i,1,ql) cout <<q[i].first<<' '<<q[i].second<<endl;
	//cout <<endl;
}
int main(){
	scanf("%d",&n);
	rep(i,1,n - 1){
		int a, b; scanf("%d%d",&a,&b);
		ins(a, b), ins(b, a);
	}
	fa[1] = 0, dep[1] = 1, dfs(1, 0);
	top[1] = 1, dfs1(1, 0);
	int Q; scanf("%d",&Q);
	rep(i,1,Q){
		int op; scanf("%d",&op);
		if (op == 0){
			int u, d; scanf("%d%d",&u,&d);
			add(1, 1, n, pre[u], ed[u], d);
		}else{
			ql = 0;
			int k; scanf("%d",&k);
			rep(i,1,k){
				int a, b; scanf("%d%d",&a,&b);
				Qry(a, b);
			}
			calc();
			printf("%d\n",ans & 2147483647);
		}
	}
	return 0;
}