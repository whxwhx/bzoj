//负数判同余要格外小心！线段树上使用儿子节点信息的时候，一定要先push儿子上的标记！
#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long LL;
const int N = 200010;
int n, k, d, a[N];

const LL inf = 100000000000000000LL;

#define lc (x << 1)
#define rc (lc + 1)
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
namespace seg{
	LL s[N * 4], mxrd[N * 4], mnrd[N * 4], rd[N * 4], tmx[N * 4], tmn[N * 4];
	void build(int x, int l, int r){ 
		s[x] = mxrd[x] = inf;
		tmx[x] = tmn[x] = mnrd[x] = rd[x] = -inf;
		if (l < r) build(lcq), build(rcq);
	}
	int a, b, mn, mx;
	LL Rd;

	void push(int x, int l, int r){
		if (tmx[x] > -inf){
			mxrd[x] = tmx[x] - rd[x];
			s[x] = tmx[x] - mnrd[x];
			if (l < r) { tmx[lc] = tmx[rc] = tmx[x]; tmx[x] = -inf; }
		}
		if (tmn[x] > -inf){
			mnrd[x] = tmn[x] + rd[x];
			s[x] = mxrd[x] - tmn[x];
			if (l < r) { tmn[lc] = tmn[rc] = tmn[x]; tmn[x] = -inf; }
		}
	}

	void modi(int x, int l, int r, bool f){
		if (a <= l && r <= b){
			if (f) tmx[x] = mx; else tmn[x] = mn;
			push(x, l, r);
		}else{
			push(x, l, r);
			if (a <= mid) modi(lcq, f); else push(lcq);
			if (b >  mid) modi(rcq, f); else push(rcq);
			mnrd[x] = max(mnrd[lc], mnrd[rc]);
			mxrd[x] = min(mxrd[lc], mxrd[rc]);
			s[x] = min(s[lc], s[rc]);
		}
	}

	void mrd(int x, int l, int r){
		if (l == r) { s[x] = tmx[x] - tmn[x] - Rd; mxrd[x] = tmx[x] - Rd, mnrd[x] = tmn[x] + Rd, rd[x] = Rd; } else {
			push(x, l, r);
			if (a <= mid) { mrd(lcq); push(rcq); } else { mrd(rcq); push(lcq); }//调用子树信息前一定要先push！
			s[x] = min(s[lc], s[rc]); 
			mxrd[x] = min(mxrd[lc], mxrd[rc]); 
			mnrd[x] = max(mnrd[lc], mnrd[rc]);
			rd[x] = max(rd[lc], rd[rc]);
		}
	}

	LL Q;
	int qry(int x, int l, int r){
		push(x, l, r); if (s[x] > Q) return 0;
		if (l == r) return l; else {
			if (a <= l && r <= b) { push(rcq); if (s[rc] <= Q) return qry(rcq); else return qry(lcq); }
			else { 
				int ans = 0;
				if (b >  mid) ans = qry(rcq);
				if (a <= mid && !ans) ans = max(ans, qry(lcq));
				return ans;
			}
		}
	}
}

struct stack{//mx
	int val[N], pos[N], top;
	void init(){ top = 0; pos[0] = n + 1; val[0] = 1000000100; }
	int ins(int x, int a){
		while (val[top] <= a) top--;
		top++; val[top] = a; pos[top] = x;
		return pos[top - 1] - 1;
	}
}s1, s2;

int nxt[N], vis[N], b[N];
int find(int x) { int l = 1, r = n + 1; while (l + 1 < r) if (b[mid] <= x) l = mid; else r = mid; return l; }

int main(){
	scanf("%d%d%d",&n,&k,&d); rep(i,1,n) scanf("%d",&a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1); seg::build(1, 1, n);
	s1.init(); s2.init(); int ans = 1, ansx = 1;
	int t = n;

	if (d == 0){
		dep(i,n,1){
			if (a[i] != a[i + 1]) t = i;
			nxt[i] = t;
		}
		dep(i,n,1){
			int rmx = nxt[i];
			if (rmx - i + 1 >= ans) ans = rmx - i + 1, ansx = i;
		}
		printf("%d %d\n",ansx,ansx + ans - 1);
		return 0;
	}

	dep(i,n,1){
		if ((a[i] % d + d) % d != (a[i + 1] % d + d) % d) t = i;//注意a[i]可能是负数！有负数判同余需要先mod再加mod!
		nxt[i] = t;
	}

	t = n;
	dep(i,n,1){
		int k = find(a[i]); if (!vis[k]) vis[k] = n + 1;
		t = min(t, vis[k] - 1); nxt[i] = min(nxt[i], t);
		vis[k] = i;
	}

	dep(i,n,1){
		int mxr = s1.ins(i, a[i]), mnr = s2.ins(i, -a[i]);
		seg::a = i, seg::b = mnr, seg::mn = a[i], seg::modi(1, 1, n, 0);
		seg::a = i, seg::b = mxr, seg::mx = a[i], seg::modi(1, 1, n, 1);
		seg::a = i, seg::Rd = 1LL * i * d, seg::mrd(1, 1, n);
		seg::a = i; seg::b = nxt[i]; seg::Q = 1LL * (k - i) * d; int rmx = seg::qry(1, 1, n);
		if (rmx - i + 1 >= ans) ans = rmx - i + 1, ansx = i;
	}

	printf("%d %d\n",ansx,ansx + ans - 1);
	return 0;
}