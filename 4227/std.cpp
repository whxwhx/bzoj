#include<cstdio>
typedef long long ll;
const int N=300010,M=400010,K=19;
const ll inf=1LL<<60;
int n,m,S,cnt,i,x,deg[N],g[N],v[M],w[M],nxt[M],ed;
int size[N],sum[N],id[N],h,t,q[N],dep[N],f[N][K],G[N],NXT[N],V[N];
ll d[N],ans[N];
struct E{int x,y,w;}a[M>>1];
inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
inline void addedge(int x,int y,int z){v[++ed]=y;w[ed]=z;nxt[ed]=g[x];g[x]=ed;}
inline void add(int x,int y){deg[y]++;v[++ed]=y;nxt[ed]=g[x];g[x]=ed;}
inline void addtree(int x,int y){V[++ed]=y;NXT[ed]=G[x];G[x]=ed;}
struct PI{
  ll x;int y;
  PI(){}
  PI(ll _x,int _y){x=_x,y=_y;}
  inline PI operator+(PI b){return x<=b.x?PI(x,y):b;}
}val[262145];
void build(int x,int a,int b){
  val[x]=PI(inf,a);
  if(a==b)return;
  int mid=(a+b)>>1;
  build(x<<1,a,mid),build(x<<1|1,mid+1,b);
}
inline void change(int x,int a,int b,int c,ll d){
  if(a==b){val[x].x=d;return;}
  int mid=(a+b)>>1;
  c<=mid?change(x<<1,a,mid,c,d):change(x<<1|1,mid+1,b,c,d);
  val[x]=val[x<<1]+val[x<<1|1];
}
inline int lca(int x,int y){
  int i;
  if(dep[x]<dep[y])i=x,x=y,y=i;
  for(i=K-1;~i;i--)if(dep[f[x][i]]>=dep[y])x=f[x][i];
  if(x==y)return x;
  for(i=K-1;~i;i--)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
  return f[x][0];
}
void dfs(int x){
  for(int i=G[x];i;i=NXT[i])dfs(V[i]),size[x]+=size[V[i]];
  sum[id[x]]=size[x];
}
int main(){
  read(n),read(m);
  for(i=1;i<=m;i++){
    read(a[i].x),read(a[i].y),read(a[i].w);
    addedge(a[i].x,a[i].y,a[i].w);
    addedge(a[i].y,a[i].x,a[i].w);
  }
  read(S);
  for(i=1;i<=n;i++)d[i]=inf;
  build(1,1,n),change(1,1,n,S,d[S]=0);
  while(val[1].x<inf)for(change(1,1,n,x=val[1].y,inf),i=g[x];i;i=nxt[i])if(d[x]+w[i]<d[v[i]])change(1,1,n,v[i],d[v[i]]=d[x]+w[i]);
  for(ed=0,i=1;i<=n;i++)g[i]=0,size[i]=d[i]<inf;
  for(cnt=n,i=1;i<=m;i++){
    if(d[a[i].x]+a[i].w==d[a[i].y])id[++cnt]=i,add(a[i].x,cnt),add(cnt,a[i].y);
    if(d[a[i].y]+a[i].w==d[a[i].x])id[++cnt]=i,add(a[i].y,cnt),add(cnt,a[i].x);
  }
  for(cnt++,i=1;i<cnt;i++)if(!deg[i])add(cnt,i);
  q[h=t=1]=cnt,ed=0;
  while(h<=t){
    x=q[h++];
    if(f[x][0])addtree(f[x][0],x);
    for(dep[x]=dep[f[x][0]]+1,i=1;i<K;i++)f[x][i]=f[f[x][i-1]][i-1];
    for(i=g[x];i;i=nxt[i]){
      if(!f[v[i]][0])f[v[i]][0]=x;else f[v[i]][0]=lca(f[v[i]][0],x);
      if(!(--deg[v[i]]))q[++t]=v[i];
    }
  }
  dfs(cnt);
  for(i=1;i<=m;i++)ans[a[i].x]+=sum[i],ans[a[i].y]+=sum[i];
  for(i=1;i<=n;i++)printf("%lld\n",ans[i]);
  return 0;
}