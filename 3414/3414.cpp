#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 100010;
int x[N], y[N], z[N];

int l[N], r[N], n, m;

int a[N], b[N], c[N];
#define ast(a) { if (!a) return false; }

bool check(int s) {
	rep(i,1,n) l[i] = r[i] = 0; int cnt = 0, t = 0;
	rep(i,1,m) c[i] = 0;
	rep(i,1,s) 
		l[i] = min(l[i], y[i]), r[i] = max(r[i], y[i]), ast(!c[y[i]] || (c[y[i]] == z[i])), c[y[i]] = z[i];
	rep(i,1,n) if (l[i]) a[l[i]]++, b[r[i]]++; else cnt++;

	int cur = 0, cur_l = 0, cur_r = 0;
	rep(i,1,m) if (!c[i]) c[i] = c[i - 1];
	rep(i,1,m) if () {

	} 
	return t <= cnt;
}

void work() {
	int m; scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d%d",&y[i],&z[i],&x[i]), z[i]++;
	int l = 0, r = m + 1;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid; else r = mid;
	}
	printf("%d\n",l);
}

int main() {
	int T; scanf("%d",&T); 
	while (T--) work();
	return 0;
}