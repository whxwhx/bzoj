#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 200000 + 10;
int a[N], b[N], n, m;
int find(int x){
	int l = 0, r = n;
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (b[mid] < x) l = mid; else r = mid;
	}
	return r;
}
int mex, cnt[N], nex[N], tmp[N];
vector<int> q[N];
typedef vector<int>::iterator vit;
#define pb(a) push_back(a)
int qa[N], qb[N], ans[N];
int tag[N * 4];
void modify(int x,int l, int r, int a, int b, int c){
	if (b < a) return;
	if (c >= tag[x]) return;
	if (a <= l && r <= b){
		tag[x] = min(tag[x], c);
		return;
	}else{
		int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
		if (a <= mid) modify(lc,l,mid,a,b,c);
		if (b >  mid) modify(rc,mid+1,r,a,b,c);
	}
}
int qry(int x, int l, int r, int a){
	if (l == r) return tag[x];
	int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1;
	if (a <= mid) return min(tag[x], qry(lc, l, mid, a)); else return min(tag[x], qry(rc, mid + 1, r, a));
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1);
	rep(i,1,n) a[i] = find(a[i]);
	
	
	rep(i,2,n) if (b[i] > b[i - 1] + 1) {mex = b[i - 1] + 1; break;}
	if (mex == 0) mex = b[n] + 1;
	if (b[1] != 0) mex = 0;
	
	rep(i,1,n) cnt[a[i]]++;
	int t = mex; 
	rep(i,1,n * 4) tag[i] = t;
	dep(i,n,1){
		modify(1,1,n,i,i,t);
		cnt[a[i]]--;
		if (!cnt[a[i]]) t = min(t, b[a[i]]);
	}
	rep(i,1,n) tmp[i] = n + 1;
	dep(i,n,1)
		nex[i] = tmp[a[i]], tmp[a[i]] = i;
	rep(i,1,m){
		scanf("%d%d", &qa[i], &qb[i]);
		q[qa[i]].pb(i);
	}
	
	rep(i,1,n){
		for(vit it = q[i].begin(); it != q[i].end(); it++) ans[*it] = qry(1,1,n,qb[*it]);
		modify(1,1,n,i,nex[i] - 1,b[a[i]]);
	}
	rep(i,1,m) printf("%d\n",ans[i]);
}