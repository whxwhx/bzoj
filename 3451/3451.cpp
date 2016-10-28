#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define Rep(i,a) for(int i = 0; i < a; i++)
using namespace std;
const int N = 30010;
struct edge{
	int to, pre;
}e[N * 2];
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,x) for(int i = u[x]; i; i = e[i].pre)
#define v e[i].to
#define max(a,b) ((a) > (b) ? (a) : (b))
bool vis[N];
int sum, rt, s[N], sz[N];
void getrt(int x, int f){
	sz[x] = 1, s[x] = 0;
	reg(i,x) if (v != f && !vis[v])
		getrt(v, x), sz[x] += sz[v], s[x] = max(s[x], sz[v]);
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}
typedef pair<int, int> nd;
#define mp(a,b) make_pair(a,b)
nd sbt[N];
int dis[N], Dis[N];
void dfs(int x, int f, int d){
	dis[d]++;
	reg(i,x) if (!vis[v] && v != f) dfs(v, x, d + 1);
}
long double ans = 0;

const int M = 4 * N + 10;
struct cp{
	double r, i;
}a[M], b[M];
cp operator + (const cp &a, const cp &b){
	return (cp){a.r + b.r, a.i + b.i};
}
cp operator - (const cp &a, const cp &b){
	return (cp){a.r - b.r, a.i - b.i};
}
cp operator * (const cp &a, const cp &b){
	return (cp){a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r};
}
int rev[M];

void init(int &n){
	int m = 1, l = 0;
	while (m < n) m <<= 1, l++;
	n = m;
	rev[0] = 0;
	rep(i,1,n - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

const long double pi = acos(-1.0);
void fft(cp *a, int l, int f){
	Rep(i,l) if (rev[i] < i) swap(a[i], a[rev[i]]);
	for (int n = 2; n <= l; n <<= 1){
		int mid = n >> 1;
		cp wn = (cp){cos(2.0 * pi * f / n), sin(2.0 * pi * f / n)};
		for(int i = 0; i < l; i += n){
			cp w = (cp){1, 0};
			Rep(j,mid){
				cp t1 = a[i + j], t2 = w * a[i + j + mid];
				a[i + j] = t1 + t2;
				a[i + j + mid] = t1 - t2;
				w = w * wn;
			}
		}
	}
	if (f == -1) Rep(i,l) a[i].r /= l;
}

void gether(int l){
	int m;
	m = (l + 1) * 2;
	init(m);
	rep(i,0,m - 1) a[i].r = a[i].i = b[i].r = b[i].i = 0;
	rep(i,1,l) a[i].r = dis[i], b[i].r = Dis[i];
	fft(a, m, 1), fft(b, m, 1);
	rep(i,0,m - 1) a[i] = a[i] * b[i];
	fft(a, m, -1);
	rep(i,0,m - 1) {
		int t = (int)(a[i].r + 0.5);
		ans += (long double)(t) / (i + 1);
	}
}
void calc(int x){
	rep(i,1,sz[x]) Dis[i] = dis[i] = 0;	
	int l = 0;
	reg(i,x) if (!vis[v]) sbt[++l] = mp(sz[v] < sz[x] ? sz[v] : sum - sz[x], v);
	sort(sbt + 1, sbt + l + 1);
	rep(i,1,l){
		int t = sbt[i].second;
		rep(j,1,sbt[i].first) dis[j] = 0;
		dfs(t, x, 1);
		rep(j,1,sbt[i].first) ans += (long double)(dis[j]) / (j + 1);
		gether(sbt[i].first);
		rep(j,1,sbt[i].first) Dis[j] += dis[j];  
	}
}
void work(int x){
	vis[x] = 1;
	calc(x);
	int tmp = sum - sz[x];
	reg(i,x) if (!vis[v]){
		sum = sz[v] < sz[x] ? sz[v] : tmp, rt = 0, getrt(v, x);
		work(rt);
	}
}
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n - 1){
		int a, b; scanf("%d%d",&a,&b);
		a++, b++;
		ins(a,b), ins(b,a);
	}
	s[rt = 0] = sum = n, getrt(1,0); 
	work(rt);
	printf("%.4Lf\n",ans * 2 + n);
	return 0;
}