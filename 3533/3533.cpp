#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
typedef long long LL;
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
inline int decode (int x, long long lastans) {
	return x ^ (lastans & 0x7fffffff);
}
#define x first
#define y second
typedef pair<int, int> node;
LL operator * (const node &a, const node &b){
	return 1LL * a.x * b.x + 1LL * a.y * b.y;
}
node operator - (const node &a, const node &b){
	return mp(a.x - b.x, a.y - b.y);
}
LL cross(const node &a, const node &b){
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}
int n;
const int N = 400100;
vector<node> s[2][N * 4];
bool vis[N * 4];
#define lc (x << 1)
#define rc (lc | 1)
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
#define pb(a) push_back(a)
const LL inf = 1LL << 62;
node q[N];
void build(int x){
	vis[x] = true;
	rep(t,0,1){
		sort(s[t][x].begin(), s[t][x].end());
		int n = s[t][x].size(), l = 0, r = 0;
		rep(i,0,n - 1){
			node a = s[t][x][i];
			while (r - l >= 2 && cross(a - q[r - 1], q[r - 1] - q[r - 2]) <= 0) r--;
			q[r++] = a;
		}
		s[t][x].clear();
		rep(i,l,r - 1) s[t][x].pb(q[i]);
	}
}
LL qry(int x, bool f, node d){
	int n = s[f][x].size();
	if (n == 0) return -inf;
	if (n == 1) return d * s[f][x][0];
	int l = -1, r = n - 1; //[l,r)
	while (l + 1 < r)
		if (d * s[f][x][mid] <= d * s[f][x][mid + 1]) l = mid; else r = mid;
	return d * s[f][x][l + 1];
}
LL qry(int x, int l, int r, int a, int b, node d){
	if (a <= l && r <= b){
		if (!vis[x]) build(x);
		return qry(x, (d.y <= 0) , (d.y > 0) ? d : mp(-d.x, -d.y));
	}else {
		LL ans = -inf;
		if (a <= mid) ans = max(ans, qry(lcq, a, b, d));
		if (b >  mid) ans = max(ans, qry(rcq, a, b, d));
		return ans;
	}
}
LL qry(int x, int y, int l, int r){
	return qry(1, 1, n, l, r, mp(x,y));
} 
void add(int x, int l, int r, int a, int dx, int dy){
	s[0][x].pb(mp(dx, dy));
	s[1][x].pb(mp(-dx, -dy));
	if (l < r){
		if (a <= mid) add(lcq, a, dx, dy);
		else add(rcq, a, dx, dy);
	}
}
void add(int pos, int x, int y){
	add(1, 1, n, pos, x, y);
}
int main(){
	char s; scanf("%d",&n);
	s = getchar(), s = getchar();
	LL ans = 0;
	int l = 0;
	rep(i,1,n){
		char c = getchar();
		while (c != 'Q' && c != 'A') c = getchar();
		if (c == 'Q'){
			int x, y, l, r; scanf("%d%d%d%d",&x,&y,&l,&r);
			if (s != 'E') x = decode(x, ans), y = decode(y, ans), l = decode(l, ans), r = decode(r, ans);
			ans = qry(x, y, l, r);
			printf("%lld\n",ans);
		}else {
			int x, y; scanf("%d%d",&x,&y);
			if (s != 'E') x = decode(x, ans), y = decode(y, ans);
			add(++l, x, y);
		}
	}
	return 0;
}