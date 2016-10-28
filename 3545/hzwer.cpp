#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
#define inf 1000000000
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int bin[20];
int n,m,Q,cnt,top,sz,ext,lastans;
int disc[100005],h[100005];
int f[200005],val[200005],st[200005],ed[200005];
int q[300005],root[300005];
int ls[5000005],rs[5000005],sum[5000005];
int deep[200005],fa[200005][17],mx[200005][17];
bool vis[200005];
struct data{int u,v,w;}a[500005];
struct edge{int to,next;}e[200005];int last[200005];
int getf(int x)
{
	return x==f[x]?x:f[x]=getf(f[x]);
}
int find(int x,int val)
{
	for(int i=17;i>=0;i--)
		if(deep[x]>=bin[i]&&mx[x][i]<=val)x=fa[x][i];
	return x;
}
void insert(int u,int v) 
{
    e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
}
bool operator<(data a,data b)
{
    return a.w<b.w;
}
void dfs(int x)
{
	vis[x]=1;q[++top]=x;
	for(int i=1;i<=16;i++)
		if(deep[x]>=bin[i])
		{
			fa[x][i]=fa[fa[x][i-1]][i-1];
			mx[x][i]=max(mx[x][i-1],mx[fa[x][i-1]][i-1]);
		}
		else break;
    for(int i=last[x];i;i=e[i].next)
	{
		deep[e[i].to]=deep[x]+1;
		mx[e[i].to][0]=val[x];
		fa[e[i].to][0]=x;
        dfs(e[i].to);
	}
    if(x>n)q[++top]=x;
}
void ins(int l,int r,int &x,int f,int val)
{
	x=++sz;
    sum[x]=sum[f]+1;
	if(l==r)return;
    ls[x]=ls[f];rs[x]=rs[f];
    int mid=(l+r)>>1;
    if(val<=mid)ins(l,mid,ls[x],ls[f],val);
    else ins(mid+1,r,rs[x],rs[f],val);
}
int query(int l,int r,int x,int y,int rank)
{
    if(l==r)return l;
    int mid=(l+r)>>1;
    if(sum[ls[y]]-sum[ls[x]]>=rank)return query(l,mid,ls[x],ls[y],rank);
    else return query(mid+1,r,rs[x],rs[y],rank-sum[ls[y]]+sum[ls[x]]);
}
void build()
{
    ext=n;
    sort(a+1,a+m+1);
    for(int i=1;i<=m;i++)
    {
        int p=getf(a[i].u),q=getf(a[i].v);
        if(p!=q)
        {
            ext++;
			f[p]=f[q]=ext;
			val[ext]=a[i].w;
			insert(ext,q);insert(ext,p);
			if(ext==2*n-1)break;
        }
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])dfs(getf(i));
    for(int i=1;i<=top;i++)
    {
		int t=q[i];
        if(t<=n)ins(1,n,root[i],root[i-1],h[t]);
        else
        {
            root[i]=root[i-1];
            if(!st[t])st[t]=i;
            else ed[t]=i;
        }
    }
}
void solve()
{
    int v,x,k;
    for(int i=1;i<=Q;i++)
    {
        v=read(),x=read(),k=read();
        //if(lastans!=-1)v^=lastans,x^=lastans,k^=lastans;
        int t=find(v,x);
        int a=root[st[t]],b=root[ed[t]];
        if(sum[b]-sum[a]<k)lastans=-1;
        else lastans=disc[query(1,n,a,b,sum[b]-sum[a]-k+1)];
        printf("%d\n",lastans);
    }
}
int main()
{
	bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
    n=read();m=read();Q=read();
    for(int i=1;i<=n;i++)h[i]=read(),disc[i]=h[i];
    sort(disc+1,disc+n+1);
    for(int i=1;i<=n;i++)h[i]=lower_bound(disc+1,disc+n+1,h[i])-disc;
    for(int i=1;i<=2*n;i++)f[i]=i;
    for(int i=1;i<=m;i++)
        a[i].u=read(),a[i].v=read(),a[i].w=read();
    build();
    solve();
    return 0;
}