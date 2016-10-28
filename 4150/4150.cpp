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
const int N = 500100;
int p[N], u[N];
/*
	首先每个都构成了一个环
	我们每次修改了一个人的开枪时间的影响是什么？
	--->会导致下一个人死亡时间改变
	然后？会导致一连串的人死亡时间改变
	但是？后面一连串的状态改变和你具体把这个修改成了什么无关，而只和『下一个人』的能不能开枪状态有关。。

	我们需要维护什么？
	1.每个人死亡时间（从而知道能不能开枪）
	2.每个人如果改变状态的影响
		也就是我们改变了一个状态之后，对后面多久有影响？

	线段树上维护左端一个人能不能开枪对应的右边人能不能开枪、以及存活人数

	每次修改直接把环里最早开枪的人拎出来。。重算整个环的答案即可。。
*/
int n; 
int id[N], cir[N], L[N], R[N], cnt = 0, l = 0;

int ans = 0, cal[N];

typedef pair<int, int> node;
priority_queue<node> q[N];

struct state{
	bool a[2];
	int l[2];
};

state merge(state a, state b, int ua, int ub){
	state c;
	//cout <<a.l[0]<<' '<<a.l[1]<<' '<<b.l[0]<<' '<<b.l[1]<<endl;
	if (ua < ub){
		c.a[0] = b.a[!a.a[0]];
		c.l[0] = a.l[0] + b.l[!a.a[0]];

		c.a[1] = b.a[!a.a[1]];
		c.l[1] = a.l[1] + b.l[!a.a[1]];
	}else {
		c.a[0] = c.a[1] = b.a[1];
		c.l[0] = a.l[0] + b.l[1];
		c.l[1] = a.l[1] + b.l[1];
	}
	if (a.a[0]) c.l[0]--;
	if (a.a[1]) c.l[1]--;
	return c;
}

state s[N * 4], I;
void build(int x, int l, int r){
	if (l == r) s[x] = I; else {
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		build(lc, l, mid);
		build(rc, mid + 1, r);
		s[x] = merge(s[lc], s[rc], u[mid], u[mid + 1]);
	}
}

int get_min(int x){
	while (true){
		node t = q[x].top();
		if (t.first == -u[t.second]) return t.second;
		else q[x].pop();
	}
}

state qry(int x, int l, int r, int a, int b){
	if (a <= l && r <= b) return s[x];
	else {
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		if (a <= mid && b <= mid) return qry(lc, l, mid, a, b);
		else if (a > mid && b > mid) return qry(rc, mid + 1, r, a, b);
		else return merge(qry(lc, l, mid, a, b), qry(rc, mid + 1, r, a, b), u[mid], u[mid + 1]);
	}
}

int calc(int x){
	int t = get_min(x); //cout <<"min:"<<t<<endl;
	if (t == L[x]){
		state S = qry(1, 1, n, t, R[x]);
		if (S.a[1]) S.l[1]--;
		return S.l[1];
	}else {
		state S = merge(qry(1, 1, n, t, R[x]), qry(1, 1, n, L[x], t - 1), u[R[x]], u[L[x]]);
		if (S.a[1]) S.l[1]--;
		return S.l[1];
	}
}

bool vis[N];
int tmp[N];
void init(){
	memset(vis, false, sizeof(vis));
	rep(i,1,n) if (!vis[i]){
		cnt++;
		L[cnt] = l + 1;
		for(int j = i; !vis[j]; j = p[j]){
			vis[j] = true, cir[j] = cnt;
			id[j] = ++l;
		}
		R[cnt] = l;
	}

	rep(i,1,n) tmp[id[i]] = u[i];
	rep(i,1,n) u[i] = tmp[i];

	rep(i,1,n) q[cir[i]].push(mp(-u[id[i]], id[i]));
	I.a[0] = 0, I.a[1] = 1;
	I.l[0] = I.l[1] = 1;
	build(1, 1, n);
	rep(i,1,cnt) ans += (cal[i] = calc(i));
	printf("%d\n",ans);
}

void modify(int x, int l, int r, int a){
	if (l < r){
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		if (a <= mid) modify(lc, l, mid, a);
		else modify(rc, mid + 1, r, a);
		s[x] = merge(s[lc], s[rc], u[mid], u[mid + 1]);
	}
}

void modi(int x, int d){
	u[id[x]] = d;
	modify(1, 1, n, id[x]);
	q[cir[x]].push(mp(-d, id[x]));
}

void work(){
	int Q; scanf("%d",&Q);
	rep(i,1,Q){
		int x, d; scanf("%d%d",&x,&d);
		modi(x, d);
		ans -= cal[cir[x]], ans += (cal[cir[x]] = calc(cir[x]));
		printf("%d\n",ans);
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&p[i]);
	rep(i,1,n) scanf("%d",&u[i]);
	init();
	work();
	return 0;
}