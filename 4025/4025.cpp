#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N = 100000 + 10;
struct edge{
	int a, b, s, t;
}e[N * 2];
vector<int> edg[N * 4];
#define pb(a) push_back(a)
#define lcq lc,l,mid
#define rcq rc,mid+1,r
void ins(int x, int l, int r, int a, int b, int e){
	if (a <= l && r <= b) edg[x].pb(e);else{
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		if (a <= mid) ins(lcq, a, b, e);
		if (b >  mid) ins(rcq, a, b, e);
	}
}

int f[N], h[N], r[N], tl = 0;
struct node{int fa, fb, ha;}st[N * 2 * 20];

typedef pair<int, int> rfq;
#define mp(a,b) make_pair(a,b)

rfq find(int x){
	rfq ans = f[x] == x ? mp(x, 0) : find(f[x]);
	if (f[x] != x) ans.second ^= r[x];
	return ans;
}
bool uni(int a, int b){
	rfq faq = find(a), fbq = find(b);
	int fa = faq.first, fb = fbq.first, ra = faq.second, rb = fbq.second;
	if (fa != fb){
		if (h[fa] < h[fb]) swap(fa, fb), swap(ra, rb);

		st[++tl] = (node){fa, fb, h[fa]};
		f[fb] = fa, r[fb] = ra ^ rb ^ 1;
		if (h[fa] == h[fb]) h[fa] = h[fb] + 1;

	}else if ((ra ^ rb) == 0) return false;
	return true;
}
void res(){
	node x = st[tl--];
	f[x.fb] = x.fb, r[x.fb] = 0;
	h[x.fa] = x.ha;
}
void cdq(int x, int l, int r){
	int cur = tl + 1;
	for(vector<int>::iterator it = edg[x].begin(); it != edg[x].end(); it++)
		if (!uni(e[*it].a, e[*it].b)){
			rep(i, l, r) printf("No\n");
			int tmp = tl;
			rep(i,cur,tmp) res();
			return;
		}
	if (l == r) {
		printf("Yes\n");
	}else{
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		cdq(lc, l, mid), cdq(rc, mid + 1, r);
	}
	int tmp = tl;
	rep(i,cur,tmp) res();
}
int main(){
	int n, m, T; scanf("%d%d%d",&n,&m,&T);
	rep(i,1,m) scanf("%d%d%d%d",&e[i].a,&e[i].b,&e[i].s,&e[i].t), e[i].s++;
	rep(i,1,n * 4) edg[i].clear();
	rep(i,1,m) if (e[i].s <= e[i].t) ins(1,1,T,e[i].s,e[i].t,i);
	rep(i,1,n) f[i] = i, r[i] = 0;
	cdq(1, 1, T);
	return 0;
}