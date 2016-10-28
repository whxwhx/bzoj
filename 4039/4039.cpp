#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long LL;
const int N = 100010;
struct square{ LL a,b,c,d; }s[N];
square operator + (const square &a, const square &b){
	square c; 
	c.a = min(a.a, b.a), c.b = max(a.b, b.b);
	c.d = min(a.d, b.d), c.c = max(a.c, b.c);
	return c;
}
bool empty(const square &a){ return a.b > a.a || a.c > a.d; }
LL x[N], y[N], x1[N], y1[N], d;
const LL INF = 100000000000000000LL;
LL ab(LL a) { return a < 0 ? -a : a; }
int n;

LL cal(LL a, LL b){
	LL ans = 0;
	rep(i,1,n){
		if (a < x[i]) ans += x[i] - a; else ans += a - x[i];
		if (b < y[i]) ans += y[i] - b; else ans += b - y[i];
		if (ab(x1[i] - a) + ab(y1[i] - b) > d) return INF;
	}
	return ans;
}

LL calc(LL a, LL b){
	LL ans = INF;
	rep(d1,-2,2) rep(d2,-2,2) ans = min(ans, cal(a + d1, b + d2));
	return ans;
}

LL ans; square t;
void work(LL x, LL y){
	ans = min(ans, calc(x, t.a + x));
	ans = min(ans, calc(x, t.c - x));
	ans = min(ans, calc(x, t.b + x));
	ans = min(ans, calc(x, t.d - x));

	ans = min(ans, calc(y - t.a, y));
	ans = min(ans, calc(y - t.b, y));
	ans = min(ans, calc(t.c - y, y));
	ans = min(ans, calc(t.d - y, y));
}

int main(){
	while (scanf("%d",&n) == 1){
		rep(i,1,n) scanf("%lld%lld",&x[i],&y[i]), x1[i] = x[i], y1[i] = y[i];
		scanf("%lld",&d);
		rep(i,1,n) s[i] = (square){y[i] + d - x[i], y[i] - d - x[i], y[i] - d + x[i], y[i] + d + x[i]};
		rep(i,2,n) s[i] = s[i - 1] + s[i]; 
		sort(x + 1, x + n + 1); sort(y + 1, y + n + 1);
		{
			ans = INF; t = s[n];
			//best choice
				if (n & 1) ans = min(ans, calc(x[(n >> 1) | 1], y[(n >> 1) | 1]));
				else {
					ans = min(ans, calc(x[n >> 1], y[n >> 1]));
					ans = min(ans, calc(x[(n >> 1) | 1], y[(n >> 1) | 1]));
				}
			//four corners
			{
				LL x = (t.c - t.a) / 2, y = x + t.a;
				ans = min(ans, calc(x, y));
				x = (t.d - t.a) / 2, y = x + t.a;
				ans = min(ans, calc(x, y));
				x = (t.d - t.b) / 2, y = x + t.b;
				ans = min(ans, calc(x, y));
				x = (t.c - t.b) / 2, y = x + t.b;
				ans = min(ans, calc(x, y));
			}
			//crossing
				if (n&1) work(x[(n>>1)|1], y[(n>>1)|1]);
				else {
					work(x[n>>1], y[n>>1]), work(x[(n>>1)|1],y[(n>>1)|1]);
					work(x[n>>1], y[(n>>1)|1]), work(x[(n>>1)|1], y[n>>1]);
				}
			if (ans < INF) printf("%lld\n",ans); else printf("impossible\n");
		}
	}
}