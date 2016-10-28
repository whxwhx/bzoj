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
const int N = 1010;
const double pi = acos(-1.0);
struct node{ double r; int x, y; }a[N], q, s[N];
LL operator * (const node &a, const node &b) { return 1LL * a.x * b.x + 1LL * a.y * b.y; }
node operator + (const node &a, const node &b) { return (node){0, a.x + b.x, a.y + b.y}; }
bool operator < (const node &a, const node &b) { return sqrt(a * a) * cos(a.r) > sqrt(b * b) * cos(b.r); }
double get(double a) { return a < 0 ? a + 2 * pi : a; }
struct sp{ double r; int a, b; }b[N * N]; 
bool operator < (const sp &a, const sp &b) { return a.r < b.r; }
int id[N], l; LL ans[N]; 
int main(){
	srand(2333); int n; scanf("%d",&n); scanf("%d%d",&q.x,&q.y);
	rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y), a[i].r = get( atan2(a[i].y, a[i].x) ) + (rand() * rand() % 1000000) / (double)100000000000.0;
	LL sx = 0; rep(i,1,n) if (a[i] * q > 0) sx += a[i] * q; printf("%lld\n",sx);
	
	sort(a + 1, a + n + 1);
	rep(i,1,n) rep(j,1,n) if (i != j){
		double x = sqrt(a[i] * a[i]) * cos(a[i].r) - sqrt(a[j] * a[j]) * cos(a[j].r), y = sqrt(a[i] * a[i]) * sin(a[i].r) - sqrt(a[j] * a[j]) * sin(a[j].r);
		swap(x, y), x = -x;
		b[++l] = (sp){ get(atan2(y, x)), i, j };
	}

	sort(b + 1, b + l + 1); 
	s[0] = (node){0,0,0}; rep(i,1,n) id[i] = i, s[i] = s[i - 1] + a[i], ans[i] = s[i] * s[i];
	rep(i,1,l){
		int t1 = b[i].a, t2 = b[i].b; swap(a[id[t1]], a[id[t2]]), swap(id[t1], id[t2]);
		if (id[t1] > id[t2]) swap(t1, t2); //cout <<id[t1]<<' '<<id[t2]<<' '<<t1<<' '<<t2<<' '<<b[i].r<<endl;
		s[id[t1]] = s[id[t1] - 1] + a[id[t1]]; 
		s[id[t2]] = s[id[t2] - 1] + a[id[t2]];
		ans[id[t1]] = max(ans[id[t1]], s[id[t1]] * s[id[t1]]);
		ans[id[t2]] = max(ans[id[t2]], s[id[t2]] * s[id[t2]]);
	}

	LL mx = 0; rep(i,1,n) mx = max(ans[i], mx); printf("%lld\n",mx);
	rep(i,1,n) printf("%lld%c",ans[i],i==n ? '\n' : ' ');
	return 0;
}