#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;
char s[N];
int K,n,i,j,rk[N],sa[N],height[N],tmp[N],cnt[N],Log[N],f[16][N],g[N];
ll L=1,R,mid;
int len,nowl,nowr,ansl,ansr;
void suffixarray(int n,int m){
  int i,j,k;n++;
  for(i=0;i<n;i++)cnt[rk[i]=s[i]]++;
  for(i=1;i<m;i++)cnt[i]+=cnt[i-1];
  for(i=0;i<n;i++)sa[--cnt[rk[i]]]=i;
  for(k=1;k<=n;k<<=1){
    for(i=0;i<n;i++){
      j=sa[i]-k;
      if(j<0)j+=n;
      tmp[cnt[rk[j]]++]=j;
    }
    sa[tmp[cnt[0]=0]]=j=0;
    for(i=1;i<n;i++){
      if(rk[tmp[i]]!=rk[tmp[i-1]]||rk[tmp[i]+k]!=rk[tmp[i-1]+k])cnt[++j]=i;
      sa[tmp[i]]=j;
    }
    memcpy(rk,sa,n*sizeof(int));
    memcpy(sa,tmp,n*sizeof(int));
    if(j>=n-1)break;
  }
  for(j=rk[height[i=k=0]=0];i<n-1;i++,k++)
    while(~k&&s[i]!=s[sa[j-1]+k])height[j]=k--,j=rk[sa[j]+1];
}
inline int lcp(int x,int y){
  if(x==y)return n-x;
  x=rk[x],y=rk[y];
  if(x>y)swap(x,y);
  int k=Log[y-x];
  return min(f[k][x+1],f[k][y-(1<<k)+1]);
}
void kth(ll k){
  ll s=0;
  for(int i=1;i<=n;s+=n-sa[i]-height[i],i++)if(s+n-sa[i]-height[i]>=k){
    nowl=sa[i],nowr=nowl+height[i]+k-s-1;
    len=nowr-nowl+1;
    return;
  }
}
inline bool ask(int l,int r){
  int t=min(lcp(l,nowl),min(r-l+1,len));
  if(t==r-l+1&&t<=len)return 1;
  if(t==len)return 0;
  return s[l+t]<=s[nowl+t];
}
bool check(){
  int i,j,k=0;
  for(i=n-1;~i;i=j,k++){
    for(j=i;~j;j--)if(!ask(j,i))break;
    if(j==i)return 0;
  }
  return k<=K;
}
int main(){
  scanf("%d%s",&K,s);
  n=strlen(s);
  suffixarray(n,128);
  for(i=2;i<=n;i++)Log[i]=Log[i>>1]+1;
  for(i=1;i<=n;i++)f[0][i]=height[i];
  for(j=1;j<17;j++)for(i=1;i+(1<<j-1)<=n;i++)f[j][i]=min(f[j-1][i],f[j-1][i+(1<<j-1)]);
  for(i=1;i<=n;i++)R+=n-sa[i]-height[i];
  while(L<=R){
    kth(mid=(L+R)>>1);
    if(check())ansl=nowl,ansr=nowr,R=mid-1;else L=mid+1;
  }
  for(i=ansl;i<=ansr;i++)putchar(s[i]);
  return 0;
}