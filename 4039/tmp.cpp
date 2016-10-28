#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include<cstdio>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long int64;
const int maxn=100010;
const int64 inf=~0ull>>2;
int64 x[maxn],y[maxn],sx[maxn],sy[maxn];
int64 m0,m1,p0,p1;
int n,d;

bool init(){
	for(int i=1;i<=n;++i)
		scanf("%lld%lld",x+i,y+i);
	scanf("%d",&d);
	m0=-inf,m1=inf,p0=-inf,p1=inf;
	for(int i=1;i<=n;++i){
		p1=min(p1,y[i]+x[i]+d),p0=max(p0,y[i]+x[i]-d);
		m1=min(m1,y[i]-x[i]+d),m0=max(m0,y[i]-x[i]-d);
	}
	if(m0>m1 || p0>p1) return false;
	sort(x+1,x+n+1),sort(y+1,y+n+1),sx[0]=sy[0]=0;
	for(int i=1;i<=n;++i)
		sx[i]=sx[i-1]+x[i],sy[i]=sy[i-1]+y[i];
	return true;
}

int64 calc(int64 x0,int64 y0){
	if(y0+x0<p0 || y0+x0>p1 || y0-x0<m0 || y0-x0>m1) return inf;
	int px=upper_bound(x+1,x+n+1,x0)-x-1;
	int py=upper_bound(y+1,y+n+1,y0)-y-1;
	return (sx[n]-2*sx[px])-(n-2*px)*x0+(sy[n]-2*sy[py])-(n-2*py)*y0;
}
bool cross(int64 x1,int64 y1,int64 x2,int64 y2){
	if(x1>x2) swap(x1,x2),swap(y1,y2);
	return x2>=x1 && x2<=y1;
}
void solve(){
	int64 ans=inf;
	if((m1+p0)%2==0)
		ans=min(ans,calc((p0-m1)/2,(p0+m1)/2));
	else{
		ans=min(ans,calc((p0-m1+1)/2,(p0+m1+1)/2));
		ans=min(ans,calc((p0-m1+1)/2,(p0+m1-1)/2));
	}
	if((m0+p1)%2==0)
		ans=min(ans,calc((p1-m0)/2,(p1+m0)/2));
	else{
		ans=min(ans,calc((p1-m0-1)/2,(p1+m0+1)/2));
		ans=min(ans,calc((p1-m0-1)/2,(p1+m0-1)/2));
	}
	if((m1+p1)%2==0)
		ans=min(ans,calc((p1-m1)/2,(p1+m1)/2));
	else{
		ans=min(ans,calc((p1-m1+1)/2,(p1+m1-1)/2));
		ans=min(ans,calc((p1-m1-1)/2,(p1+m1-1)/2));
	}
	if((m0+p0)%2==0)
		ans=min(ans,calc((p0-m0)/2,(p0+m0)/2));
	else{
		ans=min(ans,calc((p0-m0+1)/2,(p0+m0+1)/2));
		ans=min(ans,calc((p0-m0-1)/2,(p0+m0+1)/2));
	}
	for(int i=1;i<=n;++i){
		int y0=max(x[i]+m0,p0-x[i]),y1=min(x[i]+m1,p1-x[i]);
		if(y0>y1) continue;
		ans=min(ans,calc(x[i],y0));
		ans=min(ans,calc(x[i],y1));
		if(n&1){
			if(cross(y[(n+1)/2],y[(n+1)/2],y0,y1))
				ans=min(ans,calc(x[i],y[(n+1)/2]));
		}
		else{
			if(cross(y[n/2],y[n/2+1],y0,y1))
				ans=min(ans,calc(x[i],y[n/2]));
		}
	}
	for(int i=1;i<=n;++i){
		int x0=max(y[i]-m1,p0-y[i]),x1=min(y[i]-m0,p1-y[i]);
		if(x0>x1) continue;
		ans=min(ans,calc(x0,y[i]));
		ans=min(ans,calc(x1,y[i]));
		if(n&1){
			if(cross(x[(n+1)/2],x[(n+1)/2],x0,x1))
				ans=min(ans,calc(x[(n+1)/2],y[i]));
		}
		else{
			if(cross(x[n/2],x[n/2+1],x0,x1))
				ans=min(ans,calc(x[n/2],y[i]));
		}
	}
	printf("%lld\n",ans);
}

int main(){
	while(scanf("%d",&n),n){
		if(init()) solve(); else puts("impossible");
	}
	return 0;
}