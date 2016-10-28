#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 2 * 100000 + 10;
typedef long long LL;
typedef pair<int, int> node;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
node t[N];
bool cmp(const node &a, const node &b){
	return a.y < b.y;
}
LL ans = 0;
node s[N], s2[N], t1[N], T2[N];
int top, t2;
int f[N], id[N];
inline int find(int x){
	return (f[x] == x || f[x] == -1) ? f[x] : f[x] = find(f[x]);
}
void cdq(int l, int r){
	if (l == r) return;
	int mid = (l + r) >> 1;
	top = t2 = 0;
	int L = l, R = r;
	rep(i,L,R) f[i] = i;
	rep(i,L,R) if (t[i].x <= mid){
		while (top && s[top - 1].x < t[i].x) top--, f[s[top].x] = top ? s[top - 1].x : -1;
		s[top++] = t[i]; id[t[i].x] = top - 1;
	}else{
		while (t2 && s2[t2 - 1].x > t[i].x) t2--;
		
		int tt = t2 == 0 ? -1 : find(s2[t2 - 1].x);
	    tt = tt == -1 ? -1 : id[tt];

		s2[t2++] = t[i];

		f[t[i].x] = top ? s[top - 1].x : -1;

		ans += top - 1 - tt;
	}
	int l1 = 0, l2 = 0;
	rep(i,L,R) if (t[i].x <= mid) t1[++l1] = t[i]; else T2[++l2] = t[i];
	int l3 = L;
	rep(i,1,l1) t[l3++] = t1[i];
	rep(i,1,l2) t[l3++] = T2[i];
	cdq(L, mid), cdq(mid + 1, R);
}
int n; 
void init(){
	scanf("%d",&n);
	rep(i,1,n) {
		int a, b;
		scanf("%d%d",&a,&b);
		t[i] = mp(a,b);
	}
	sort(t + 1, t + n + 1);
	rep(i,1,n) t[i].x = i;
	sort(t + 1, t + n + 1, cmp);
	rep(i,1,n) t[i].y = i;
}
int main(){
	init();
	cdq(1, n);
	printf("%lld\n",ans);
}