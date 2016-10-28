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
const int N = 600010;
typedef long long LL;
typedef unsigned long long uLL;
int n, m, tp;
struct op{
	int a, b, l, r;
};
struct oper{
	int a, b;
};
oper operator +(const oper &a, const oper &b){
	return (oper){1LL * a.a * b.a % m, (1LL * a.b * b.a % m + b.b) % m};
}

vector<oper> s[N * 4];
vector<int> sl[N * 4];

#define mid ((l + r) >> 1)
#define lc (x << 1)
#define rc (lc + 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
void upd(int x){
	int l1 = sl[lc].size(), l2 = sl[rc].size();
	oper t[3] = {(oper){0,0}, s[lc][0], s[rc][0]};
	int t1 = 0, t2 = 0;
	while (t1 < l1 || t2 < l2){
		if (t1 == l1) {
			sl[x].pb(sl[rc][t2]);
			t[2] = s[rc][t2];
			s[x].pb(t[1] + t[2]);
			t2++;
		}else if (t2 == l2){
			sl[x].pb(sl[lc][t1]);
			t[1] = s[lc][t1];
			s[x].pb(t[1] + t[2]);
			t1++;
		}else {
			if (sl[lc][t1] < sl[rc][t2]){
				sl[x].pb(sl[lc][t1]);
				t[1] = s[lc][t1];
				s[x].pb(t[1] + t[2]);
				t1++;
			}else if (sl[lc][t1] == sl[rc][t2]){
				sl[x].pb(sl[lc][t1]);
				t[1] = s[lc][t1], t[2] = s[rc][t2];
				s[x].pb(t[1] + t[2]);
				t1++; t2++;
			}else{
				sl[x].pb(sl[rc][t2]);
				t[2] = s[rc][t2];
				s[x].pb(t[1] + t[2]);
				t2++;
			}
		}
	}
}

void add(int x, int l, int r, int a, op d){
	if (l == r){
		if (d.l > 1) sl[x].pb(1), s[x].pb(((oper){1, 0}));
		sl[x].pb(d.l), s[x].pb(((oper){d.a, d.b}));
		if (d.r < n) sl[x].pb(d.r + 1), s[x].pb(((oper){1, 0}));
	}else {
		if (a <= mid) add(lcq, a, d); else add(rcq, a, d);
		if (a == r) upd(x);
	}
}

int find(int x, int pos){
	int l = 0, r = sl[x].size();
	while (l + 1 < r)
		if (sl[x][mid] <= pos) l = mid; else r = mid;
	return l;
}

oper qry(int x, int pos){
	int d = find(x, pos);
	return s[x][d];
}

oper qry(int x, int l, int r, int a, int b, int pos){
	if (a <= l && r <= b) return qry(x, pos);
	else {
		oper c = {1, 0};
		if (a <= mid) c = c + qry(lcq, a, b, pos);
		if (b >  mid) c = c + qry(rcq, a, b, pos);
		return c;
	}
}

int A[N];

inline int read(){
	int x = 0, f = 1;char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}

int main(){
	tp = read();
	n = read();
	m = read();
	rep(i,1,n) A[i] = read();
	int ans = 0, cnt = 0;
	int q; q = read();
	rep(i,1,q){
		int cmd; scanf("%d",&cmd);
		if (cmd == 1){
			int l, r, a, b; 
			l = read(); r = read(); a = read(); b = read();
			if (tp & 1) l ^= ans, r ^= ans;
			cnt++; op t = (op){a, b, l, r};
			add(1, 1, q, cnt, t);
		}else{
			int a, b, k;
			a = read(); b = read(); k = read();
			if (tp & 1) a ^= ans, b ^= ans, k ^= ans;
			oper c = qry(1, 1, q, a, b, k);
			ans = (1LL * A[k] * c.a % m + c.b) % m;
			if (ans < 0) ans += m;
			printf("%d\n",ans);
		}
	}
	return 0;
}