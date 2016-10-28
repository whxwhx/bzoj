#include<iostream>
#include<set>
#include<map>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#define inf 1000000000
#define pa pair<int,int>
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,cnt,tot,ned;
int sumv;
int u[100005],v[100005],w[100005],c[100005];
int fa[100005];
struct edge{
	int u,v,w,c;
}e[100005];
bool operator<(edge a,edge b)
{
	return a.w==b.w?a.c<b.c:a.w<b.w;
}
int find(int x)
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
bool check(int x)
{
	tot=cnt=0;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		e[i].u=u[i],e[i].v=v[i],e[i].w=w[i];e[i].c=c[i];
		if(!c[i])e[i].w+=x;
	}
	sort(e+1,e+m+1);
	for(int i=1;i<=m;i++)
	{
		int p=find(e[i].u),q=find(e[i].v);
		//cout <<e[i].u<<' '<<e[i].v<<endl;
		//cout <<p<<' '<<q<<endl;
		if(p!=q)
		{
			fa[p]=q;
			tot+=e[i].w; //cout <<e[i].w<<endl;
			if(!e[i].c)cnt++;
		}
	}
	//cout <<endl;
	return cnt>=ned;
}
int main()
{
	n=read();m=read();ned=read();
	for(int i=1;i<=m;i++)
	{
		u[i]=read(),v[i]=read(),w[i]=read(),c[i]=read();
		u[i]++;v[i]++;
	}
	int l=-105,r=105;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1,sumv=tot-ned*mid;
		else r=mid-1;
	}
	printf("%d\n",sumv);
	return 0;
}