#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<queue>
#define pa pair<int,int>
#define ll long long
#define inf 100000000
using namespace std;
int read()
{
    int x=0;char ch=getchar();
    while(ch>'9'||ch<'0')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int a[15][15];
int bin[20];
int n,m,K;
int f[12][12][1024];
struct data{
    int fit,sed,thd;
}pre[15][15][1024];
int xx[4]={0,0,1,-1},yy[4]={1,-1,0,0};
queue<pa>q;
bool inq[15][15],vis[15][15];
void spfa(int sta)
{
    while(!q.empty())
    {
        int x=q.front().first,y=q.front().second;
        inq[x][y]=0;q.pop();
        for(int k=0;k<4;k++)
        {
            int nowx=x+xx[k],nowy=y+yy[k];
            if(x<1||y<1||x>n||y>m)continue;
            if(f[nowx][nowy][sta]>f[x][y][sta]+a[nowx][nowy])
            {
                f[nowx][nowy][sta]=f[x][y][sta]+a[nowx][nowy];
                pre[nowx][nowy][sta]=(data){x,y,sta};
                if(!inq[nowx][nowy])
                {
                    q.push(make_pair(nowx,nowy));
                    inq[nowx][nowy]=1;
                }
            }
        }
    }
}
void dfs(int x,int y,int sta)
{
    if(x>inf||pre[x][y][sta].thd==0)return;
    vis[x][y]=1;
    data t=pre[x][y][sta];
    dfs(t.fit,t.sed,t.thd);
    if(t.fit==x&&t.sed==y)dfs(x,y,sta-t.thd);
}
int main()
{
    bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
    n=read();m=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            a[i][j]=read();
            if(!a[i][j])K++;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<bin[K];k++)
                f[i][j][k]=pre[i][j][k].fit=inf;
    K=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!a[i][j])
                f[i][j][bin[K]]=0,K++;
    for(int sta=1;sta<bin[K];sta++)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                for(int s=sta&(sta-1);s;s=sta&(s-1))
                {
                    int t=f[i][j][s]+f[i][j][sta-s]-a[i][j];
                    if(t<f[i][j][sta])
                    {
                        f[i][j][sta]=t;
                        pre[i][j][sta]=(data){i,j,s};
                    }
                }
                if(f[i][j][sta]<inf)
                    q.push(make_pair(i,j)),inq[i][j]=1;
            }spfa(sta);
    }
    int x,y;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!a[i][j])
            {
                x=i;y=j;break;
            }
    dfs(x,y,bin[K]-1);
    printf("%d\n",f[x][y][bin[K]-1]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!a[i][j])printf("x");
            else if(vis[i][j])printf("o");
            else printf("_");
        }
        puts("");
    }
    return 0;
}