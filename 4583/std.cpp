#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ll long long
#define N 505
#define P 1000000007

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return ret;
}
int fast_pow(int x,int y){
	int ret=1;
	while (y){
		if (y&1) ret=(ll)ret*x%P;
		x=(ll)x*x%P;
		y=y>>1;
	}
	return ret;
}

struct node{
	int l,c0,c1,c2;
} a[N];
inline bool operator <(const node &u,const node &v){
	return u.l<v.l;
}
int n;
int fact[N],inv[N];

int dp[N][N],f[N][N],sum,now;
void jump(int step){
	if (!step) return;
	if (!sum){now+=step;return;}
	memset(f,0,sizeof(f));
	for (int i=0;i<=100;++i)
		for (int j=0;j<=100;++j){
			int k=sum-i-j;
			if (k<0||k>100) continue;
			if (i) (f[i-1][j]+=dp[i][j])%=P;
			if (j) (f[i][j-1]+=dp[i][j])%=P;
			if (k) (f[i][j]+=dp[i][j])%=P;
		}
	for (int i=0;i<=100;++i)
		for (int j=0;j<=100;++j)
			dp[i][j]=f[i][j];
	++now;--sum;
	jump(step-1);
}

int main(){
	for (int i=fact[0]=1;i<=500;++i) fact[i]=(ll)fact[i-1]*i%P;
	for (int i=0;i<=500;++i) inv[i]=fast_pow(fact[i],P-2);
	n=read();
	for (int i=1;i<=n;++i) a[i].l=read();
	for (int i=1;i<=n;++i) a[i].c0=read();
	for (int i=1;i<=n;++i) a[i].c1=read();
	for (int i=1;i<=n;++i) a[i].c2=read();
	sort(a+1,a+n+1);
	memset(dp,0,sizeof(dp));dp[0][0]=1;
	sum=0;now=0;
	for (int l=1;l<=n;++l){
		jump(a[l].l-now);
		memset(f,0,sizeof(f));
		int k;
		if (sum<=a[l].c0+a[l].c1+a[l].c2)
			for (int i=0;i<=a[l].c0;++i)
				for (int j=0;j<=a[l].c1;++j){
					k=sum-i-j;
					if (k<0||k>a[l].c2) continue;
					(f[a[l].c0-i][a[l].c1-j]+=(ll)dp[i][j]*fact[sum]%P*inv[i]%P*inv[j]%P*inv[k]%P)%=P;
				}
		else
			for (int i=a[l].c0;i<=100;++i)
				for (int j=a[l].c1;j<=100;++j){
					k=sum-i-j;
					if (k<a[l].c2||k>100) continue;
					(f[i-a[l].c0][j-a[l].c1]+=(ll)dp[i][j]*fact[a[l].c0+a[l].c1+a[l].c2]%P*inv[a[l].c0]%P*inv[a[l].c1]%P*inv[a[l].c2]%P)%=P;
				}
		for (int i=0;i<=100;++i)
			for (int j=0;j<=100;++j)
				dp[i][j]=f[i][j];
		now+=min(a[l].c0+a[l].c1+a[l].c2,sum);
		sum=abs(a[l].c0+a[l].c1+a[l].c2-sum);
	}
	jump(500);
	printf("%d\n",dp[0][0]);
	return 0;
}