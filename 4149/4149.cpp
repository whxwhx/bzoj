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
int a[N], l[N][2], r[N][2], lmn[N][2];
typedef pair<int, int> node;
node st[N];
int top;

vector<node> q[2][N];

int n; 
int s[N * 4];
void build(int x, int l, int r){
	s[x] = n + 1;
	if (l < r){
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		build(lc, l, mid), build(rc, mid + 1, r);
	}
}

void add(int x, int l, int r, int a, int d){
	s[x] = min(s[x], d);
	if (l < r){
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		if (a <= mid) add(lc, l, mid, a, d);
		else add(rc, mid + 1, r, a, d);
	}
}

int qry(int x, int l, int r, int a, int b){
	if (a <= l && r <= b) return s[x];
	else {
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		int ans = n + 1;
		if (a <= mid) ans = min(ans, qry(lc, l, mid, a, b));
		if (b >  mid) ans = min(ans, qry(rc, mid + 1, r, a, b));
		return ans;
	}
}

int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);

	top = 0; int d = 0;
	rep(i,1,n) {
		while (top && st[top].first > a[i]) top--;
		if (top){
			l[i][d] = st[top].second + 1;
			if (st[top].first == a[i]) top--;
		} else l[i][d] = 1;
		st[++top] = mp(a[i], i);
	}

	top = 0, d = 1; rep(i,1,n) a[i] = -a[i];
	rep(i,1,n) {
		while (top && st[top].first > a[i]) top--;
		if (top){
			l[i][d] = st[top].second + 1;
			if (st[top].first == a[i]) top--;
		} else l[i][d] = 1;
		st[++top] = mp(a[i], i);
	}

	top = 0, d = 0; rep(i,1,n) a[i] = -a[i];
	dep(i,n,1) {
		while (top && st[top].first > a[i]) top--;
		if (top){
			r[i][d] = st[top].second - 1;
			if (st[top].first == a[i]) top--;
		} else r[i][d] = n;
		st[++top] = mp(a[i], i);
	}

	top = 0, d = 1; rep(i,1,n) a[i] = -a[i];
	dep(i,n,1) {
		while (top && st[top].first > a[i]) top--;
		if (top){
			r[i][d] = st[top].second - 1;
			if (st[top].first == a[i]) top--;
		} else r[i][d] = n;
		st[++top] = mp(a[i], i);
	}

	typedef vector<node>::iterator vit;
	rep(d,0,1)
		rep(i,1,n) q[d][r[i][d]].pb(mp(l[i][d], i));
	
	int ans = 0, ansl = 1;
	rep(d,0,1){
		build(1, 1, n);
		dep(i,n,1){
			for(vit it = q[d][i].begin(); it != q[d][i].end(); it++)
				add(1, 1, n, (*it).second, (*it).first);
			for(vit it = q[d^1][i].begin(); it != q[d^1][i].end(); it++){
				int l1 = max(qry(1, 1, n, (*it).first, i), (*it).first);
				if (l1 <= (*it).second){
					if (i - l1 > ans || (i - l1 == ans && l1 < ansl))
						ans = i - l1, ansl = l1;
				}
			}
		}
	}
	printf("%d %d\n", ans + 1, ansl);
	return 0;
}