
F.A.Qs	Home	Discuss	ProblemSet	Status	Ranklist	Contest	ModifyUser   wu_hong_xun	Logout	捐赠本站
Notice:最近屡有来自宁波余姚中学的用户恶意卡测评机，IP为61.175.134.38， 在此特予以警告，望其自重！
Problem1000

var
 a,b:int64;
begin
 readln(a,b);
 writeln(a+b);
end.
Problem1000

t1,t2=map(int, raw_input().split())
print str(t1+t2)
Problem1001

var
 n,m,s,t,k,i,j,tot,l,r:longint;
 f,tt,c:array[0..12000000]of longint;
 dis,q,d:array[0..1900010]of longint;
 h:array[0..1900010]of boolean;
procedure insert(ff,t,k:longint);
begin
     inc(tot);
	 f[tot]:=ff;
     tt[tot]:=t;
	 c[tot]:=k;
	 inc(tot);
	 f[tot]:=t;
	 tt[tot]:=ff;
	 c[tot]:=k;
end;
procedure spfa;
begin
 fillchar(dis,sizeof(dis),0);dis[0]:=1;fillchar(h,sizeof(h),false);
 l:=0;r:=1;d[0]:=0;h[0]:=true;
 repeat
     k:=d[l];
     if q[k]>0 then begin 
       i:=q[k];
	  while f[i]=k do begin 
           if (dis[k]+c[i]<dis[tt[i]]) or (dis[tt[i]]=0) then begin
                dis[tt[i]]:=dis[k]+c[i]; 
                 if not(h[tt[i]]) then begin
                   d[r]:=tt[i];inc(r);r:=r mod 1900010;h[tt[i]]:=true;
                end;
           end;
		  inc(i);
	  end;
	 end;
	 h[k]:=false;inc(l);l:=l mod 1900010;
 until l=r;
end;
procedure sort(l,r:longint);
var
 m,i,j,t:longint;
begin
 m:=f[(l+r) div 2];
 i:=l;j:=r;
 repeat
  while f[i]<m do inc(i);
  while f[j]>m do dec(j);
  if i<=j then begin 
      t:=f[i];f[i]:=f[j];f[j]:=t;
	  t:=tt[i];tt[i]:=tt[j];tt[j]:=t;
	  t:=c[i];c[i]:=c[j];c[j]:=t;
     inc(i);dec(j);
  end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin
 readln(n,m);
 s:=0;t:=(n-1)*(m-1)*2+1;
 for i:=1 to m-1 do begin
     read(k);
     if n=1 then insert(s,t,k) else insert(s,i,k);
 end;if m>1 then readln;
 for i:=2 to n-1 do begin  
   for j:=1 to m-1 do begin
        read(k);
        insert((i-1)*(m-1)*2+j,(i-2)*(m-1)*2+(m-1)+j,k);
   end;
   if m>1 then readln;
 end;
 if n>1 then begin
   for j:=1 to m-1 do begin
       read(k);
       insert(t,(n-2)*(m-1)*2+(m-1)+j,k);
   end;if m>1 then readln;
 end;
 for i:=1 to n-1 do begin
     read(k);
     if m>1 then insert(t,(i-1)*(m-1)*2+(m-1)+1,k) else insert(s,t,k);
     for j:=2 to m-1 do begin
         read(k);
         insert((i-1)*(m-1)*2+j-1,(i-1)*(m-1)*2+(m-1)+j,k); 
     end;
     if m>1 then begin
      read(k);
      insert(s,(i-1)*(m-1)*2+m-1,k);
     end;readln;
 end;
 for i:=1 to n-1 do
   for j:=1 to m-1 do begin
      read(k);
      insert((i-1)*(m-1)*2+j,(i-1)*(m-1)*2+(m-1)+j,k);
   end; 
   sort(1,tot);fillchar(q,sizeof(q),0);
   for i:=1 to tot do if q[f[i]]=0 then q[f[i]]:=i;
   spfa;
   writeln(dis[t]-1);
end.
Problem1003

var
 k,l:int64;
 n,m,e,d,i,j,p,a,b:longint;
 dp,dis:array[0..100]of int64;
 w:array[1..20]of boolean;
 s:array[1..100,1..20]of boolean;
 f,t,c:array[1..10000]of int64;
function bellman(a,b:longint):int64;
var
 flag:boolean;
 i,j:longint;
begin 
 fillchar(w,sizeof(w),true);
 for i:=a to b do
	 for j:=1 to m do w[j]:=w[j] and s[i,j];
 fillchar(dis,sizeof(dis),0);dis[1]:=1;flag:=true;
 while flag do begin 
    flag:=false;
    for i:=1 to e do begin 
		 if (not w[f[i]]) or (not w[t[i]]) then continue;
		 if dis[f[i]]>0 then if (dis[t[i]]=0) or (dis[f[i]]+c[i]<dis[t[i]]) then begin dis[t[i]]:=dis[f[i]]+c[i];flag:=true;end;
		 if dis[t[i]]>0 then if (dis[f[i]]=0) or (dis[t[i]]+c[i]<dis[f[i]]) then begin dis[f[i]]:=dis[t[i]]+c[i];flag:=true;end;
	 end;
 end;
 exit(dis[m]-1);
end;
begin 
 readln(n,m,k,e);
 for i:=1 to e do readln(f[i],t[i],c[i]);
 readln(d);fillchar(s,sizeof(s),true);
 for i:=1 to d do begin 
	 readln(p,a,b);
     for j:=a to b do s[j,p]:=false;
 end;
 dp[0]:=-k;
 for i:=1 to n do begin 
     dp[i]:=maxlongint;
     for j:=0 to i-1 do begin 
		 l:=bellman(j+1,i);if l<=0 then continue;
	     if dp[j]+k+l*(i-j)<dp[i] then dp[i]:=dp[j]+k+l*(i-j);
	 end;
 end;
 writeln(dp[n]);
end.
Problem1004

#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define maxn 70
#define for(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int r,b,g,m,p,n;
struct perm{
	int a[maxn];
};
perm s[70];
int powed[1000];
int pow(int a)//a^(p-2) mod p
{
	a%=p;if (powed[a]) return powed[a];
	int x=p-2,ans=1,s=a;
	if (!x) return 1;
	while (x>0){
		if (x&1) ans=(ans*s) %p;
		s=(s*s) %p;
		x=x >> 1;
	}
	powed[a]=ans;
	return ans;
}
bool vis[100];
int a[100],f[100][100][100];
int calc(perm &s)
{
	//broke_into_circles
	memset(vis,false,sizeof(vis));
	int l=0;
	for (i,1,n){
		if (vis[i]) continue;
		a[++l]=0;int j=i;
		while (not vis[j]){
			a[l]++;vis[j]=true;
			j=s.a[j];
		}
	}
	//dp
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	for (i,1,l)
		for (j,0,r)
			for (t,0,g)
			{
				f[i][j][t]=f[i-1][j][t];
				if (j>=a[i]) f[i][j][t]=(f[i][j][t]+f[i-1][j-a[i]][t])%p;
				if (t>=a[i]) f[i][j][t]=(f[i][j][t]+f[i-1][j][t-a[i]])%p;
			}
	return f[l][r][g];	
}
int main(){
	scanf("%d%d%d%d%d",&r,&b,&g,&m,&p);
	memset(powed,0,sizeof(powed));
	int n=r+b+g;
	int tot=0;
	for (i,1,m) for (j,1,n) scanf("%d",&s[i].a[j]);
	for (i,1,m) tot=(tot + calc(s[i])) % p;
	int tmp=1;
	for (i,r+1,n) tmp=(tmp * i)%p;
	for (i,1,b) tmp=(tmp * pow(i))%p;
	for (i,1,g) tmp=(tmp * pow(i))%p;
	tot+=tmp;
	tot=(tot*pow(m+1))%p;
	if (tot<0) tot+=p;
	printf("%d",tot);
	return 0;
}
Problem1005

type
  hugeint=array[0..168]of longint;
var
 flag:boolean;
 ans:array[1..10000]of longint;
 p:array[1..168]of longint;
 ak,at:hugeint;
 n,tot,m,i,k,j,j1,t,jw,l:longint;
 a:array[1..1000]of longint;
procedure get(k:longint);
var
 i:longint;
begin
 i:=1;fillchar(at,sizeof(at),0); 
 while k>1 do 
	 if k mod p[i]=0 then begin k:=k div p[i];inc(at[i]);end else inc(i);
end;
function max(a,b:longint):longint;
begin
 if a>b then exit(a) else exit(b); 
end;
begin 
 j1:=0;
 for i:=2 to 999 do begin
	 flag:=false;
    for j:=2 to i-1 do if i mod j=0 then begin flag:=true;break;end;
	if not flag then begin inc(j1);p[j1]:=i;end;
 end;
 readln(m);tot:=0;n:=0;
 for i:=1 to m do begin 
	  readln(a[i]);if a[i]>=m then begin writeln(0);halt;end;
      if a[i]=0 then if n<>1 then begin writeln(0);halt;end else  begin writeln(1);halt;end; 
	 if a[i]>0 then begin 
		   tot:=tot+(a[i]-1);
	      inc(n);
	   end;
 end;
 if (m-n=0) or (m-2=0) then begin writeln(0);exit;end;
 k:=m-n;get(k);ak:=at;
 for i:=1 to 168 do ak[i]:=ak[i]*(m-2-tot);
 for i:=m-2-tot+1 to m-2 do begin 
	 if i<2 then continue;
	 get(i);
     for j:=1 to 168 do ak[j]:=ak[j]+at[j];
 end;
 for i:=1 to m do begin
	for j:=2 to a[i]-1 do begin 
         get(j);
	     for j1:=1 to 168 do ak[j1]:=ak[j1]-at[j1];
	 end;
 end; 
 l:=1;fillchar(ans,sizeof(ans),0);
 ans[l]:=1;
 for i:=1 to 168 do 
	  for j:=1 to ak[i] do begin
		 jw:=0;
		  for t:=1 to l do  begin 
			  ans[t]:=ans[t]*p[i]+jw;
		      jw:=ans[t] div 10;ans[t]:=ans[t] mod 10;
		 end;
		 while jw>0 do begin inc(l);ans[l]:=jw mod 10;jw:=jw div 10;end;
	  end;
 for i:=l downto 1 do write(ans[i]);
end.
Problem1005

 
type
  hugeint=array[0..168]of longint;
var
 flag:boolean;
 ans:array[1..10000]of longint;
 p:array[1..168]of longint=(
     2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,
103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,
199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,
307,311,313,317,331,337,347,349,
353,359,367,373,379,383,389,397,
401,409,419,421,431,433,439,443,449,
457,461,463,467,479,487,491,499,
503,509,521,523,541,547,
557,563,569,571,577,587,593,599,
601,607,613,617,619,631,641,643,647,
653,659,661,673,677,683,691,
701,709,719,727,733,739,743,
751,757,761,769,773,787,797,
809,811,821,823,827,829,839,
853,857,859,863,877,881,883,887,
907,911,919,929,937,941,947,
953,967,971,977,983,991,997);
 ak,at:hugeint;
 n,tot,m,i,k,j,j1,t,jw,l:longint;
 a:array[1..1000]of longint;
procedure get(k:longint);
var
 i:longint;
begin
 i:=1;fillchar(at,sizeof(at),0); 
 while k>1 do
     if k mod p[i]=0 then begin k:=k div p[i];inc(at[i]);end else inc(i);
end;
function max(a,b:longint):longint;
begin
 if a>b then exit(a) else exit(b); 
end;
begin
 readln(m);tot:=0;n:=0;
 for i:=1 to m do begin
      readln(a[i]);if a[i]>=m then begin writeln(0);halt;end;
      if a[i]=0 then if n<>1 then begin writeln(0);halt;end else  begin writeln(1);halt;end; 
     if a[i]>0 then begin
           tot:=tot+(a[i]-1);
          inc(n);
       end;
 end;
 if (m-n=0) or (m-2=0) then begin writeln(0);exit;end;
 k:=m-n;get(k);ak:=at;
 for i:=1 to 168 do ak[i]:=ak[i]*(m-2-tot);
 for i:=m-2-tot+1 to m-2 do begin
     if i<2 then continue;
     get(i);
     for j:=1 to 168 do ak[j]:=ak[j]+at[j];
 end;
 for i:=1 to m do begin
    for j:=2 to a[i]-1 do begin
         get(j);
         for j1:=1 to 168 do ak[j1]:=ak[j1]-at[j1];
     end;
 end; 
 l:=1;fillchar(ans,sizeof(ans),0);
 ans[l]:=1;
 for i:=1 to 168 do
      for j:=1 to ak[i] do begin
         jw:=0;
          for t:=1 to l do  begin
              ans[t]:=ans[t]*p[i]+jw;
              jw:=ans[t] div 10;ans[t]:=ans[t] mod 10;
         end;
         while jw>0 do begin inc(l);ans[l]:=jw mod 10;jw:=jw div 10;end;
      end;
 for i:=l downto 1 do write(ans[i]);
end.
Problem1007

type
	 line=record 
        k,b,l:longint;
    end;
var
 h:array[1..50000]of boolean;
 st,a:array[1..50000]of line;
 top,n,i,nt,j:longint;
 t:line;
procedure sort(l,r:longint);
var
 t:line;
 i,j,mid:longint;
begin 
 i:=l;j:=r;mid:=a[(l+r) shr 1].k;
 repeat
	 while a[i].k>mid do inc(i);
	 while a[j].k<mid do dec(j);
	 if i<=j then begin 
		 t:=a[i];a[i]:=a[j];a[j]:=t;
	     inc(i);dec(j);
	 end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
procedure push(a:line);
begin 
  inc(top);st[top]:=a;
end;
function x(a,b:line):extended;
begin 
  exit((b.b-a.b)/(a.k-b.k));
end;
begin 
 readln(n);nt:=n;
 for i:=1 to n do begin readln(a[i].k,a[i].b);a[i].l:=i;end;
 sort(1,n);top:=0;push(a[1]);
 i:=1;
 while i<n do begin 
	 inc(i);
	 if a[i].k=a[i-1].k then begin 
		 if a[i].b>a[i-1].b then begin 
			 t:=a[i-1];a[i-1]:=a[i];a[i]:=t;
		 end;
		 dec(n);
		 for j:=i to n do a[j]:=a[j+1];
		 dec(i);
	 end;
 end;
 for i:=2 to n do begin 
	 while (top>=2) and (x(st[top],st[top-1])<=x(st[top],a[i])) do dec(top);
	 push(a[i]);
 end;
 fillchar(h,sizeof(h),false);
 for i:=1 to top do h[st[i].l]:=true;
 for i:=1 to nt do if h[i] then write(i,' ');
end.
Problem1008

var
 n,m,ans,ansall:int64;
function count(a,b:int64):int64;
var
 k:int64;
begin 
 if b=0 then exit(1);
 k:=count(a,b shr 1);
 count:=k*k;
 if b and 1=1 then count:=count*a;
 count:=count mod 100003;
end;
begin 
 readln(m,n);ans:=(m*count(m-1,n-1)) mod 100003;ansall:=count(m,n);
 ans:=ansall-ans;ans:=ans mod 100003;
 while ans<0 do inc(ans,100003);
 writeln(ans);
end.
Problem1009

type
	arr=array[0..20,0..20]of longint;
var
 c:char;
 n,m,mo,i,j,ans:longint;
 a,p:array[1..20]of longint;
 f:arr;
function chen(a,b:arr):arr;
var
 i,j,k:longint;
begin
 for i:=0 to m do begin 
	 for j:=0 to m do begin 
		 chen[i,j]:=0;
		 for k:=0 to m do chen[i,j]:=(chen[i,j]+a[i,k]*b[k,j]) mod mo;
    end;
 end;
end;
 function get(a:arr;n:longint):arr;
 var
  t:arr;
  begin
     if n=1 then exit(a);
     t:=get(a,n shr 1);
     get:=chen(t,t);
     if n and 1=1 then get:=chen(get,a);
   end;
 procedure kmp;
  begin 
      p[1]:=0;
       for i:=2 to m do begin 
	          j:=p[i-1];
			 while (a[j+1]<>a[i]) and (j>0) do j:=p[j];
	         if a[j+1]=a[i] then p[i]:=j+1;
        end;
   end;
	procedure make_matrix;
	 var
			 i,j,k:longint;
	 begin 
			fillchar(f,sizeof(f),0);
			 for i:=0 to m-1 do begin
				 for j:=0 to 9 do begin
					 k:=i; 
					 while (j<>a[k+1]) and (k>0) do k:=p[k];
					 if j=a[k+1] then inc(f[k+1,i]) else inc(f[0,i]);
				 end;
			 end;
	 end;
begin 
 readln(n,m,mo);
 for i:=1 to m do begin 
	 read(c);
     a[i]:=ord(c)-ord('0');
 end;
 kmp;make_matrix;
 f:=get(f,n);ans:=0;
 for i:=0 to m-1 do ans:=(ans+f[i,0]) mod mo;
 writeln(ans);
end.
Problem1010

type
 dot=record
    x,y:int64;
 end;
var
 n,l,a,top,tail,i:longint;
 k:dot;
 d:array[0..10000000]of dot;
 s,f:array[0..50000]of int64;
procedure ind(a:dot);
var
 i:longint;
 k,k1:dot;
begin
 if tail-top+1<2 then begin 
	  inc(tail);d[tail]:=a;exit;
 end;
 for i:=tail downto top+1 do begin 
	  k:=d[i];k1:=d[i-1];
      if  (a.y-k.y)/(a.x-k.x)>=(k.y-k1.y)/(k.x-k1.x) then begin 
		  tail:=i+1;d[tail]:=a;exit;
	  end;
 end;
 d[top+1]:=a;tail:=top+1;
end;
function outd(a:int64):dot;
var 
     i:longint;
	 k,k1:dot;
begin 
     for i:= top to tail-1 do begin 
		 k:=d[i];k1:=d[i+1];
		 if (k.y-k1.y)/(k.x-k1.x)>=a then begin 
			 top:=i;exit(k);
		 end;
	 end;
	 top:=tail;exit(d[top]);
end;
begin 
 readln(n,l);s[0]:=0;
 for i:=1 to n do begin 
	  readln(a);
     s[i]:=s[i-1]+a;
 end;
 k.x:=l+1;k.y:=k.x*k.x;
 top:=1;tail:=1;d[1]:=k;
 for i:=1 to n do begin
	 k:=outd((i+s[i])*2);
     f[i]:=k.y-k.x*(i+s[i])*2+(i+s[i])*(i+s[i]);
	 k.x:=l+1+i+s[i];k.y:=f[i]+k.x*k.x;ind(k);
 end;
 writeln(f[n]);
end.
Problem1010

{$inline on}
type
 dot=record
    x,y:int64;
 end;
var
 n,l,a,top,tail,i:longint;
 k:dot;
 d:array[0..10000000]of dot;
 s,f:array[0..50000]of int64;
procedure ind(a:dot);inline;
var
 i:longint;
 k,k1:dot;
begin
 if tail-top+1<2 then begin 
	  inc(tail);d[tail]:=a;exit;
 end;
 for i:=tail downto top+1 do begin 
	  k:=d[i];k1:=d[i-1];
      if  (a.y-k.y)/(a.x-k.x)>=(k.y-k1.y)/(k.x-k1.x) then begin 
		  tail:=i+1;d[tail]:=a;exit;
	  end;
 end;
 d[top+1]:=a;tail:=top+1;
end;
function outd(a:int64):dot;inline;
var 
     i:longint;
	 k,k1:dot;
begin 
     for i:= top to tail-1 do begin 
		 k:=d[i];k1:=d[i+1];
		 if (k.y-k1.y)/(k.x-k1.x)>=a then begin 
			 top:=i;exit(k);
		 end;
	 end;
	 top:=tail;exit(d[top]);
end;
begin 
 readln(n,l);s[0]:=0;
 for i:=1 to n do begin 
	  readln(a);
     s[i]:=s[i-1]+a;
 end;
 k.x:=l+1;k.y:=k.x*k.x;
 top:=1;tail:=1;d[1]:=k;
 for i:=1 to n do begin
	 k:=outd((i+s[i])*2);
     f[i]:=k.y-k.x*(i+s[i])*2+(i+s[i])*(i+s[i]);
	 k.x:=l+1+i+s[i];k.y:=f[i]+k.x*k.x;ind(k);
 end;
 writeln(f[n]);
end.
Problem1011

const 
 t=100;
var
 n,i,j,k:longint;
 a:extended;
 m:array[1..100000]of int64;
 f:array[1..100000]of extended;
begin 
 readln(n,a);
 for i:=1 to n do readln(m[i]);
 if n<=t then 
	 for i:=1 to n do begin 
		 f[i]:=0;
	     for j:=1 to trunc(a*i) do f[i]:=f[i]+m[i]*m[j]/(i-j);
	     writeln(f[i]:0:6);
	 end
 else begin 
	 for i:=1 to t do begin 
		 f[i]:=0;
	     for j:=1 to trunc(a*i) do  f[i]:=f[i]+m[i]*m[j]/(i-j);
	     writeln(f[i]:0:6);
	 end;
	 for i:=1 to n-t do begin 
		 f[i+t]:=f[i]/m[i]/(i+t-trunc(i*a)/2)*(i-trunc(i*a)/2);
	     for j:=trunc(i*a)+1 to trunc((i+t)*a) do f[i+t]:=f[i+t]+m[j]/(i+t-j);
		 f[i+t]:=f[i+t]*m[i+t];
		 writeln(f[i+t]:0:6);
	 end;
 end;
end.
Problem1012

var
 k:char;
 a,fa,h:array[1..200000]of longint;
 r,i,d,s,t,n,m:longint;
function father(u:longint):longint;
begin
 if fa[u]<>u then fa[u]:=father(fa[u]);
 exit(fa[u]);
end;
begin 
 readln(r,d);t:=0;n:=0;m:=0;
 for i:=1 to r do begin 
	 read(k);read(s);readln;
     if k='A' then begin
		 s:=(s+t) mod d;
	     inc(n);a[n]:=s;fa[n]:=n;
	     while (m>0) and (a[h[m]]<=a[n]) do begin 
		     fa[h[m]]:=n;dec(m);
		 end;
		 inc(m);h[m]:=n;
	 end else begin 
		 t:=a[father(n-s+1)];writeln(t);
	 end;
 end;
end.
Problem1013

type
 equ=array[1..21]of extended;
 //Equation
var 
 n,i,j,k:longint;
 m:array[1..21]of equ;
 a:array[1..21,1..21]of extended;
procedure init;
begin
 readln(n);
 for i:=1 to n+1 do begin 
	 for j:=1 to n do read(a[i,j]);
	 readln;
 end;
 for i:=1 to n do begin 
	 m[i,n+1]:=0;
	 for j:=1 to n do begin 
		  m[i,j]:=2*(a[i+1][j]-a[i][j]);m[i,n+1]:=m[i,n+1]+sqr(a[i+1][j])-sqr(a[i][j]);
	 end;
 end;
end;
procedure solve;
var
	 r,j:longint;
	 t:equ;
	 f:extended;
begin
     for i:=1 to n do begin 
		 {选择变量i绝对值较大的方程提高数值稳定性}
		 r:=i;
		 for j:=i+1 to n do if abs(m[j,i])>abs(m[r,i]) then r:=j;
		 if r<>i then begin t:=m[j];m[j]:=m[r];m[r]:=t;end;
		 //加减消元消去i
		 for j:=i+1 to n do begin 
			 f:=m[j,i]/m[i,i];
			 for k:=i to n+1 do m[j,k]:=m[j,k]-m[i,k]*f;
		 end;
	 end;
	 //回代
	 for i:=n downto 1 do begin 
		 for j:=i+1 to n do 
			 m[i,n+1]:=m[i,n+1]-m[j,n+1]*m[i,j];
		 m[i,n+1]:=m[i,n+1]/m[i,i];
	 end;
end;
procedure print;
begin
	 for i:=1 to n-1 do write(m[i][n+1]:0:3,' ');
	 writeln(m[n][n+1]:0:3);
end;
begin 
	init;
	solve;
	print; 
end.
Problem1014

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef unsigned int ui; 
using namespace std;
const int N=5010150;
int n;
ui g[N];
int l=0;
char s[N];
struct node{
    node *ch[2];
    int s,d;//size hash data
    ui h;
    int cmp(int &x){
        if (x== (ch[0]->s +1)) return -1;
        if (x<=ch[0]->s) return 0; else{
            x-=ch[0]->s+1;
            return 1;
        }
    }
    void upd(){
        h=((ui)ch[0]->h + (ui)g[ch[0]->s]*(ui)d) + (ui)g[(ch[0]->s) + 1]* (ui)(ch[1]->h);
        s=(ch[0]->s)+(ch[1]->s)+1;
    }
}t[N];
node *null,*root;
node* new_node(int d){
    node* s=&t[l++];
    s->ch[0]=s->ch[1]=null;
    s->s=1;s->h=s->d=d;
    return s;
}
void rotate(node* &o,int d){
    node* k=o->ch[d];
    o->ch[d]=k->ch[d^1];
    k->ch[d^1]=o;
    o->upd();k->upd();
    o=k;
}
void splay(node* &o,int k){
    int d1=o->cmp(k);
    if (d1!=-1){
        int d2=o->ch[d1]->cmp(k);
        if (d2!=-1){
            splay(o->ch[d1]->ch[d2],k);
            if (d1==d2) rotate(o,d1); else rotate(o->ch[d1],d2);
        }
        rotate(o,d1);               
    }
}
void build(node* &o,int l,int r){
    if (l>r) return;
    if (l==r){
        if (l==0 || l==n+1)  o=new_node(0); else o=new_node((int)(s[l-1]-'a'));//!
        return;
    }
    int mid=(l+r) >> 1;//[l,r]-->[l,mid-1] + mid +[r,mid+1]
    if(mid==0 || mid==n+1) o=new_node(0); else o=new_node((int)(s[mid-1]-'a'));//!
    build(o->ch[0],l,mid-1);build(o->ch[1],mid+1,r);
    o->upd();//!
}
ui hash(int a,int b){
    splay(root,a-1);
    splay(root->ch[1],b-a+2);//(b+1)-(a-1)
    return root->ch[1]->ch[0]->h;
}
void modify(int x,int d){
    splay(root,x);
    root->d=d;root->upd();
}
void insert(int x,int d){
    splay(root,x);
    splay(root->ch[1],1);//(x+1)-x
    root->ch[1]->ch[0]=new_node(d);
}   
void debug(node* o){
    if (o==null) return;
    debug(o->ch[0]);
    printf("%c",(char)((int)'a'+o->d));
    debug(o->ch[1]);
}
int main(){
    scanf("%s",s);n=strlen(s);
    g[0]=1;//g[i]=27^i % Mod
    rep(i,1,N-1) g[i]= (g[i-1]*27);
    null=&t[l++];
    null->ch[0]=null->ch[1]=null;
    null->s=0;null->h=null->d=0;
    root=null;
    build(root,0,n+1);
    int m;scanf("%d",&m);
    rep(t,1,m){
        char c=getchar();
        while (c=='\r' || c=='\n' || c==' ') c=getchar();
        if (c=='Q'){
            //debug(root);printf("\n");
            int a,b;scanf("%d%d",&a,&b);
            int ans=0;
            for(int i=1<<18;i;i>>=1)
                if (a+i-1<=n && b+i-1<=n && hash(a+1,a+i)==hash(b+1,b+i)) {
                    ans+=i;a+=i;b+=i;
                }
            printf("%d\n",ans);
        } else if (c=='R'){
            int x;scanf("%d",&x);
            char d=getchar();
            while (d=='\r' || d=='\n' || d==' ') d=getchar();
            modify(x+1,(int)d-'a');
        } else if (c=='I'){
            int x;scanf("%d",&x);
            char d=getchar();
            while (d=='\r' || d=='\n' || d==' ') d=getchar();
            insert(x+1,(int)d-'a');
            n++;//!
        }
    }
    return 0;
}
/*
  debug: 
  1.splay(o->ch[1],d) d要d-=o->ch[0]+1 important
  2.rep(i,1,n) g[i]= (g[i-1]*27);---->rep(i,1,N-1) silly
*/ 
Problem1015

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define ab(x) (x<0? -x : x)//abs
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
const int N=800000;
int u[N],l=0,f[N],ans[N],d[N];
struct edge{
	int to,pre;
}e[N];
void ins(int a,int b){
	e[++l]=(edge){b,u[a]};u[a]=l;
}
bool vis[N];
int find(int x){
	f[x]= (f[x]==x) ? x : find(f[x]);
	return f[x];
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	rep(i,1,m){
		int a,b;
		scanf("%d%d",&a,&b);a+=1;b+=1;
		ins(a,b);ins(b,a);
	}
	int t;scanf("%d",&t);int tmp=t;
	memset(vis,false,sizeof(vis));
	rep(i,1,t) {scanf("%d",&d[i]);d[i]+=1;vis[d[i]]=true;}
	rep(i,1,n) if (!vis[i]) d[++t]=i;
	rep(i,1,n) f[i]=i;
	int cnt=0;memset(vis,false,sizeof(vis));
	dep(i,t,1){
		vis[d[i]]=true;cnt++;
		for(int j=u[d[i]];j;j=e[j].pre)if (vis[e[j].to]){
			int qi=find(d[i]),qj=find(e[j].to);
			if (qi != qj){
				f[qi]=qj;cnt--;
			}
		}
		ans[i]=cnt;
	}
	printf("%d\n",ans[1]);
	rep(i,2,tmp+1) printf("%d\n",ans[i]);
	return 0;
}
Problem1016

#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define mod 31011
#define maxn 1000
#define maxm 2000
using namespace std;
struct edge{
	int a,b,c;
};
int sum;
edge e[maxm];
int f[maxn],a[maxm],t[maxm],k[maxn],l=0;
bool cmp(const edge &a,const edge &b){return a.c<b.c;}//const!
int find(int x){
	return (f[x]==x)?x:find(f[x]);
}
void dfs(int now,int r,int chosen,int k){
	if (chosen==k) sum++; else {
		if (now<=r) {
			int q=find(e[now].a),p=find(e[now].b);
			if (p!=q) {
				f[q]=p;dfs(now+1,r,chosen+1,k);
				f[q]=q;
			}
			dfs(now+1,r,chosen,k);
		}
	}
}
int main(){
	int n,m,i;
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++) f[i]=i;
	for (i=1;i<=m;i++) scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].c);
	sort(e+1,e+m+1,cmp);
	int cnt=0;
	for (i=1;i<=m; 	i++){
		if (e[i].c==e[i-1].c && l>0) t[l]++ ;else {a[++l]=i;t[l]=0;}
		int q=find(e[i].a),p=find(e[i].b);
		if (p!=q){ f[q]=p;k[l]++;cnt++;}
	}
	if (cnt!=n-1){cout <<0;return 0;} 
	for (i=1;i<=n;i++) f[i]=i;
	int ans=1;
	for (i=1;i<=l;i++) {
		sum=0;
		dfs(a[i],a[i]+t[i],0,k[i]);
		ans*=sum;ans%=mod;
		for (int j=a[i];j<=a[i]+t[i];j++)
		{
			int p=find(e[j].a),q=find(e[j].b);
			if (p!=q) f[q]=p;
		}
	}
	cout <<ans;
	return 0;
}
Problem1017

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 52, M = 2010, NUM = 110;
int f[N][NUM][M], g[N][M], w[N];
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
typedef pair<int, int> node;
typedef vector<node>::iterator vit;
vector<node> son[N];
char tp[N];
int cost[N], num[N], n, m, fa[N], ans = 0;
void init(){
	rep(i,1,n) if (tp[i] == 'B')
		rep(j,0,num[i]){
			int ed = m - j * cost[i];
			rep(k,0,ed) f[i][j][k] =min(k / cost[i], num[i] - j) * w[i], ans = max(ans, f[i][j][k]);
		}
}
#define reg(i,x) for(vit i = son[x].begin(); i != son[x].end(); i++)
#define v ((*i).first)
#define vm ((*i).second)
void dp(int x){
	if (tp[x] == 'B') return;
	num[x] = NUM;
	reg(i,x) dp(v), num[x] = min(num[x], num[v] / vm), cost[x] += cost[v] * vm;

	//calc
	rep(j,0,num[x]){
		//calc_g
		int t = 0;
		reg(i,x){
			++t;
			rep(k,0,m - cost[x] * j){
				g[t][k] = 0;
				rep(t1, 0, k)
					g[t][k] = max(g[t][k], g[t - 1][k - t1] + f[v][j * vm][t1]);
			}
		}
		//calc_f
		rep(i,0,j) 
			rep(k,0,m - cost[x] * j) 
				f[x][i][k + (j - i) * cost[x]] = max(f[x][i][k + (j - i) * cost[x]], g[t][k] + (j - i) * w[x]), ans = max(ans, f[x][i][k + (j - i) * cost[x]]);
	}
}
int main(){
	scanf("%d %d",&n, &m);
	rep(i,1,n){
		scanf("%d ",&w[i]);
		tp[i] = getchar();
		while (tp[i] != 'A' && tp[i] != 'B') tp[i] = getchar();
		if (tp[i] == 'A'){
			int c; scanf("%d",&c);
			rep(j,1,c) {
				int t1, t2; scanf("%d %d", &t1, &t2);
				son[i].pb(mp(t1, t2));
				fa[t1] = i;
			}
		}else
			scanf("%d %d", &cost[i], &num[i]);
	}
	init();
	rep(i,1,n) if (!fa[i]) dp(i);
	printf("%d\n",ans);
}
Problem1018

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#define maxn 100100
using namespace std;
bool rx[2][maxn];
struct node{
	bool a[4][4];
	/*
		0 2
		1 3
	*/
};
node T[maxn*4];
bool change_x,change_x_value;
bool calc(node &lc, node &rc, int mid, int s, int t){
	return (lc.a[s][2] && rx[0][mid] && rc.a[0][t]) || (lc.a[s][3] && rx[1][mid] && rc.a[1][t]);
}
void upd(node &o,node &lc, node &rc,int mid){
	o.a[0][2]=calc(lc,rc,mid,0,2);
	o.a[0][3]=calc(lc,rc,mid,0,3);
	o.a[1][2]=calc(lc,rc,mid,1,2);
	o.a[1][3]=calc(lc,rc,mid,1,3);
	o.a[0][1]=lc.a[0][1] || (lc.a[0][2] && rx[0][mid] && rc.a[0][1] && rx[1][mid] && lc.a[1][3]);
	o.a[2][3]=rc.a[2][3] || (rc.a[0][2] && rx[0][mid] && lc.a[2][3] && rx[1][mid] && rc.a[1][3]); 
}
void insert(int x,int l,int r,int d){
	if (l==r) {
		T[x].a[0][2]=T[x].a[1][3]=true;
		if (change_x){
			T[x].a[0][3]=T[x].a[1][2]=T[x].a[0][1]=T[x].a[2][3]=change_x_value;
		}
		return;
	}
	int mid=(l+r) >> 1,lc=x << 1,rc=(x << 1)+1;
	if (d<=mid) insert(lc,l,mid,d); else insert(rc,mid+1,r,d);
	upd(T[x],T[lc],T[rc],mid); 
}
node querry(int x,int l,int r,int a,int b){
	if (a<=l && b>=r) return T[x];
	int mid=(l+r) >> 1,lc=x << 1,rc=(x << 1)+1;
	node ans;
	if (a>mid) ans=querry(rc,mid+1,r,a,b);
	else if (b<=mid) ans=querry(lc,l,mid,a,b);
	else {
	    node t1=querry(lc,l,mid,a,b),t2=querry(rc,mid+1,r,a,b);
		upd(ans,t1,t2,mid);
	}
	return ans;
}
void build(int x,int l,int r){
	if (l==r){T[x].a[0][2]=T[x].a[1][3]=true;T[x].a[0][1]=T[x].a[0][3]=T[x].a[1][2]=T[x].a[2][3]=false;return;}
	int mid=(l+r) >> 1,lc=x << 1,rc=(x << 1)+1;
	build(lc,l,mid);build(rc,mid+1,r);
	T[x].a[0][2]=T[x].a[1][3]=T[x].a[0][1]=T[x].a[0][3]=T[x].a[1][2]=T[x].a[2][3]=false;
}
int main(){
	int n;
	scanf("%d",&n);
	build(1,1,n);
	memset(rx,false,sizeof(rx));
	for (;;){
		char s;
		int a,b,c,d;
		s=getchar();
		while (s=='\n' || s==' ' || s=='\r') s=getchar();
		if (s=='E') break;
		while (getchar()!=' ');
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if (s=='O') {
			if (a==c){
				rx[a-1][b]=true;
				change_x=false;
				insert(1,1,n,b);
			} else if (b==d){
				change_x=change_x_value=true;
				insert(1,1,n,b);
			}
		} else if (s=='A'){
			if (b>d){
				int t=a;a=c;c=t;
				t=b;b=d;d=t;
			}
			node m=querry(1,1,n,b,d);
			if (m.a[a-1][c+1]) printf("Y\n"); else { 
				node l=querry(1,1,n,1,b),r=querry(1,1,n,d,n);
				bool l_1=l.a[2][3] || m.a[0][1];//(a-1)^1
				bool r_1=r.a[0][1] || m.a[2][3];//(c+1)^1
				if ((m.a[ (a-1) ^ 1 ][ (c+1) ^ 1 ] && l_1 && r_1) || (m.a[a-1][(c+1) ^ 1] &&  r_1) || (m.a[(a-1)^1][c+1] && l_1)) printf("Y\n"); else printf("N\n");
			}
		} else if (s=='C'){
			if (a==c){
				rx[a-1][b]=change_x=false;
				insert(1,1,n,b);
			} else if (b==d){
				change_x=true;
				change_x_value=false;
				insert(1,1,n,b);
			}

		}
	}
	return 0;
}
Problem1022

var
 T,i,n,a,ans:longint;
procedure work;
var
 i:longint;
 flag:boolean;
begin 
 readln(n);flag:=false;ans:=0;
 for i:=1 to n do begin 
   read(a);
	 if a>1 then flag:=true;
	 ans:=ans xor a;
 end;
 if not flag then begin 
   if odd(n) then writeln('Brother') else writeln('John');
 end else begin 
	 if ans<>0 then writeln('John') else writeln('Brother');
 end;
end;
begin 
 readln(T);
 for i:=1 to T do work;
end.
Problem1024

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const double eps = 0.00000001;
double ab(double x){
	return x > 0 ? x : -x;
}
double dfs(double x,double y,double a,int n){
	if (ab(x * y - a) < eps) return max(x,y) / min(x,y);
	double ans = 100000000000;
	rep(i,1,n/2) ans = min(ans, max(dfs(a / y * i, y, a, i), dfs(x - a / y * i, y, a, n - i)));
	rep(i,1,n/2) ans = min(ans, max(dfs(x, a / x * i, a, i), dfs(x, y - a / x * i, a, n - i)));
	return ans;
}
int main(){
	int x,y,n; scanf("%d%d%d",&x,&y,&n);
	printf("%.6lf",dfs((double)x, (double)y, ((double)x * y)/n, n));
}
Problem1025

var
 n,i,j,l,k:longint;
 p:array[1..1000]of longint;
 f:array[0..1000,0..1000]of int64;
 a:array[1..1000]of boolean;
procedure init;
var
 i,j:longint;
begin 
 fillchar(a,sizeof(a),true);l:=0;
 for i:=2 to n do begin 
     if a[i] then begin 
	     inc(l);p[l]:=i;
	 end;
	 for j:=1 to l do begin 
	     if p[j]*i>n then break;
		 a[p[j]*i]:=false;
		 if i mod p[j]=0 then break;
	 end;
 end;
end;
begin 
 readln(n);
 init;for i:=0 to n do f[0,i]:=1;
 for i:=1 to l do begin 
     k:=p[i];
     f[i]:=f[i-1];
	 while k<=n do begin 
	    for j:=k to n do f[i,j]:=f[i,j]+f[i-1,j-k];
		k:=k*p[i];
     end;
 end;
 writeln(f[l,n]);
end.
Problem1026

uses math;
var
 m:array[1..12]of longint;
 a,b,l,i,j,k,ans1,ans2:longint;
 f:array[0..12,0..9]of longint;
begin
 readln(a,b);l:=0;fillchar(f,sizeof(f),0);
 inc(b);
 while b>0 do begin
	 inc(l);m[l]:=b mod 10;b:=b div 10; 
 end; 
 for i:=l downto 2 do 
	 if abs(m[i]-m[i-1])<2 then begin 
		 m[i-1]:=max(0,m[i]-1);
		 for j:=i-2 downto 1 do m[j]:=0;
		 break;
	 end;
 for i:=0 to 9 do f[1,i]:=1;
 for i:=2 to l do
     for j:=0 to 9 do 
		 for k:=0 to 9 do 
		     if abs(k-j)>=2 then f[i,j]:=f[i,j]+f[i-1,k]; 
 ans1:=-f[l,0];
 for i:=l downto 1 do begin  
		 for k:=0 to m[i]-1 do begin
			 if i<>l then if abs(k-m[i+1])<2 then continue;
			 ans1:=ans1+f[i,k];
		 end;
		 if i<>l then for k:=1 to 9 do ans1:=ans1+f[i,k];
 end;
 l:=0;ans2:=ans1;
 while a>0 do begin
	 inc(l);m[l]:=a mod 10;a:=a div 10; 
 end; 
 for i:=l downto 2 do 
	 if abs(m[i]-m[i-1])<2 then begin 
		 m[i-1]:=max(0,m[i]-1);
		 for j:=i-2 downto 1 do m[j]:=0;
		 break;
	 end;
 ans1:=-f[l,0];
 for i:=l downto 1 do begin  
		 for k:=0 to m[i]-1 do begin
			 if i<>l then if abs(k-m[i+1])<2 then continue;
			 ans1:=ans1+f[i,k];
		 end;
		 if i<>l then for k:=1 to 9 do ans1:=ans1+f[i,k];
 end;
 writeln(ans2-ans1);
end.
Problem1026

uses math;
var
 flag:boolean;
 m:array[1..12]of longint;
 a,b,l,i,j,k,ans1,ans2:longint;
 f:array[0..12,0..9]of longint;
begin
 readln(a,b);l:=0;fillchar(f,sizeof(f),0);
 inc(b);flag:=true;
 while b>0 do begin
	 inc(l);m[l]:=b mod 10;b:=b div 10; 
 end; 
 for i:=0 to 9 do f[1,i]:=1;
 for i:=2 to l do
     for j:=0 to 9 do 
		 for k:=0 to 9 do 
		     if abs(k-j)>=2 then f[i,j]:=f[i,j]+f[i-1,k]; 
 ans1:=-f[l,0];
 for i:=l downto 1 do begin  
		 if flag then for k:=0 to m[i]-1 do begin
			 if i<>l then if abs(k-m[i+1])<2 then continue;
			 ans1:=ans1+f[i,k];
		 end;
	     if (i<l) and (abs(m[i]-m[i+1])<2) then flag:=false;
		 if i<>l then for k:=1 to 9 do ans1:=ans1+f[i,k];
 end;
 l:=0;ans2:=ans1;
 while a>0 do begin
	 inc(l);m[l]:=a mod 10;a:=a div 10; 
 end; 
 for i:=l downto 2 do 
	 if abs(m[i]-m[i-1])<2 then begin 
		 m[i-1]:=max(0,m[i]-1);
		 for j:=i-2 downto 1 do m[j]:=0;
		 break;
	 end;
 ans1:=-f[l,0];flag:=true;
 for i:=l downto 1 do begin 
		 if flag then for k:=0 to m[i]-1 do begin
			 if i<>l then if abs(k-m[i+1])<2 then continue;
			 ans1:=ans1+f[i,k];
		 end;
	     if (i<l) and (abs(m[i]-m[i+1])<2) then flag:=false;
		 if i<>l then for k:=1 to 9 do ans1:=ans1+f[i,k];
 end;
 writeln(ans2-ans1);
end.
Problem1027

const eps=1e-8;
type point=record x,y:double;end;
var
  a,b:array[1..1000]of point;
  g:array[1..1000,1..1000]of longint;
  i,j,n,m,ans:longint;
operator -(a1,a2:point)res:point;
begin
 res.x:=a1.x-a2.x;
 res.y:=a1.y-a2.y;
end;
operator *(a1,a2:point)res:double;
begin
 res:=a1.x*a2.y-a1.y*a2.x;
end;
procedure init;
var
  tmp:double;
begin
 readln(n,m);
 for i:=1 to n do
  readln(a[i].x,a[i].y,tmp);
 for i:=1 to m do
  readln(b[i].x,b[i].y,tmp);
end;
function ok(j,k:longint):boolean;
var
  i:longint;
  t1,t2:point;
begin
 for i:=1 to m do
  begin
   t1:=a[j]-a[k];
   t2:=b[i]-a[k];
   if t1*t2>eps then exit(false);
                if abs(t1*t2)<eps then
                 begin
                  if (b[i].x>a[j].x)and(b[i].x>a[k].x) then exit(false);
                  if (b[i].x<a[j].x)and(b[i].x<a[k].x) then exit(false);
                  if (b[i].y>a[j].y)and(b[i].y>a[k].y) then exit(false);
                  if (b[i].y<a[j].y)and(b[i].y<a[k].y) then exit(false);
                 end;
  end;
 ok:=true;
end;
procedure floyd;
var
  i,j,k:longint;
begin
 for k:=1 to n do
  for i:=1 to n do
   for j:=1 to n do
    if g[i,k]+g[k,j]<g[i,j] then g[i,j]:=g[i,k]+g[k,j];
end;
procedure main;
var
    flag:boolean;
begin
        for i:=1 to n do
         begin
           flag:=true;
           for j:=1 to m do
            if (abs(a[i].x-b[j].x)>eps)or(abs(a[i].y-b[j].y)>eps) then
             begin
               flag:=false;
               break;
             end;
           if flag then
            begin
              writeln(1);exit;
            end;
         end;
 for i:=1 to n do for j:=1 to n do g[i,j]:=10000000;
 for i:=1 to n do
  for j:=i+1 to n do
  begin
   if ok(i,j) then g[i,j]:=1;
   if ok(j,i) then g[j,i]:=1;
  end;
 floyd;
 ans:=maxlongint;
 for i:=1 to n do
  for j:=1 to n do
   begin
                if i<>j then
     if ans>g[i,j]+g[j,i] then ans:=g[i,j]+g[j,i];
   end;
  if ans<10000000 then writeln(ans)
  else writeln(-1);
end;
begin
  init;
  main;
end.
Problem1027

 const
    eps=1e-8;
 type 
 dot=record 
     x,y:extended;
 end;
var
 flag:boolean;
 i,j,t,min,n,m:longint;
 f:array[1..500,1..500]of longint;
 a,b:array[1..500]of dot;
operator /(a,b:dot)res:dot;
begin 
 res.x:=a.x-b.x;
 res.y:=a.y-b.y;
end;
operator <<(a,b:dot)res:extended;
begin 
 res:=(a.x*b.y-b.x*a.y);
end;
function check(i,j:longint):boolean;
var
 k1,k2:dot;
 k:longint;
 flag:boolean;
begin 
 for k:=1 to n do begin 
     k1:=a[i] / a[j];k2:=b[k] / a[j];
	 if k1 << k2<-eps then exit(false);
	 if k1 << k2< eps then begin 
        if (a[i].x<b[k].x) and (a[j].x<b[j].x) then exit(false);
        if (a[i].y<b[k].y) and (a[j].y<b[j].y) then exit(false);
        if (a[i].x>b[k].x) and (a[j].x>b[j].x) then exit(false);
        if (a[i].y>b[k].y) and (a[j].y>b[j].y) then exit(false);
     end;
 end;
 exit(true);
end;
procedure floyd;
var
 i,j,k:longint;
begin 
 for k:=1 to m do 
     for i:=1 to m do begin
         if f[i,k]=0 then continue;	 
	     for j:=1 to m do begin		 
		     if f[k,j]=0 then continue;
			 if (f[i,k]+f[k,j]<f[i,j]) or (f[i,j]=0) then f[i,j]:=f[i,k]+f[k,j];
		 end;
	 end;
end;
begin 
 readln(m,n);
 for i:=1 to m do readln(a[i].x,a[i].y);
 for i:=1 to n do readln(b[i].x,b[i].y);
 for i:=1 to m do begin 
     flag:=true;
     for j:=1 to n do begin 
	     if (abs(a[i].x-b[j].x)>eps) or (abs(a[i].y-b[j].y)>eps) then begin flag:=false;break;end;
	 end;
	 if flag then begin writeln(1);halt;end; 
 end;
 fillchar(f,sizeof(f),0);
 for i:=1 to m do begin 
     for j:=i+1 to m do begin 
	     if check(i,j) then f[i,j]:=1;
		 if check(j,i) then f[j,i]:=1;
	 end;
 end;
 floyd;
 min:=maxlongint;
 for i:=1 to m do if (f[i,i]>0) and (f[i,i]<min) then min:=f[i,i];
 if min=maxlongint then writeln(-1) else writeln(min);
end.
Problem1029

	var
	 n,i,ans,l:longint;
	 T:longint;
	 a,b,h:array[1..300000]of longint;
	procedure sort(l,r:longint);
	var
	 m,i,j,t:longint;
	begin
	 m:=b[(l+r) div 2];
	 i:=l;j:=r;
	 repeat
		while b[i]<m do inc(i);
		while b[j]>m do dec(j);
		if i<=j then begin 
			t:=a[i];a[i]:=a[j];a[j]:=t;
			t:=b[i];b[i]:=b[j];b[j]:=t;
			inc(i);dec(j);
		end;
	 until i>j;
	 if l<j then sort(l,j);
	 if i<r then sort(i,r);
	end;
	function check(a,b:longint):boolean;
	begin
	 if (a=0) or (b>l) then exit(false);
	 if h[b]>h[a] then exit(true) else exit(false);
	end;
	procedure swap(var a,b:longint);
	var  
	 c:longint;
	begin
	 c:=a;a:=b;b:=c; 
	end;
	procedure add(x:longint);
	var
	 i:longint;
	begin 
	 inc(l);h[l]:=x;i:=l;
	 while check(i shr 1,i) do begin 
		 swap(h[i shr 1],h[i]);i:=i shr 1;
	 end;
	end;
	procedure setas(x:longint);
	var
	 lc,rc,i:longint;
	begin 
	 h[1]:=x;
	 i:=1;lc:=i shl 1;rc:=lc+1;
	 while check(i,lc) or check(i,rc) do begin 
		 if check(lc,rc) then begin 
			 swap(h[i],h[rc]);i:=rc;
		 end else begin
			 swap(h[i],h[lc]);i:=lc;
		 end;
		 lc:=i shl 1;rc:=lc+1;
	 end;
	end;
	begin
	 readln(n);
	 for i:=1 to n do readln(a[i],b[i]);
	 sort(1,n);T:=0;ans:=0;l:=0;
	 for i:=1 to n do
		 if T+a[i]<=b[i] then begin 
			 T:=T+a[i];add(a[i]);inc(ans);
		 end else begin 
			 if l=0 then continue;
			 if (h[1]>a[i]) and (T-h[1]+a[i]<=b[i]) then begin 
				 T:=T-h[1]+a[i];setas(a[i]);
			 end;
		 end;
	 writeln(ans);
	end.
Problem1030

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=9010,M=10007;
struct node{
	node *ch[26],*f;
	int v,num,l;
}T[N],*root,*null;
int l=0;
node *nw(){
	node *k=&T[++l];k->num=l;return k;
}

#define oc o->ch[c[i]-'A']
void ins(char *c,int v){
	node *o=root;int n=strlen(c);
	rep(i,0,n-1) {
		if (!oc) oc=nw();
		o=oc;
	}
	o->v=v;
}

node *q[N];
#define xc x->ch[i]
#define xf x->f
#define xcf xc->f
void getfail(){
	int l=0,r=0;node *x=root;root->f=root;
	rep(i,0,25) if (!xc) xc=root; else q[r++]=xc,xcf=root,xc->l=xc->v;//!
	while (l<r){
		x=q[l++];
		rep(i,0,25) 
			if (!xc) xc=xf->ch[i]; else 
				q[r++]=xc,xcf=xf->ch[i],xc->l=(xc->v) || (xcf->l);
	}
}	

char c[110];
int f[110][N];
int main(){
	null=&T[0];root=nw();
	int n,m;scanf("%d%d",&n,&m);
	rep(i,1,n){
		scanf("%s",c);
		ins(c,1);
	}
	getfail();
	f[0][1]=1;	
	rep(i,0,m-1)
		rep(j,1,l) if (!T[j].l)
			rep(k,0,25) 
				f[i+1][T[j].ch[k]->num]+=f[i][j],
				f[i+1][T[j].ch[k]->num]%=M;
	int ans=1;
	rep(i,1,m) ans*=26,ans%=M;
	int ans2=0;
	rep(j,1,l) if (!T[j].l) ans2+=f[m][j],ans2%=M;
	printf("%d\n",(ans-ans2+M)%M);
	return 0;
}
Problem1030

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=9010,M=10007;
struct node{
    node *ch[26],*f;
    int v,num;
}T[N],*root,*null;
int l=0;
node *nw(){
    node *k=&T[++l];k->num=l;return k;
}
 
#define oc o->ch[c[i]-'A']
void ins(char *c,int v){
    node *o=root;int n=strlen(c);
    rep(i,0,n-1) {
        if (!oc) oc=nw();
        o=oc;
    }
    o->v=1;
}
 
node *q[N];
#define xc x->ch[i]
#define xf x->f
#define xcf xc->f
void getfail(){
    int l=0,r=0;node *x=root;root->f=root;
    rep(i,0,25) if (!xc) xc=root; else q[r++]=xc,xcf=root;//!
    while (l<r){
        x=q[l++];
        rep(i,0,25) 
            if (!xc) xc=xf->ch[i]; else
                q[r++]=xc,xcf=xf->ch[i],xc->v=(xc->v) || (xcf->v);
    }
}   
 
char c[110];
int f[110][N];
int main(){
    null=&T[0];root=nw();
    int n,m;scanf("%d%d",&n,&m);
    rep(i,1,n){
        scanf("%s",c);
        ins(c,1);
    }
    getfail();
    f[0][1]=1;  
    rep(i,0,m-1)
        rep(j,1,l) if (!T[j].v)
            rep(k,0,25) 
                f[i+1][T[j].ch[k]->num]+=f[i][j],
                f[i+1][T[j].ch[k]->num]%=M;
    int ans=1;
    rep(i,1,m) ans*=26,ans%=M;
    int ans2=0;
    rep(j,1,l) if (!T[j].v) ans2+=f[m][j],ans2%=M;
    printf("%d\n",(ans-ans2+M)%M);
    return 0;
}
Problem1031

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=200100;
char s[N];
int n,t[N],t1[N],c[N],sa[N];
void buildsa(int m){
	int *x=t,*y=t1;
	rep(i,0,m-1) c[i]=0;
	rep(i,0,n-1) c[x[i]=s[i]]++;
	rep(i,1,m-1) c[i]+=c[i-1];
	rep(i,0,n-1) sa[--c[x[i]]]=i;
	for(int k=1;k<=n;k<<=1){
		int p=0;
		rep(i,n-k,n-1) y[p++]=i;
		rep(i,0,n-1) if (sa[i]>=k) y[p++]=sa[i]-k;
		rep(i,0,m-1) c[i]=0;
		rep(i,0,n-1) c[x[y[i]]]++;
		rep(i,1,m-1) c[i]+=c[i-1];
		dep(i,n-1,0) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=1, x[sa[0]]=0;
		rep(i,1,n-1)
			x[sa[i]]= y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]?p-1:p++;
		if (p>=n) break;
		m=p;
	}
}
int main(){
	scanf("%s",s);n=strlen(s);
	rep(i,0,n-1) s[n+i]=s[i];
	n<<=1;
	buildsa(256);
	rep(i,0,n-1) if (sa[i]<(n >> 1)) 
		printf("%c",s[sa[i]+(n>>1)-1]);
	return 0;
}
Problem1031

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=200100;
char s[N];
int n,t[N],t1[N],c[N],sa[N];
void buildsa(int m){
	int *x=t,*y=t1;
	rep(i,0,m-1) c[i]=0;
	rep(i,0,n-1) c[x[i]=s[i]]++;
	rep(i,1,m-1) c[i]+=c[i-1];
	dep(i,n-1,0) sa[--c[x[i]]]=i;
	for(int k=1;k<=n;k<<=1){
		int p=0;
		rep(i,n-k,n-1) y[p++]=i;
		rep(i,0,n-1) if (sa[i]>=k) y[p++]=sa[i]-k;
		rep(i,0,m-1) c[i]=0;
		rep(i,0,n-1) c[x[y[i]]]++;
		rep(i,1,m-1) c[i]+=c[i-1];
		dep(i,n-1,0) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=1, x[sa[0]]=0;
		rep(i,1,n-1)
			x[sa[i]]= y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]?p-1:p++;
		if (p>=n) break;
		m=p;
	}
}
int main(){
	scanf("%s",s);n=strlen(s);
	rep(i,0,n-1) s[n+i]=s[i];
	n<<=1;
	buildsa(256);
	rep(i,0,n-1) if (sa[i]<(n >> 1)) 
		printf("%c",s[sa[i]+(n>>1)-1]);
	return 0;
}
Problem1034

type
  arr=array[1..100000]of longint;
var
 n,i:longint;
 a,b:arr;
procedure sort(var a:arr;l,r:longint);
var
 i,j,t,m:longint;
begin
  i:=l;j:=r;m:=a[(l+r) shr 1];
  repeat
   while a[i]<m do inc(i);
   while a[j]>m do dec(j);
   if i<=j then begin 
     t:=a[i];a[i]:=a[j];a[j]:=t;
	 inc(i);dec(j);
   end;
  until i>j;
  if l<j then sort(a,l,j);
  if i<r then sort(a,i,r);
end;
function work(a,b:arr):longint;
var
 ia,ja,ib,jb,i:longint;
begin
  work:=0;
  ia:=1;ja:=n;ib:=1;jb:=n;
  for i:=1 to n do begin
     if a[ia]>b[ib] then begin work:=work+2;ia:=ia+1;ib:=ib+1;continue;end;
   	 if a[ja]>b[jb] then begin work:=work+2;ja:=ja-1;jb:=jb-1;continue;end;
	 if a[ia]=b[jb] then inc(work);//attention!
	 inc(ia);dec(jb);
  end;
end;
begin 
 readln(n);
 for i:=1 to n do readln(a[i]);
 for i:=1 to n do readln(b[i]);
 sort(a,1,n);sort(b,1,n);
 writeln(work(a,b),' ',n*2-work(b,a));
end.
Problem1036

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
using namespace std;
const int N=50000;
const int inf=30001;
struct edge{
	int to,pre;
}e[N*2];
int l=0;
int u[N],w[N],top[N],vis[N],dep[N],size[N],son[N],fa[N];
#define lch (x << 1)
#define rch (lch+1)
#define mid ((l+r) >> 1)
#define lc lch,l,mid
#define rc rch,mid+1,r
struct sgt{
	int size;
	int s[N*4+1],mx[N*4+1];
	void upd(int x){
		s[x]=s[lch]+s[rch];mx[x]=max(mx[lch],mx[rch]);
	}
	void modify(int x,int l,int r,int a,int d){
		if (l==r) s[x]=mx[x]=d;else{
			if (a<=mid) modify(lc,a,d); else modify(rc,a,d);
			upd(x);//!
		}
	}
	void modi(int x,int y){
		modify(1,1,size,x,y);
	}
	int querry_sum(int x,int l,int r,int a,int b){
		if (a<=l && b>=r) return s[x];
		int ans=0;
		if (a<=mid) ans+=querry_sum(lc,a,b);
		if (b> mid) ans+=querry_sum(rc,a,b);
		return ans; 
	}
	int q_s(int a,int b){
		return querry_sum(1,1,size,a,b);
	}
	int querry_max(int x,int l,int r,int a,int b){
		if (a<=l && b>=r) return mx[x];
		int ans=-inf;
		if (a<=mid) ans=max(ans,querry_max(lc,a,b));
		if (b> mid) ans=max(ans,querry_max(rc,a,b));
		return ans;
	}
	int q_m(int a,int b){
		return querry_max(1,1,size,a,b);
	}
}s;
void ins(int a,int b){
	e[++l]=(edge){b,u[a]};u[a]=l;
}
void dfs(int x){
	size[x]=1,son[x]=0;
	reg(i,x) if (v != fa[x]) {
			dep[v] =dep[x]+1;fa[v]=x;
			dfs(v);size[x]+=size[v];
			if (size[v]>size[son[x]]) son[x]=v;
	}
}
int dfs_clock=0;
void build(int x){
	vis[x]=++dfs_clock;
	if (son[x]!=0) {
		top[son[x]]=top[x];
		build(son[x]);
	}
	reg(i,x) if (v!=fa[x] && v!=son[x]){
			top[v]=v;build(v);
	}
}
void ask_sum(int a,int b){
	int ta=top[a],tb=top[b],ans=0;
	while (ta!=tb){
		if (dep[ta]<dep[tb]){
			swap(a,b);swap(ta,tb);
		}
		ans+=s.q_s(vis[ta],vis[a]);
		a=fa[ta];ta=top[a];
	}
	if (dep[a]>dep[b]) swap(a,b);
	ans+=s.q_s(vis[a],vis[b]);
	printf("%d\n",ans);
}
void ask_max(int a,int b){
	int ta=top[a],tb=top[b],ans=-inf;
	while (ta!=tb){
		if (dep[ta]<dep[tb]){
			swap(a,b);swap(ta,tb);
		}
		ans=max(ans,s.q_m(vis[ta],vis[a]));
		a=fa[ta];ta=top[a];
	}
	if (dep[a]>dep[b]) swap(a,b);
	ans=max(ans,s.q_m(vis[a],vis[b]));
	printf("%d\n",ans);
}
char st[100];
int main(){
	int n;scanf("%d",&n);
	s.size=n;
	rep(i,1,n) dep[i]=0,vis[i]=0;
	size[0]=0;
	rep(i,1,n-1){
		int a,b;scanf("%d%d",&a,&b);
		ins(a,b);ins(b,a);
	}
	dep[1]=1;dfs(1);fa[1]=1;
	top[1]=1;build(1);
	rep(i,1,n) {
		scanf("%d",&w[i]);
		s.modi(vis[i],w[i]);
	}
	int m;scanf("%d",&m);
	rep(i,1,m){
		int a,b;
		scanf("%s%d%d",st,&a,&b);
		if (st[0]=='C') s.modi(vis[a],b);
		else if (st[1]=='S') ask_sum(a,b);
		else ask_max(a,b);
	}
	return 0;
}
Problem1040

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
const int N=1100000,M=2*N;
struct edge{
	int to,pre;
}e[M];
int l=1;
int u[N];
void ins(int a,int b){
	e[++l]=(edge){b,u[a]};u[a]=l;
}
void insert(int a,int b){
	ins(a,b);ins(b,a);
}
int a[N],vis[N],fa[N],a1,b1,R;
LL f[N][2];
void dfs(int x){
	vis[x]=1;
	reg(i,x) if (!vis[v]){
		fa[v]=x;dfs(v);
	}else if (fa[x]!=v){
		a1=x, b1=v;
	}
}
int calc[N];
void sol(int x){
	f[x][0]=0,f[x][1]=a[x];calc[x]=1;
	reg(i,x) if (fa[v]==x && calc[v]==0){
		sol(v);
		f[x][0]+=max(f[v][0],f[v][1]);
		f[x][1]+=f[v][0];
	}
	if (R==x) f[x][1]=0;
}
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n) u[i]=0;
	rep(i,1,n){
		int b;scanf("%d%d",&a[i],&b);
		insert(i,b);
	}
	rep(i,1,n) vis[i]=0;
	LL ans=0;
	rep(i,1,n) if (!vis[i]){
		a1=-1;
		dfs(i);
		R=a1;
		rep(j,1,n) calc[j]=0;
		sol(i);
		LL t1=max(f[i][0],f[i][1]);
		R=b1;
		rep(j,1,n) calc[j]=0;
		sol(i);
		LL t2=max(f[i][0],f[i][1]);
		ans+=max(t1,t2);
	}
	cout <<ans<<endl;
}
Problem1042

const
 max_s=100000;
var
 s,tot,i:longint; 
 c,d:array[1..5]of longint;
 f:array[0..max_s] of int64;
procedure dp;
var
 i,j:longint;
begin 
 f[0]:=1;
 for i:=1 to 4 do
     for j:=0 to max_s do  
	     if j-c[i]>=0 then f[j]:=f[j]+f[j-c[i]];
end;
procedure work;
var
 ans:int64;
 i,j,k:longint;
begin 
 ans:=0;
 readln(d[1],d[2],d[3],d[4],s);
 ans:=f[s];
 for i:=1 to 4 do begin 
     if s-(d[i]+1)*c[i]<0 then continue;
	 ans:=ans-f[s-(d[i]+1)*c[i]];
 end;
 for i:=1 to 4 do  
    for j:=i+1 to 4 do begin 
       if s-(d[i]+1)*c[i]-(d[j]+1)*c[j]<0 then continue;ans:=ans+f[s-(d[i]+1)*c[i]-(d[j]+1)*c[j]];
 end;
 for i:=1 to 4 do 
    for j:=i+1 to 4 do 
      for k:=j+1 to 4 do begin 
	     if s-(d[i]+1)*c[i]-(d[j]+1)*c[j]-(d[k]+1)*c[k]<0 then continue;
       	 ans:=ans-f[s-(d[i]+1)*c[i]-(d[j]+1)*c[j]-(d[k]+1)*c[k]]; 
       end;
 if s-(d[1]+1)*c[1]-(d[2]+1)*c[2]-(d[3]+1)*c[3]-(d[4]+1)*c[4]>=0 then ans:=ans+f[s-(d[1]+1)*c[1]-(d[2]+1)*c[2]-(d[3]+1)*c[3]-(d[4]+1)*c[4]];
 writeln(ans); 
end;
begin 
 readln(c[1],c[2],c[3],c[4],tot);
 dp;
 for i:=1 to tot do work;
end.
Problem1045

#include <iostream>
#include <cstdio>
#include <algorithm>
#define ab(a) ((a) < 0 ? -(a) : (a))
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
LL ans = 0;
const int N = 1000100;
int a[N], aver;
LL s[N], sum;
int main(){
	int n;scanf("%d",&n); sum = 0;
	rep(i,0,n - 1) scanf("%d",&a[i]), sum += a[i];
	aver = sum / n, s[0] = 0;
	rep(i,1,n - 1) s[i] = s[i - 1] + a[i] - aver;
	rep(i,1,n - 1) s[i] = -s[i];
	nth_element(s, s + n / 2, s + n);
	LL t = s[n/2];
	rep(i,0,n - 1) ans += ab(t - s[i]);
	printf("%lld\n",ans);
	return 0;
}
Problem1046

var
  n,i,l,max,m:longint;
  h,f,a:array[0..10001]of longint;
function binary_search(l,r,a:Longint):longint;//[l,r)
var
  m:longint;
begin 
 if l+1=r then exit(l);
  m:=(l+r) shr 1;
  if h[m]>a then exit(binary_search(m,r,a)) else exit(binary_search(l,m,a));
end;
procedure dp;
var
 i,j:longint;
begin
 fillchar(h,sizeof(h),0);h[0]:=maxlongint;max:=0;
 for i:=n downto 1 do begin 
      j:=binary_search(0,max+1,a[i]);
	  if h[j+1]<a[i] then h[j+1]:=a[i];
	  f[i]:=j+1;if f[i]>max then max:=f[i];
 end;
end;
procedure work(l:longint);
var
 i,k:longint;
begin 
 if max<l then begin writeln('Impossible');exit;end;
 k:=longint(int64(int64(-maxlongint)+1));
 for i:=1 to n do begin 
      if (f[i]>=l) and (a[i]>k) then begin 
			  if l>1 then write(a[i],' ') else write(a[i]);
	         k:=a[i];dec(l);
		 end;
	  if l=0 then break;
 end;
 writeln;
end;
 begin 
 readln(n);
 for i:=1 to n do read(a[i]);
 dp;
 readln(m);
 for i:=1 to m do begin 
     readln(l);work(l);
 end;
end.
Problem1047

type arr=array[1..1000000]of longint;
var
 r,c,n,i,j,top,tail,ans:longint;
 m,sn,sx,fn,fx:arr;
 d:array[1..1000]of longint;
//min
procedure ind(var a:arr;x:longint);
var
 k,i:longint;
 flag:boolean;
begin
 flag:=false;
 for i:=tail downto top do if a[d[i]]<a[x] then begin flag:=true;k:=i;break;end;
 if flag then begin 
	 tail:=k;inc(tail);d[tail]:=x;
 end else begin 
	 tail:=top;d[top]:=x;
 end;
end;
procedure oud(var a:arr;x:longint);// a special oud for this problem
begin
 if  x=d[top] then inc(top);
end;
//max
procedure ind1(var a:arr;x:longint);
var
 k,i:longint;
 flag:boolean;
begin
 flag:=false;
 for i:=tail downto top do if a[d[i]]>a[x] then begin flag:=true;k:=i;break;end;
 if flag then begin 
	 tail:=k;inc(tail);d[tail]:=x;
 end else begin 
	 tail:=top;d[top]:=x;
 end;
end;
procedure oud1(var a:arr;x:longint);// a special oud for this problem
begin
 if  x=d[top] then inc(top);
end;
function get(a,b:longint):longint;
begin 
 exit((a-1)*c+b);
end;
function get1(a,b:longint):longint;
begin
 exit((a-1)*(c-n+1)+b); 
end;
begin 
 readln(r,c,n);
 for i:=1 to r do begin 
	  for j:=1 to c do read(m[get(i,j)]);
	  readln;
 end;
 for i:=1 to r do begin 
	 tail:=0;top:=1;
      for j:=1 to n-1 do ind(m,get(i,j));
	  for j:=n to c do begin 
	     ind(m,get(i,j));sn[get1(i,j-n+1)]:=m[d[top]];oud(m,get(i,j-n+1));
	  end;
 end;
 for i:=1 to r do begin 
	 tail:=0;top:=1;
      for j:=1 to n-1 do ind1(m,get(i,j));
	  for j:=n to c do begin 
	     ind1(m,get(i,j));sx[get1(i,j-n+1)]:=m[d[top]];oud1(m,get(i,j-n+1));
	  end;
 end;
 for j:=1 to c-n+1 do begin 
     tail:=0;top:=1;
     for i:=1 to n-1 do ind(sn,get1(i,j));
	 for i:=n to r do begin 
		 ind(sn,get1(i,j));fn[get1(i-n+1,j)]:=sn[d[top]];oud(sn,get1(i-n+1,j));
	 end;
 end;
 for j:=1 to c-n+1 do begin 
     tail:=0;top:=1;
     for i:=1 to n-1 do ind1(sx,get1(i,j));
	 for i:=n to r do begin 
		 ind1(sx,get1(i,j));fx[get1(i-n+1,j)]:=sx[d[top]];oud1(sx,get1(i-n+1,j));
	 end;
 end;
 ans:=maxlongint;
 for i:=1 to r-n+1 do 
	  for j:=1 to c-n+1 do if fx[get1(i,j)]-fn[get1(i,j)]<ans then ans:=fx[get1(i,j)]-fn[get1(i,j)];
 writeln(ans);
end.
Problem1050

var
 flag:boolean;
 n,m,s,t,i,ans_min,ans_max,fx,fy,j:longint;
 x,y,v:array[1..5000]of longint;
 f:array[1..500] of longint;
procedure swap(var a,b:longint);
var
 c:longint;
begin 
 c:=a;a:=b;b:=c;
end;
procedure sort(l,r:longint);
var
 i,j,m:longint;
begin 
 i:=l;j:=r;m:=v[(l+r) div 2];
 repeat
	 while v[i]<m do inc(i);
	 while v[j]>m do dec(j);
	 if i<=j then begin 
		 swap(x[i],x[j]);swap(y[i],y[j]);swap(v[i],v[j]);
	     inc(i);dec(j);
	 end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
function find(x:longint):longint;
begin
 if f[x]=x then exit(x);
 find:=find(f[x]);
 f[x]:=find;
end;
function gcd(x,y:longint):longint;
begin 
 if y=0 then exit(x) else exit(gcd(y,x mod y)); 
end;
begin 
 readln(n,m);
 for i:=1 to m do readln(x[i],y[i],v[i]);
 readln(s,t);
 sort(1,m);flag:=false;
 for i:=1 to m do begin 
	 for j:=1 to n do f[j]:=j;
     for j:=i to m do begin 
		 if flag then if v[j]/v[i]>ans_max/ans_min then break;
	     fy:=find(y[j]);fx:=find(x[j]);f[fx]:=fy;
		 if find(s)=find(t) then begin 
			 if flag=false then begin flag:=true;ans_max:=v[j];ans_min:=v[i];end else if v[j]/v[i]<ans_max/ans_min then begin ans_max:=v[j];ans_min:=v[i];end;
			 break;
		end;
	 end; 
 end;
 if flag=false then writeln('IMPOSSIBLE') else begin if ans_min<0 then begin ans_max:=-ans_max;ans_min:=-ans_min;end;t:=gcd(ans_max,ans_min);write(ans_max div t);if ans_min div t<>1 then writeln('/',ans_min div t);end;
end.
Problem1051

var
 h:array[1..10010]of boolean;
 s,l,num,ou:array[1..10010]of longint;
 f,t,st,pre,low:array[1..50010]of longint;
 n,m,time,top,i,kind,ans:longint;
procedure sort(l,r:longint);
var
 i,j,mid,k:longint;
begin
 i:=l;j:=r;mid:=f[(l+r) div 2];
 repeat
	 while f[i]<mid do inc(i);
	 while mid<f[j] do dec(j);
	 if i<=j then begin 
		 k:=f[i];f[i]:=f[j];f[j]:=k;
	     k:=t[i];t[i]:=t[j];t[j]:=k;
	     inc(i);dec(j);
	 end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
procedure push(u:longint);
begin 
 inc(top);st[top]:=u;h[u]:=true;
end;
function pop:longint;
begin 
  pop:=st[top];dec(top);h[pop]:=false;
end;
procedure tarjin(u:longint);
var
  i:longint;
begin 
  inc(time);pre[u]:=time;low[u]:=time;push(u);
  i:=l[u];
  while f[i]=u do begin 
     if pre[t[i]]=0 then //attention!pre!
		 begin tarjin(t[i]);if low[t[i]]<low[u] then low[u]:=low[t[i]];end else 
	  if h[t[i]] then if low[t[i]]<low[u] then low[u]:=low[t[i]];
     inc(i);
  end;
   if pre[u]=low[u] then begin
	    inc(kind);
	    while st[top]<>u do begin s[pop]:=kind;inc(num[kind]);end;
	    s[pop]:=kind;inc(num[kind]);
   end;
end;
begin 
 readln(n,m);
 for i:=1 to m do  readln(f[i],t[i]);fillchar(ou,sizeof(ou),0);
 sort(1,m);fillchar(l,sizeof(l),0);fillchar(s,sizeof(s),0);fillchar(h,sizeof(h),false);top:=0;time:=0;
 for i:=1 to m do if l[f[i]]=0 then l[f[i]]:=i;
 for i:=1 to n do if s[i]=0 then tarjin(i);ans:=0;
 for i:=1 to m do if s[f[i]]<>s[t[i]] then inc(ou[s[f[i]]]);// attention!<>!
 for i:=1 to kind do 
	 if ou[i]=0 then 
		  if ans=0 then ans:=num[i] else begin ans:=0;exit;end;
 writeln(ans);
end.
Problem1053

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
using namespace std;
LL p[11]={2,3,5,7,11,13,17,19,21,23,29},n,ans1=0,ans=0;
void dfs(LL x,LL cnt,LL num,LL last){
	if (cnt>ans1 || (cnt==ans1 && ans > num)){ans1=cnt;ans=num;}
	if (x>=11|| num>n) return;
	dfs(x+1,cnt,num,0);
	for(LL i=1;(num*p[x]) <= n && i<=last;i++){
		num*=p[x];
		dfs(x+1,cnt*(i+1),num,i);
	}
}
int main(){
	scanf("%lld",&n);
	dfs(0,1,1,30);
	printf("%lld",ans);
	return 0;
}
Problem1055

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int trans(char c){
	int t=0;
	if (c=='W') t = 1;
	if (c=='I') t = 2;
	if (c=='N') t = 3;
	if (c=='G') t = 4;
	return t;
}
int get(){
	char c=getchar();while (!trans(c)) c=getchar();
	return trans(c);
}
pair<int, int> t[5][17];
int f[210][210][5];
char s[300];
int S[300];
int w[5];
int main(){
	scanf("%d%d%d%d",&w[1],&w[2],&w[3],&w[4]);
	rep(i,1,w[1]) t[1][i].first = get(), t[1][i].second = get();
	rep(i,1,w[2]) t[2][i].first = get(), t[2][i].second = get();
	rep(i,1,w[3]) t[3][i].first = get(), t[3][i].second = get();
	rep(i,1,w[4]) t[4][i].first = get(), t[4][i].second = get();
	scanf("%s",s);int len = strlen(s);
	rep(i,1,len) S[i] = trans(s[i-1]);
	rep(i,1,len) f[i][i][S[i]] = 1;
	rep(i,1,len - 1)
		rep(j,1,len - i){
			int l = j, r = j + i;
			rep(q1, 1, 4){
				rep (k, l, r - 1) {
					rep(q, 1, w[q1]){
						f[l][r][q1] = f[l][r][q1] || (f[l][k][ t[q1][q].first ] && f[k+1][r][ t[q1][q].second ]);
						if (f[l][r][q1]) break;
					}
					if (f[l][r][q1]) break;
				}
			}
		}
	int cnt = 0;
	rep(i,1,4) if (f[1][len][i]){
		if (i == 1) cout<<"W";
		if (i == 2) cout<<"I";
		if (i == 3) cout<<"N";
		if (i == 4) cout<<"G";
		cnt++;
	}
	if (!cnt) cout <<"The name is wrong!";
	cout <<endl;
	return 0;
}
Problem1064

type
 edge=record
     l:longint;
	 u:array[1..100000]of longint;
	 v,pre,c:array[1..1000000]of longint;
 end;
var
 e:edge;
 havec:boolean;
 n,m,a,b,i,ans,max,min,maxl:longint;
 v:array[1..100000]of boolean;
 d:array[1..100000]of longint;
function gcd(a,b:longint):longint;
begin
 if b=0 then exit(a) else exit(gcd(b,a mod b)); 
end;
procedure print_no;
begin
   writeln(-1,' ',-1);halt;
end;
procedure add_edge(var e:edge;a,b,w:longint);
begin 
 with e do begin 
     inc(l);v[l]:=b;c[l]:=w;
	 pre[l]:=u[a];
	 u[a]:=l;
 end;
end;
procedure add(a,b:longint);
begin 
 add_edge(e,a,b,1);add_edge(e,b,a,-1);
end;
procedure dfs(x,l:longint);
var
 i:longint;
begin 
 d[x]:=l;v[x]:=true;
 if d[x]>max then max:=d[x];
 if d[x]<min then min:=d[x];
 i:=e.u[x];
 while i<>0 do begin
     if v[e.v[i]] and (d[e.v[i]]<>d[x]+e.c[i]) then begin 
	     if havec then ans:=gcd(ans,abs(d[e.v[i]]-(d[x]+e.c[i]))) else ans:=abs(d[e.v[i]]-(d[x]+e.c[i]));
		 havec:=true;
	 end;
	 if not v[e.v[i]] then dfs(e.v[i],d[x]+e.c[i]);
     i:=e.pre[i];
 end;
end;
begin 
 readln(n,m);
 for i:=1 to m do begin readln(a,b);add(a,b);end;
 fillchar(v,sizeof(v),false);havec:=false;maxl:=0;
 for i:=1 to n do 
     if not v[i] then begin max:=0;min:=maxlongint;dfs(i,0);maxl:=maxl+max-min+1;end;
 if havec then begin 
     if ans<3 then print_no;
	 write(ans,' ');
	 for i:=3 to ans do if ans mod i=0 then begin writeln(i);halt;end;
 end else begin 
     if maxl<3 then print_no;
	 writeln(maxl,' ',3);
 end;
end.
Problem1066

var
 q,e:char;
 a:array[1..1000,1..1000]of longint;
 i,j,t,r,c,dd,k1,k2,tot,n:longint;
 h:array[1..1000]of boolean;
 d:array[0..1000]of longint;
 dis,p:array[1..1000]of longint;
 k,c1,c2,ans,top:longint;
function get(a,b:longint):longint;
begin
 if (a=0) and (b=0) then exit(r*c+1);
 if (a=r+1) and (b=c+1) then exit(r*c+2);
 exit((a-1)*c+b);
end;
procedure incb(f1,f2,t1,t2,c:longint);
begin
 a[get(f1,f2)*2,get(t1,t2)*2-1]:=c;
end;
function dis1(a,b,c,d:longint):real;
begin 
 exit(sqrt(sqr(a-c)+sqr(b-d)));
end;
procedure spfa(s:longint);
var
 i,l,r:longint;
begin 
 l:=0;r:=1;d[l]:=s;
 fillchar(dis,sizeof(dis),0);dis[s]:=1;fillchar(h,sizeof(h),false);
 h[s]:=true;
 repeat
	 k:=d[l];
	 for i:=1 to n do 
		 if (a[k,i]>0) and (i<>s) then 
		 if (dis[k]+1<dis[i]) or (dis[i]=0) then begin 
		     dis[i]:=dis[k]+1;
			 if not h[i] then begin 
			     d[r]:=i;h[i]:=true;inc(r);r:=r mod 1000;
			 end;
		 end;
	 h[k]:=false;inc(l);l:=l mod 1000;
 until l>=r;
end;
function outd(u:longint):longint;
var
 i:longint;
begin
 outd:=0;
 for i:=1 to n do if (a[u,i]>0) and (dis[u]+1=dis[i]) then inc(outd);
end;
procedure dfs(s,t:longint);
var
 u,v,min,i:longint;
begin
 top:=1;p[1]:=s;
 while outd(s)>0 do begin 
    u:=p[top];
	if u<>t then  
	     if outd(u)>0 then begin  
		     for v:=1 to n do 
			 if (a[u,v]>0)  and (dis[u]+1=dis[v])then begin 
			     inc(top);p[top]:=v;break;
			 end
		 end else begin 
		     dec(top);dis[u]:=-1;
	end else begin 
	   min:=0;
	   for i:=1 to top-1 do if (min=0) or (min>a[p[i],p[i+1]]) then min:=a[p[i],p[i+1]];
	   inc(ans,min);
	   for i:=top-1 downto 1 do begin
	       dec(a[p[i],p[i+1]],min);
	       inc(a[p[i+1],p[i]],min);
		   if a[p[i],p[i+1]]=0 then top:=i;
	  end;
	end;
 end;
end;
procedure dinic;
begin 
 spfa(c1);
 while dis[c2]>0 do begin 
     dfs(c1,c2);spfa(c1);
 end;
end;
begin
 fillchar(a,sizeof(a),0);
 readln(r,c,dd);
 for i:=1 to r do begin 
	 for j:=1 to c do begin 
		  read(e);t:=get(i,j);a[t*2-1,t*2]:=ord(e)-ord('0');
    end;readln;
 end;
 //(0,0)--->s' (r+1,c+1)----->t'
 tot:=0;
 for i:=1 to r do begin 
	 for j:=1 to c do begin
		 read(q);if q='L' then begin inc(tot);incb(0,0,i,j,1);end;
	 end;readln;
 end;
 for i:=1 to r do begin
	 for j:=1 to c do begin 
		 for k1:=1 to r do  for k2:=1 to c do if dis1(i,j,k1,k2)<=dd then incb(i,j,k1,k2,tot);
		 if (i<=dd) or (j<=dd) or (r-i+1<=dd) or (c-j+1<=dd) then incb(i,j,r+1,c+1,tot);
	 end;
  end;
 n:=get(r+1,c+1)*2;
 c1:=get(0,0);c2:=get(r+1,c+1);
 a[c1*2-1,c1*2]:=tot;a[c2*2-1,c2*2]:=tot;c1:=c1*2-1;c2:=c2*2;
 {for i:=1 to n do  begin 
	 for j:=1 to n do if a[i,j]=maxlongint-1 then write(4,' ') else write(a[i,j],' ');
     writeln;
 end;}
 dinic;
 writeln(tot-ans);
end.
Problem1070

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define v e[i].to
#define ew e[i].w
#define iw e[i^1].w
#define iv e[i^1].to
#define ec e[i].c
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
const int M=360000;//*2!
const int N=1000;
const int inf=1000000;
int S,T;
struct edge{
	int to,pre,w,c;
}e[M];
int l=1;//!
int h[N],u[N],q[N],inq[N],from[N];
void ins(int a,int b,int w,int c){
	e[++l]=(edge){b,u[a],w,c};u[a]=l;
}
void insert(int a,int b,int w,int c){
	ins(a,b,w,c);ins(b,a,0,-c);
}
int cost;
bool spfa(){
	rep(i,S,T) h[i]=inf,inq[i]=0,from[i]=0;
	int l=0,r=1;q[h[S]=0]=S;
	while (l!=r){
		int x=q[l++];l%=N;inq[x]=0;
		reg(i,x) if(ew && h[x]+ec < h[v]){
			h[v]=h[x]+ec;from[v]=i;
			if (!inq[v]){inq[v]=1;q[r++]=v;r%=N;}
		}
	}
	return h[T]!=inf;
}
void mcf(){
	int x=inf;
	for(int i=from[T];i;i=from[iv]) 
		x=min(x,ew);
	for(int i=from[T];i;i=from[iv]) ew-=x,iw+=x,cost+=ec*x;
}
#define worker(a,b) ((a-1)*n+1+b)
#define car(a) (n*m+1+a)
int main(){
	int n,m;scanf("%d%d",&m,&n);
	S=1;
	T=1+n*m+n+1;
	rep(i,1,m) rep(j,1,n) insert(worker(i,j),T,1,0);
	rep(i,1,n){
		rep(j,1,m){
			int t;
			scanf("%d",&t);
			rep(k,1,n) insert(car(i),worker(j,k),1,t*k);
		}
		insert(S,car(i),1,0);
	}
	cost=0;
	while (spfa()) mcf();
	double ans=((double)cost)/n;
	if (ans<0.00001) ans=0;
	printf("%.2lf",ans);
	return 0;	
}
Problem1076

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#define id(x) (1<<(x-1))
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=1 << 15;
double f[111][N];
int p[16],s[16];
int main(){
	int k,n;
	scanf("%d%d",&k,&n);
	rep(i,1,n){
		scanf("%d",&p[i]);
		s[i]=0;
		int t;scanf("%d",&t);
		while (t != 0){
			s[i]=s[i] | id(t);
			scanf("%d",&t);
		}
	}

	memset(f,0,sizeof(f));
	dep(i,k,1)
		rep(j,0,id(n+1)-1){
			rep(t,1,n)
				if ((j & s[t]) == s[t]) f[i][j]+=max(f[i+1][j],f[i+1][j | id(t)] + p[t]);
				else f[i][j]+=f[i+1][j];
			f[i][j]/=n;
		}

	printf("%.6lf",f[1][0]);
}
Problem1083

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define for(i,a,b) for(int i=a;i<=b;i++)
#define maxn 100010
#define maxm 1000010
using namespace std;
struct edge{
	int s,t,c;
};
edge e[maxm];
int f[maxn];
bool cmp(const edge &a,const edge &b){return a.c<b.c;}
int find(int x){
	f[x]= f[x]==x ? x:find(f[x]);
	return f[x];
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	if (n==1){printf("%d %d",0,0);return 0;}
	for (i,1,m) scanf("%d%d%d",&e[i].s,&e[i].t,&e[i].c);
	for (i,1,m) f[i]=i;
	sort(e+1,e+m+1,cmp);
	int cnt=0;
	for (i,1,m){
		int q=find(e[i].s),p=find(e[i].t);
		if (p!=q){
			cnt++;
			f[q]=p;
		}
		if (cnt==n-1){
			printf("%d %d",cnt,e[i].c);
			return 0;
		}
	}
	return 0;
}
Problem1084

uses math;
var
 n,m,k:longint;
 a,s,s1,s2:array[-1..100]of longint;
 f:array[0..100,0..10]of longint;
 b:array[1..2,0..100]of longint;
 g:array[-1..100,-1..100,0..10]of longint;
procedure work1;
var
 i,j,t:longint;
begin
 for i:=1 to n do readln(a[i]); 
 s[0]:=0;for i:=1 to n do s[i]:=s[i-1]+a[i];
 for i:=1 to n do 
   for j:=1 to k do begin 
	   f[i,j]:=f[i-1,j];
	   for t:=0 to i-1 do
		   f[i,j]:=max(f[i,j],f[t,j-1]+s[i]-s[t]);
	 end;
 writeln(f[n,k]);
end;
procedure work2;
var
 i,j,t,t1:longint;
begin
 for i:=1 to n do readln(b[1,i],b[2,i]);
 s1[0]:=0;s2[0]:=0;
 for i:=1 to n do begin s1[i]:=s1[i-1]+b[1,i];s2[i]:=s2[i-1]+b[2,i];end;
 for i:=0 to n do 
   for j:=0 to n do  
	   for t:=1 to k do begin 
		   g[i,j,t]:=max(g[i-1,j,t],g[i,j-1,t]);
			 for t1:=0 to i-1 do g[i,j,t]:=max(g[i,j,t],g[t1,j,t-1]+s1[i]-s1[t1]);
   		 for t1:=0 to j-1 do g[i,j,t]:=max(g[i,j,t],g[i,t1,t-1]+s2[j]-s2[t1]); 
			 if i=j then 
			   for t1:=0 to i-1 do 
				   g[i,j,t]:=max(g[i,j,t],g[t1,t1,t-1]+s1[i]-s1[t1]+s2[j]-s2[t1]);
		 end;
 writeln(g[n,n,k]);
end;
begin 
 readln(n,m,k);
 if m=1 then work1;
 if m=2 then work2;
end.
Problem1086

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int N=2000;
int n,b;
int u[N],l=1;
struct edge{
	int to,pre;
}e[N];

void insert(int a,int b){
	e[l]=(edge){b,u[a]};
	u[a]=l++;
}

bool vis[N];
int q_l=0,q[N],cnt=0,cap[N],bel[N];
void dfs(int x){
	vis[x]=true;int t=q_l;
	for(int i=u[x];i;i=e[i].pre) if (!vis[e[i].to]){
		dfs(e[i].to);
		if (q_l-t>=b){
			cap[++cnt]=x;
			rep(i,t+1,q_l) bel[q[i]]=cnt;
			q_l=t;
		}
	}
	q[++q_l]=x;
	if (q_l-t>=b){
			cap[++cnt]=x;
			rep(i,t+1,q_l) bel[q[i]]=cnt;
			q_l=t;
	}
}
int main(){
	scanf("%d%d",&n,&b);
	rep(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		insert(u,v);insert(v,u);
	}

	memset(vis,false,sizeof(vis));
	dfs(1);
	if (q_l>0) {
		if (!cnt){printf("0\n");return 0;} else rep(i,1,q_l) bel[q[i]]=cnt;
	}
	printf("%d\n",cnt);
	rep(i,1,n) printf("%d ",bel[i]);printf("\n");
	rep(i,1,cnt) printf("%d ",cap[i]);printf("\n");
	return 0;
}
Problem1088

var
 n,i,ans:longint;
 a,s:array[1..10000]of longint;
function get:longint;
var
 i:longint;
begin
 a[2]:=s[1]-a[1];
 for i:=2 to n-1 do begin 
	 a[i+1]:=s[i]-a[i]-a[i-1];
     if not ((a[i+1]=1) or (a[i+1]=0) ) then exit(0);
 end;
 if a[n]+a[n-1]<>s[n] then exit(0) else exit(1);
end;
begin
 readln(n);
 for i:=1 to n do read(s[i]);
 ans:=0;
 for i:=0 to 1 do begin 
	 a[1]:=i;ans:=ans+get;
 end;
 writeln(ans);
end.

 
Problem1090

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
char s[110];
int l, f[110][110], q[110];
bool c[110][110][110];
vector<int> d[110];
#define pb(a) push_back(a);
typedef vector<int>::iterator vit;
bool check(int a, int b, int c, int d){
	if (a + 1 < d) return 1;
	rep(i, 1, c) if (s[a + i] != s[b + i]) return 0;
	return 1;
}
int main(){
	scanf("%s",s + 1), l = strlen(s + 1);
	rep(i,1,100) rep(j,1,i) if (i % j == 0) d[i].pb(j);
	rep(i,1,9) q[i] = 1;
	rep(i,10,99) q[i] = 2;
	q[100] = 3;

	rep(i,1,l) {
		rep(j,1,l) c[i][i - 1][j] = 1;
		rep(j, i, l)
			for(vit t = d[j - i + 1].begin();t!=d[j - i + 1].end();t++)
				c[i][j][*t] = c[i][j - *t][*t] && check(j - *t - *t, j - *t, *t, i);
	}

	dep(i,l,1){
		f[i][i - 1] = 0;
		rep(j,i,l){
			f[i][j] = f[i][j - 1] + 1;
			rep(k,i,j - 1)
				for(vit t = d[j - k + 1].begin();t!=d[j - k + 1].end();t++)
					if (c[k][j][*t])
						f[i][j] = min(f[i][j], f[i][k - 1] + f[k][k + *t - 1] + 2 + q[(j - k + 1) / *t]);					
		}
	}
	printf("%d\n",f[1][l]);
	return 0;
}
Problem1096

type
	 dot=record
		 x,y:int64; 
     end;
var
 k:dot;
 d:array[0..1000000]of dot;
 n,i,head,tail:longint;
 f,x,p,c,s,t,a,b,tj:int64;
procedure ind(k:dot);
begin 
 while (tail-head>=2) and (((k.y-d[tail-1].y)/(k.x-d[tail-1].x))<(d[tail-1].y-d[tail-2].y)/(d[tail-1].x-d[tail-2].x)) do dec(tail);
 d[tail]:=k;inc(tail)//queue := before inc(tail)
end;
function oud(k:int64):dot;
begin 
 while (tail-head>=2) and ((d[head].y-d[head+1].y)/(d[head].x-d[head+1].x)<k) do inc(head);
 exit(d[head]);
end;
begin 
 readln(n);
 s:=0;t:=0;
 k.x:=0;k.y:=0;
 head:=0;tail:=1;d[0]:=k;
 for i:=1 to n do begin
	 readln(x,p,c);
	 s:=s+p*x;
     t:=t+p;
     k:=oud(x);a:=c-s;b:=k.y;tj:=k.x;
     f:=b+a+(t-tj)*x;
     k.x:=t;k.y:=s+f;
     ind(k);
 end;
 writeln(f);
end.
Problem1098

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 100010;
const int M = 4000010;
struct edge{
	int to, pre;
}e[M];
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
int vis[N], nex[N], pre[N];
int t[N], t1[N];
void del(int x){
	nex[pre[x]] = nex[x];
	pre[nex[x]] = pre[x];
}
int n, m, tmp, Ans[N];
void print(int x){
	for(int i = nex[0]; i<=n; i=nex[i]) cout <<i<<' ';
	cout <<endl;
}
int q[N];
void bfs(int x){
	int l = 0, r = 1;q[l] = x;del(x);
	while (l < r){
		int x = q[l++]; 
		vis[x] = 1, tmp++;

		reg(i,x) t[v] = 1;
		int a = nex[0];
		while (a <= n){
			if (!t[a])
				del(a), q[r++] = a;
			a = nex[a];
		}
		reg(i,x) t[v] = 0;
	}
}
int a1[N];
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m) {
		int x, y; scanf("%d%d",&x,&y);
		ins(x, y),ins(y, x);
	}
	int ans = 0;
	rep(i,0,n) nex[i] = i + 1;
	rep(i,1,n) pre[i] = i - 1;
	rep(i,1,n) t[i] = 0;
	rep(i,1,n) if (!vis[i]) tmp = 0, ans++, bfs(i), Ans[i] = tmp;
	printf("%d\n",ans);
	int tl = 0;
	rep(i,1,n) if (Ans[i]) a1[++tl] = Ans[i];
	sort(a1 + 1, a1 + tl + 1);
	rep(i,1,tl) printf("%d ",a1[i]);
	printf("\n");
	return 0;
}
Problem1101

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define maxn 51000
using namespace std;
bool a[maxn];
int miu[maxn],p[maxn],s[maxn],l;
void get_miu(){
	miu[1]=1;l=0;
	memset(a,true,sizeof(a));
	for (int i=2;i<=maxn;i++){
		if (a[i]){
			p[++l]=i;miu[i]=-1;
		}
		for (int j=1;j<=l;j++){
			int t=p[j]*i;if (t>maxn) break;
			a[t]=false;
			if (i%p[j]==0){
				miu[t]=0;break;
			}else miu[t]=-miu[i];
		}
	}
	s[0]=0;
	for (int i=1;i<=maxn;i++) s[i]=s[i-1]+miu[i];
}
int calc(int a,int b){
	int ans=0,r;
	for (int l=1;l<=min(a,b);){
		r=min(a/(a/l),b/(b/l));if (r>min(a,b)) r=min(a,b);
		ans+=(s[r]-s[l-1])*(a/l)*(b/l);
		l=r+1;
	}
	return ans; 
}
int main(){
	int n;
	get_miu();
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int a,b,d;
		scanf("%d%d%d",&a,&b,&d);
		printf("%d\n",calc(a/d,b/d));
	}
	return 0;
}
Problem1101

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ab(x) (x<0? -x : x)//abs
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef long long LL;
using namespace std;
const int N=1000001;
bool a[N];
int miu[N],p[N],l=0;
void init(){
	miu[1]=1;
	memset(a,true,sizeof(a));
	rep(i,2,N-1){
		if (a[i]){
			p[++l]=i;
			miu[i]=-1;
		}
		rep(j,1,l){
			if(((LL)p[j]*i) >= N) break;
			int k=p[j]*i;
			a[k]=false;
			if (i % p[j]==0){
				miu[k]=0;break;
			} else miu[k]=-miu[i];
		}
	}
	miu[0]=0;
	rep(i,1,N-1) miu[i]+=miu[i-1];
}
void work(){
	int a,b,d;scanf("%d%d%d",&a,&b,&d);
	int n=a/d,m=b/d;
	LL ans=0;
	int r;
	for(int l=1;l<=n && l<=m;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans+=((LL)miu[r]-miu[l-1])*(n/l)*(m/l);
	}
	printf("%lld\n",ans);
}
int main(){
	int n;scanf("%d",&n);
	init();
	rep(i,1,n) work(); 
	return 0;
}
Problem1101

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ab(x) (x<0? -x : x)//abs
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef long long LL;
using namespace std;
const int N=50010;
bool a[N];
int miu[N],p[N],l=0;
void init(){
	miu[1]=1;
	memset(a,true,sizeof(a));
	rep(i,2,N-1){
		if (a[i]){
			p[++l]=i;
			miu[i]=-1;
		}
		rep(j,1,l){
			if(((LL)p[j]*i) >= N) break;
			int k=p[j]*i;
			a[k]=false;
			if (i % p[j]==0){
				miu[k]=0;break;
			} else miu[k]=-miu[i];
		}
	}
	miu[0]=0;
	rep(i,1,N-1) miu[i]+=miu[i-1];
}
void work(){
	int a,b,d;scanf("%d%d%d",&a,&b,&d);
	int n=a/d,m=b/d;
	LL ans=0;
	int r;
	for(int l=1;l<=n && l<=m;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans+=((LL)miu[r]-miu[l-1])*(n/l)*(m/l);
	}
	printf("%lld\n",ans);
}
int main(){
	int n;scanf("%d",&n);
	init();
	rep(i,1,n) work(); 
	return 0;
}
Problem1103

type
 bit=array[1..500000]of longint;
var
 tmp:char;
 ans:bit;
 n,a,b,m,i,l,dfsl:longint;
 u,v,h,d1,d2,depth:array[0..500000]of longint;
 visited:array[1..500000]of boolean;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin 
 i:=l;j:=r;m:=u[(l+r) shr 1];
 repeat
  while u[i]<m do inc(i);
  while u[j]>m do dec(j);
  if i<=j then begin 
     t:=u[i];u[i]:=u[j];u[j]:=t;
	 t:=v[i];v[i]:=v[j];v[j]:=t;
	 inc(i);dec(j);
  end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
procedure dfs(x:longint);
var
 i:longint;
begin 
 visited[x]:=true;
 inc(dfsl);d1[x]:=dfsl;
 i:=h[x];
 while u[i]=x do begin
     if not visited[v[i]] then begin 
	     depth[v[i]]:=depth[x]+1; 
         dfs(v[i]);
	 end;
	 inc(i);
 end;
 inc(dfsl);d2[x]:=dfsl;
end;
procedure add(x,d:longint);
begin
 while x<=dfsl do begin 
     ans[x]:=ans[x]+d;x:=x+(-x) and x;
 end;	 
end;
function sum(x:longint):longint;
begin
 sum:=0;
 while x>0 do begin 
     sum:=sum+ans[x];x:=x-(-x) and x;
 end;	 
end;
begin
 readln(n);l:=0;
 for i:=1 to n-1 do begin  
     readln(a,b);
	 inc(l);u[l]:=a;v[l]:=b;inc(l);u[l]:=b;v[l]:=a;
 end;
 sort(1,l);fillchar(h,sizeof(h),0);
 for i:=1 to l do 
     if h[u[i]]=0 then h[u[i]]:=i;
 dfsl:=0;
 fillchar(visited,sizeof(visited),false);depth[1]:=1;
 dfs(1);
 fillchar(ans,sizeof(ans),0);
 for i:=1 to l do 
     if depth[u[i]]<depth[v[i]] then begin 
	     add(d1[v[i]],1);add(d2[v[i]],-1);
	 end;
 readln(m);
 i:=0;
 while i<m do begin  
     read(tmp);
     if tmp='A' then begin 
      	readln(a,b);
		if depth[a]>depth[b] then begin 
      	     add(d1[a],-1);add(d2[a],1)
		 end else begin 
			 add(d1[b],-1);add(d2[b],1);
	    end;
     end else begin
     	readln(a);inc(i);
		writeln(sum(d1[a]));
	 end;
 end;
end.
Problem1113

#include <iostream>
using namespace std;
const int maxn=250000+10;
int n,a[maxn],b[maxn],s[maxn],top,ans;
int main(){
	cin >>n;int i;
	for (i=1;i<=n;i++) cin>>a[i]>>b[i];
	top=1;s[1]=b[n];ans=n;
	for (i=n-1;i>=1;i--){
		while ((s[top]>b[i]) && top) top--;
		while ((s[top]==b[i]) && top){
			ans--;top--;
		}
		s[++top]=b[i];
	}
	cout <<ans;
	return 0;
}
Problem1115

var
 T,i,n:longint;
 a:array[0..1000]of longint;
procedure work;
var
 i,ans:longint;
begin 
 readln(n);ans:=0;a[0]:=0;
 for i:=1 to n do read(a[i]);readln;
 for i:=1 to n do if (n-i+1) and 1=1 then  ans:=ans xor (a[i]-a[i-1]);
 if ans=0 then writeln('NIE') else writeln('TAK');
end;
begin 
 readln(T);
 for i:=1 to T do work;
end.
Problem1124

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int ans1, ans2;
const int N = 1000000+10;
int f[N], vis[N];
struct edge{
	int to,pre;
}e[N*2];
#define v e[i].to
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
int u[N],l=0;
void ins(int a,int b){
	e[++l] = (edge) {b, u[a]}, u[a] = l;
}
int cnt, n;
int d[N], t[N], q[N];
int dfs(int x){
	vis[x] = -1;
	int ans = 1;
	if (!d[x]) cnt++;
	reg(i,x) if (!vis[v]) ans += dfs(v);
	return ans;	
}

void work1(){
	rep(i, 1, n) vis[i] = 0, d[i] = 0;
	rep(i, 1, n) d[f[i]]++;
	int l = 0, r = 0;
	rep(i, 1, n) if (!d[i]) q[r++] = i;
	ans1 = n;
	while (l < r){
		int x = q[l++], y = f[f[x]];
		if (f[x] != y && !vis[f[x]]){
			d[y]--, vis[f[x]] = 1;
			if (!d[y]) q[r++] = y;
		}
		ans1--;
	}
	rep(i, 1, n) if (d[i] && (!vis[i])){
		int tmp = 1, x = f[i]; vis[i] = 1;
		while (x != i) vis[x] = 1, x = f[x], tmp++;
		ans1 -= tmp / 2;
	}
}

void work2(){
	rep(i, 1, n) d[i] = vis[i] = 0;
	rep(i, 1, n) ins(f[i], i), ins(i, f[i]), d[f[i]]++;
	rep(i, 1, n)if (!vis[i]){
		if (f[i] == i) ans2++, vis[i] = i;else{
			cnt = 0; int sz = dfs(i);
			int x = i, tmp  = 0;
			while (vis[x]!=i){
				t[x] = tmp++;
				vis[x] = i, x = f[x];
			}
			int size = tmp - t[x];
			if (!cnt) ans2 += size - 1; else ans2 +=sz - cnt;
		}
	}
}

int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&f[i]);
	work1();
	work2();
	printf("%d %d\n", ans1, ans2);
}
Problem1188

var
 T,i:longint;
 sg,a:array[1..21]of longint;
 hash:array[0..128]of boolean;
procedure init(n:longint);
var
 i,j,k:longint;
begin 
 sg[n]:=0;
 for i:=n-1 downto 1 do begin 
   fillchar(hash,sizeof(hash),false);
   for j:=i+1 to n do  
	  for k:=j to n do 
		 hash[sg[j] xor sg[k]]:=true;
	 for j:=0 to 128 do if not hash[j] then begin sg[i]:=j;break;end;
 end;
end;
procedure work;
var
 flag:boolean;
 n,i,j,k,ans,sum:longint;
begin
 readln(n);init(n);
 ans:=0;
 for i:=1 to n do read(a[i]);readln; 
 for i:=1 to n do 
   if odd(a[i]) then ans:=ans xor sg[i];
 if ans=0 then begin 
   writeln('-1 -1 -1');
	 writeln(0);
 end else begin
   flag:=true;sum:=0; 
	 for i:=1 to n do begin 
	  if a[i]=0 then continue;
	  for j:=i+1 to n do  
		  for k:=j to n do
			   if ans xor sg[i] xor sg[j] xor sg[k]=0 then begin 
				   inc(sum);
					 if flag then begin writeln(i-1,' ',j-1,' ',k-1);flag:=false;end;
				 end;
	 end;
	 writeln(sum);
 end;
end;
begin 
 readln(T);
 for i:=1 to T do work;
end.
Problem1189

var
 wx:array[1..4]of longint=(0,1,0,-1);
 wy:array[1..4]of longint=(1,0,-1,0);
 dist:array[1..20,1..20]of longint;
 q:array[1..20,1..20]of char;
 g:array[1..20,1..20]of longint;
 r,c,kl,tot,i,j,n:longint;
 vi:array[1..20,1..20]of boolean;
 a:array[1..1000,1..1000]of longint;
 h:array[1..1000]of boolean;
 d:array[0..1000]of longint;
 dis,p:array[1..1000]of longint;
 k,c1,c2,ans,top:longint;
procedure spfa1(x,y:longint);
var
 i:longint;
begin 
 for i:=1 to 4 do begin 
     if q[x+wx[i],y+wy[i]]='.' then 
	  if (dist[x+wx[i],y+wy[i]]=0) or (dist[x+wx[i],y+wy[i]]>dist[x,y]+1) then begin 
		   dist[x+wx[i],y+wy[i]]:=dist[x,y]+1;spfa1(x+wx[i],y+wy[i]);
	 end;
 end;
end;
procedure make(t:longint);
var 
 ki,kj:longint;
begin
 fillchar(a,sizeof(a),0);
 for i:=1 to r do 
	 for j:=1 to c do begin 
		 if q[i,j]='.' then a[1,g[i,j]]:=1;
		 if q[i,j]='D' then begin
			 fillchar(dist,sizeof(dist),0);dist[i,j]:=1; 
			 spfa1(i,j);
		     for ki:=1 to  r do 
				 for kj:=1 to c do
					  if q[ki,kj]='.' then if dist[ki,kj]>0 then if dist[ki,kj]-1<=t then begin a[g[ki,kj],g[i,j]]:=1;vi[ki,kj]:=true;end;
			 a[g[i,j],2]:=t;
		 end;
	 end;
end;
procedure spfa(s:longint);
var
 i,l,r:longint;
begin 
 l:=0;r:=1;d[l]:=s;
 fillchar(dis,sizeof(dis),0);dis[s]:=1;fillchar(h,sizeof(h),false);
 h[s]:=true;
 repeat
	 k:=d[l];
	 for i:=1 to n do 
		 if (a[k,i]>0) and (i<>s) then 
		 if (dis[k]+1<dis[i]) or (dis[i]=0) then begin 
		     dis[i]:=dis[k]+1;
			 if not h[i] then begin 
			     d[r]:=i;h[i]:=true;inc(r);r:=r mod 1000;
			 end;
		 end;
	 h[k]:=false;inc(l);l:=l mod 1000;
 until l>=r;
end;
function outd(u:longint):longint;
var
 i:longint;
begin
 outd:=0;
 for i:=1 to n do if (a[u,i]>0) and (dis[u]+1=dis[i]) then inc(outd);
end;
procedure dfs(s,t:longint);
var
 u,v,min,i:longint;
begin
 top:=1;p[1]:=s;
 while outd(s)>0 do begin 
    u:=p[top];
	if u<>t then  
	     if outd(u)>0 then begin  
		     for v:=1 to n do 
			 if (a[u,v]>0)  and (dis[u]+1=dis[v])then begin 
			     inc(top);p[top]:=v;break;
			 end
		 end else begin 
		     dec(top);dis[u]:=-1;
	end else begin 
	   min:=0;
	   for i:=1 to top-1 do if (min=0) or (min>a[p[i],p[i+1]]) then min:=a[p[i],p[i+1]];
	   inc(ans,min);
	   for i:=top-1 downto 1 do begin
	       dec(a[p[i],p[i+1]],min);
	       inc(a[p[i+1],p[i]],min);
		   if a[p[i],p[i+1]]=0 then top:=i;
	  end;
	end;
 end;
end;
procedure dinic;
begin 
 ans:=0;
 spfa(c1);
 while dis[c2]>0 do begin 
     dfs(c1,c2);spfa(c1);
 end;
end;
procedure try1;
var
	i,j:longint;
begin
	 fillchar(vi,sizeof(vi),false);
	make(400);for i:=1 to r do for j:=1 to c do if q[i,j]='.' then if not(vi[i,j]) then begin writeln('impossible');halt;end;
	for i:=1 to 400 do begin 
		 make(i);dinic;
	     if ans=tot then begin writeln(i);halt;end;
    end;
end;
begin 
 readln(r,c);kl:=2;tot:=0;
 for i:=1 to r do begin 
    for j:=1 to c do begin 
		 read(q[i,j]);
		 if (q[i,j]='.') or (q[i,j]='D') then begin 
			 inc(kl);g[i,j]:=kl;
		 end;
		 if q[i,j]='.' then inc(tot);
    end;readln;
 end;
 n:=kl;c1:=1;c2:=2;
 try1;
end.
Problem1196

type
 edge=record 
     u,v,w:longint;
 end;
var
 i,n,m,k,l,r,mid,a,b,c,d:longint;
 f:array[1..10000]of longint;
 e1,e2:array[1..20000]of edge;
procedure sort_1(l,r:longint);
var
 i,j,m:longint;
 t:edge;
begin 
 i:=l;j:=r;m:=e1[(l+r) shr 1].w;
 repeat
   while e1[i].w<m do inc(i);
   while e1[j].w>m do dec(j);
   if i<=j then begin 
       t:=e1[i];e1[i]:=e1[j];e1[j]:=t;
	   inc(i);dec(j);
   end;
 until i>j;
 if l<j then sort_1(l,j);
 if i<r then sort_1(i,r);
end;
procedure sort_2(l,r:longint);
var
 i,j,m:longint;
 t:edge;
begin 
 i:=l;j:=r;m:=e2[(l+r) shr 1].w;
 repeat
   while e2[i].w<m do inc(i);
   while e2[j].w>m do dec(j);
   if i<=j then begin 
       t:=e2[i];e2[i]:=e2[j];e2[j]:=t;
	   inc(i);dec(j);
   end;
 until i>j;
 if l<j then sort_2(l,j);
 if i<r then sort_2(i,r);
end;
function find(x:longint):longint;
begin
 if f[x]=x then exit(x);
 f[x]:=find(f[x]);
 exit(f[x]); 
end;
procedure init;
var 
 i:longint;
begin 
  for i:=1 to n do f[i]:=i;
end;
function check(mid,k:longint):boolean;
var
 i,a,b,tot,sum:longint;
begin 
 init;tot:=0;
 for i:=1 to m do 
     with e1[i] do begin 
       	 if w>mid then break;
	     a:=find(u);b:=find(v);
		 if a<>b then begin 
		      inc(tot);
		      f[a]:=b;
		 end;
	 end;
 sum:=tot;
 for i:=1 to m do 
     with e2[i] do begin 
       	 if w>mid then break;
	     a:=find(u);b:=find(v);
		 if a<>b then begin 
		      inc(sum);
		      f[a]:=b;
		 end;
	 end;
 if (sum=n-1) and (tot>=k) then exit(true) else exit(false);
end;
begin 
 readln(n,k,m);dec(m);
 for i:=1 to m do begin 
     readln(a,b,c,d);
     with e1[i] do begin 
	     u:=a;v:=b;w:=c;
	 end;
	 with e2[i] do begin 
	     u:=a;v:=b;w:=d;
	 end;
 end;
 sort_1(1,m);sort_2(1,m);
 l:=0;r:=30000;//(l,r]
 repeat
  mid:=(l+r) shr 1;
  if check(mid,k) then r:=mid else l:=mid;
 until l+1=r;
 writeln(r);
end.
Problem1208

#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#define mp(a,b) make_pair(a,b)
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef set<int>::iterator setit;
set<int> s;
int main(){
	int n; scanf("%d",&n);
	s.clear();
	int f = 0, ans = 0;
	rep(i,1,n){
		int a,b;
		scanf("%d%d", &a, &b);
		if (f == a || s.empty()) s.insert(b), f = a;
		else{
			setit t2 = s.lower_bound(b), t1 = t2; if (t1!=s.begin()) t1--; else t1 = s.end();
			if (t2!=s.end() && (t1==s.end() || *t2 - b < b - *t1))  ans += *t2 - b, s.erase(t2), ans %= 1000000;
				else ans += b - *t1, s.erase(t1), ans %= 1000000;
		}
	}
	cout <<ans<<endl;
}

Problem1257

//k mod i=k-[k/i]*i
//sigma(k mod i)=sigma(k-[k/i]*i)=k*n-sigma([k/i]*i)
#include <iostream>
#define ll long long
using namespace std;
ll sum(ll l,ll r){
	return (ll) (l+r)*(r-l+1)/2;
}
int main(){
	ll n,k;
	cin >>n>>k;
	ll ans=k*n,r;
	for (ll l=1;l<=n;l=r+1){ 
		if (k/l==0) break;
		r=k/(k/l);if (r>n) r=n;
		ans-=(ll) (k/l)*sum(l,r);
	}
	cout <<ans;
}
Problem1293

var
 t,ans:int64;
 l,r,n,k,kind,m,i,j,ll:longint;
 last:array[1..100]of int64;
 a,b:array[1..5000000]of int64;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin 
 i:=l;j:=r;m:=b[(l+r) shr 1];
 repeat
  while b[i]<m do inc(i);
  while b[j]>m do dec(j);
  if i<=j then begin 
     t:=b[i];b[i]:=b[j];b[j]:=t;
     t:=a[i];a[i]:=a[j];a[j]:=t;
	 inc(i);dec(j);
  end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin 
 readln(n,k);ll:=0;
 for i:=1 to k do begin
     read(m);
	 for j:=1 to m do begin 
	     read(t);
		 inc(ll);
		 b[ll]:=t;
		 a[ll]:=i;
	 end;
	 readln;
 end;
 sort(1,n);
 l:=1;r:=0;fillchar(last,sizeof(last),0);kind:=0;
 while kind<k do begin 
     inc(r);
     if last[a[r]]=0 then inc(kind);
	 last[a[r]]:=r;
 end;
 while last[a[l]]<>l do inc(l);
 ans:=b[r]-b[l];
 while r<n do begin 
     inc(l);dec(kind);
     while (kind<k) and (r<n) do begin 
         inc(r);
         if last[a[r]]<l then inc(kind);
	     last[a[r]]:=r;
     end;
	 if kind<k then break;
     while last[a[l]]<>l do inc(l);
	 if b[r]-b[l]<ans then ans:=b[r]-b[l];
 end;
 writeln(ans);
end.
Problem1293

var
 t,ans:int64;
 l,r,n,k,kind,m,i,j,ll,maxmin,max:longint;
 last:array[1..100]of int64;
 a,b:array[1..5000000]of int64;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin 
 i:=l;j:=r;m:=b[(l+r) shr 1];
 repeat
  while b[i]<m do inc(i);
  while b[j]>m do dec(j);
  if i<=j then begin 
     t:=b[i];b[i]:=b[j];b[j]:=t;
     t:=a[i];a[i]:=a[j];a[j]:=t;
	 inc(i);dec(j);
  end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin 
 readln(n,k);ll:=0;maxmin:=n;
 for i:=1 to k do begin
     read(m);max:=0;
	 for j:=1 to m do begin 
	     read(t);if t>max then max:=t;
		 inc(ll);
		 b[ll]:=t;
		 a[ll]:=i;
	 end;
	 if max<maxmin then maxmin:=max;
	 readln;
 end;
 sort(1,n);
 l:=1;r:=0;fillchar(last,sizeof(last),0);kind:=0;
 while kind<k do begin 
     inc(r);
     if last[a[r]]=0 then inc(kind);
	 last[a[r]]:=r;
 end;
 while last[a[l]]<>l do inc(l);
 ans:=b[r]-b[l];
 while (r<n) and (l<maxmin) do begin 
     inc(l);dec(kind);
     while (kind<k) and (r<n) do begin 
         inc(r);
         if last[a[r]]<l then inc(kind);
	     last[a[r]]:=r;
     end;
	 if kind<k then break;
     while last[a[l]]<>l do inc(l);
	 if b[r]-b[l]<ans then ans:=b[r]-b[l];
 end;
 writeln(ans);
end.
	
Problem1295

 program maxlength;
uses math;
const maxn=4000;
type
  ty1=^ty2;
  ty2=record
     x,s:longint;
     next:ty1;
  end;

var
  n,m,t,i,j,k,tot:longint;
  ans:extended;
  p:char;
  first:array[0..900] of ty1;
  dui:array[0..maxn] of longint;
  f:array[0..900,0..900] of longint;
  get:array[0..900] of boolean;
  map:array[0..900] of longint;
//================================求距离
function dis(x,y:longint):extended;
var
  fx1,fx2,fy1,fy2:longint;
begin
  fy1:=x mod m;                   //计算它的x,y坐标
  if fy1=0 then fy1:=m;           //注意可能为最后一排
  fx1:=(x-fy1) div m+1;
  fy2:=y mod m;
  if fy2=0 then fy2:=m;
  fx2:=(y-fy2) div m+1;
  dis:=sqrt(sqr(fx1-fx2)+sqr(fy1-fy2));
end;
//================================链表插入
procedure insert(x,y,z:longint);
var
  p:ty1;
begin
  new(p);
  p^.x:=y;
  p^.s:=z;
  p^.next:=first[x];
  first[x]:=p;
end;
//================================建图
procedure tmp(k,y:longint);
begin
   if k-m>0 then insert(k-m,k,y);
   if k+m<=tot then insert(k+m,k,y);
   if (k-1) mod m<>0 then insert(k-1,k,y);
   if k mod m<>0 then insert(k+1,k,y);
   map[k]:=y;
end;
//================================SPFA
procedure spfa(x:longint);
var
  l,r,t:longint;
  p:ty1;
begin
  fillchar(get,sizeof(get),false);
  l:=0; r:=1; dui[r]:=x; f[x,x]:=map[x]; get[x]:=true;
  while l<>r do
  begin
    inc(l); if l>maxn then l:=0;
    t:=dui[l];
    get[t]:=false;
    p:=first[t];
    while p<>nil do
    begin
      if f[x,p^.x]>f[x,t]+p^.s then
      begin
        f[x,p^.x]:=f[x,t]+p^.s;
        if not get[p^.x] then
        begin
          get[p^.x]:=true;
          inc(r); if r>maxn then r:=0;
          dui[r]:=p^.x;
        end;
      end;
      p:=p^.next;
    end;
  end;
end;
//================================main
begin
  readln(n,m,t);
  fillchar(f,sizeof(f),$7);
  tot:=m*n;
  for i:=1 to n do
  begin
    for j:=1 to m do
    begin
      read(p);
      k:=(i-1)*m+j;
      if p='1' then tmp(k,1) else tmp(k,0);
    end;
    readln;
  end;
  for i:=1 to tot do spfa(i);
  ans:=0;
  for i:=1 to tot do
  for j:=1 to tot do
  if (f[i,j]<=t) then ans:=max(ans,dis(i,j));   //只在满足题意的点中求距离
  writeln(ans:0:6);
end.
Problem1296

uses math;
var
 c:char;
 t:array[1..50,0..50]of longint;
 s:array[0..50]of longint;
 n,m,tt,i,ii,j,k:longint;
 g:array[0..50,0..50]of longint;
 f:array[0..50,0..2500]of longint;
begin 
 readln(n,m,tt);
 for ii:=1 to n do begin 
   s[0]:=0;
	 for j:=1 to m do begin 
	   read(c);if c='1' then s[j]:=s[j-1]+1 else s[j]:=s[j-1];
   end;
	 readln;
	 fillchar(g,sizeof(g),0);
	 for i:=1 to m do 
	  for j:=1 to i do begin 
		 g[i,j]:=g[i-1,j];
		 for k:=0 to i-1 do g[i,j]:=max(g[i,j],g[k,j-1]+max(s[i]-s[k],(i-k)-(s[i]-s[k])));
		end;
   for i:=1 to m do t[ii,i]:=g[m,i];
 end;
 fillchar(f,sizeof(f),0);
 for i:=1 to n do 
   for j:=1 to tt do begin 
	   f[i,j]:=f[i-1,j];
		 for k:=1 to min(j,m) do
		   f[i,j]:=max(f[i,j],f[i-1,j-k]+t[i,k]);
	 end;
 writeln(f[n,tt]);
end.
Problem1297

type
 matrix=array[1..90,1..90]of integer;
var
 w:char;
 n,l,t,i,j:longint;
 a,ans,tmp,c:matrix;
 g:array[1..10,1..9]of longint;
procedure init_ans;
var
 i:longint;
begin
 fillchar(ans,sizeof(ans),0);
 for i:=1 to l do ans[i,i]:=1;
end;
procedure chen(var a,b:matrix);
var
 i,j,k,tmp:longint;
begin 
 fillchar(c,sizeof(c),0);
 for i:=1 to l do 
   for j:=1 to l do begin 
	   tmp:=0;
	   for k:=1 to l do tmp:=tmp+a[i,k]*b[k,j];
		 c[i,j]:=tmp mod 2009;
	 end;
 a:=c;
end;
procedure calc;//a^t
begin 
 init_ans;
 while t>0 do begin 
   if t and 1>0 then chen(ans,a);
	 tmp:=a;
	 chen(a,tmp);
	 t:=t shr 1;
 end;
end;
begin 
 readln(n,t);l:=n;
 for i:=1 to n do begin 
   g[i,1]:=i;
	 for j:=2 to 9 do begin
	   inc(l);g[i,j]:=l;a[g[i,j-1],l]:=1;
	 end;
 end;
 for i:=1 to n do begin 
   for j:=1 to n do begin 
	   read(w);
		 if ord(w)-ord('0')>0 then a[g[i,ord(w)-ord('0')],j]:=1;
	 end;readln;
 end;
 calc;
 
 writeln(ans[1,n]);
end.
Problem1305

#include<iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define v e[i].to
#define ec e[i].c
#define ic e[i^1].c
const int N=1000,M=100000,inf=1000000;
using namespace std;
struct edge{
  int to,pre,c;
}e[M];
int u[N],l=1;
void ins(int a,int b,int c){
  e[++l]=(edge){b,u[a],c};u[a]=l;
}
void insert(int a,int b,int c){
  ins(a,b,c);ins(b,a,0);
}
int q[N],h[N],cur[N],S,T;
bool bfs(){
  int l=0,r=1;rep(i,0,T) h[i]=-1;
  h[q[0]=S]=0;
  while (l!=r){
    int x=q[l++];l%=N;
    reg(i,x) if (h[v]==-1 && ec) h[v]=h[x]+1,q[r++]=v,r%=N;
  }
  return h[T]!=-1;
}
int dfs(int x,int f){
  if (x==T || f==0) return f;
  int used=0,w;
  reg(i,x) if (h[x]+1==h[v] && ec){
    w=min(ec,f-used), w=dfs(v,w);
    ec-=w;if (ec) cur[x]=i;
    ic+=w;
    used+=w;
    if (used==f) break;
  }
  if (used==0) h[x]=-1;
  return used;
}
int ans=0;
void dinic(){
  ans=0;
  while (bfs()){
    rep(i,0,T) cur[i]=u[i];
    ans+=dfs(S,inf);
  }
}
#define boy1(a) a
#define boy2(a) (n+a)
#define girl1(a) (2*n+a)
#define girl2(a) (3*n+a)
int t[100][100];
int main(){
  int n,k;scanf("%d%d",&n,&k);
  rep(i,1,n) rep(j,1,n){
  	char c=getchar();
  	while (c==' '|| c=='\n' || c=='\r') c=getchar();
  	if (c=='Y') t[i][j]=1; else t[i][j]=0;
  }
  S=0, T=4*n+1;
  int L=0,R=n*n+2;//[l,r)
  while (L+1<R){
  	int mid=(L+R) >> 1;
  	rep(i,0,T) u[i]=0;
  	l=1;
  	rep(i,1,n) insert(S,boy1(i),mid), insert(girl1(i),T,mid);
  	rep(i,1,n) insert(boy1(i),boy2(i),k);
  	rep(i,1,n) insert(girl2(i),girl1(i),k);
  	rep(i,1,n) rep(j,1,n) if (t[i][j]) insert(boy1(i),girl1(j),1);else insert(boy2(i),girl2(j),1);
  	dinic();
  	if (ans==mid*n) L=mid;else R=mid;
  }
  printf("%d\n",L);
  return 0;
}
Problem1406

var
 n,a,b,i,l,j :longint;
 ans:array[1..1000000] of longint;
procedure add(a:longint);
begin 
 inc(l);
 ans[l]:=a;
end;
procedure sort(l,r:longint);
var
 i,j,t,m:longint;
begin 
 i:=l;j:=r;m:=ans[(l+r) shr 1];
 repeat
   while ans[i]<m do inc(i);
   while ans[j]>m do dec(j);
   if i<=j then begin 
       t:=ans[i];ans[i]:=ans[j];ans[j]:=t;
       inc(i);dec(j);
	end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
procedure print;
var
 i:longint;
begin 
 if l=0 then begin writeln('None');halt;end;
 sort(1,l);
 writeln(ans[1]);
 for i:=2 to l do if ans[i]<>ans[i-1] then writeln(ans[i]);
end;
begin 
 readln(n);
 for j:=1 to trunc(sqrt(n)) do begin 
    if n mod j<>0 then continue;
    a:=j;
    b:=n div a;
    for i:=1 to n do begin 
       if b*i-1>=n then break;
       if (b*i-2) mod a=0 then add(b*i-1);
    end;
    for i:=1 to n do begin 
        if a*i-1>=n then break;
        if (a*i-2) mod b=0 then add(a*i-1);
    end;
  end;
  print;
end.
Problem1455

#include <iostream>
#include <cstdio>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=1000001;
bool dead[N];
int v[N],l[N],r[N],f[N],d[N];
int find(int x){return f[x]=f[x]==x?x:find(f[x]);}
#define la l[a]
#define ra r[a]
int merge(int a,int b){
	if (!a || !b) return a+b;
	if (v[a]>v[b]) swap(a,b);
	ra=merge(ra,b);
	if (d[la] < d[ra]) swap(la,ra);
	d[a]=d[ra]+1;
	return a;
}
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n) scanf("%d",&v[i]),f[i]=i;
	int m;scanf("%d",&m);
	rep(i,1,m){
		char g=getchar();while (g!='M' && g!='K') g=getchar();
		if (g=='M'){
			int a,b;scanf("%d%d",&a,&b);
			if (! (dead[a] || dead[b]) ){
				int f1=find(a),f2=find(b);
				if (f1!=f2) {
					int t=merge(f1,f2);
					f[f1]=f[f2]=t;
				}
			}
		}else{
			int a;scanf("%d",&a);
			int ans=0;
			if (!dead[a]){
				int fa=find(a);
				ans=v[fa];
				dead[fa]=1;
				f[fa]=merge(l[fa],r[fa]);
				f[f[fa]]=f[fa];
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
Problem1455

#include <iostream>
#include <cstdio>
#include <cstdlib>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=1000001;
bool dead[N];
int v[N],l[N],r[N],f[N];
int find(int x){return f[x]=f[x]==x?x:find(f[x]);}
#define la l[a]
#define ra r[a]
int merge(int a,int b){
	if (!a || !b) return a+b;
	if (v[a]>v[b]) swap(a,b);
	if (rand()&1) la=merge(la,b);else ra=merge(ra,b);
	return a;
}
int main(){
	srand(233);
	int n;scanf("%d",&n);
	rep(i,1,n) scanf("%d",&v[i]),f[i]=i;
	int m;scanf("%d",&m);
	rep(i,1,m){
		char g=getchar();while (g!='M' && g!='K') g=getchar();
		if (g=='M'){
			int a,b;scanf("%d%d",&a,&b);
			if (! (dead[a] || dead[b]) ){
				int f1=find(a),f2=find(b);
				if (f1!=f2) {
					int t=merge(f1,f2);
					f[f1]=f[f2]=t;
				}
			}
		}else{
			int a;scanf("%d",&a);
			int ans=0;
			if (!dead[a]){
				int fa=find(a);
				ans=v[fa];
				dead[fa]=1;
				f[fa]=merge(l[fa],r[fa]);
				f[f[fa]]=f[fa];
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
Problem1467

#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#define put(c) {printf("%d\n",c);return;}
#define nos()  {printf("No Solution\n");return;}
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=200000;
struct hash{
	int a,x,pre;
}h[N];
int l=0,u[29423];
void ins(int a,int x){
	h[++l]=(hash){a, x, u[a % 29423]};u[a % 29423]=l;
}
int find(int a){
	for(int i=u[a % 29423];i;i=h[i].pre) if (h[i].a==a) return h[i].x;
	return -1;
}
int x,y;
int extgcd(int a,int b,int m){
	if (b==0){
		x=1, y=0;return a;
	}else {
		int t=extgcd(b,a%b,m);
		int x1=x,y1=y;
		x=y1,y=x1-(long long)(a/b)*y1%m;
		y%=m;
		return t; 
	}
}
int inv(int a,int m){
	extgcd(a,m,m);
	x%=m;
	if (x<m) x+=m;
	x%=m;
	return x;
}
int gcd(int a,int b){
	return b ? gcd(b,a%b) : a;
}
void work(int a,int b,int m){
	int tmp=1;
	rep(i,0,50){
		if (tmp==b) put(i);
		tmp=(long long)tmp * a % m;
	}
	int times=0,t=1;
	while ((tmp=gcd(a,m))!=1){
		times++;
		m/=tmp;
		if (b % tmp) nos();
		b/=tmp;
		t=(long long)t * (a/tmp) % m;
	}
	int k=(int)sqrt(m)+1, tt=1;
	rep(i,0,29423-1) u[i]=0;
	l=0;
	rep(i,0,k) {
		ins(tt,i);tt=(long long)tt * a % m; 
	}
	ins(tt,k+1);
	int inv_a_k_1=inv(tt,m);//inv(a^(k+1))
	b=(long long)b*inv(t,m)%m;
	rep(i,0,k+3){
		int f;
		if (~(f=find(b))) put(i*(k+1)+times+f);
		b=(long long)b*inv_a_k_1 % m;
	}
	nos();
}
int main(){
	int a,m,b;
	while (scanf("%d%d%d",&a,&m,&b)==3) if (a==0 && m==0 && b==0) return 0;else work(a,b,m);}
/*
Sample Input
5 58 33
2 4 3
0 0 0

Sample Output
9
No Solution
*/
Problem1468

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
#define ec e[i].c
using namespace std;
int K;
const int N=50000,M=N*4;
struct edge{
	int to,pre,c;
}e[M];
int u[N];
int vis[N],sum=0,size[N],s[N],root;
int L=1;
void ins(int a,int b,int c){
	e[++L]=(edge){b,u[a],c};u[a]=L;
}
void insert(int a,int b,int c){
	ins(a,b,c);ins(b,a,c);
}
void get_root(int x,int fa){
	size[x]=1, s[x]=0;
	reg(i,x) if (v!=fa && (!vis[v])){
		get_root(v,x);
		size[x]+=size[v];
		s[x]=max(s[x],size[v]);
	}
	s[x]=max(s[x],sum-size[x]);
	if (s[x]<s[root]) root=x;
}
int ans=0;
int d[N],dep[N],l;
void get_dep(int x,int fa){
	dep[++l]=d[x];
	reg(i,x) if (v!=fa && (!vis[v])){
		d[v]=d[x]+ec;get_dep(v,x);
	}
}
int calc(int x,int now){
	d[x]=now, l=0, get_dep(x,0);
	sort(dep+1,dep+1+l);
	int ans=0;
	for(int i=1,j=l;i<j;i++) {
		while (dep[j]+dep[i]>K && i<j) j--;
		if (dep[j]+dep[i]<=K) ans+=(j-i);
	}
	return ans;
}
void work(int x){
	vis[x]=1;
	ans+=calc(x,0);
	reg(i,x) if (!vis[v]){
		ans-=calc(v,ec);
		sum=size[v];
		root=0;
		get_root(v,x);
		work(root);
	}
}
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n-1) {
		int a,b,c;scanf("%d%d%d",&a,&b,&c);
		insert(a,b,c);
	}
	scanf("%d",&K);
	rep(i,1,n) vis[i]=0;
	sum=n;root=0;s[0]=n;
	get_root(1,0);
	work(root);
	printf("%d\n",ans);
	return 0;
}
Problem1503

#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstdlib>//rand()
using namespace std;
const int inf=0x7fffffff;
bool r_is_inf=false;
struct node{
	int s,v,r,t;
	node *ch[2];
	int cmp(int x) const{
		if (x==v) return -1;else return (x<v?0:1);
	}
	int cmpk(int k) const{
		if (ch[0]->s>=k) return 0;
		if ((ch[0]->s)+t>=k) return -1;
		return 1;
	}
	void update(){
		s=(ch[0]->s) + (ch[1]->s) + t;
	}
};
node* nul;//instead of NULL
void rotate(node* &o,int d){
	node* k=o->ch[d];
	o->ch[d]=k->ch[d^1];
	k->ch[d^1]=o;
	o->update();k->update();
	o=k;
}
void insert(node* &o,int x){
	if (o==nul) {o=new node;o->ch[0]=o->ch[1]=nul;o->s=o->t=1;o->v=x;if (r_is_inf) o->r=inf; else o->r=rand()-100;return;}
	int d=o->cmp(x);
	if (d==-1) {
		(o->t)++;(o->s)++;if (r_is_inf) o->r=inf;
	} else {
		insert(o->ch[d],x);
		if (o->ch[d]->r > o->r) rotate(o,d); else o->update();
	}
}
int kth(node* &o,int k){
	if (o==nul) return -1;
	int d=o->cmpk(k);
	if (d==-1)return o->v;
	if (d==1) k-=(o->ch[0]->s)+o->t;
	return kth(o->ch[d],k);
}

int main(){
	srand(233);
	int ans=0;
	nul=new node;nul->s=0;
	node *root=nul;
	int n,m,a,done=0;
	char t[1];
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		scanf("%s%d",t,&a);
		if (t[0]=='I')
			if (a>=m){
				ans++;
				a-=done;
				r_is_inf=false;
				insert(root,a);
			}
		if (t[0]=='S' && a<=0){a=-a;t[0]='A';}
		if (t[0]=='A' && a>=0) done+=a;
		if (t[0]=='A' && a<0){a=-a;t[0]='S';}
		if (t[0]=='S'){
			r_is_inf=true;
			insert(root,m-done+a-1);
			root=root->ch[1];
			done-=a;
		}
		if (t[0]=='F') {
			if (a> (root->s) || a<=0) printf("%d\n",-1); else printf("%d\n",kth(root,(root->s)-a+1)+done);
		}
	}
	ans-=root->s;
	printf("%d\n",ans);
	return 0;
}
Problem1529

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int ans;
int f[1100000];
int findrt(int x){
	f[x]= (f[x]==x) ?x:findrt(f[x]);
	return f[x];
}
void gather(int a,int b){
	int q[2];
	q[0]=findrt(a),q[1]=findrt(b);
	if (q[0]!=q[1]){
		int t=rand()%2;
		f[q[t]]=q[t^1];
		ans--;
	}
}
int main(){
	srand(233);
	int n;scanf("%d",&n);
	ans=n;
	rep(i,1,n) f[i]=i;
	rep(i,1,n) {
		int f;
		scanf("%d",&f);
		gather(f,i);
	}
	printf("%d\n",ans);
	return 0;
}
Problem1552

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int inf=100000000;
using namespace std;
struct nod{
	int a,x;
}a[100200];
bool cmp(const nod &a,const nod &b){
	return a.a < b.a || (a.a==b.a && a.x < b.x);
}
struct node *null,*root;
struct node{
	node *ch[2],*f;
	int s,k,m,fl;
	int d(){return f->ch[1]==this;}
	void st(node *c,int d){ch[d]=c;c->f=this;}
	void push(){
		if (fl){
			fl=0;
			ch[0]->fl^=1;ch[1]->fl^=1;
			swap(ch[0],ch[1]);
		}
	}
	void upd(){
		s=ch[0]->s+ch[1]->s+1;
		m=min(ch[0]->m,ch[1]->m);
		m=min(m,k);
	}
}T[100200];
int l=0;
node *newnode(int a){
	node *o=&T[l++];
	o->s=1, o->k= o->m = a, o->ch[0]=o->ch[1]=o->f=null, o->fl=0;
	return o;
}
void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->f!=null) f->f->st(o,f->d());else o->f=f->f;
	f->st(o->ch[d^1],d), o->st(f,d^1);
	f->upd();
	if (f==root) root=o;//!
}
void fix(node *o){
	if (o->f!=null) fix(o->f);
	o->push();
}
void splay(node *o,node *f=null){
	fix(o);
	while (o->f!=f)
		if (o->f->f==f) rot(o);
		else (o->f->d()==o->d())?(rot(o->f),rot(o)):(rot(o),rot(o));
	o->upd();
}
node *find(node *o,int k){
	o->push();
	int s=o->ch[0]->s+1;
	if (k==s) return o;
	if (k < s) return find(o->ch[0],k); else return find(o->ch[1],k-s);
}
void get(int l,int r){
	splay(find(root,l));splay(find(root,r+2),root);
}
void ins(int x,int a){
	node *o=newnode(a);
	get(x,x-1);
	root->ch[1]->st(o,0);
	root->ch[1]->upd();
	root->upd();
}
void init(){
	null=&T[l++];
	null->k=null->m=inf;null->s=0;null->ch[0]=null->ch[1]=null->f=null;
	root=newnode(inf);
	root->st(newnode(inf),1);	
}
int fm(node *o){
	o->push();
	int s=o->ch[0]->s+1;
	if (o->m==o->k) return s;
	if (o->m==o->ch[0]->m) return fm(o->ch[0]); else return fm(o->ch[1])+s;
}
void p(node *o){
	if (o==null) return;
	o->push();
	p(o->ch[0]);printf("%d ",o->k);p(o->ch[1]);
}
bool cmp1(const nod &a,const nod &b){
	return a.x < b.x;
}
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i].a),a[i].x=i;
	sort(a+1,a+n+1,cmp);
	init();
	rep(i,1,n) a[i].a=i;
	sort(a+1,a+n+1,cmp1);
	rep(i,1,n) ins(a[i].x,a[i].a);
	rep(i,1,n){
		get(i,n);
		int t=fm(root->ch[1]->ch[0]);t+=i-1;
		printf("%d",t);if (i!=n) printf(" ");
		get(i,t);
		root->ch[1]->ch[0]->fl^=1;
	}
}
/*debug
    when find() push() first!
    if (f==root) o=root!
*/
Problem1588

type
 dot=record
     r:extended;
     lc,rc,s:longint;
 end;
 treap=array[1..1000000]of dot;
var
 ans:int64;
 T:treap;
 n,i,a,l:longint;
procedure left(x:longint);
var
 tmp:dot;
 r_c,k:longint;
begin 
 with T[x] do begin 
        r_c:=rc;
	 rc:=T[r_c].lc;
         tmp:=T[x];T[x]:=T[r_c];T[r_c]:=tmp;k:=x;x:=r_c;r_c:=k;
	 T[r_c].lc:=x;
 end;
end;
procedure right(x:longint);
var
 tmp:dot;
 l,k:longint;
begin 
 with T[x] do begin 
        l:=lc;
	 lc:=T[l].rc;
	 tmp:=T[x];T[x]:=T[l];T[l]:=tmp;k:=x;x:=l;l:=k;
	 T[l].rc:=x;
 end;
end;
 procedure add(x,d:longint);
begin
 if x>l then begin 
       inc(l);
	T[l].r:=random;T[l].s:=d;
	T[l].lc:=0;T[l].rc:=0; 
 end else with T[x] do begin 
        if d>s then begin 
		 if rc=0 then rc:=l+1;
		  add(rc,d);
		 if T[rc].r>r then left(x);
         end;
	 if d<s then begin 
	        if lc=0 then lc:=l+1;
	         add(lc,d);
		 if T[lc].r>r then right(x);
	 end;
 end;
end;
function min(a,b:longint):longint;
begin 
 if a<b then exit(a) else exit(b); 
end;
function min_64(a,b:int64):int64;
begin 
 if a<b then exit(a) else exit(b); 
end;
function max(a,b:longint):longint;
begin
 if a>b then exit(a) else exit(b); 
end;
function pre(x,d:longint):longint;
begin
 if x=0 then  exit(-maxlongint);
  with T[x] do begin 
        if s=d then exit(s);
        if s<d then exit(max(s,pre(rc,d))) else exit(pre(lc,d));
  end;
end;
function next(x,d:longint):longint;
begin
 if x=0 then exit(maxlongint);
  with T[x] do begin 
        if s=d then exit(s);
         if s>d then exit(min(s,next(lc,d))) else exit(next(rc,d));
 end;
end;
begin
 randomize; 
 readln(n);l:=0;
 readln(a);ans:=a;add(1,a);
 for i:=2 to n do begin 
        if eof then a:=0 else readln(a);
	 ans:=ans+min_64(abs(int64(pre(1,a))-int64(a)),abs(int64(next(1,a))-int64(a)));
	 add(1,a);
 end;
 writeln(ans);
end.
Problem1588

#include <cstdio>
#include <cmath>
#include <cstdlib>//rand
#include <iostream>
using namespace std;
const int inff=50000000;
int n,a;
long long ans;
struct node{
	node *ch[2];
	int v,r;
	int cmp(int x) const{
		if (x==v) return -1;
		return x<v?0:1;
	}
};
void rotate(node* &o,int d){
	node *k=o->ch[d];
	o->ch[d]=k->ch[d^1];
	k->ch[d^1]=o;
	o=k;//!
}
void insert(node* &o,int x){
	if (o==NULL){o=new node;o->ch[0]=o->ch[1]=NULL;o->v=x;o->r=rand();}
    else {
    	int d=o->cmp(x);
    	if (d!=-1){
    		insert(o->ch[d],x);
    		if (o->ch[d]->r > o->r) rotate(o,d);
    	}
    }
}
int pre(node* &o,int x){
	if (o==NULL) return -inff;
	int d=o->cmp(x);
	if (d==-1) return x; else return max(pre(o->ch[d],x),!d?-inff:o->v);
}
int next(node* &o,int x){
	if (o==NULL) return inff;
	int d=o->cmp(x);
	if (d==-1) return x; else return min(next(o->ch[d],x),!d?o->v:inff);
}
int main(){
	srand(1201);
	scanf ("%d",&n);
	scanf ("%d",&a);ans=abs(a);
	node *root=new node;
	root->ch[0]=root->ch[1]=NULL;root->v=a;root->r=rand();
	for (int i=2;i<=n;i++){
		if (scanf("%d",&a)==EOF) a=0;
		ans+=min(abs(a-pre(root,a)),abs(next(root,a)-a));
		insert(root,a);
	}
	printf("%d\n",ans);
	return 0;
}
Problem1588

#include <cstdio>
#include <cmath>
#include <cstdlib>//rand
#include <iostream>
using namespace std;
const int inff=50000000;
int n,a;
long long ans;
struct node{
	int v;
	node *ch[2];
	int cmp(int x)const{
		if (x==v) return -1; else return x<v?0:1;
	}
};
node *root;
void rotate(node* &o,int d){
	node* k=o->ch[d];
	o->ch[d]=k->ch[d^1];
	k->ch[d^1]=o;
	o=k;
}
void splay(node* &o,int x){
	int d=o->cmp(x);
	if (d!=-1){
		int d1=o->ch[d]->cmp(x);
		if (d1!=-1) {
			splay(o->ch[d]->ch[d1],x);
			if (d==d1) rotate(o,d); else rotate(o->ch[d],d1);
		}
		rotate(o,d);
	}
}
void insert(node* &o,int x){
	if (o==NULL){o=new node;o->ch[0]=o->ch[1]=NULL;o->v=x;splay(root,x);return;}
	int d=o->cmp(x);
	if (d!=-1) insert(o->ch[d],x);
}
int pre(node* &o,int x){
	if (o==NULL) return -inff;
	int d=o->cmp(x);
	if (d==-1) return x; else return max(pre(o->ch[d],x),!d?-inff:o->v);
}
int next(node* &o,int x){
	if (o==NULL) return inff;
	int d=o->cmp(x);
	if (d==-1) return x; else return min(next(o->ch[d],x),!d?o->v:inff);
}
int main(){
	scanf ("%d",&n);
	scanf ("%d",&a);ans=abs(a);
	root=new node;
	root->ch[0]=root->ch[1]=NULL;root->v=a;
	for (int i=2;i<=n;i++){
		if (scanf("%d",&a)==EOF) a=0;
		ans+=min(abs(a-pre(root,a)),abs(next(root,a)-a));
		insert(root,a);
	}
	cout <<ans;
	return 0;
}
Problem1590

type
   dot=record 
	     ch:array[0..1]of longint;
		 times,sum:longint;
	end;
var
     l:longint;
     a:array[1..1000000]of dot;
	 n,m,i:longint;
procedure new;
begin
  inc(l);
  a[l].ch[0]:=0;a[l].ch[1]:=0;a[l].times:=0;a[l].sum:=0; 
end;
procedure insert;
var
 k,x,t,i:longint;
begin
     x:=1;read(t);
     for i:=1 to t do begin 
		 inc(a[x].sum);
		 read(k);
		 if a[x].ch[k]=0 then begin new;a[x].ch[k]:=l;end;
		 x:=a[x].ch[k];
	 end;
	 inc(a[x].times);
	 readln;
end;
procedure work;
var 
 flag:boolean;
 k,x,ans,t,i:longint;
begin 
     x:=1;ans:=0;read(t);flag:=true;
     for i:=1 to t do begin 
		 read(k);
		 if a[x].ch[k]=0 then begin flag:=false;break;end;
		 x:=a[x].ch[k];ans:=ans+a[x].times;
	 end;
	 if flag then ans:=ans+a[x].sum;
	 writeln(ans);
	 readln;
end;
begin 
   readln(n,m);l:=0;new;
	for i:=1 to n do insert;
	for i:=1 to m do work;
end.
Problem1592

//f[i][j]表示修到i，高为b[j]的最小花费
//f[i][j]=min(f[i-1][y]|y<=j)+abs(a[i]-b[j]))
var
 n,i,j,g,ans:longint;
 a,b:array[0..2000]of longint;
 f:array[0..2000,0..2000]of longint;
procedure sort(l,r:longint);
var
 i,j,t,m:longint;
begin
 i:=l;j:=r;m:=b[(l+r) shr 1]; 
 repeat
    while b[i]<m do inc(i);
	while b[j]>m do dec(j);
	if i<=j then begin 
	   t:=b[i];b[i]:=b[j];b[j]:=t;
	   inc(i);dec(j);
	end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
function min(a,b:longint):longint;
begin
 if a<b then exit(a) else exit(b); 
end;
begin 
 readln(n);
 for i:=1 to n do readln(a[i]);
 b:=a;
 sort(1,n);
 b[0]:=maxlongint;
 fillchar(f,sizeof(f),0);
 for i:=1 to n do begin 
    g:=maxlongint;
    for j:=1 to n do begin	
		g:=min(g,f[i-1][j]);
	    f[i][j]:=g+abs(a[i]-b[j]);
	end;
 end;
 ans:=maxlongint;
 for i:=1 to n do ans:=min(ans,f[n][i]);
 fillchar(f,sizeof(f),0);
 for i:=1 to n do begin 
    g:=maxlongint;
    for j:=n downto 1 do begin	
		g:=min(g,f[i-1][j]);
	    f[i][j]:=g+abs(a[i]-b[j]);
	end;
 end;
 for i:=1 to n do ans:=min(ans,f[n][i]);
 writeln(ans);
end.
Problem1597

type
 rec=record
     x,y:int64;
 end;
 dot=rec;
var
 x:dot;
 F,max_y:int64;
 n,m,i,top,tail:longint;
 a,b:array[1..500000]of rec;
 q:array[1..1000000]of dot;
function cmp(a,b:rec):boolean;
begin
 if a.x>b.x then exit(true);
 if (a.x=b.x) and (a.y>b.y) then exit(true);
 exit(false);
end;
procedure sort(l,r:longint);
var
 m,t:rec;
 i,j:longint;
begin
 i:=l;j:=r;m:=a[(l+r) shr 1];
 repeat
   while cmp(a[i],m) do inc(i);
   while cmp(m,a[j]) do dec(j);
   if i<=j then begin 
     t:=a[i];a[i]:=a[j];a[j]:=t;
	 inc(i);dec(j);
   end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
procedure push(x:dot);
var
 i:longint;
begin
 for i:=tail downto top+1 do begin 
     if (x.y-q[i].y)/(x.x-q[i].x)<=(q[i].y-q[i-1].y)/(q[i].x-q[i-1].x) then begin 
	     tail:=i+1;q[tail]:=x;exit;
	 end;
 end;
 if top>tail then begin inc(tail);q[tail]:=x;end else begin q[top+1]:=x;tail:=top+1;end;
end;
function pop(x:longint):dot;
var
 i:longint;
begin 
 for i:=top to tail-1 do begin 
     if (q[i+1].y-q[i].y)/(q[i+1].x-q[i].x)<x then begin top:=i;exit(q[i]);end;
 end;
 top:=tail;exit(q[tail]);
end;
begin 
 readln(n);
 for i:=1 to n do with a[i] do readln(x,y);
 sort(1,n);max_y:=0;m:=0;
 for i:=1 to n do 
     if a[i].y>max_y then begin 
	     max_y:=a[i].y;inc(m);b[m]:=a[i];
     end; 
 top:=1;tail:=1;q[1].x:=b[1].x;q[1].y:=0;
 for i:=1 to m do begin 
     x:=pop(-b[i].y);
	 f:=x.y+x.x*b[i].y;
	 if i<m then begin 
	     x.y:=f;x.x:=b[i+1].x;
	     push(x);
	 end;
 end;
 writeln(f);
end.
Problem1606

const
 maxc=50000;
var
 c,h,v,i,j:longint;
 f:array[0..maxc]of longint;
 function max(a,b:longint):longint;
 begin
     if a>b then exit(a) else exit(b); 
 end;
begin 
 readln(c,h);
 fillchar(f,sizeof(f),0);
 for i:=1 to h do begin 
         readln(v);
	 for j:=c downto v do f[j]:=max(f[j],f[j-v]+v);
 end;
 writeln(f[c]);
end.
Problem1607

var
 i,max,n,j:longint;
 a:array[1..100000]of longint;
 ans,cnt:array[1..1000000]of longint;
 k:array[1..1000000]of boolean;
 begin 
  readln(n);max:=0;fillchar(k,sizeof(k),false);
  for i:=1 to n do begin 
         readln(a[i]);inc(cnt[a[i]]);
	 if a[i]>max then max:=a[i];
  end;
  for i:=1 to n do begin
         if k[a[i]] then continue;  
         k[a[i]]:=true;
         for j:=1 to max div a[i] do 
	         ans[a[i]*j]:=ans[a[i]*j]+cnt[a[i]];
	 cnt[a[i]]:=0;
 end;
  for i:=1 to n do writeln(ans[a[i]]-1);
end.
Problem1610

const
 zero=1e-8;
var
 l,ans,i,j,n:longint;
 x,y:array[1..400]of extended;
 k:array[1..90000]of extended;
 flag:boolean;
procedure sort(l,r:longint);
var
 i,j:longint;
 m,t:extended;
begin 
 i:=l;j:=r;m:=k[(i+j) shr 1];
 repeat
     while k[i]<m do inc(i);
     while k[j]>m do dec(j);
    if i<=j then begin 
         t:=k[i];k[i]:=k[j];k[j]:=t;
          inc(i);dec(j);		 
    end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin 
 readln(n);flag:=false;ans:=0;l:=0;
 for i:=1 to n do readln(x[i],y[i]);
 for i:=1 to n do 
        for j:=i+1 to n do
             if abs(x[i]-x[j])<zero then begin 
			  if not flag then inc(ans);flag:=true;
	     end else begin 
	          inc(l);k[l]:=(y[i]-y[j])/(x[i]-x[j]);
	     end;
 sort(1,l);
 if l>0 then inc(ans);
 for i:=2 to l do if abs(k[i]-k[i-1])>zero then inc(ans);
 writeln(ans);
end.
Problem1610

const
 zero=1e-8;
var
 l,ans,i,j,n:longint;
 x,y:array[1..200]of extended;
 k:array[1..40000]of extended;
 flag:boolean;
procedure sort(l,r:longint);
var
 i,j:longint;
 m,t:extended;
begin 
 i:=l;j:=r;m:=k[(i+j) shr 1];
 repeat
     while k[i]<m do inc(i);
     while k[j]>m do dec(j);
    if i<=j then begin 
         t:=k[i];k[i]:=k[j];k[j]:=t;
          inc(i);dec(j);		 
    end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin 
 readln(n);flag:=false;ans:=0;l:=0;
 for i:=1 to n do readln(x[i],y[i]);
 for i:=1 to n do 
        for j:=i+1 to n do
             if abs(x[i]-x[j])<zero then begin 
			  if not flag then inc(ans);flag:=true;
	     end else begin 
	          inc(l);k[l]:=(y[i]-y[j])/(x[i]-x[j]);
	     end;
 sort(1,l);
 if l>0 then inc(ans);
 for i:=2 to l do if abs(k[i]-k[i-1])>zero then inc(ans);
 writeln(ans);
end.
Problem1612

type
 arr=array[1..100]of boolean; 
var
 ans,n,m,i:longint;
 u,v:array[1..4500]of longint;
 h,f,g:array[0..100]of longint;
 a:array[1..100]of arr;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin
  i:=l;j:=r;m:=u[(l+r) shr 1];
  repeat
         while u[i]<m do inc(i);
         while u[j]>m do dec(j);
	 if i<=j then begin 
	        t:=u[i];u[i]:=u[j];u[j]:=t;
	        t:=v[i];v[i]:=v[j];v[j]:=t;
	        inc(i);dec(j);
	 end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
 end; 
 procedure sort_2(l,r:longint);
var
 i,j,m,t:longint;
begin
  i:=l;j:=r;m:=v[(l+r) shr 1];
  repeat
         while v[i]<m do inc(i);
         while v[j]>m do dec(j);
	 if i<=j then begin 
	        t:=u[i];u[i]:=u[j];u[j]:=t;
	        t:=v[i];v[i]:=v[j];v[j]:=t;
	        inc(i);dec(j);
	 end;
  until i>j;
  if l<j then sort_2(l,j);
  if i<r then sort_2(i,r);
 end;
 function gether(a,b:arr):arr;
var
 i:longint;
 begin 
   for i:=1 to n do if a[i] or b[i] then gether[i]:=true else gether[i]:=false;
 end;
procedure dp_f(x:longint);
var
 i:longint;
begin 
     if f[x]>0 then exit;
     fillchar(a[x],sizeof(a[x]),false);
     a[x,x]:=true;
     i:=h[x];
     while u[i]=x do begin 
	 dp_f(v[i]);
         a[x]:=gether(a[x],a[v[i]]);
	 inc(i);
     end;
     for i:=1 to n do if a[x][i] then inc(f[x]);
end;
procedure dp_g(x:longint);
var
 i:longint;
begin 
     if g[x]>0 then exit;
     fillchar(a[x],sizeof(a[x]),false);
     a[x,x]:=true;
     i:=h[x];
     while v[i]=x do begin 
	 dp_g(u[i]);
         a[x]:=gether(a[x],a[u[i]]);
	 inc(i);
     end;
     for i:=1 to n do if a[x][i] then inc(g[x]);
end;
begin 
 readln(n,m);
 for i:=1 to m do readln(u[i],v[i]);
 sort(1,m);
 for i:=m downto 1 do h[u[i]]:=i;
 for i:=1 to n do dp_f(i);
 sort_2(1,m);
 for i:=m downto 1 do h[v[i]]:=i;
 for i:=1 to n do dp_g(i);
 for i:=1 to n do if f[i]+g[i]=n+1 then inc(ans);
 writeln(ans);
end.
Problem1613

const
  maxn=10010;
  maxm=510;
var
 n,m,i,j:longint;
 d:array[1..maxn]of longint;
 f:array[0..maxn,0..maxm]of longint;
function max(a,b:longint):longint;
begin
 if a>b then exit(a) else exit(b); 
end;
 begin 
 readln(n,m);
 for i:=1 to n do readln(d[i]);
 fillchar(f,sizeof(f),0);
 for i:=1 to n do begin 
     for j:=1 to m do begin 
         if i-j<0 then break;
	 if f[i-j,j]>f[i,0] then f[i,0]:=f[i-j,j];
     end;
    if f[i-1,0]>f[i,0] then f[i,0]:=f[i-1,0];
     for j:=1 to m do 
	  f[i,j]:=f[i-1,j-1]+d[i];
 end;
 writeln(f[n,0]);
end.
Problem1614

var
 n,p,k,max,ll,r,mid,i:longint;
 a,b,l,c,h:array[1..20000]of longint;
 q:array[1..2000000]of longint;
 inq:array[1..2000]of boolean;
 dis:array[1..2000]of longint;
procedure sort(ll,r:longint);
var
 i,j,t,m:longint;
begin 
 i:=ll;j:=r;m:=a[(ll+r) shr 1];
 repeat
      while a[i]<m do inc(i);
      while a[j]>m do dec(j);
      if i<=j then begin 
            t:=a[i];a[i]:=a[j];a[j]:=t;
            t:=b[i];b[i]:=b[j];b[j]:=t;
            t:=l[i];l[i]:=l[j];l[j]:=t;
	     inc(i);dec(j);
	end;
 until i>j;
 if ll<j then sort(ll,j);
 if i<r then sort(i,r);
end;
function check(mid:longint):boolean;
var 
 i,ll,r,u,v:longint;
begin 
  for i:=1 to p do if l[i]<=mid then c[i]:=0 else c[i]:=1;
  ll:=1;r:=2;q[ll]:=1;fillchar(inq,sizeof(inq),false);
  for i:=1 to n do dis[i]:=-1;
  dis[1]:=0;
  repeat
         u:=q[ll];inq[u]:=false;
	 i:=h[u];
	 while a[i]=u do begin 
	        v:=b[i];
	        if (dis[v]=-1) or (dis[u]+c[i]<dis[v]) then begin 
	                 dis[v]:=dis[u]+c[i];
			 if not inq[v] then begin 
				  inq[v]:=true;
				  q[r]:=v;inc(r);
		         end;
	        end;
                 inc(i);
	 end;
	 inc(ll);
  until ll+1>r;
 if dis[n]=-1 then begin writeln(-1);halt;end;
 if dis[n]<=k then  exit(true) else exit(false);
end;
begin
 readln(n,p,k);max:=0;
 for i:=1 to p do begin 
         readln(a[i],b[i],l[i]);
	 a[p+i]:=b[i];b[p+i]:=a[i];l[p+i]:=l[i];
          if l[i]>max then max:=l[i];
 end;
 p:=p*2;
 sort(1,p);
 for i:=p downto 1 do h[a[i]]:=i;
 ll:=-1;r:=max;//(ll,r]
 repeat
     mid:=(ll+r) shr 1;
     if check(mid) then r:=mid else ll:=mid;
 until ll+1=r;
 if check(r) then writeln(r) else writeln(-1);
end.
Problem1617

const
 inf=5000000;
var
 n,m,a,i,j:longint;
 s:array[0..2500]of longint;
 f:array[0..2500]of longint;
begin 
 readln(n,m);s[0]:=0;
 for i:=1 to n do begin   
          read(a);
	 s[i]:=s[i-1]+a;
 end;
 f[0]:=0;
 for i:=1 to n do  begin 
           f[i]:=inf;
          for j:=0 to i-1 do 
		  if f[j]+s[i-j]+2*m<f[i] then f[i]:=f[j]+s[i-j]+2*m;
 end;
 writeln(f[n]-m);
end.
Problem1618

const
  maxr=60000;
  inf=100000000;
var
 n,r,i,j,ans:longint;
 f:array[0..maxr]of longint;
 p,c:array[1..100]of longint;
begin 
 readln(n,r);
 for i:=1 to n do readln(p[i],c[i]);
 for i:=1 to maxr do f[i]:=inf;
 f[0]:=0;
 for i:=1 to n do 
  for j:=p[i] to maxr do
          if f[j-p[i]]+c[i]<f[j] then f[j]:=f[j-p[i]]+c[i];
 ans:=inf;
 for i:=r to maxr do if f[i]<ans then ans:=f[i];
 writeln(ans);
end.
Problem1620

var
 n,i,ans:longint;
 s,t:array[1..1000]of longint;
procedure sort(l,r:longint);
var
 i,j,m,tmp:longint;
begin
  i:=l;j:=r;m:=s[(l+r) shr 1];
  repeat
          while s[i]<m do inc(i);
	 while s[j]>m do dec(j);
	 if i<=j then  begin 
	          tmp:=s[i];s[i]:=s[j];s[j]:=tmp;
	          tmp:=t[i];t[i]:=t[j];t[j]:=tmp;
		 inc(i);dec(j);
	 end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;
function min(a,b:longint):longint;
begin
 if a<b then exit(a) else exit(b); 
end;
begin 
 readln(n);
 for i:=1 to n do readln(t[i],s[i]);
 sort(1,n);
 ans:=s[n];
 for i:=n downto 1 do begin 
          ans:=min(ans,s[i]);
	 ans:=ans-t[i];
 end;
 if ans<0 then writeln(-1) else writeln(ans);
end.
Problem1621

const
 mo=411529;
var
  n,k,l:longint;
 function f(x:longint):longint;
 begin
     if (x mod 2<>k mod 2) or (x<=k) then exit(1);
    f:=f((x+k) shr 1)+f((x-k) shr 1);
   exit(f);
 end;
begin 
 l:=0;
  readln(n,k);
  writeln(f(n));
end.
Problem1623

var
 n,m,d,l,i,k,ans:longint;
 v:array[1..500000]of longint;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin
   i:=l;j:=r;m:=v[(l+r) shr 1];
   repeat
         while v[i]<m do inc(i);
         while v[j]>m do dec(j);
	if i<=j then begin 
		  t:=v[i];v[i]:=v[j];v[j]:=t;
		  inc(i);dec(j);
	 end;	
   until i>j;
   if l<j then sort(l,j);
   if i<r then sort(i,r);
end;
 begin
 readln(n,m,d,l);
 for i:=1 to n do readln(v[i]); 
 sort(1,n);ans:=0;
 for i:=1 to n do begin 
          k:=ans div m;
	 if v[i]-k*d >=l then inc(ans);
 end;
 writeln(ans);
end.
Problem1624

var
 n,m,k,ans,i,j:longint;
 a:array[1..100000]of longint;
 f:array[1..100,1..100]of longint;
begin 
 readln(n,m);
 for i:=1 to m do readln(a[i]);
 for i:=1 to n do for j:=1 to n do f[i][j]:=-1;
 for i:=1 to n do begin 
     for j:=1 to n do read(f[i][j]);
     readln;
 end;
 for k:=1 to n do  
          for i:=1 to n do 
		  for j:=1 to n do 
		         if (f[i,k]>=0) and (f[k,j]>=0) and ((f[i,k]+f[k,j]<f[i,j]) or (f[i,j]=-1)) then f[i,j]:=f[i,k]+f[k,j];
 ans:=f[1,a[1]];
 for i:=2 to m do ans:=ans+f[a[i-1],a[i]];
 writeln(ans);
end.
Problem1635

//The most important point to notice is that the "see" relationships can be disjoint or one can lie inside another, but they cannot cross over.
var
 f,hash:array[0..10000]of longint;//f[i]=h[i]-h[i-1]
 v,pre:array[0..1000000]of longint;
 l,a,b,ans,n,k,maxh,r,i:longint;
procedure swap(var  a,b:longint);
var
 c:longint;
begin
 c:=a;a:=b;b:=c; 
end;
function find(a,b:longint):boolean;
var
 i:longint;
begin 
 i:=hash[a];
 while i<>0 do begin 
     if v[i]=b then exit(true);
	 i:=pre[i];
 end;
 exit(false);
end;
procedure insert(a,b:longint);
begin 
 inc(l);v[l]:=b;
 pre[l]:=hash[a];hash[a]:=l;
end;
begin
 readln(n,k,maxh,r);
 fillchar(f,sizeof(f),0);
 f[0]:=maxh;l:=0;
 for i:=1 to r do begin 
     readln(a,b);if a>b then swap(a,b);
	 if find(a,b) then continue else insert(a,b);
	 //(a,b)-1
	 dec(f[a+1]);
     inc(f[b]);
  end;
  ans:=maxh;
 for i:=1 to n do begin 
    ans:=ans+f[i];
	writeln(ans);
 end;
end.
Problem1636

uses math;
var
 n,q,m,i,l,r:longint;
 a,b:array[1..1000000]of longint;
function ma(l,r:longint):longint;
begin 
 l:=l+m;r:=r+m;dec(l);inc(r);ma:=0;
 while l xor r<>1 do begin 
    if l and 1=0 then ma:=max(ma,a[l+1]);
	if r and 1=1 then ma:=max(ma,a[r-1]);
	l:=l shr 1;r:=r shr 1;
 end;
end;
function mb(l,r:longint):longint;
begin 
 l:=l+m;r:=r+m;dec(l);inc(r);mb:=maxlongint;
 while l xor r<>1 do begin 
    if l and 1=0 then mb:=min(mb,b[l+1]);
	if r and 1=1 then mb:=min(mb,b[r-1]);
	l:=l shr 1;r:=r shr 1;
 end;
end;
begin
 readln(n,q);
 m:=1;while m<n+2 do m:=m shl 1;
 for i:=m+1 to m+n do begin read(a[i]);b[i]:=a[i];end;
 for i:=m-1 downto 1 do begin 
    a[i]:=max(a[i shl 1],a[(i shl 1)+1]);
	b[i]:=min(b[i shl 1],b[(i shl 1)+1]);
 end;
 for i:=1 to q do begin 
   readln(l,r);writeln(ma(l,r)-mb(l,r));
 end;
end.
Problem1637

var
 s,n,i,ans:longint;
 hash,id,x:array[1..50000]of longint;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin 
 i:=l;j:=r;m:=x[(l+r) shr 1];
 repeat
   while x[i]<m do inc(i);
   while x[j]>m do dec(j);
   if i<=j then begin 
     t:=x[i];x[i]:=x[j];x[j]:=t;
	 t:=id[i];id[i]:=id[j];id[j]:=t;
	 inc(i);dec(j);
   end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin 
 readln(n);
 for i:=1 to n do begin 
    readln(id[i],x[i]);if id[i]=0 then id[i]:=-1;
 end;
 sort(1,n);s:=0;ans:=0;fillchar(hash,sizeof(hash),0);
 for i:=1 to n do begin 
   if hash[s]=0 then hash[s]:=i;
   s:=s+id[i];
   if (hash[s]<>0) and (x[i]-x[hash[s]]>ans) then ans:=x[i]-x[hash[s]];
 end;
 writeln(ans);
end.
Problem1638

var
 u,v:array[0..50000]of longint;
 f,g,h:array[1..5000]of int64;
 i,n,m,t:longint;
 ans:int64;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin 
 i:=l;j:=r;m:=u[(l+r) shr 1];
 repeat
    while u[i]<m do inc(i);
	while u[j]>m do dec(j);
	if i<=j then begin 
	    t:=u[i];u[i]:=u[j];u[j]:=t;
	    t:=v[i];v[i]:=v[j];v[j]:=t;
		inc(i);dec(j);
	end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
procedure dp1(x:longint);
var
 i:longint;
begin 
 if x=n then f[x]:=1 else f[x]:=0;
 i:=h[x];
 while u[i]=x do begin 
     if f[v[i]]=-1 then dp1(v[i]);
	 f[x]:=f[x]+f[v[i]];
	 inc(i);
 end;
end;
procedure dp2(x:longint);
var
 i:longint;
begin 
 g[x]:=0;
 i:=h[x];if u[i]<>x then g[x]:=1;
 while u[i]=x do begin 
     if g[v[i]]=-1 then dp2(v[i]);
	 g[x]:=g[x]+g[v[i]];
	 inc(i);
 end;
end;
begin 
 readln(n,m);
 for i:=1 to n do begin 
     f[i]:=-1;g[i]:=-1;
 end;
 for i:=1 to m do readln(u[i],v[i]);
 sort(1,m);
 for i:=m downto 1 do h[u[i]]:=i;
 for i:=1 to n do if f[i]=-1 then dp1(i);
 for i:=1 to m do begin 
     t:=u[i];u[i]:=v[i];v[i]:=t;
 end;
 sort(1,m);
 for i:=m downto 1 do h[u[i]]:=i;
 for i:=1 to n do 
	 if g[i]=-1 then dp2(i);
 ans:=0;
 for i:=1 to m do if f[u[i]]*g[v[i]]>ans then ans:=f[u[i]]*g[v[i]];
 writeln(ans); 
end.
Problem1650

const
 maxn=50000;
var
 T,n,m,i,l,r,mid:longint;
 d:array[1..maxn] of longint;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin
 i:=l;j:=r;m:=d[(l+r) shr 1];
 repeat
   while d[i]<m do inc(i);
	 while d[j]>m do dec(j);
	 if i<=j then begin 
	    t:=d[i];d[i]:=d[j];d[j]:=t;
			inc(i);dec(j);
	 end;
 until i>j; 
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
function check(x:longint):boolean;
var
 i,last,cnt:longint;
begin 
 last:=0;cnt:=0;
 for i:=1 to n do
   if d[i]-last<x then inc(cnt) else last:=d[i];
 for i:=n downto 1 do 
   if T-d[i]<x then inc(cnt) else break;
 if cnt>m then exit(false) else exit(true);
end;
begin 
 readln(T,n,m);
 for i:=1 to n do readln(d[i]);
 sort(1,n);
 l:=1;r:=T+1;//[l,r)
 repeat
  mid:=(l+r) shr 1;
	if check(mid) then l:=mid else r:=mid;
 until l+1=r;
 writeln(l);
end.
Problem1657

var
 n,i,max:longint;
 h,v,a:array[1..50000]of longint;
 top:longint;
 s:array[0..50000]of longint;
begin 
 readln(n);fillchar(a,sizeof(a),0);
 for i:=1 to n do readln(h[i],v[i]);
 //right
 top:=0;
 for i:=1 to n do begin 
   while (top>0) and (h[s[top-1]]<h[i]) do begin
	   inc(a[i],v[s[top-1]]);dec(top);
	 end;
	 s[top]:=i;inc(top);
 end;
 //left
 top:=0;
 for i:=n downto 1 do begin 
   while (top>0) and (h[s[top-1]]<h[i]) do begin
	   inc(a[i],v[s[top-1]]);dec(top);
	 end;
	 s[top]:=i;inc(top);
 end;
 max:=1;
 for i:=2 to n do if a[i]>a[max] then max:=i;
 writeln(a[max]);
end.
Problem1660

#include <iostream>
using namespace std;
int n,h[80001],s[80001],top;
long long ans;
int main(){
	cin >>n;int i;
	for (i=1;i<=n;i++) cin>>h[i];
    top=1;s[top]=n;ans=0;
    for (i=n-1;i>=1;i--) {
    	while ((h[s[top]] < h[i]) && top) top--;
    	if (!top) ans+=n-i; else ans+=s[top]-i-1;
    	if ((h[s[top]]==h[i]) && top) top--;
    	s[++top]=i;
    }
    cout <<ans;
    return 0;
}
Problem1663

var
 n,i,j,ans,t:longint;
 p,h,f:array[1..400]of longint;
 a:array[1..400,1..400]of longint;
begin 
 readln(n);
 for i:=1 to n do readln(p[i]);
 for i:=1 to n do 
     for j:=1 to n do 
	   readln(a[i][j]);
 for i:=1 to n do h[i]:=i;
 for i:=1 to n do
     for j:=n downto i+1 do 
	   if p[h[j]]<p[h[j-1]] then begin t:=h[j];h[j]:=h[j-1];h[j-1]:=t;end;
 ans:=0;
 for i:=1 to n do begin 
	   f[h[i]]:=0;
	   if a[1][h[1]]<=p[h[i]] then f[h[i]]:=1;
       for j:=1 to i-1 do begin
          if p[h[j]]+a[h[j]][h[i]]<=p[h[i]] then 
			 if f[h[j]]+1>f[h[i]] then f[h[i]]:=f[h[j]]+1;
       end;
	   if f[h[i]]>ans then ans:=f[h[i]];
 end;
 writeln(ans);
end.
Problem1672

//f[i]=f[j]+s[k] 
//f[r[i]]=min{f[j]|j>=l[i]-1} 按照r[i]排序l[i]没有单调性 所以无法使用单调队列 
//min{f[l[i]..e]}BIT
var
 n,m,e,a,b,c,l,t,i,k:longint;
 t1,t2,s:array[1..100000]of longint;
 f:array[1..1000000]of longint;
procedure swap(a,b:longint);
var
 t:longint;
begin
 t:=t1[a];t1[a]:=t1[b];t1[b]:=t;
 t:=t2[a];t2[a]:=t2[b];t2[b]:=t;
 t:=s[a];s[a]:=s[b];s[b]:=t; 
end;
procedure sort(l,r:longint);
var
 m,i,j:longint;
begin 
 i:=l;j:=r;m:=t2[(l+r) shr 1];
 repeat
    while t2[i]<m do inc(i);
	while t2[j]>m do dec(j);
	if i<=j then begin 
	    swap(i,j);inc(i);dec(j);
	end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
function min(x:longint):longint;
begin
  min:=maxlongint;
  while x<=e do begin 
     if f[x]<min then min:=f[x];x:=x+(-x) and x;
  end;
end;
procedure setas(x,new:longint);
begin
 while x>0 do begin 
     if f[x]>new then f[x]:=new;x:=x-(-x) and x;
 end;
end;
begin 
 readln(n,m,e);l:=0;
 for i:=1 to n do begin 
     readln(a,b,c);
	 if a<m then a:=m;
	 if b>e then b:=e;
	 if a<=b then begin 
	     inc(l);t1[l]:=a;t2[l]:=b;s[l]:=c;
	 end;
 end;
 n:=l;
 sort(1,n);
 for i:=1 to n do begin 
     t2[i]:=t2[i]-(m-2);t1[i]:=t1[i]-(m-2);
 end;
 e:=e-(m-2);m:=2;
 for i:=2 to e do f[i]:=maxlongint;
 f[1]:=0;
 for i:=1 to n do begin 
     k:=min(t1[i]-1);
	 if k=maxlongint then continue;
	 t:=k+s[i];
	 setas(t2[i],t);
 end;
 if f[e]=maxlongint then writeln(-1) else writeln(f[e]);
end.
Problem1676

var
 c,f1,f2,d,i,fd:longint;
 s,a,b:array[0..2000]of longint;
begin 
 readln(c,f1,f2,d);fillchar(s,sizeof(s),0);
 for i:=1 to c do begin 
    readln(a[i],b[i]);if b[i]>d then b[i]:=d;
	inc(s[a[i]],1);dec(s[b[i]+1]);
 end;
 fd:=0;
 for i:=1 to d do fd:=fd+s[i];
 for i:=d downto 1 do begin 
	f2:=f2+fd;
	if f2=f1 then begin writeln(i);halt;end;
	fd:=fd-s[i];
 end;
 writeln(0);
end.
Problem1676

var
 c,f1,f2,d,i,fd,a,b:longint;
 s:array[0..2000]of longint;
begin 
 readln(c,f1,f2,d);fillchar(s,sizeof(s),0);
 for i:=1 to c do begin 
    readln(a,b);if b>d then b:=d;
	inc(s[a],1);dec(s[b+1]);
 end;
 fd:=0;
 for i:=1 to d do fd:=fd+s[i];
 for i:=d downto 1 do begin 
	f2:=f2+fd;
	if f2=f1 then begin writeln(i);halt;end;
	fd:=fd-s[i];
 end;
 writeln(0);
end.
Problem1677

#include<iostream>
using namespace std;
int f[1000000],n;
int main(){
  f[0]=1;cin >>n;
  for (int i=1;i<=n;i++){
  	f[i]=f[i-1];
  	if (!(i & 1)) f[i]+=f[i >> 1];
  	f[i]%=1000000000;
  }
  cout <<f[n]<<"\n";
  return 0;
}
Problem1679

var
 ans:int64;
 n,i:longint;
 a:array[1..1000000]of longint;
procedure sort(l,r:longint);
var
 i,j,t,m:longint;
begin
 i:=l;j:=r;m:=a[(l+r) shr 1];
 repeat
   while a[i]<m do inc(i);
   while a[j]>m do dec(j);
   if i<=j then begin 
     t:=a[i];a[i]:=a[j];a[j]:=t;
	 inc(i);dec(j);
   end;	 
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;
begin 
 read(n);
 for i:=1 to n do read(a[i]);
 sort(1,n);
 for i:=1 to n-1 do 
   ans:=ans+int64(i*(n-i))*(a[i+1]-a[i]);
 writeln(ans*2);
end.
Problem1685

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=30;
struct node{
	int a,b;
};
int n,c;
node s[maxn];
bool cmp(const node &a,const node &b){return(a.a<b.a);}
int main(){
	cin >>n>>c;
	int i;
	for (i=1;i<=n;i++){
		int x,y;cin >>x>>y;
		s[i].a=x;s[i].b=y;
	}	                                
	sort(s+1,s+n+1,cmp);
	int ans;
    for (ans=0;;ans++){
    	int t=c;
    	for (i=n;i>=1 && t>0;i--){
    		int tmp=min(t/s[i].a,s[i].b>0?s[i].b:0);
    		s[i].b-=tmp;t-=tmp*s[i].a;
    	}
    	if (!t) continue;
        for (i=1;i<=n && !s[i].b;i++);
        if (!s[i].b) break;
        s[i].b--;
    }
	cout <<ans;
	return 0;
}
Problem1691

#include <iostream>
#include <algorithm>
#include <set>
#define ll long long 
using namespace std;
struct node{
	int a,b;
};
bool cmp(const node &a,const node &b){return a.b>b.b;}
const int maxn=100000;
node a[maxn],b[maxn];
int n,m,i,j;
multiset<int>s;
ll ans;
int main(){
  cin >>n>>m;
  for (i=0;i<n;i++) cin>>a[i].a>>a[i].b;
  for (i=0;i<m;i++) cin>>b[i].a>>b[i].b;
  sort(a,a+n,cmp);sort(b,b+m,cmp);
  j=0;ans=0;
  for (i=0;i<n;i++){
  	while (b[j].b>=a[i].b && j<m) s.insert(b[j++].a);
  	multiset<int>::iterator it=s.lower_bound(a[i].a);
  	if (it==s.end()){cout <<"-1";return 0;}
  	ans+=*it;s.erase(it);
  }
  cout <<ans;
  return 0;
}
Problem1692

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=700100;
int s[N];
char tmp[1];
int sa[N],t[N],t1[N],c[N],rank[N];
void buildsa(int n,int m){
	int *x=t,*y=t1;
	rep(i,0,m-1) c[i]=0;
	rep(i,0,n-1) c[x[i]=s[i]]++;
	rep(i,1,m-1) c[i]+=c[i-1];
	dep(i,n-1,0) sa[--c[x[i]]]=i;
	for(int k=1;k<=n;k<<=1){
		int p=0;
		rep(i,n-k,n-1) y[p++]=i;
		rep(i,0,n-1) if (sa[i]>=k) y[p++]=sa[i]-k;
		rep(i,0,m-1) c[i]=0;
		rep(i,0,n-1) c[x[y[i]]]++;
		rep(i,1,m-1) c[i]+=c[i-1];
		dep(i,n-1,0) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=1, x[sa[0]]=0;
		rep(i,1,n-1)
			x[sa[i]]=y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
		if (p>=n) break;
		m=p;
	}
}
int main(){
	int n;scanf("%d",&n);
	rep(i,0,n-1){
		scanf("%s",tmp);
		s[i]=tmp[0]-'A'+1;
	}
	s[n]=0;
	rep(i,1,n) s[n+i]=s[n-i];
	buildsa(n*2+1,27);
	rep(i,0,n*2) rank[sa[i]]=i;
	int l=0,r=n-1;
	rep(i,1,n){
		if (rank[l]<rank[n*2-r]) printf("%c",(char)s[l]+'A'-1),l++;else 
			printf("%c",(char)s[r]+'A'-1),r--;
		if (i%80==0) printf("\n");
	}
	return 0;
}
Problem1693

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define row(i) i
#define col(i) n+i
const int maxn=10000;
const int maxm=100000;
const int inf=0x7fffffff;
using namespace std;
int s,t;

int u[maxn],cur[maxn],h[maxn];
struct edge{
	int to,pre,w;
}e[maxm];
int l=2;
void ins(int a,int b,int c){
	e[l].to=b;e[l].w=c;
	e[l].pre=u[a];u[a]=l++;
}
void insert(int u,int v,int w){
	ins(u,v,w);ins(v,u,0);
}

int q[maxn];
bool bfs(){
	int l=0,r=1;q[l]=s;
	rep(i,s,t) h[i]=-1;h[s]=0;
	while (l!=r){
		int x=q[l++];
		for(int i=u[x];i;i=e[i].pre)
			if (h[e[i].to]==-1 && e[i].w){
				h[e[i].to]=h[x]+1;q[r++]=e[i].to;
			}
	}
	return h[t]!=-1;
}

int dfs(int x,int f){
	if (x==t || f==0) return f;
	int used=0,w;
	for(int i=cur[x];i;i=e[i].pre)
		if (h[x]+1==h[e[i].to] && e[i].w){
			w=min(f-used,e[i].w);
			w=dfs(e[i].to,w);
			e[i].w-=w;if (e[i].w) cur[x]=i;
			e[i^1].w+=w;
			used+=w;if (used==f) return f;
	 	}
	if (!used) h[x]=-1;
	return used;
}

int dinic(){
	int ans=0;
	while (bfs()){
		rep(i,s,t) cur[i]=u[i];
		ans+=dfs(s,inf);
	}
	return ans;
}
int main(){
	int n,k;scanf("%d%d",&n,&k);
	s=0;t=n*2+1;
	rep(i,1,n) insert(s,row(i),1),insert(col(i),t,1);
	rep(i,1,k){
		int r,c;
		scanf("%d%d",&r,&c);
		insert(row(r),col(c),inf);
	}
	printf("%d\n",dinic());
}
Problem1697

var
 n,i,min,j,cnt,cnt2,ans,a_min:longint;
 a,b:array[1..10000]of longint;
 visited:array[1..10000]of boolean;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin 
 i:=l;j:=r;m:=a[b[(l+r) shr 1]];
 repeat
   while a[b[i]]<m do inc(i);
	 while a[b[j]]>m do dec(j);
	 if i<=j then begin
     t:=b[i];b[i]:=b[j];b[j]:=t;	 
	   inc(i);dec(j);
	 end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
function get_min(a,b:longint):longint;
begin
 if a<b then exit(a) else exit(b); 
end;
begin 
 readln(n);ans:=0;
 for i:=1 to n do readln(a[i]);a_min:=a[1];
 for i:=2 to n do if a_min>a[i] then a_min:=a[i];
 for i:=1 to n do b[i]:=i;
 sort(1,n);fillchar(visited,sizeof(visited),false);
 for i:=1 to n do begin 
   if visited[i] then continue;
	 if b[i]=i then begin visited[i]:=true;continue;end;
	 j:=i;cnt:=0;min:=a[j];cnt2:=0;
	 while not visited[j] do begin 
	   visited[j]:=true;inc(cnt,a[j]);inc(cnt2);
		 j:=b[j];if a[j]<min then min:=a[j];
   end;	 
	 ans:=ans+get_min(cnt+(cnt2-2)*min,cnt+a_min*(cnt2+1)+min);
 end;
 writeln(ans);
end.
Problem1699

uses math;
var
 n,q,m,i,l,r:longint;
 a,b:array[1..1000000]of longint;
function ma(l,r:longint):longint;
begin 
 l:=l+m;r:=r+m;dec(l);inc(r);ma:=0;
 while l xor r<>1 do begin 
    if l and 1=0 then ma:=max(ma,a[l+1]);
	if r and 1=1 then ma:=max(ma,a[r-1]);
	l:=l shr 1;r:=r shr 1;
 end;
end;
function mb(l,r:longint):longint;
begin 
 l:=l+m;r:=r+m;dec(l);inc(r);mb:=maxlongint;
 while l xor r<>1 do begin 
    if l and 1=0 then mb:=min(mb,b[l+1]);
	if r and 1=1 then mb:=min(mb,b[r-1]);
	l:=l shr 1;r:=r shr 1;
 end;
end;
begin
 readln(n,q);
 m:=1;while m<n+2 do m:=m shl 1;
 for i:=m+1 to m+n do begin read(a[i]);b[i]:=a[i];end;
 for i:=m-1 downto 1 do begin 
    a[i]:=max(a[i shl 1],a[(i shl 1)+1]);
	b[i]:=min(b[i shl 1],b[(i shl 1)+1]);
 end;
 for i:=1 to q do begin 
   readln(l,r);writeln(ma(l,r)-mb(l,r));
 end;
end.
Problem1700

{
 f[i,j] means in the month f[i,j] we solved the problems belong to [i,j].
 f[i,j]:=min(f[k,i-1] | m-Sum_b[k,i-1]>=Sum_a[i,j] ) +1;
 be careful!
 if m>=Sum_a[i,j] f[i,j] may :=f[k,i-1]+2 So that in a month cows solve nothing
 f[0,0]:=1; 
 O(p^3);
}
var
 s_a,s_b,a,b:array[-10..800]of longint;
 m,p,i,j,k,ans:longint;
 f:array[0..800,0..800]of longint;
begin
 readln(m,p);
 for i:=1 to p do readln(a[i],b[i]);
 fillchar(f,sizeof(f),0);fillchar(s_a,sizeof(s_a),0);fillchar(s_b,sizeof(s_b),0);
 for i:=1 to p do begin 
   s_a[i]:=s_a[i-1]+a[i];
	 s_b[i]:=s_b[i-1]+b[i];
 end;
 f[0,0]:=1;
 for i:=1 to p do 
   for j:=i to p do begin 
	   if (s_a[j]-s_a[i-1]>m) or (s_b[j]-s_b[i-1]>m) then continue;
	   for k:=0 to i-1 do begin 
		   if f[k,i-1]=0 then continue;
			 if s_b[i-1]-s_b[k-1]+s_a[j]-s_a[i-1]<=m then begin 
         if (f[i,j]=0) or (f[k,i-1]+1<f[i,j]) then f[i,j]:=f[k,i-1]+1
       end else 
				 if (f[i,j]=0) or (f[k,i-1]+2<f[i,j]) then f[i,j]:=f[k,i-1]+2;				
		 end;
	 end;
 ans:=maxlongint;
 for i:=1 to p do if (f[i,p]>0) and (f[i,p]<ans) then ans:=f[i,p];
 writeln(ans+1);//+1 for the last month
end.
Problem1704

var
 n,i,j,s,cnt,ans,ansk:longint;
 c:char;
 a,t:array[1..10000]of longint;
begin 
 readln(n);
 for i:=1 to n do begin
  readln(c);
	if c='B' then a[i]:=1 else a[i]:=0;
 end;
 ans:=maxlongint;
 for i:=n downto 1 do begin
   s:=0;cnt:=0;
   for j:=1 to n-i+1 do begin 
	   if j-i>0 then s:=s xor t[j-i];
		 if a[j] xor s=1 then begin inc(cnt);s:=s xor 1;t[j]:=1;end else t[j]:=0;
		 if cnt>=ans then break;
	 end;
	 if cnt>=ans then continue;
	 for j:=n-i+2 to n do begin 
	   if j-i>0 then s:=s xor t[j-i];
		 if a[j] xor s=1 then begin cnt:=maxlongint;break;end;
	 end;
	 if cnt<ans then begin ans:=cnt;ansk:=i;end;
 end;
 writeln(ansk,' ',ans);
end.
Problem1705

uses math;
var
 n,c,i,j,ans,h,inf:longint;
 f,f1,f2,a:array[1..100000]of longint;
begin
 inf:=1 shl 30;
 readln(n,c);h:=0;fillchar(f,sizeof(f),0);
 for i:=1 to n do begin readln(a[i]);if a[i]>h then h:=a[i];end;
 for i:=1 to n do begin
   f1[1]:=f[1];f2[h]:=f[h];
   for j:=2 to h do f1[j]:=min(f1[j-1]+c,f[j]);
   for j:=h-1 downto 1 do f2[j]:=min(f2[j+1]+c,f[j]);
   for j:=1 to a[i] do f[j]:=inf;
   for j:=a[i] to h do f[j]:=min(f1[j],f2[j])+(a[i]-j)*(a[i]-j);
 end;
 ans:=maxlongint;
 for i:=1 to h do if f[i]<ans then ans:=f[i];
 writeln(ans);
end.
Problem1711

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define food(i) i
#define drink(i) f+i 
#define cow1(i) d+f+i
#define cow2(i) d+f+n+i
const int maxn=1000;
const int inf=0x7fffffff;
const int maxm=2000000;
using namespace std;

int s,t;
int u[maxn],cur[maxn];
struct edge{
	int to,pre,v;
}e[maxm];
int l=1;
void ins(int a,int b,int c){
	e[++l].to=b;e[l].pre=u[a];e[l].v=c;u[a]=l;
}
void insert(int a,int b,int c){
	ins(a,b,c);ins(b,a,0);
}

int dis[maxn],q[maxn];
bool bfs(){
	int l=0,r=1;q[l]=s;
	rep(i,s,t) dis[i]=-1;dis[s]=0;
	while (l!=r){
		int t=q[l];l++;
		for(int i=u[t];i;i=e[i].pre)
			if (e[i].v && dis[e[i].to]==-1){
				dis[e[i].to]=dis[t]+1;q[r++]=e[i].to;
			}
	}
	return dis[t]!=-1;
}

int dfs(int x,int f){
	if (x==t) return f;
	int w,used=0;
	for(int i=cur[x];i;i=e[i].pre)
		if (e[i].v && dis[e[i].to]==dis[x]+1){
			w=min(f-used,e[i].v);
			w=dfs(e[i].to,w);
			e[i].v-=w;
			if (e[i].v) cur[x]=i;
			e[i^1].v+=w;
			used+=w;
			if (used==f) return f;
		}
	if (!used) dis[x]=-1;
	return used;
}
int dinic(){
	int ans=0;
	while (bfs()){
		rep(i,s,t) cur[i]=u[i];
		ans+=dfs(s,inf);
	}
	return ans;
}
int main(){
	int n,f,d;
	scanf("%d%d%d",&n,&f,&d);
	s=0,t=n*2+f+d+1;
	rep(i,1,f) insert(s,food(i),1);
	rep(i,1,d) insert(drink(i),t,1);
	rep(i,1,n) insert(cow1(i),cow2(i),1);
	rep(i,1,n){
		int f_i,d_i;
		scanf("%d%d",&f_i,&d_i);
		rep(j,1,f_i){
			int tmp;
			scanf("%d",&tmp);
			insert(food(tmp),cow1(i),1);
		}
		rep(j,1,d_i){
			int tmp;
			scanf("%d",&tmp);
			insert(cow2(i),drink(tmp),1);
		}
	}
	printf("%d",dinic());
	return 0;
}
Problem1711

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define food(i) i
#define drink(i) f+i 
#define cow1(i) d+f+i
#define cow2(i) d+f+n+i
const int maxn=1000;
const int inf=0x7fffffff;
const int maxm=2000000;
using namespace std;
  
int s,t;
int u[maxn],cur[maxn];
struct edge{
    int to,pre,v;
}e[maxm];
int l=1;
void ins(int a,int b,int c){
    e[++l].to=b;e[l].pre=u[a];e[l].v=c;u[a]=l;
}
void insert(int a,int b,int c){
    ins(a,b,c);ins(b,a,0);
}
  
int dis[maxn],q[maxn];
bool bfs(){
    int l=0,r=1;q[l]=s;
    rep(i,s,t) dis[i]=-1;dis[s]=0;
    while (l!=r){
        int t=q[l];l++;
        for(int i=u[t];i;i=e[i].pre)
            if (e[i].v && dis[e[i].to]==-1){
                dis[e[i].to]=dis[t]+1;q[r++]=e[i].to;
            }
    }
    return dis[t]!=-1;
}
  
int dfs(int x,int f){
    if (x==t || f==0) return f;
    int w,used=0;
    for(int i=cur[x];i;i=e[i].pre)
        if (e[i].v && dis[e[i].to]==dis[x]+1){
            w=min(f-used,e[i].v);
            w=dfs(e[i].to,w);
            e[i].v-=w;
            if (e[i].v) cur[x]=i;
            e[i^1].v+=w;
            used+=w;
            if (used==f) return f;
        }
    if (!used) dis[x]=-1;
    return used;
}
int dinic(){
    int ans=0;
    while (bfs()){
        rep(i,s,t) cur[i]=u[i];
        ans+=dfs(s,inf);
    }
    return ans;
}
int main(){
    int n,f,d;
    scanf("%d%d%d",&n,&f,&d);
    s=0,t=n*2+f+d+1;
    rep(i,1,f) insert(s,food(i),1);
    rep(i,1,d) insert(drink(i),t,1);
    rep(i,1,n) insert(cow1(i),cow2(i),1);
    rep(i,1,n){
        int f_i,d_i;
        scanf("%d%d",&f_i,&d_i);
        rep(j,1,f_i){
            int tmp;
            scanf("%d",&tmp);
            insert(food(tmp),cow1(i),1);
        }
        rep(j,1,d_i){
            int tmp;
            scanf("%d",&tmp);
            insert(cow2(i),drink(tmp),1);
        }
    }
    printf("%d",dinic());
    return 0;
}
Problem1741

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define row(i) i
#define col(i) n+i
const int maxn=10000;
const int maxm=100000;
const int inf=0x7fffffff;
using namespace std;
int s,t;

int u[maxn],cur[maxn],h[maxn];
struct edge{
	int to,pre,w;
}e[maxm];
int l=2;
void ins(int a,int b,int c){
	e[l].to=b;e[l].w=c;
	e[l].pre=u[a];u[a]=l++;
}
void insert(int u,int v,int w){
	ins(u,v,w);ins(v,u,0);
}

int q[maxn];
bool bfs(){
	int l=0,r=1;q[l]=s;
	rep(i,s,t) h[i]=-1;h[s]=0;
	while (l!=r){
		int x=q[l++];
		for(int i=u[x];i;i=e[i].pre)
			if (h[e[i].to]==-1 && e[i].w){
				h[e[i].to]=h[x]+1;q[r++]=e[i].to;
			}
	}
	return h[t]!=-1;
}

int dfs(int x,int f){
	if (x==t || f==0) return f;
	int used=0,w;
	for(int i=cur[x];i;i=e[i].pre)
		if (h[x]+1==h[e[i].to] && e[i].w){
			w=min(f-used,e[i].w);
			w=dfs(e[i].to,w);
			e[i].w-=w;if (e[i].w) cur[x]=i;
			e[i^1].w+=w;
			used+=w;if (used==f) return f;
	 	}
	if (!used) h[x]=-1;
	return used;
}

int dinic(){
	int ans=0;
	while (bfs()){
		rep(i,s,t) cur[i]=u[i];
		ans+=dfs(s,inf);
	}
	return ans;
}
int main(){
	int n,k;scanf("%d%d",&n,&k);
	s=0;t=n*2+1;
	rep(i,1,n) insert(s,row(i),1),insert(col(i),t,1);
	rep(i,1,k){
		int r,c;
		scanf("%d%d",&r,&c);
		insert(row(r),col(c),inf);
	}
	printf("%d\n",dinic());
}
Problem1741

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define row(i) i
#define col(i) n+i
typedef int LL;
const int maxn=10000;
const int maxm=100000;
const int inf=0x7fffffff;
using namespace std;
int s,t;

int u[maxn],cur[maxn],h[maxn];
struct edge{
	int to,pre,w;
}e[maxm];
int l=2;
void ins(LL a,LL b,LL c){
	e[l]=(edge){b,u[a],c};u[a]=l++;
}
void insert(LL u,LL v,LL w){
	ins(u,v,w);ins(v,u,0);
}

int q[maxn];
bool bfs(){
	int l=0,r=1;q[l]=s;
	rep(i,s,t) h[i]=-1;h[s]=0;
	while (l<r){
		int x=q[l++];
		for(int i=u[x];i;i=e[i].pre)
			if (e[i].w && h[e[i].to]==-1) h[e[i].to]=h[x]+1,q[r++]=e[i].to;
	}
	return h[t]!=-1;
}
LL dfs(int x,LL f){
	if (f==(LL)0 || x==t) return f;
	LL used=0,w;
	for(int i=cur[x];i;i=e[i].pre)
		if (e[i].w && h[x]+1==h[e[i].to]){
			w=min(e[i].w,f-used);
			w=dfs(e[i].to,w);
			e[i].w-=w;if (e[i].w) cur[x]=i;
			e[i^1].w+=w;
			used+=w;if (used==f) return f;
		}
	if (!used) h[x]=-1;
	return used;
}
LL dinic(){
	LL ans=0;
	while (bfs()){
		rep(i,s,t) cur[i]=u[i];
		ans+=dfs(s,inf);
	}
	return ans;
}
int main(){
	int n,k;scanf("%d%d",&n,&k);
	s=0;t=n*2+1;
	rep(i,1,n) insert(s,row(i),1),insert(col(i),t,1);
	rep(i,1,k){
		int r,c;
		scanf("%d%d",&r,&c);
		insert(row(r),col(c),inf);
	}
	printf("%d\n",dinic());
}
Problem1758

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
#define v e[i].to
#define ec e[i].c
#define mc (ec - mid)
#define reg(i,x) for(int i = u[x];i;i=e[i].pre)
#define rek(i,x) reg(i,x) if (!vis[v]) 
#define ret(i,x) reg(i,x) if (!vis[v] && v!=f)
const int N = 100010;
struct edge{
	int to, pre, c;
}e[N * 2];
int u[N], l = 0;
int L,R;
void ins(int a,int b,int c){
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}
double ans = 0;
int sz[N], s[N], sum, vis[N], rt, max_edge, t = 0;
double mid;
int get_dep(int x,int f){
	int ans = 1;
	ret(i,x) ans = max(ans, get_dep(v,x) + 1);
	return ans;
}
pair <int, int> son[N];
const double inf = 1000000000000.0;
#define mp(a,b) make_pair(a,b)
double dist[N], mx[N];
bool flag;
void dfs(int x,int f, int dep, double dis){
	if (dep > R) return;
	dist[dep] = max(dist[dep], dis);
	if (dis > 0 && L <= dep) {flag = true;return;} 
	ret(i,x) { dfs(v, x, dep + 1, dis + mc); if (flag) return; }
}
typedef pair<int, double> node;
struct queue{
	int l, r;
	node q[N];
	void clr(){
		l = r = 0;
	}
	queue(){
		clr();
	}
#define dep first
#define dis second
	void push(const node &a){
		while (l < r && q[r - 1].dis <= a.dis) r--;
		q[r++] = a;
	}
	double top(int dep){
		while (l < r && q[l].dep + dep > R) l++;
		if (l==r) return -inf; else return q[l].dis; 
	}
}q;
#undef dep
#undef dis
bool Jud(int x){
	int l = 0;
	rek(i,x){
		int cur_dep = min(get_dep(v,x),R);
		son[++l] = mp(cur_dep, i);
	}
	sort(son+1, son+l+1);
	rep(i,1,son[l].first) mx[i] = -inf;
	rep(k,1,l){
		int i = son[k].second, cur_dep = son[k].first;
		rep(j,1,cur_dep) dist[j] = -inf;
		flag = false, dfs(v, x, 1, mc); if (flag) return true;
		/*queue*/
		q.clr();
		int j = cur_dep;
		rep(i,1,son[k-1].first){
			while (i + j >= L && j > 0) q.push(mp(j, dist[j])), j--;
			double t = q.top(i);
			if (t + mx[i] > 0) return true;
		}
		/*end of queue*/
		rep(i,1,cur_dep) mx[i] = max(dist[i], mx[i]);//update mx
	}
	return false;
}
const double eps = 0.0000001;
void calc(int x){
	double l = ans, r = max_edge + 1;
	while (l + eps < r && t <= 200){
		 mid = (l + r) / 2;
		 if (Jud(x)) l = mid; else r = mid; //binary_search
	}
	ans = l;
}
void getrt(int x,int f){
	sz[x] = 1, s[x] = 0;
	ret(i,x) getrt(v,x), sz[x] += sz[v], s[x] = max(s[x], sz[x]);
	s[x] = max(s[x], sum - sz[x]);
	if (s[x] < s[rt]) rt = x;
}
void work(int x){
	vis[x] = 1;	calc(x);
	rek(i,x){
		sum = sz[v], rt = 0, getrt(v,x);
		if (sz[v] >= L) work(rt);
	}
}
#undef v
int main(){
	int n; scanf("%d", &n);
	scanf("%d%d", &L,&R);
	max_edge = 0;
	rep(i,1,n-1){
		int a,b,v;scanf("%d%d%d",&a,&b,&v);
		ins(a,b,v), ins(b,a,v);
		max_edge = max(max_edge, v);
	}
	s[ rt = 0 ] = sum = n, getrt(1,0);
	work(rt);
	printf("%.3lf\n",ans);
	return 0;
}
Problem1777

var
 n,t,l,tmp,i,ans,a,b:longint;
 f,r,d:array[1..10000]of longint;
function find(x:longint):longint;
begin
 if f[x]=x then exit(x);
 find:=find(f[x]);
 d[x]:=d[x] xor d[f[x]];
 f[x]:=find;
 exit(find); 
end;
begin 
 readln(n,t,l);f[1]:=1;d[1]:=0;
 for i:=2 to n do begin 
   readln(f[i],r[i]);r[i]:=r[i] mod (l+1);
   d[i]:=1;
 end;
 ans:=0;
 for i:=1 to n do begin 
   tmp:=find(i);if d[i]=1 then ans:=ans xor r[i];
 end;
 for i:=1 to t do begin 
   readln(a,b);tmp:=find(a);
	 tmp:=b mod (l+1);
	 if d[a]=1 then ans:=ans xor r[a] xor tmp;
	 r[a]:=tmp;
	 if ans=0 then writeln('No') else writeln('Yes');
 end;
end.
Problem1798

var
 c,p,t,g:int64;
 i,n,m,ss:longint;
 a,s,k,d:array[1..400000]of int64;
procedure mark(x,flag:longint;t:int64);
begin 
  t:=t mod p;
  if flag=1 then begin 
	  k[x]:=(k[x]*t) mod p;
      d[x]:=(d[x]*t) mod p;
  end;
  if flag=2 then d[x]:=(d[x]+t) mod p;
end;
procedure push(x,l,r:longint);
var
 lc,rc:longint;
begin 
  if (k[x]=1) and (d[x]=0) then exit;
  lc:=x shl 1;rc:=lc+1;
 s[x]:=((s[x]*k[x]) mod p+(d[x]*int64(r-l)) mod p) mod p;
 if l+1<r then begin 
     mark(lc,1,k[x]);mark(lc,2,d[x]);
     mark(rc,1,k[x]);mark(rc,2,d[x]);
 end;
 k[x]:=1;d[x]:=0;
end;
procedure update(x:longint);
var
 lc,rc:longint;
begin
 lc:=x shl 1;rc:=lc+1;s[x]:=(s[lc]+s[rc]) mod p;
end;
procedure setas(x,l,r,a,b,flag:longint;t:int64);
var
 lc,rc,m:longint;
begin 
  lc:=x shl 1;rc:=lc+1;m:=(l+r) shr 1;
 if (a<=l) and (b>=r) then begin  mark(x,flag,t);push(x,l,r);exit;end;
 if (r<=a) or (l>=b) then begin push(x,l,r);exit;end;
 push(x,l,r);setas(lc,l,m,a,b,flag,t);setas(rc,m,r,a,b,flag,t);update(x);
end;
function sum(x,l,r,a,b:longint):int64;
var
 lc,rc,m:longint;
begin 
 lc:=x shl 1;rc:=lc+1;m:=(l+r) shr 1;
 if (a<=l) and (b>=r) then begin push(x,l,r);exit(s[x]);end;
 if (r<=a) or (l>=b) then begin exit(0);end;
 push(x,l,r);exit((sum(lc,l,m,a,b)+sum(rc,m,r,a,b)) mod p);
end;
begin
 readln(n,p);
 for i:=1 to n do read(a[i]);readln;
 for i:=1 to 400000 do k[i]:=1;
 fillchar(d,sizeof(d),0);fillchar(s,sizeof(s),0);
 for i:=1 to n do
	 setas(1,1,n+1,i,i+1,2,a[i]);
 inc(n);
 readln(m);
 for i:=1 to m do begin
	read(ss);
    if ss=1 then begin
		 readln(t,g,c);
		 setas(1,1,n,t,g+1,1,c);
	end;
	if ss=2 then begin 
		readln(t,g,c);
	    setas(1,1,n,t,g+1,2,c);
	end;
	if ss=3 then begin 
		 readln(t,g);
	     writeln(sum(1,1,n,t,g+1));
	end;
 end;
end.
Problem1801

#include <iostream>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;

int n,m;
const LL N=110;
const LL M=9999973;
LL f[N][N][N];

int main(){
	cin >>n>>m;
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	LL ans=0;
	rep(i,1,n) rep(j,0,m) rep(k,0,m-j){
				LL tmp=f[i-1][j][k];
				if (j) tmp+=f[i-1][j-1][k]*(m-(j-1)-k),tmp%=M;
				if (j<m && k) tmp+=f[i-1][j+1][k-1]*(j+1),tmp%=M;
				if (j>=2) tmp+=f[i-1][j-2][k]*((LL)m-(j-2)-k)*(m-(j-2)-k-1)/2,tmp%=M;
				if (j&&k) tmp+=f[i-1][j][k-1]*(m-j-(k-1))*j,tmp%=M;
				if (j+2<=m && k-2>=0) tmp+=f[i-1][j+2][k-2]*(j+2)*(j+1)/2,tmp%=M;
				if (i==n) ans+=tmp,ans%=M;
				f[i][j][k]=tmp;
	}
	cout <<ans;
	return 0;
}
Problem1814

/*
最小表示法
*/

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

const int MAXD=15;
const int HASH=30007;
const int STATE=1000010;
using namespace std;
int N,M;
int maze[MAXD][MAXD];
int code[MAXD];
int ch[MAXD];//最小表示法使用
int ex,ey;//最后一个非障碍格子的坐标
struct HASHMAP
{
    int head[HASH],next[STATE],size;
    long long state[STATE];
    long long f[STATE];
    void init()
    {
        size=0;
        memset(head,-1,sizeof(head));
    }
    void push(long long st,long long ans)
    {
        int i;
        int h=st%HASH;
        for(i=head[h];i!=-1;i=next[i])//这里要注意是next
          if(state[i]==st)
          {
              f[i]+=ans;
              return;
          }
        state[size]=st;
        f[size]=ans;
        next[size]=head[h];
        head[h]=size++;
    }
}hm[2];
void decode(int *code,int m,long long  st)
{
    for(int i=m;i>=0;i--)
    {
        code[i]=st&7;
        st>>=3;
    }
}
long long encode(int *code,int m)//最小表示法
{
    int cnt=1;
    memset(ch,-1,sizeof(ch));
    ch[0]=0;
    long long st=0;
    for(int i=0;i<=m;i++)
    {
        if(ch[code[i]]==-1)ch[code[i]]=cnt++;
        code[i]=ch[code[i]];
        st<<=3;
        st|=code[i];
    }
    return st;
}
void shift(int *code,int m)
{
    for(int i=m;i>0;i--)code[i]=code[i-1];
    code[0]=0;
}
void dpblank(int i,int j,int cur)
{
    int k,left,up;
    for(k=0;k<hm[cur].size;k++)
    {
        decode(code,M,hm[cur].state[k]);
        left=code[j-1];
        up=code[j];
        if(left&&up)
        {
            if(left==up)//只能出现在最后一个非障碍格子
            {
                if(i==ex&&j==ey)
                {
                    code[j-1]=code[j]=0;
                    if(j==M)shift(code,M);
                    hm[cur^1].push(encode(code,M),hm[cur].f[k]);
                }
            }
            else//不在同一个连通分量则合并
            {
                code[j-1]=code[j]=0;
                for(int t=0;t<=M;t++)
                  if(code[t]==up)
                    code[t]=left;
                if(j==M)shift(code,M);
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
        else if((left&&(!up))||((!left)&&up))
        {
            int t;
            if(left)t=left;
            else t=up;
            if(maze[i][j+1])
            {
                code[j-1]=0;
                code[j]=t;
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
            if(maze[i+1][j])
            {
                code[j-1]=t;
                code[j]=0;
                if(j==M)shift(code,M);
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
        else//无插头，则构造新的连通块
        {
            if(maze[i][j+1]&&maze[i+1][j])
            {
                code[j-1]=code[j]=13;
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
    }
}
void dpblock(int i,int j,int cur)
{
    int k;
    for(k=0;k<hm[cur].size;k++)
    {
        decode(code,M,hm[cur].state[k]);
        code[j-1]=code[j]=0;
        if(j==M)shift(code,M);
        hm[cur^1].push(encode(code,M),hm[cur].f[k]);
    }
}
char str[MAXD];
void init()
{
    memset(maze,0,sizeof(maze));

    ex=0;
    for(int i=1;i<=N;i++)
    {
        scanf("%s",&str);
        for(int j=0;j<M;j++)
        {
            if(str[j]=='.')
            {
                ex=i;
                ey=j+1;
                maze[i][j+1]=1;
            }
        }
    }
}
void solve()
{
    int i,j,cur=0;
    long long ans=0;
    hm[cur].init();
    hm[cur].push(0,1);
    for(i=1;i<=N;i++)
      for(j=1;j<=M;j++)
      {
          hm[cur^1].init();
          if(maze[i][j])dpblank(i,j,cur);
          else  dpblock(i,j,cur);
          cur^=1;
      }
    for(i=0;i<hm[cur].size;i++)
      ans+=hm[cur].f[i];
    printf("%lld\n",ans);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        init();
        if(ex==0)//没有空的格子
        {
            printf("0\n");
            continue;
        }
        solve();
    }
    return 0;
}
Problem1833

type
 num=array[0..12]of longint;
var
 i:longint;
 t1,t2:qword;
 f,ten:array[-1..12]of qword;
 a,b:num;
procedure init;
var
 i:longint;
begin 
 fillchar(f,sizeof(f),0);
 f[0]:=1;ten[0]:=1;
 for i:=1 to 11 do begin 
   ten[i]:=ten[i-1]*10;
	 f[i]:=10*f[i-1]+ten[i];
 end;
 ten[12]:=ten[11]*10;
end;
function calc(a:num;x:int64;t:longint):qword;
{
  [0..a]中t出现了多少次
  x=a 
}
var
 i:longint;
 flag,firstime:boolean;
 ans:qword;
begin 
 if x<0 then exit(0);
 if t=0 then ans:=1 else ans:=0;flag:=false;firstime:=true;
 for i:=12 downto 0 do begin
   if (a[i]=0) and (not flag) then continue else flag:=true;
	 { calc this bit }
	   if (not firstime) or (t<>0) then begin 
	   	 if a[i]>t then ans:=ans+ten[i];
	     if a[i]=t then ans:=ans+(x mod ten[i]+1);
	   end;
	 {calc 1/0..a[i]-1}
	 if firstime then ans:=ans+(a[i]-1)*f[i-1] else ans:=ans+a[i]*f[i-1];	
	 {calc 0}
	 if t<>0 then ans:=ans+ten[i-1];
	 if i-2>=0 then ans:=ans+9*f[i-2];
	 {reduce x}
	 x:=x mod ten[i];
	 firstime:=false;
 end;
 exit(ans);
end;
procedure trans(var a:num;x:qword);
var
 i:longint;
begin
 for i:=0 to 12 do begin 
   a[i]:=x mod 10;x:=x div 10;
 end;
end;
begin
 readln(t1,t2);dec(t1);
 init;
 trans(a,t1);trans(b,t2);
 for i:=0 to 9 do begin 
   write(calc(b,t2,i)-calc(a,t1,i));if i<9 then write(' ');
 end;
end.
Problem1854

var
 f:array[1..100000]of longint;
 a:array[1..100000]of boolean;
 n,u,v,i,aa,b:longint;
function find(x:longint):longint;
begin 
 if f[x]=x then exit(x);
 f[x]:=find(f[x]);exit(f[x]);
end;
begin 
 readln(n);fillchar(a,sizeof(a),false);
 for i:=1 to 100000 do f[i]:=i;
 for i:=1 to n do begin 
     readln(aa,b);
     u:=find(aa);v:=find(b);
	 if u=v then begin a[u]:=true;a[v]:=true;end else begin
	     if a[u] or a[v] then begin 
		     a[u]:=true;a[v]:=true;
		 end else begin 
		     if u<v then begin 
			     a[u]:=true;f[u]:=v;
			 end else begin 
			     a[v]:=true;f[v]:=u;
			 end;
		 end;
	 end;
 end;
 for i:=1 to 100000 do if a[i]=false then begin writeln(i-1);halt;end;
 writeln(100000);
end.
Problem1856

const
 mo=20100403;
var
 ans,tmp:int64;
 n,m,i:longint;
function get(x:longint):int64;
var
 f:longint;
 ans,tmp:int64;
begin 
 tmp:=x;ans:=1;
 f:=mo-2;
 while f>0 do begin 
     if f and 1=1 then ans:=(ans*tmp) mod mo;
	 tmp:=(tmp*tmp) mod mo;
	 f:=f shr 1;
 end;
 exit(ans);
end;
begin 
 readln(n,m);
 {
    length=n+m
    all=C(n+m,n);
	wrong:
	   n 1 m 0
	   2k+1-->ok
       k 1 k+1 0	   
	   
	   n-k
	   m-k-1
	   
	   m-k-1
	   n-k
	   
	   m-k-1+k=m-1 1
	   n-k+k+1=n+1 0
	   C(n+m,n+1)
	ans=all-wrong=C(n+m,n)-C(n+m,n+1)
	C(n+m,n)=(n+m)!/(m!n!)
	C(n+m,n+1)=(n+m)!/((m-1)!(n+1)!)=(n+m)!/(m!n!*(n+1)/m)=(n+m)!/n!m! *(m/n+1)
	1-m/n+1=(n+1-m)/n+1
	ans=((n+m)!/n!/m!) *(n+1-m)/n+1=(n+m)!(n+1-m) /(n+1)!m!
 }
 if n<m then begin writeln(0);halt;end;
 ans:=1;
 for i:=m+1 to n+m do ans:=(ans*i) mod mo;//(n+m) / m!
 tmp:=1;
 ans:=int64(int64(ans)*(n+1-m)) mod mo;
 for i:=1 to n+1 do tmp:=int64(int64(tmp)*i) mod mo;//(n+1)!
 ans:=(ans*get(tmp)) mod mo;
 writeln(ans);
end.
Problem1857

const
 eps=1e-4;
type
 dot=record
   x,y:extended;
 end;
var
 d1,d2:extended;
 a,b,c,d,l1,r1,l2,r2,m1,m2:dot;
 p,q,r,times1:longint;
function dis(a,b:dot):extended;
begin
  exit(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
end;
function check(a,b:dot):boolean;
begin
 if (abs(a.x-b.x)<eps) and (abs(a.y-b.y)<eps) then exit(true) else exit(false);
end;
function pre(x,a,b:dot):dot;
begin
 if check(a,b) then exit(x);
 if b.x-a.x<eps then begin 
     x.y:=x.y-eps;exit(x);
 end;
 x.x:=x.x-eps;
 x.y:=x.y-((b.y-a.y)*eps)/(b.x-a.x);
 exit(x); 
end;
function next(x,a,b:dot):dot;
begin
 if check(a,b) then exit(x);
 if b.x-a.x<eps then begin 
     x.y:=x.y+eps;exit(x);
 end;
 x.x:=x.x+eps;
 x.y:=x.y+((b.y-a.y)*eps)/(b.x-a.x);
 exit(x); 
end;
function dist(x,y:dot):extended;
begin 
 exit(dis(a,x)/p+dis(x,y)/r+dis(y,d)/q);
end;
function mid(a,b:dot):dot;
begin
 mid.x:=(a.x+b.x)/2;
 mid.y:=(a.y+b.y)/2;
 exit(mid); 
end;
procedure swap(var a,b:dot);
var
 c:dot;
begin
 c:=a;a:=b;b:=c;
end;
function get(a:dot):extended;
var
 times2:longint;
 d1,d2:extended;
begin 
   l2:=c;r2:=d;
   if l2.x>r2.x then swap(l2,r2);
   if (abs(l2.x-r2.x)<eps) and (l2.y>r2.y) then swap(l2,r2);
   times2:=0;
   repeat
     m2:=mid(l2,r2);//writeln(l2.x:0:2,' ',l2.y:0:2,' ',r2.x:0:2,' ',r2.y:0:2);
	 d2:=dist(a,next(m2,l2,r2));d1:=dist(a,pre(m2,l2,r2));//writeln('  ',m2.x:0:2,' ',m2.y:0:2,' ',d1:0:8,' ',d2:0:8);
	 if d1>d2 then l2:=m2 else r2:=m2;
	 inc(times2);
   until (times2>900) or (check(l2,r2));
   m2:=mid(l2,r2);
   exit(dist(a,m2));
end;
begin 
 readln(a.x,a.y,b.x,b.y);
 readln(c.x,c.y,d.x,d.y);
 readln(p,q,r);
 l1:=a;r1:=b;
   if l1.x>r1.x then swap(l1,r1);
   if (abs(l1.x-r1.x)<eps) and (l1.y>r1.y) then swap(l1,r1);
 times1:=0;
 repeat
   m1:=mid(l1,r1);
   d1:=get(pre(m1,l1,r1));d2:=get(next(m1,l1,r1));//writeln(m1.x:0:2,' ',m1.y:0:2,' ',d1:0:8,' ',d2:0:8);
   if d1>d2 then l1:=m1 else r1:=m1;
   inc(times1);
 until (times1>900) or (check(l1,r1));
 m1:=mid(l1,r1);writeln(get(m1):0:2);
end.
Problem1858

var
 lm1,rm1,m1,lm0,rm0,m0,t1,t0,d:array[1..610000]of longint;
 n,m,k,a,b,i,max,now:longint;
function max1(a,b:longint):longint;
begin
 if a>b then exit(a) else exit(b);
end;
procedure mark(x,f:longint);
begin 
 if f=0 then exit;
  if f=3 then 
	  case d[x] of 
	   0:d[x]:=3;
	   1:d[x]:=2;
	   2:d[x]:=1;
	   3:d[x]:=0;
	  end
  else 
	  d[x]:=f;
end;
procedure swap(var  a,b:longint);
var
	 t:longint;
begin
 	t:=a;a:=b;b:=t;
end;
procedure swap_t(x:longint);
begin
 swap(lm0[x],lm1[x]);swap(m0[x],m1[x]);swap(rm0[x],rm1[x]);swap(t0[x],t1[x]);	
end;
procedure push(x,l,r:longint);
var
 m,lc,rc:longint;
begin
 if d[x]=0 then exit;
  m:=(l+r) shr 1;lc:=x shl 1;rc:=lc+1;
 if d[x]=1 then begin 
		 lm1[x]:=0;rm1[x]:=0;m1[x]:=0;
	     lm0[x]:=r-l;rm0[x]:=r-l;m0[x]:=r-l;
	     t1[x]:=0;t0[x]:=r-l;
 end;
 if d[x]=2 then begin 
		 lm0[x]:=0;rm0[x]:=0;m0[x]:=0;
	     lm1[x]:=r-l;rm1[x]:=r-l;m1[x]:=r-l;
	     t0[x]:=0;t1[x]:=r-l;
 end;
 if d[x]=3 then swap_t(x);
 mark(lc,d[x]);mark(rc,d[x]);
 d[x]:=0;
end;
procedure update(x,l,r:longint);
var
 m,lc,rc:longint;
begin
 if l+1=r then exit;
 m:=(l+r) shr 1;lc:=x shl 1;rc:=lc+1;
 //t1
    t1[x]:=t1[lc]+t1[rc];
 //t0
	t0[x]:=t0[lc]+t0[rc];
 //lm1
    if lm1[lc]=m-l then lm1[x]:=lm1[lc]+lm1[rc] else lm1[x]:=lm1[lc];
 //lm0
    if lm0[lc]=m-l then lm0[x]:=lm0[lc]+lm0[rc] else lm0[x]:=lm0[lc];
 //rm1
	if rm1[rc]=r-m then rm1[x]:=rm1[rc]+rm1[lc] else rm1[x]:=rm1[rc]; 
 //rm0
	if rm0[rc]=r-m then rm0[x]:=rm0[rc]+rm0[lc] else rm0[x]:=rm0[rc]; 
 //m1
	m1[x]:=max1(m1[lc],m1[rc]);m1[x]:=max1(m1[x],rm1[lc]+lm1[rc]);
 //m0
	m0[x]:=max1(m0[lc],m0[rc]);m0[x]:=max1(m0[x],rm0[lc]+lm0[rc]);
end;

procedure setf(x,l,r,a,b,f:longint);
var
 m,lc,rc:longint;
begin 
 m:=(l+r) shr 1;lc:=x shl 1;rc:=lc+1;
 if (b<=l) or (a>=r) then begin push(x,l,r);exit;end;//push before exit(so that we can update his father)
 if (a<=l) and (b>=r) then begin mark(x,f);push(x,l,r);exit;end;
 push(x,l,r);
 setf(lc,l,m,a,b,f);setf(rc,m,r,a,b,f);
 update(x,l,r);
end;
function querry1(x,l,r,a,b:longint):longint;
var
 m,lc,rc:longint;
begin
 if (b<=l) or (a>=r) then exit(0);
 push(x,l,r);
 if (a<=l) and (b>=r) then exit(t1[x]);
 m:=(l+r) shr 1;lc:=x shl 1;rc:=lc+1;
 exit(querry1(lc,l,m,a,b)+querry1(rc,m,r,a,b));
end;
procedure querry2(x,l,r,a,b:longint);
var
 m,lc,rc:longint;
begin
 if (b<=l) or (a>=r) then exit;
 push(x,l,r);
 m:=(l+r) shr 1;lc:=x shl 1;rc:=lc+1;
 if (a<=l) and (b>=r) then begin
	 if m1[x]>max then max:=m1[x];
	 if now+lm1[x]>max then max:=now+lm1[x];
	 if rm1[x]=r-l then now:=now+rm1[x] else now:=rm1[x];
 end else begin 
	 querry2(lc,l,m,a,b);querry2(rc,m,r,a,b);
 end;
end;
procedure print(x,l,r:longint);
var
 m,lc,rc:longint;
begin
 m:=(l+r) shr 1;lc:=x shl 1;rc:=lc+1;
 writeln(x,' l:',l,' r:',r,' d:',d[x],' t0:',t0[x],' t1:',t1[x],' lm0:',lm0[x],' m0:',m0[x],' rm0:',rm0[x],' lm1:',lm1[x],' m1:',m1[x],' rm1:',rm1[x]); 
 if l+1<>r then begin print(lc,l,m);print(rc,m,r);end;
end;
begin 
 readln(n,m);
 d[1]:=1;//init
 inc(n);//attention! [1,n)
 //print(1,1,n);
 for i:=1 to n-1 do begin 
	 read(k);
     setf(1,1,n,i,i+1,k+1);
 //writeln;
 end;
 //print(1,1,n);
 readln;
 for i:=1 to m do begin 
     readln(k,a,b);inc(a);inc(b,2);
     if (k=0) or (k=1) or (k=2) then setf(1,1,n,a,b,k+1);
	 if k=3 then writeln(querry1(1,1,n,a,b));
	 if k=4 then begin 
		 max:=0;now:=0;
	     querry2(1,1,n,a,b);
	     writeln(max);
	 end;
	 //writeln(querry1(1,1,n,38,61));
	//print(1,1,n);
 end;
end.
Problem1874

var
 n,m,i,j,ans:longint;
 hash:array[0..11]of boolean;
 sg:array[0..1200]of longint;
 a,b:array[1..10]of longint;
procedure init;
begin 
 sg[0]:=0;
 for i:=1 to 1200 do begin 
   fillchar(hash,sizeof(hash),false);
   for j:=1 to m do if i-b[j]>=0 then hash[sg[i-b[j]]]:=true;
	 for j:=0 to 11 do if not hash[j] then begin sg[i]:=j;break;end;
 end;
end;
begin 
 readln(n);
 for i:=1 to n do readln(a[i]);
 readln(m);
 for i:=1 to m do readln(b[i]);
 init;
 ans:=0;
 for i:=1 to n do ans:=ans xor sg[a[i]];
 if ans=0 then writeln('NO') else begin 
   writeln('YES');
	 for i:=1 to n do 
	   for j:=1 to m do 
		   if a[i]-b[j]>=0 then 
			  if ans xor sg[a[i]] xor sg[a[i]-b[j]]=0 then begin 
				   writeln(i,' ',b[j]);halt;
			  end;
 end;
end.
Problem1899

var
 n,i,j,ans:longint;
 a,b,s:array[0..200]of longint;
 f:array[1..200,1..40000]of longint;
function max(a,b:longint):longint;
begin
 if a>b then exit(a) else exit(b); 
end;
function min(a,b:longint):longint;
begin 
 if a>b then exit(b) else exit(a);
end;
procedure swap(i,j:longint);
var
 t:longint;
begin
 t:=a[i];a[i]:=a[j];a[j]:=t;
 t:=b[i];b[i]:=b[j];b[j]:=t; 
end;
begin
 readln(n);
 for i:=1 to n do readln(a[i],b[i]);
 for i:=1 to n-1 do 
    for j:=n downto i+1 do 
       if b[j]>b[j-1] then swap(j,j-1);
 s[0]:=0;
 for i:=1 to n do s[i]:=s[i-1]+a[i];
 for i:=0 to s[2] do f[1,i]:=maxlongint;
 f[1,a[1]]:=a[1]+b[1];
 for i:=2 to n do begin 
  for j:=1 to s[i] do 
     if j-a[i]<=0 then f[i,j]:=max(f[i-1,j],s[i]-j+b[i]) else f[i,j]:=min(max(f[i-1,j],s[i]-j+b[i]),max(f[i-1,j-a[i]],j+b[i]));
  for j:=s[i]+1 to s[i+1] do f[i,j]:=maxlongint;
 end;
 ans:=maxlongint;
 for i:=1 to s[n] do if ans>f[n,i] then ans:=f[n,i];
 writeln(ans);
end.
Problem1901

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=30000,inf=1000000001;

struct que{
	int tp     ,    pos,val,t   ,   l,r,k,tim;
}q[N],q1[N],q2[N];
int l=0;

struct BIT{
	int s[N];
	int lowbit(int x){
		return x & (-x);
	}
	void clear(){
		memset(s,0,sizeof(s));
	}
	void add(int x,int d){
		while (x<=N){
			s[x]+=d;x+=lowbit(x);
		}
	}
	int sum(int x){
		int ans=0;
		while (x>0){
			ans+=s[x];x-=lowbit(x);
		}
		return ans;
	}
}B;

int a[N],ans[N];


void binary(int l,int r,int a,int b){//[l,r) [a,b] q1[l,mid) q2[mid,r)
//	cout <<l<<' '<<r<<' '<<a<<' '<<b<<"\n";
//	getchar();
	if (a>b) return;
	int mid=(l+r) >> 1,l1=0,l2=0;
	if (l+1==r){
		rep(i,a,b) if (q[i].tp==2) ans[q[i].tim]=l;
		return;
	}
	rep(i,a,b)
		if (q[i].tp==1){
			if ( q[i].val<mid ) {
				B.add(q[i].pos,q[i].t);
				q1[++l1]=q[i];
			} else q2[++l2]=q[i];
		} else {
			int t=B.sum(q[i].r)-B.sum(q[i].l-1);
			if (t >= q[i].k) q1[++l1]=q[i]; else {
				q2[++l2]=q[i];
				q2[l2].k-=t;
			}
		}
	rep(i,a,b) if (q[i].tp==1 && q[i].val<mid) B.add(q[i].pos,-q[i].t);
	int cnt=a;
	rep(i,1,l1) q[cnt++]=q1[i];
	rep(i,1,l2) q[cnt++]=q2[i];
	binary(l,mid,a,a+l1-1);
	binary(mid,r,a+l1,b);
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	rep(i,1,n){
		scanf("%d",&a[i]);
		l++;
		q[l].tp=1;
		q[l].pos=i;
		q[l].val=a[i];
		q[l].t=1;
	}
	int cnt=0;
	rep(i,1,m){
		char s;scanf("\n%c",&s);
		if (s=='Q'){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			l++;
			q[l].tp=2;
			q[l].l=x;
			q[l].r=y;
			q[l].k=z;
			q[l].tim=++cnt;
		}
		if (s=='C'){
			int x,y;
			scanf("%d%d",&x,&y);
			l++;
			q[l].tp=1;
			q[l].pos=x;
			q[l].val=a[x];
			q[l].t=-1;
			l++;
			q[l].tp=1;
			q[l].pos=x;
			q[l].val=y;
			q[l].t=1;
			a[x]=y;
		}
	}
	B.clear();
	binary(0,inf,1,l);
	rep(i,1,cnt) printf("%d\n",ans[i]);
	return 0;
}
Problem1911

type
  dot=record
     x,y:int64; 
  end;
var
 k:dot;
 r:array[0..1000000]of dot;
 s:array[0..1000000]of int64;
 n,a,b,c,u,top,tail,i:longint;
 f:int64;
procedure ind(k:dot);
begin 
 while (tail>1) and ((k.y-r[tail-1].y)/(k.x-r[tail-1].x)>(r[tail-1].y-r[tail-2].y)/(r[tail-1].x-r[tail-2].x)) do dec(tail);
 r[tail]:=k;inc(tail);
end;
function oud(k:longint):dot;
begin 
 while (top+1<tail) and ((r[top].y-r[top+1].y)/(r[top].x-r[top+1].x)>k) do  inc(top);
 exit(r[top]);
end;
begin 
 readln(n);readln(a,b,c);s[0]:=0;
 k.x:=0;k.y:=0;r[0]:=k;top:=0;tail:=1;
 for i:=1 to n do begin 
	 read(u);s[i]:=s[i-1]+u;
     k:=oud(2*a*s[i]);
     f:=k.y-2*a*s[i]*k.x+a*s[i]*s[i]+b*s[i]+c;
     k.x:=s[i];k.y:=a*s[i]*s[i]-b*s[i]+f;
     ind(k);
 end;
 writeln(f);
end.
Problem1922

const
 maxint64=9223372036854775807;
type
     edge=record
          u,v:longint;
         w:int64;
     end;
var
 flag:boolean;
 n,m,i,j,s,an1:longint;
 t,k:int64;
 b:array[1..5000,0..3000]of longint;
 dis:array[1..5000]of int64;
 h:array[1..5000]of longint;
 a:array[1..70000]of edge;
procedure sort(l,r:longint);
var
 t:edge;
 i,j,mid:longint;
begin 
 i:=l;j:=r;mid:=a[(l+r) div 2].v;
 repeat
	 while a[i].v<mid do inc(i);
	 while a[j].v>mid do dec(j);
	 if i<=j then begin 
	     t:=a[i];a[i]:=a[j];a[j]:=t;
	     inc(i);dec(j);
	 end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin 
 readln(n,m);fillchar(h,sizeof(h),0);
 for i:=1 to m do with a[i] do readln(u,v,w);
 sort(1,m); 
 for i:=1 to m do with a[i] do if h[v]=0 then h[v]:=i;
 for i:=1 to n do begin 
	  read(b[i,0]);
	  for j:=1 to b[i,0]  do read(b[i,j]);
	  readln; 
 end;
 flag:=true;dis[1]:=0;for i:=2 to n do dis[i]:=-1;
 while flag do begin
	 flag:=false;
	  for i:=2 to n do begin 
		  t:=0;k:=dis[i];
	      for j:=1 to b[i,0] do if dis[b[i,j]]<0 then begin t:=-1;break;end else if dis[b[i,j]]>t then t:=dis[b[i,j]];
		  dis[i]:=t;if dis[i]<0 then continue;
		  j:=h[i];t:=maxint64;
		  if j>0 then 
		     while (a[j].v=i) and (j<=m) do begin 
			    with a[j] do if (dis[u]>=0) and (u<>v) then if dis[u]+w<t then begin t:=dis[u]+w;s:=j;end;
			    inc(j);
		     end;
		  if t=maxint64 then dis[i]:=-1 else if t>dis[i] then dis[i]:=t;
		  if ((k<0) and (dis[i]>0)) or (dis[i]<k) then flag:=true else dis[i]:=k;
	 end;
 end;
 writeln(dis[n]);
end.
Problem1925

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 4210;
int n, p, f[2][N][2], s[N][2];
int main(){
	scanf("%d%d",&n,&p);
	int t = 1;
	f[1][1][0] = f[1][1][1] = 1;
	rep(i,2,n){
		t^=1;
		s[0][0] = s[0][1] = 0;
		rep(j,1,i - 1) 
			s[j][0] = s[j - 1][0] + f[t^1][j][0], s[j][1] = s[j - 1][1] + f[t^1][j][1],
			s[j][0]%= p,							s[j][1]%= p;
		rep(j,1,i)
			f[t][j][0] = (s[i - 1][1] - s[j - 1][1]) % p, 
			f[t][j][1] = s[j - 1][0];
	}
	int ans = 0;
	rep(i,1,n) ans += f[t][i][0], ans %= p, ans += f[t][i][1], ans %= p;
	if (ans < 0) ans += p;
	printf("%d\n",ans);
	return 0;
}
Problem1927

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
#define ew e[i].w
#define ec e[i].c
#define iw e[i^1].w
#define iv e[i^1].to
using namespace std;
const int inf=0xfffffff,N=2000,M=600000;
int a[N],u[N];
struct edge{
	int to,pre,w,c;
}e[M];
int l=1;
int S,T;
void ins(int a,int b,int w,int c){
	e[++l]=(edge){b,u[a],w,c};u[a]=l;
}
void insert(int a,int b,int w,int c){
	ins(a,b,w,c);ins(b,a,0,-c);
}
int h[N],inq[N],q[N],fr[N];
bool spfa(){
	rep(i,S,T) h[i]=inf,inq[i]=fr[i]=0;
	int l=0,r=1,x;q[h[S]=0]=S;
	while (l!=r){
		x=q[l++];if (l==N) l=0;inq[x]=0;
		reg(i,x) if (ew && h[x]+ec < h[v]){
			h[v]=h[x]+ec;fr[v]=i;
			if (!inq[v]){
				inq[v]=1;q[r++]=v;if (r==N) r=0;
			}
		}
	}
	return h[T]!=inf;
}
int cost=0,ans=0;
void mcf(){
	int x=inf;
	for(int i=fr[T];i;i=fr[iv]) x=min(x,ew);
	for(int i=fr[T];i;i=fr[iv]) ew-=x,iw+=x,cost+=x*ec;
	ans+=x;
}
#define id1(a) a+1
#define id2(a) a+n+1
int main(){
	int n,m;scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]);
	S=1, T=2*n+1+1;
	rep(i,1,n) insert(S,id1(i),1,0), insert(S,id2(i),1,a[i]) ,insert(id2(i),T,1,0);
	rep(i,1,m) {
		int a,b,c;scanf("%d%d%d",&a,&b,&c);if (a>b) swap(a,b);
		insert(id1(a),id2(b),1,c);
	}
	while (spfa()) mcf();
	printf("%d\n",cost);
	return 0;
}
Problem1951

/*g^{\sum_{k|n}C(n,k)} % p
p=999911659 1 <= g <= 10^9，1 <= n <= 10^9。

ans=g^{\sum_{k|n}C(n,k) % (p-1)} % p
---->\sum_{k|n}C(n,k) % (p-1)

k|n---->sqrt(n) for k

C(n,k) % (p-1)
p-1=2*3*4679*35617

Lucas C(n,k) mod 2,3,4679,35617

CRT*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
const LL P=999911659;
LL p[10]={2,3,4679,35617};
using namespace std;
LL ans=0;
LL qpow(LL a,LL b,LL p){//a^b mod p
	LL ans=1;a%=p;
	for(;b;(b =b >> 1, a=(LL)a*a%p)) if (b & 1) ans=(LL)ans * a % p;
	return ans%p;
}
LL fact[35617][10];
LL C(LL n,LL m,LL x){//C(n,m) % p[x]
	if (n<m) return 0;
	return (LL)fact[n][x]*qpow(fact[m][x] * fact[n-m][x] % p[x],p[x]-2,p[x]) % p[x];
}
LL Lucas(LL n,LL m,LL x){
	if (m==0) return 1;
	else return (LL)Lucas(n/p[x],m/p[x],x)*C(n%p[x],m%p[x],x)%p[x];
}
LL x,y;
void ex_gcd(LL a,LL b,LL M){
	if (b==0) x=1,y=0; else {
		ex_gcd(b,a%b,M);
		int t=x;
		x=y, y=(LL)t-(a/b)*y % M, y%=M;
	}
}
LL n,g;
void init(){
	rep(i,0,3){
		fact[0][i]=1;
		rep(j,1,p[i]-1) fact[j][i]=(LL)fact[j-1][i]*j % p[i];
	}
}
struct modequ{
	LL a,b;// x=a mod b
}e[4];
LL Inv(LL a,LL b) {//a^(-1) in mod b
	ex_gcd(a,b,b);x%=b;if (x<0)x+=b;
	return x;
}
modequ geth(const modequ &a,const modequ &b){
	LL p=a.b*b.b;
	modequ ans;
	ans.a=((LL)b.b*a.a%p*Inv(b.b,a.b)%p+(LL)a.b*b.a*Inv(a.b,b.b)%p)%p , ans.b=p;
	return ans;
}	
void work(int x){
	rep(i,0,3) e[i].a=(e[i].a+Lucas(n,x,i))%e[i].b;
}
int main(){
	cin >>n>>g;
	init();
	rep(i,0,3) e[i]=(modequ){0,p[i]};
	for(int i=1;i*i<=n;i++)if (!(n % i)){
		work(i);if (i*i < n)work(n/i);
	}
	if (g==P){printf("0\n");return 0;}
	modequ a=e[0];
	rep(i,1,3) a=geth(a,e[i]);
	ans=a.a % (P-1);
	if (ans<0) ans+=P-1;
	g%=P;
	cout <<qpow(g,ans,P)<<endl;
	return 0;
}
/*
 after %p[x] n may be smaller than m
 C(n,m) should return 0 when n<m
*/
Problem1986

//f[i]=min{f[j]+1} 且2*A<=j-i<=2*B A B是常数 所以单调队列搞定
// if i∈[lj,rj) then f[i]:=maxlongint
var
 a,b,n,i,top,tail,j,g,ll,m:longint;
 f,l,r,q:array[0..2000000]of longint;
procedure swap(a,b:longint);
var
 t:longint;
begin
 t:=l[a];l[a]:=l[b];l[b]:=t;
 t:=r[a];r[a]:=r[b];r[b]:=t; 
end;
procedure add(x:longint);
var
 i:longint;
begin
 for i:=tail downto top do begin 
     if f[q[i]]>=f[x] then tail:=i-1 else break;
 end;
 inc(tail);q[tail]:=x;
end;
function min(x:longint):longint;
var
 i:longint;
begin 
 for i:=top to tail do 
     if x-q[i]>2*b then top:=i+1;
 if top>tail then exit(maxlongint) else exit(f[q[top]]);
end;
begin 
 readln(n,ll);
 readln(a,b);
 for i:=1 to n do readln(l[i],r[i]);
 for i:=1 to n do begin 
     for j:=1 to n do begin 
	     if i=j then continue;
		 if (l[i]<=l[j]) and (r[i]>=r[j]) then begin l[j]:=maxlongint;r[j]:=maxlongint;end;
	 end;
 end;
 for i:=1 to n do 
     for j:=n downto i+1 do
	     if l[j]<l[j-1] then swap(j,j-1);
 l[n+1]:=maxlongint;r[n+1]:=maxlongint;
 f[0]:=0;top:=1;tail:=0;
 m:=1;
 for j:=1 to ll shr 1 do begin
	 i:=j shl 1;f[i-1]:=maxlongint;
	 if i-2*a>=0 then add(i-2*a);
     while r[m]<=i do inc(m);
	 if l[m]<i then begin  f[i]:=maxlongint;continue;end;
     g:=min(i);
	 if g=maxlongint then f[i]:=maxlongint else f[i]:=g+1;
 end; 
 if f[ll]=maxlongint then writeln(-1) else writeln(f[ll]);
end.
Problem2002

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=200005;
struct node *null;//define before node
struct node{
	node *f,*ch[2];
	int s;
	int d(){return f->ch[1]==this;}//cmp
	bool c(){return f==null || (f->ch[0]!=this && f->ch[1]!=this); }//check
	void upd(){s=ch[0]->s + ch[1]->s + 1;}//upd()
	void st(node* t,int d){ ch[d]=t, t->f=this; }
}s[N];
void rot(node* o){
	int d=o->d();node* f=o->f;
	if (f->c()) o->f=f->f; else f->f->st(o,f->d());
	f->st(o->ch[d^1], d);
	o->st(f,d^1);
	f->upd();
}
void splay(node* o){
	while (!o->c())
		if (o->f->c()) rot(o);else 
			if (o->d()==o->f->d()) {rot(o->f);rot(o);} else {rot(o);rot(o);};
	o->upd();
}
void access(node* f){
	for(node* c=null; f!=null; f=f->f){
		splay(f);
		f->st(c,1), f->upd();
		c=f;
	}
}
void link(node* o,node* f){
	access(o);splay(o);
	o->ch[0]->f=null;o->ch[0]=null;o->f=f;o->upd();
}
int main(){
	int n;scanf("%d",&n);
	null=new node;
	null->s=0;null->ch[0]=null->ch[1]=null->f=null;
	rep(i,1,n){
		int k;scanf("%d",&k);
		if (i+k<=n) s[i].f=&s[i+k]; else s[i].f=null;
		s[i].ch[0]=s[i].ch[1]=null;
		s[i].s=1;
	}
	int m;scanf("%d",&m);
	rep(i,1,m){
		int a,b;
		scanf("%d%d",&a,&b);b++;
		if (a==1){
			access(&s[b]);
			splay(&s[b]);
			printf("%d\n",s[b].s);
		}else{
			int c;
			scanf("%d",&c);
			if (b+c<=n) link(&s[b],&s[b+c]);else link(&s[b],null);
		}
	}
	return 0;
}
Problem2005

{
 n m
 1 ≤ n, m ≤ 100,000
 sigma [1<=i<=n][1<=j<=m](2*(gcd(i,j)-1)+1)
 sigma [1<=i<=n][1<=j<=m](2*gcd(i,j)-1)
 =2*sigma [1<=i<=n][1<=j<=m](gcd(i,j))-nm
 }
 var
  sum:int64;
  a,n,m,i,j:longint;
  g:array[1..100000]of int64;
 function min(a,b:longint):longint;
 begin
   if a<b then exit(a) else exit(b); 
 end;
 begin 
  readln(n,m);
  a:=min(n,m);sum:=0;
  for i:=a downto 1 do begin
     g[i]:=int64(n div i)*int64(m div i);  
     for j:=2 to a div i do 
	     g[i]:=g[i]-g[i*j];
	 sum:=sum+i*g[i];
 end;
 writeln(2*sum-int64(n)*int64(m));
 end.
 
Problem2006

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define lc (x << 1)
#define rc (lc + 1)
using namespace std;
const int N=501000,inf=0x7fffffff;
typedef long long LL;
int n,k,L,R,s[N],m[N*4];
void build(int x,int l,int r){
	if (l==r) m[x]=l;else {
		int mid=(l+r)>>1;
		build(lc,l,mid),build(rc,mid+1,r);
		if (s[m[lc]]<s[m[rc]]) m[x]=m[lc]; else m[x]=m[rc];
	}
}
int query(int x,int l,int r,int a,int b){
	if (a<=l && r<=b) return m[x];else {
		int ans=a,mid=(l+r) >> 1;
		if (a<=mid) {
			int t=query(lc,l,mid,a,b);
			if (s[t]<s[ans]) ans=t;
		}
		if (b>mid) {
			int t=query(rc,mid+1,r,a,b);
			if (s[t]<s[ans]) ans=t;
		}
		return ans;
	}
}
int qry(int a,int b){
	return query(1,0,n,a,b);
}
struct node{
	int x,l,r,a,ax;
};
bool operator < (const node &a,const node &b){
	return a.a < b.a;
}
priority_queue<node> q;
int main(){
	scanf("%d%d%d%d",&n,&k,&L,&R);s[0]=0;
	rep(i,1,n) scanf("%d",&s[i]),s[i]+=s[i-1];
	build(1,0,n);
	rep(i,1,n) {
		int l=max(i-R,0),r=i-L;
		if (r >= 0){
			int ax=qry(l,r);
			q.push((node){i,l,r,s[i]-s[ax],ax});
		}
	}
	LL ans=0;
	rep(i,1,k){
		node t=q.top();q.pop();
		ans+=t.a;
		if (t.l<t.ax){
			int x1=qry(t.l,t.ax-1);
			q.push((node){ t.x,t.l,t.ax-1,s[t.x]-s[x1],x1 });
		}
		if (t.ax<t.r){
			int x1=qry(t.ax+1,t.r);
			q.push((node){ t.x,t.ax+1,t.r,s[t.x]-s[x1],x1 });
		}
	}
	cout <<ans<<endl;
	return 0;
}
Problem2007

const
  maxn=250000;
type
  dot=record
	 x,s:longint;
  end;
var
  n,l,i,j,w,tt,dl:longint;
  visited:array[0..maxn+10]of boolean;
  u,dis:array[0..maxn+10]of longint;
  v,pre,c:array[1..8000001]of longint;
  d:array[1..maxn*4]of dot;
procedure insert(a,b,w:longint);
begin 
  inc(l);v[l]:=b;c[l]:=w;
  pre[l]:=u[a];u[a]:=l;
end;
function get(r,c:longint):longint;
begin
  if (r=0) or (c>n) then exit(tt);
  if (r>n) or (c=0) then exit(0);
  exit((r-1)*n+c);
end;
procedure swap(var a,b:dot);
var
 c:dot;
begin
 c:=a;a:=b;b:=c; 
end;
procedure add(xx,s:longint);
var
 x,f:longint;
begin 
 inc(dl);d[dl].x:=xx;d[dl].s:=s;x:=dl;
 while (x<>1) and (d[x shr 1].s>d[x].s) do begin 
     f:=x shr 1;swap(d[x],d[f]);x:=f;
 end;
end;
function check(child,x:longint):boolean;
begin
  if child>dl then exit(false);
   if d[child].s<d[x].s then exit(true) else exit(false);	
end;
procedure del;
var
 x,lc,rc:longint;
begin
 swap(d[dl],d[1]);dec(dl);
 x:=1;lc:=x shl 1;rc:=lc+1;
 while check(lc,x) or check(rc,x) do begin
     if check(rc,lc) then begin
           swap(d[x],d[rc]);x:=rc;lc:=x shl 1;rc:=lc+1;
      end else begin 
	       swap(d[x],d[lc]);x:=lc;lc:=x shl 1;rc:=lc+1;
		end;
 end; 
end;
procedure dij;
var
 i,x,j:longint;
begin 
 dl:=0;
 fillchar(visited,sizeof(visited),false);
 for i:=1 to tt do dis[i]:=maxlongint;dis[0]:=0;
 for i:=0 to tt do add(i,dis[i]);
 for i:=0 to tt do begin
     x:=d[1].x;while visited[x] do begin del;x:=d[1].x;end;
	 visited[x]:=true;del;
	 j:=u[x];
	 while j>0 do begin 
	     if dis[x]+c[j]<dis[v[j]] then begin 
			     dis[v[j]]:=dis[x]+c[j];
		         add(v[j],dis[v[j]]);
		  end;
	     j:=pre[j];
	 end;
 end;
end;
begin 
 readln(n);l:=0;tt:=n*n+1;
 for i:=1 to n+1 do
     for j:=1 to n do begin  
         readln(w);
	     insert(get(i,j),get(i-1,j),w);
	 end;
 for i:=1 to n do
     for j:=1 to n+1 do begin 
         readln(w);
         insert(get(i,j-1),get(i,j),w);
    end;				 
 for i:=1 to n+1 do 
     for j:=1 to n do begin 
		  readln(w);
		  insert(get(i-1,j),get(i,j),w);
	 end;
 for i:=1 to n do 
     for j:=1 to n+1 do begin 
		  readln(w);
		  insert(get(i,j),get(i,j-1),w);
	 end;
 dij;
 writeln(dis[tt]);
end.
Problem2014

type
 ll=int64;
var
 n,i:longint;
 ans,b,w:ll;
 p,c:array[1..100000]of ll;
procedure sort(l,r:longint);
var
 i,j:longint;
 m,t:ll;
begin
 i:=l;j:=r;m:=p[(l+r) shr 1]; 
 repeat
    while p[i]<m do inc(i);
	while p[j]>m do dec(j);
	if i<=j then begin 
	  t:=c[i];c[i]:=c[j];c[j]:=t;
	  t:=p[i];p[i]:=p[j];p[j]:=t;
	  inc(i);dec(j);
	end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
function min(a,b:ll):ll;
begin
 if a<b then exit(a) else exit(b); 
end;
begin 
 readln(n,b);
 for i:=1 to n do readln(p[i],c[i]);
 sort(1,n);
 ans:=0;
 for i:=1 to n do begin 
     if b<p[i] then break;
	 w:=min(b div p[i],c[i]);
	 inc(ans,w);
	 b:=b-w*p[i];
 end;
 writeln(ans);
end.
Problem2017

var
 min:int64;
 i,j,t,n:longint;
 s:array[0..2000]of int64;
 c:array[0..2000]of longint;
 f:array[0..2000,1..2000] of int64;
begin 
 readln(n);
 for i:=1 to n do readln(c[i]);
 s[0]:=0;
 for i:=n downto 1 do s[n-i+1]:=s[n-i]+c[i];
 fillchar(f,sizeof(f),0);
 for i:=1 to n-1 do begin 
     min:=f[i-1,1];t:=1;
    for j:=1 to n do begin 
	     while (t+1<=j*2) and (t+1<=i) do begin inc(t);if f[i-t,t]<min then min:=f[i-t,t];end;
		 f[i,j]:=s[i]-min;
	 end;
 end;
 if (f[n-2,2]>f[n-1,1]) or (n=1) then writeln(s[n]-f[n-1,1]) else writeln(s[n]-f[n-2,2]);
end.
Problem2038

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
const int maxn=500000;

struct node{
	int a,b;
}a[maxn];
bool cmp(const node &a,const node &b){return a.a<b.a;}

int sqr_n;
struct querry{
	int l,r,t;
}q[maxn];
bool cmp1(const querry &a,const querry &b){
	return ((a.l / sqr_n) < (b.l / sqr_n) || ((a.l/sqr_n) == (b.l/sqr_n)) && (a.r < b.r));
};

LL T[maxn];
LL sum_T,sum_T_2;
LL ans1[maxn],ans2[maxn];

void add(int x,int d){
	sum_T+=d;
	sum_T_2-=T[x]*T[x];T[x]+=d;
	sum_T_2+=T[x]*T[x];
}

LL gcd(LL a,LL b){
	if (a==0) return (b==0) ? 1:b;
	return (b==0) ? a:gcd(b, a % b);
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	rep(i,1,n) 
		scanf("%d",&a[i].a),a[i].b=i;
	sort(a+1,a+n+1,cmp);
	int tmp=a[1].a,t;
	a[1].a=1;
	rep(i,2,n){
		t=a[i].a;
		if  (a[i].a==tmp) a[i].a=a[i-1].a; else a[i].a=a[i-1].a+1;
		tmp=t;
	}
	int s[maxn];
	rep(i,1,n) s[a[i].b]=a[i].a;
	
	sqr_n=(int)sqrt(n);if (sqr_n==0) sqr_n=1;
	rep(i,1,m) scanf("%d%d",&q[i].l,&q[i].r),q[i].t=i;
	sort(q+1,q+m+1,cmp1);

	int l=1,r=1;
	memset(T,0,sizeof(T));
	T[s[1]]=1;sum_T=1;sum_T_2=1;
	rep(i,1,m){
		while (l<q[i].l){
			add(s[l],-1);l++;
		}
		while (l>q[i].l){	
			l--;add(s[l],1);
		}
		while (r>q[i].r){
			add(s[r],-1);r--;
		}
		while (r<q[i].r){
			r++;add(s[r],1);
		}
		LL g=gcd(((LL)r-l+1)*((LL)r-l),sum_T_2-sum_T);
		ans1[q[i].t]=(sum_T_2-sum_T)/g;
		ans2[q[i].t]=((LL)r-l+1)*((LL)r-l)/g;
	}

	rep(i,1,m) {
		printf("%lld",ans1[i]);
		printf("/");
		printf("%lld\n",ans2[i]);
	}
}
Problem2049

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define read(a) a=getnum()
#define print(a) printf("%d", a)
#define dbg(x) cout << #x << "=" << x << endl;
#define dbgarr(a, n) for1(i, 0, n) cout << a[i] << " "; cout << endl
 
inline int getnum() { int ret=0, k=1; char c; for(c=getchar(); c<'0' || c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0' && c<='9'; c=getchar()) ret=ret*10+c-'0'; return ret*k; }
 
const int N=10005;
int n, m;
 
struct node* null;
struct node {
    node* ch[2], *fa;
    bool rev;
    bool d() const { return fa->ch[1]==this; }
    void setc(node* c, bool d) { ch[d]=c; c->fa=this; }
    bool check() const { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=true;
            ch[1]->rev^=true;
            swap(ch[0], ch[1]);
            rev=false;
        }
    }
}*nd[N];
 
inline void rot(node* r) {
    node* fa=r->fa; bool d=r->d();
    fa->pushdown(); r->pushdown();
    if(fa->check()) r->fa=fa->fa;
    else fa->fa->setc(r, fa->d());
    fa->setc(r->ch[!d], d);
    r->setc(fa, !d);
}
 
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
 
inline void splay(node* r) {
    fix(r);
    while(!r->check())
        if(r->fa->check()) rot(r);
        else r->d()==r->fa->d()?(rot(r->fa), rot(r)):(rot(r), rot(r));
}
 
inline node* access(node* x) {
    node* y=null;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    return y;
}
 
inline void mkroot(node* x) {
    access(x)->rev^=true; splay(x);
}
 
inline void link(node* x, node* y) {
    mkroot(x); x->fa=y;
}
 
inline void cut(node* x, node* y) {
    mkroot(x);
    access(y); splay(y);
    y->ch[0]->fa=null; y->ch[0]=null;
}
 
inline node* findrt(node* x) {
    access(x); splay(x);
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
 
int main() {
    read(n); read(m);
    null=new node; null->fa=null->ch[0]=null->ch[1]=null; null->rev=false;
    char s[10];
    int u, v;
    for1(i, 1, n) {
        nd[i]=new node;
        nd[i]->fa=nd[i]->ch[0]=nd[i]->ch[1]=null; nd[i]->rev=false;
    }
    rep(i, m) {
        scanf("%s", s);
        read(u); read(v);
        if(s[0]=='Q')
            findrt(nd[u])==findrt(nd[v])?(printf("Yes\n")):(printf("No\n"));
        else if(s[0]=='C') link(nd[u], nd[v]);
        else cut(nd[u], nd[v]);
    }
     
    return 0;
}
Problem2049

 
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define read(a) a=getnum()
#define print(a) printf("%d", a)
#define dbg(x) cout << #x << "=" << x << endl;
#define dbgarr(a, n) for1(i, 0, n) cout << a[i] << " "; cout << endl
  
inline int getnum() { int ret=0, k=1; char c; for(c=getchar(); c<'0' || c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0' && c<='9'; c=getchar()) ret=ret*10+c-'0'; return ret*k; }
  
const int N=10005;
int n, m;
  
struct node* null;
struct node {
    node* ch[2], *fa;
    bool rev;
    bool d() const { return fa->ch[1]==this; }
    void setc(node* c, bool d) { ch[d]=c; c->fa=this; }
    bool check() const { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=true;
            ch[1]->rev^=true;
            swap(ch[0], ch[1]);
            rev=false;
        }
    }
}*nd[N];
  
inline void rot(node* r) {
    node* fa=r->fa; bool d=r->d();
    fa->pushdown(); r->pushdown();
    if(fa->check()) r->fa=fa->fa;
    else fa->fa->setc(r, fa->d());
    fa->setc(r->ch[!d], d);
    r->setc(fa, !d);
}
  
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
  
inline void splay(node* r) {
    fix(r);
    while(!r->check())
        if(r->fa->check()) rot(r);
        else r->d()==r->fa->d()?(rot(r->fa), rot(r)):(rot(r), rot(r));
}
  
inline node* access(node* x) {
    node* y=null;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    return y;
}
  
inline void mkroot(node* x) {
    access(x)->rev^=true;
}
  
inline void link(node* x, node* y) {
    mkroot(x); splay(x);x->fa=y;
}
  
inline void cut(node* x, node* y) {
    mkroot(x);
    access(y); splay(y);
    y->ch[0]->fa=null; y->ch[0]=null;
}
  
inline node* findrt(node* x) {
    access(x); splay(x);
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
  
int main() {
    read(n); read(m);
    null=new node; null->fa=null->ch[0]=null->ch[1]=null; null->rev=false;
    char s[10];
    int u, v;
    for1(i, 1, n) {
        nd[i]=new node;
        nd[i]->fa=nd[i]->ch[0]=nd[i]->ch[1]=null; nd[i]->rev=false;
    }
    rep(i, m) {
        scanf("%s", s);
        read(u); read(v);
        if(s[0]=='Q')
            findrt(nd[u])==findrt(nd[v])?(printf("Yes\n")):(printf("No\n"));
        else if(s[0]=='C') link(nd[u], nd[v]);
        else cut(nd[u], nd[v]);
    }
      
    return 0;
}
Problem2049

 
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define read(a) a=getnum()
#define print(a) printf("%d", a)
#define dbg(x) cout << #x << "=" << x << endl;
#define dbgarr(a, n) for1(i, 0, n) cout << a[i] << " "; cout << endl
  
inline int getnum() { int ret=0, k=1; char c; for(c=getchar(); c<'0' || c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0' && c<='9'; c=getchar()) ret=ret*10+c-'0'; return ret*k; }
  
const int N=10005;
int n, m;
  
struct node* null;
struct node {
    node* ch[2], *fa;
    bool rev;
    bool d() const { return fa->ch[1]==this; }
    void setc(node* c, bool d) { ch[d]=c; c->fa=this; }
    bool check() const { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=true;
            ch[1]->rev^=true;
            swap(ch[0], ch[1]);
            rev=false;
        }
    }
}*nd[N];
  
inline void rot(node* r) {
    node* fa=r->fa; bool d=r->d();
    fa->pushdown(); r->pushdown();
    if(fa->check()) r->fa=fa->fa;
    else fa->fa->setc(r, fa->d());
    fa->setc(r->ch[!d], d);
    r->setc(fa, !d);
}
  
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
  
inline void splay(node* r) {
    fix(r);
    while(!r->check())
        if(r->fa->check()) rot(r);
        else r->d()==r->fa->d()?(rot(r->fa), rot(r)):(rot(r), rot(r));
}
  
inline void access(node* x) {
    node *y=null,*t=x;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    splay(t);
}
  
inline void mkroot(node* x) {
    access(x);x->rev^=true;
}
  
inline void link(node* x, node* y) {
    mkroot(x);x->fa=y;
}
  
inline void cut(node* x, node* y) {
    mkroot(x);
    access(y); splay(y);
    y->ch[0]->fa=null; y->ch[0]=null;
}
  
inline node* findrt(node* x) {
    access(x); splay(x);
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
  
int main() {
    read(n); read(m);
    null=new node; null->fa=null->ch[0]=null->ch[1]=null; null->rev=false;
    char s[10];
    int u, v;
    for1(i, 1, n) {
        nd[i]=new node;
        nd[i]->fa=nd[i]->ch[0]=nd[i]->ch[1]=null; nd[i]->rev=false;
    }
    rep(i, m) {
        scanf("%s", s);
        read(u); read(v);
        if(s[0]=='Q')
            findrt(nd[u])==findrt(nd[v])?(printf("Yes\n")):(printf("No\n"));
        else if(s[0]=='C') link(nd[u], nd[v]);
        else cut(nd[u], nd[v]);
    }
      
    return 0;
}
Problem2049

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20000;
struct node *null;
struct node{
	node *ch[2],*f;
	int rev;
	int d(){return f->ch[1]==this;}
	bool c(){return f==null || (f->ch[0]!=this && f->ch[1]!=this);}
	void st(node *c,int d){ch[d]=c;c->f=this;}
	void push(){
		if (rev){
			ch[0]->rev^=1;ch[1]->rev^=1;
			swap(ch[0],ch[1]);
			rev=0;
		}
	}
}s[N];
void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->c()) o->f=f->f; else f->f->st(o,f->d());
	f->st(o->ch[d^1],d);o->st(f,d^1);
}
void fix(node *o){
	if (!o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (!o->c())
		if (o->f->c()) rot(o); else o->d()==o->f->d()?(rot(o->f), rot(o)):(rot(o), rot(o));	
}
void access(node *o){
	node *t=o;
	for(node *c=null;o!=null;o=o->f){
		splay(o);
		o->st(c,1);
		c=o;
	}
	splay(t);
}
void mrt(node *o){
	access(o);o->rev^=1;
}
//mrt(u)
void cut(node *v){
	access(v);v->ch[0]->f=null;v->ch[0]=null;//v->upd();
}
void link(node *u,node *v){
	mrt(v);v->f=u;
}	
node *frt(node *o){
	access(o);o->push();
	while (o->ch[0]!=null){
		o=o->ch[0];o->push();
	}
	return o;
}
char ss[100];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	null=&s[0];null->ch[0]=null->ch[1]=null->f=null;null->rev=0;
	rep(i,1,n) {
		s[i].ch[0]=s[i].ch[1]=s[i].f=null;
		s[i].rev=0;
	}
	rep(i,1,m){
		int a,b;scanf("%s%d%d",ss,&a,&b);
		char c=ss[0];
		if (c=='Q') printf(frt(&s[a])==frt(&s[b])?"Yes\n" : "No\n");
		else if (c=='C') link(&s[a],&s[b]);
		else if (c=='D') {
			mrt(&s[a]);
			cut(&s[b]);
		}
	}
	return 0;
}
Problem2049

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define read(a) a=getnum()
#define print(a) printf("%d", a)
#define dbg(x) cout << #x << "=" << x << endl;
#define dbgarr(a, n) for1(i, 0, n) cout << a[i] << " "; cout << endl
 
inline int getnum() { int ret=0, k=1; char c; for(c=getchar(); c<'0' || c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0' && c<='9'; c=getchar()) ret=ret*10+c-'0'; return ret*k; }
 
const int N=10005;
int n, m;
 
struct node* null;
struct node {
    node* ch[2], *fa;
    bool rev;
    bool d() const { return fa->ch[1]==this; }
    void setc(node* c, bool d) { ch[d]=c; c->fa=this; }
    bool check() const { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=true;
            ch[1]->rev^=true;
            swap(ch[0], ch[1]);
            rev=false;
        }
    }
}*nd[N];
 
inline void rot(node* r) {
    node* fa=r->fa; bool d=r->d();
    fa->pushdown(); r->pushdown();
    if(fa->check()) r->fa=fa->fa;
    else fa->fa->setc(r, fa->d());
    fa->setc(r->ch[!d], d);
    r->setc(fa, !d);
}
 
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
 
inline void splay(node* r) {
    fix(r);
    while(!r->check())
        if(r->fa->check()) rot(r);
        else r->d()==r->fa->d()?(rot(r->fa), rot(r)):(rot(r), rot(r));
}
 
inline node* access(node* x) {
    node* y=null;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    return y;
}
 
inline void mkroot(node* x) {
    access(x)->rev^=true; splay(x);
}
 
inline void link(node* x, node* y) {
    mkroot(x); x->fa=y;
}
 
inline void cut(node* x, node* y) {
    mkroot(x);
    access(y); splay(y);
    x->fa=null; y->ch[0]=null;
}
 
inline node* findrt(node* x) {
    access(x); splay(x);
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
 
int main() {
    read(n); read(m);
    null=new node; null->fa=null->ch[0]=null->ch[1]=null; null->rev=false;
    char s[10];
    int u, v;
    for1(i, 1, n) {
        nd[i]=new node;
        nd[i]->fa=nd[i]->ch[0]=nd[i]->ch[1]=null; nd[i]->rev=false;
    }
    rep(i, m) {
        scanf("%s", s);
        read(u); read(v);
        if(s[0]=='Q')
            findrt(nd[u])==findrt(nd[v])?(printf("Yes\n")):(printf("No\n"));
        else if(s[0]=='C') link(nd[u], nd[v]);
        else cut(nd[u], nd[v]);
    }
     
    return 0;
}
Problem2049

//bzoj 2049
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20000;
struct node *null;
struct node{
	node *ch[2], *f;
	bool rev;
	void push(){if (rev) swap(ch[0], ch[1]), ch[0]->rev ^= 1, ch[1]->rev ^= 1, rev = 0;}
	int d(){return f->ch[1] == this;}
	bool c(){return f==null || f->ch[0] != this && f->ch[1] != this;} //f==null !
	void st(node *o, int d){ch[d] = o, o->f = this;}
}s[N];
void rot(node *o){
	node *f = o -> f; int d = o->d();
	if (!f->c()) f->f->st(o, f->d()); else o->f = f->f;
	f->st(o->ch[d^1],d), o->st(f, d^1);
	//f->upd();
}
void fix(node *o){
	if (!o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (!o->c())
		if (o->f->c()) rot(o); else
			(o->d() == o->f->d()) ? (rot(o->f), rot(o)) : (rot(o), rot(o));
	//o->upd();
}
void access(node *o){
	node *t = o;
	for(node *c = null; o != null; o = o->f){
		splay(o);
		o->st(c, 1);
		c = o;
	}
	splay(t);
}
void mrt(node *o){
	access(o), o->rev ^= 1;
}
void link(node *u, node *v){
	mrt(v), v->f = u;
}
//mrt(u)
void cut(node *v){//!!
	access(v), v->ch[0]->f = null, v->ch[0] = null;//v->upd();
}
node* frt(node *o){
	access(o), o->push();
	while (o->ch[0] != null) o = o->ch[0], o->push();
	return o;
}
char ss[100];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	null=&s[0];null->ch[0]=null->ch[1]=null->f=null;null->rev=0;
	rep(i,1,n) {
		s[i].ch[0]=s[i].ch[1]=s[i].f=null;
		s[i].rev=0;
	}
	rep(i,1,m){
		int a,b;scanf("%s%d%d",ss,&a,&b);
		char c=ss[0];
		if (c=='Q') printf(frt(&s[a])==frt(&s[b])?"Yes\n" : "No\n");
		else if (c=='C') link(&s[a],&s[b]);
		else if (c=='D') {
			mrt(&s[a]);
			cut(&s[b]);
		}
	}
	return 0;
}
Problem2049

//bzoj 2049
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20000;
struct node *null;
struct node{
	node *ch[2], *f;
	bool rev;
	void push(){if (rev) swap(ch[0], ch[1]), ch[0]->rev ^= 1, ch[1]->rev ^= 1, rev = 0;}
	int d(){return f->ch[1] == this;}
	bool c(){return f==null || f->ch[0] != this && f->ch[1] != this;} //f==null !
	void st(node *o, int d){ch[d] = o, o->f = this;}
}s[N];
void rot(node *o){
	node *f = o -> f; int d = o->d();
	if (!f->c()) f->f->st(o, f->d()); else o->f = f->f;
	f->st(o->ch[d^1],d), o->st(f, d^1);
	//f->upd();
}
void fix(node *o){
	if (!o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (!o->c())
		if (o->f->c()) rot(o); else
			(o->d() == o->f->d()) ? (rot(o->f), rot(o)) : (rot(o), rot(o));
	//o->upd();
}
void access(node *o){
	node *t = o;
	for(node *c = null; o != null; o = o->f){
		splay(o);
		o->st(c, 1);
		c = o;
	}
	splay(t);
}
void mrt(node *o){
	access(o), o->rev ^= 1;
}
void link(node *u, node *v){
	mrt(v), v->f = u;
}
//mrt(u)
void cut(node *v){//!!
	access(v), v->ch[0]->f = null, v->ch[0] = null;//v->upd();
}
node* frt(node *o){
	access(o), o->push();
	while (o->ch[0] != null) o = o->ch[0], o->push();
	splay(o);return o;
}
char ss[100];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	null=&s[0];null->ch[0]=null->ch[1]=null->f=null;null->rev=0;
	rep(i,1,n) {
		s[i].ch[0]=s[i].ch[1]=s[i].f=null;
		s[i].rev=0;
	}
	rep(i,1,m){
		int a,b;scanf("%s%d%d",ss,&a,&b);
		char c=ss[0];
		if (c=='Q') printf(frt(&s[a])==frt(&s[b])?"Yes\n" : "No\n");
		else if (c=='C') link(&s[a],&s[b]);
		else if (c=='D') {
			mrt(&s[a]);
			cut(&s[b]);
		}
	}
	return 0;
}
Problem2049

//bzoj 2049
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20000;
struct node *null;
struct node{
	node *ch[2], *f;
	bool rev;
	//void upd(){}
	bool c(){return f == null || (f->ch[0] != this && f->ch[1] != this);}
	bool d(){return f->ch[1]==this;}
	void push(){if (rev) rev = 0, ch[0]->rev ^= 1, ch[1]->rev^=1, swap(ch[0], ch[1]);}
	void st(node *o, int d){ch[d] = o, o->f = this;} 
}s[N];
void rot(node *o){
	node *f = o -> f; int d = o -> d();
	if (f->c()) o->f = f->f; else f->f->st(o, f->d());
	f->st(o->ch[d^1], d), o->st(f, d^1);
	//f->upd();
}
void fix(node *o){
	if (!o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (!o->c())
		if (o->f->c()) rot(o); else
			(o->d() == o->f->d()) ? (rot(o->f), rot(o)) : (rot(o), rot(o));
	//o->upd();
}
void access(node *o){
 	node *t = o;
 	for(node *c = null; o != null; o = o -> f){
 		splay(o);
 		o->st(c, 1);
 		//o->upd();
 		c = o;
 	}
 	splay(t);
}
void mrt(node *o){
	access(o), o->rev ^= 1;
}
void link(node *u, node *v){
	mrt(v), v->f = u;
}
//mrt(u)
void cut(node *v){
	access(v);
	v->ch[0]->f = null, v->ch[0] = null; //v->upd();
}
node *frt(node *o){
	access(o);
	o->push();
	while (o->ch[0] != null) 
		o = o->ch[0], 
		o->push();
	return o;
}
char ss[100];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	null=&s[0];null->ch[0]=null->ch[1]=null->f=null;null->rev=0;
	rep(i,1,n) {
		s[i].ch[0]=s[i].ch[1]=s[i].f=null;
		s[i].rev=0;
	}
	rep(i,1,m){
		int a,b;scanf("%s%d%d",ss,&a,&b);
		char c=ss[0];
		if (c=='Q') printf(frt(&s[a])==frt(&s[b])?"Yes\n" : "No\n");
		else if (c=='C') link(&s[a],&s[b]);
		else if (c=='D') {
			mrt(&s[a]);
			cut(&s[b]);
		}
	}
	return 0;
}
Problem2054

var
 l,r,i,n,m,p,q:longint;
 f,a:array[1..1000000]of longint;
procedure swap(var a,b:longint);
var
 c:longint;
begin 
 c:=a;a:=b;b:=c;
end;
function find(x:longint):longint;
begin
 if f[x]<>x then f[x]:=find(f[x]);exit(f[x]); 
end;
procedure work(l,r,k:longint);
var
 i:longint;
begin
 i:=find(l);
 while i<=r do begin 
   a[i]:=k;f[i]:=i+1;i:=find(i);
 end; 
end;
begin 
 readln(n,m,p,q);fillchar(a,sizeof(a),0);
 for i:=1 to n+1 do f[i]:=i;
 for i:=m downto 1 do begin 
   l:=(i*p+q) mod n+1;
	 r:=(i*q+p) mod n+1;
	 if l>r then swap(l,r);
	 work(l,r,i);
 end;
 for i:=1 to n do writeln(a[i]);
end.
Problem2066

var
 n,m,ans,i,j,l,cnt:longint;
 a,b:array[0..3000000]of longint;
procedure add(x:longint);
begin 
 if x>2 then begin 
   if odd(x) then x:=3 else x:=2;
 end;
 inc(l,x);inc(b[l]);
end;
begin 
 readln(m,n);ans:=0;fillchar(b,sizeof(b),0);
 for i:=1 to n do read(a[i]);
 

 if a[n]=m-1 then begin 
   for i:=n downto 1 do 
	   if a[i]=m-(n-i)-1 then inc(ans) else break;
	 writeln(ans);
	 halt;
 end;
 
 a[n+1]:=m-1;l:=0;
 for i:=n downto 1 do add(a[i+1]-a[i]-1);
 m:=l;
 
 ans:=0;cnt:=0;
 for i:=1 to m do if odd(i) then ans:=ans xor b[i];
 for i:=1 to m do
   for j:=1 to b[i] do 
	   if odd(i) then begin 
		   if ans xor b[i] xor (b[i]-j)=0 then inc(cnt);
		 end else begin 
		   if ans xor b[i-1] xor (b[i-1]+j)=0 then inc(cnt);
		 end;
 writeln(cnt);
end.
Problem2096

#include <bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=a;i<=b;i++)
#define pii pair<int , int>
#define mp make_pair
#define key first
#define id second

inline int rd() {
	char c = getchar();
	while (!isdigit(c)) c = getchar() ; int x = c - '0';
	while (isdigit(c = getchar())) x = x * 10 + c - '0';
	return x;
}

inline void upmax(int&a , int b) { if (a < b) a = b ; }

int K , n , a[3000001] , ans;

void input() {
	K = rd() , n = rd();
	For(i , 1 , n) a[i] = rd();
}

priority_queue<pii> mx , mn;

void solve() {
	for(int l = 1 , r = 1;r <= n;r ++) {
		mx.push(mp(a[r] , r)) , mn.push(mp(- a[r] , r));
		while (mx.top().key + mn.top().key > K) {
			l ++;
			while (!mx.empty() && mx.top().id < l) mx.pop();
			while (!mn.empty() && mn.top().id < l) mn.pop();
		}
		upmax(ans , r - l + 1);
	}
	printf("%d\n" , ans);
}

int main() {
	input();
	solve();
	return 0;
}
Problem2101

var
 n,i,j:longint;
 c,s:array[0..5000]of longint;
 f:array[1..6000]of longint;
function sum(l,r:longint):longint;
begin 
 exit(s[r]-s[l-1]);
end;
function min(a,b:longint):longint;
begin
 if a<b then exit(a) else exit(b); 
end;
begin 
 readln(n);fillchar(f,sizeof(f),0);
 for i:=1 to n do readln(c[i]);
 s[0]:=0;
 for i:=1 to n do s[i]:=s[i-1]+c[i];
 fillchar(f,sizeof(f),0);
 for i:=1 to n do 
     for j:=1 to n-i+1 do
         f[j]:=sum(j,j+i-1)-min(f[j],f[j+1]);
 writeln(f[1]);
end.
Problem2115

const
 max_bit=60;
var
 t,tt,ans:int64;
 l,n,m,i,j,x,y:longint;
 visited:array[1..60000]of boolean;
 dis:array[0..60000]of int64;
 u:array[0..60000]of longint;
 v,pre:array[1..300000]of longint;
 w:array[1..300000]of int64;
 a:array[1..300000]of int64;
 h:array[1..60]of int64;
 al:longint;
procedure add(a,b:longint;c:int64);
begin
 inc(l);v[l]:=b;w[l]:=c;
 pre[l]:=u[a];u[a]:=l;
end;
procedure ins(x,y:longint;z:int64);
begin
 add(x,y,z);add(y,x,z);
end;
procedure dfs(x:longint;d:int64);
var
 i:longint;
begin 
 visited[x]:=true;dis[x]:=d;
 i:=u[x];
 while i>0 do begin 
   if not visited[v[i]] then dfs(v[i],d xor w[i]) 
	 else begin 
	   inc(al);a[al]:=w[i] xor d xor dis[v[i]];
	 end;
   i:=pre[i];
 end;
end;
begin 
 readln(n,m);fillchar(visited,sizeof(visited),false);al:=0;
 for i:=1 to m do begin 
   readln(x,y,t);
	 ins(x,y,t);
 end;
 dfs(1,0);fillchar(h,sizeof(h),0);
 for i:=1 to al do
   for j:=max_bit downto 1 do begin //1 shl (j-1)
	   tt:=int64(1) shl (j-1); 
		 if a[i] and tt>0 then begin 
			 if h[j]>0 then a[i]:=a[i] xor h[j] else begin h[j]:=a[i];break;end;
		 end;
	 end;
 ans:=dis[n];
 for i:=max_bit downto 1 do begin 
	 tt:=int64(1) shl (i-1); 
   if (ans and tt=0) and (h[i]>0) then ans:=ans xor h[i];
 end;
 writeln(ans);
end.
Problem2115

const
 max_bit=60;
var
 t,ans:int64;
 l,n,m,i,j,x,y:longint;
 visited:array[1..60000]of boolean;
 dis:array[0..60000]of int64;
 u:array[0..60000]of longint;
 v,pre:array[1..300000]of longint;
 w:array[1..300000]of int64;
 tt,h:array[0..61]of int64;
procedure add(a,b:longint;c:int64);
begin
 inc(l);v[l]:=b;w[l]:=c;
 pre[l]:=u[a];u[a]:=l;
end;
procedure ins(x,y:longint;z:int64);
begin
 add(x,y,z);add(y,x,z);
end;
procedure add_a(a:int64);
var
 j:longint;
begin 
   for j:=max_bit downto 1 do begin //1 shl (j-1) 
		 if a and tt[j-1]>0 then begin 
			 if h[j]>0 then a:=a xor h[j] else begin h[j]:=a;exit;end;
		 end;
	 end;
end;
procedure dfs(x:longint;d:int64);
var
 i:longint;
begin 
 visited[x]:=true;dis[x]:=d;
 i:=u[x];
 while i>0 do begin 
   if not visited[v[i]] then dfs(v[i],d xor w[i]) 
	 else add_a(w[i] xor d xor dis[v[i]]);
   i:=pre[i];
 end;
end;
begin 
 readln(n,m);fillchar(visited,sizeof(visited),false);
 for i:=1 to m do begin 
   readln(x,y,t);
	 ins(x,y,t);
 end;fillchar(h,sizeof(h),0);
 tt[0]:=1;for i:=1 to max_bit-1 do tt[i]:=tt[i-1]*2;
 dfs(1,0);
 ans:=dis[n];
 for i:=max_bit downto 1 do
   if (ans and tt[i-1]=0) and (h[i]>0) then ans:=ans xor h[i];
 writeln(ans);
end.
Problem2118

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 500010;
struct edge{
	int to, c, pre;
}e[8000100];
int a[N], u[N], l = 0;
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c
void ins(int a,int b,int c){
	e[++l] = (edge) {b, c, u[a]}, u[a] = l;
}
typedef long long LL;
typedef pair<LL, int> node;
LL d[N];
#define pos second
#define mp(a,b) make_pair(a,b)
const LL inf = 1000000000010;
priority_queue<node> q;
bool vis[N];
void dij(){
 	rep(i,0,a[1]-1) vis[i] = 0; 
 	d[0] = 0; rep(i,1,a[1] - 1) d[i] = inf;
	q.push(mp(-d[0], 0));
	while (!q.empty()){
		int x = q.top().pos; q.pop();
		if (vis[x]) continue; else vis[x] = true;
		reg(i,x) if (d[x] + ec < d[v]) d[v] = d[x] + ec, q.push(mp(-d[v], v));
	}
}
LL calc(LL A,LL b){
	return b > A ? 0 : (A - b) / a[1] + 1;
}
int main(){
	int n; 
	LL B_min, B_max;
	scanf("%d%lld%lld",&n,&B_min,&B_max);
	rep(i,1,n) scanf("%d",&a[i]);
	sort(a+1,a+n+1);


	int j = 0;	
	rep(i,1,n) if (a[i]) {j = i;break;}
	int t = 0;
	rep(i,j,n) a[++t] = a[i];
	n = t;
	if (!n){
		if (B_min <= 0 && B_max >= 0) printf("1\n"); else printf("0\n");
		return 0;
	} 	

 	rep(i,0,a[1] - 1)
 		rep(j,2,n) ins(i, (i + a[j]) % a[1], a[j]);
 	dij();
 	LL ans = 0;
 	rep(i,0,a[1] - 1)
 		if (d[i] > B_max) continue;else{
 			ans += calc(B_max,d[i]) - calc(B_min-1,d[i]);
 		} 
 	cout <<ans<<endl;
}
Problem2121

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int L = 152, N = 32;
int l, n;
char c[L], s[N][22], len[N];
bool clr[L][L];
int f[L][L][N], ans[L], p[L][N], t[N];
void dp(){
	rep(i,1,l) rep(j,i + 1, l) clr[i][j] = 0;
	dep(i,l,1){
		rep(j,1,n) f[i][i - 1][j] = 1;
		rep(j,i,l){
			rep(k,1,n)
				f[i][j][k] = (f[i][j - 1][k] << 1) & p[j][k];
			rep(t,i,j) if (clr[t][j])
				rep(k,1,n) f[i][j][k] |= f[i][t - 1][k];
			rep(k,1,n) if (f[i][j][k] >> len[k] & 1) clr[i][j] = 1;
		}
	}
	//rep(i,1,l) rep(j,i,l) rep(k,1,n) rep(t,0,len[k] - 1) cout <<i<<' '<<j<<' '<<k<<' '<<t<<' '<< (f[i][j][k] >> t & 1)<<endl;
	//rep(i,1,l) rep(j,i,l) cout <<i<<' '<<j<<' '<<clr[i][j]<<endl;
}
void calc(){
	ans[0] = 0;
	rep(i,1,l){
		ans[i] = ans[i - 1] + 1;
		rep(j,1,i) if (clr[j][i]) ans[i] = min(ans[i], ans[j - 1]);
	}
	printf("%d\n",ans[l]);
}
int main(){
	scanf("%s",c + 1), l = strlen(c + 1);
	scanf("%d",&n);
	rep(i,1,n)
		scanf("%s",s[i]+1), len[i] = strlen(s[i]+1);
	rep(i,1,L)
		rep(j,1,n){
			p[i][j] = 0;
			rep(k,1,len[j]) if (s[j][k] == c[i]) p[i][j] |= 1 << k;
		}
	dp();
	calc();
}
Problem2154

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ab(x) (x<0? -x : x)//abs
#define mo(x,t) ((x >= 0) ? x % t : ( x % t )+t)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef long long LL;
using namespace std;

const int N=10000102;
const int P=20101009;//is_prime
LL f[N],p[N],L[N],l=0; //L[x]  :  l^-1(x)
bool a[N];

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int t=min(n,m);
	memset(a,true,sizeof(a));
	f[1]=1;L[1]=1;
	rep(i,2,t){///
		L[i]=mo(-(P/i) * (LL)L[P % i] , P);
		if (a[i]){
			p[++l]=i;
			f[i]=mo(L[i]-L[1],P);
		}
		rep(j,1,l){
			if (i*p[j] > t) break;
			a[i*p[j]]=false;
			if (i % p[j]==0){
				f[i*p[j]]=((LL)f[i]*L[p[j]]) % P;break;
			} else f[i*p[j]]=mo((LL)f[i]*f[p[j]],P);
		}
	}
	f[0]=0;
	rep(i,1,t) f[i]*=((LL)i*i) % P,f[i]%=P;
	rep(i,1,t) f[i]+=f[i-1],f[i]%=P;
	LL ans=0;
	int r;
	for(int l=1;l<=t;l=r+1){
		r=min(n/(n/l),m/(m/l));
		LL tmp=((LL)(n/l+1)*(n/l)/2) % P;
		tmp*=((LL)(m/l+1)*(m/l)/2) % P; tmp %=P;
		tmp*=(f[r]-f[l-1]) % P;tmp%=P;
		ans+=tmp;ans%=P;	
	}
	ans=mo(ans,P);
	printf("%d",ans);
	return 0;
}
	
Problem2179

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a) for(int i = 0; i < a; i++)
#define Rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 262144;
struct cp{
	double r, i;
}A[N], B[N];
cp operator + (const cp &a, const cp &b){
	return (cp){a.r + b.r, a.i + b.i};
}
cp operator - (const cp &a, const cp &b){
	return (cp){a.r - b.r, a.i - b.i};
}
cp operator * (const cp &a, const cp &b){
	return (cp){a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r};
}

char a[N], b[N];
int la, lb, lc, ans[N], rev[N];
void init(int &n){
	int m = 1, l = 0;
	while (m < n) m <<= 1, l++;
	n = m;
	rep(i,n){
		int t = 0, k = i;
		Rep(i,1,l) t = (t << 1) | (k & 1), k >>= 1;
		rev[i] = t;
	}
}
double pi = acos(-1.0);
void fft(cp *a, int l, int f){
	rep(i,l) if (rev[i] < i) swap(a[i], a[rev[i]]);
	for(int n = 2; n <= l; n <<= 1){
		cp wn = (cp){cos(2.0 * pi * f / n), sin(2.0 * pi * f / n)};
		int mid = n >> 1;
		for(int i = 0; i < l; i += n){
			cp w = (cp){1,0};
			rep(j,mid){
				cp t1 = a[i + j], t2 = a[i + j + mid] * w;
				a[i + j] = t1 + t2;
				a[i + j + mid] = t1 - t2;
				w = w * wn;
			}
		}
	}
	if (f == -1) rep(i,l) a[i].r /= l;
}
int main(){
	int n; scanf("%d",&n);
	scanf("%s",a);
	scanf("%s",b);
	la = strlen(a), lb = strlen(b);
	lc = la + lb - 1;
	rep(i,la) A[la - 1 - i].r = a[i] - '0';
	rep(i,lb) B[lb - 1 - i].r = b[i] - '0';

	init(lc);
	fft(A, lc, 1), fft(B, lc, 1);
	rep(i,lc) A[i] = A[i] * B[i];
	fft(A, lc, -1);
	rep(i,lc) ans[i] = (int)(A[i].r + 0.5);
	rep(i,lc) ans[i + 1] += ans[i] / 10, ans[i] %= 10;
	while (!ans[lc]) lc--;
	dep(i, lc, 0) printf("%d",ans[i]);
	printf("\n");
	return 0;
}
Problem2190

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#define maxn 50000
using namespace std;
bool a[maxn];
int p[maxn],miu[maxn],s[maxn],l;
void get_miu(){
	l=0;memset(a,true,sizeof(a));
	miu[1]=1;
	for (int i=2;i<=maxn;i++){
		if (a[i]){
			p[++l]=i;miu[i]=-1;;
		}
		for (int j=1;j<=l;j++){
			int t=p[j]*i;
			if (t>maxn) break;
			a[t]=false;
			if (i%p[j]==0){
				miu[t]=0;break;
			} else 
				miu[t]=-miu[i];
		}
	}
	s[0]=0;
	for (int i=1;i<=maxn;i++) s[i]=s[i-1]+miu[i];
}
long long calc(int n){
	long long ans=0;
	for (int l=1;l<=n;){
		int r=n/(n/l);
		ans+=(long long)(s[r]-s[l-1])*(n/l)*(n/l);
		l=r+1;
	}
	return ans+2;
}
int main(){
	int n;scanf("%d",&n);
	get_miu();
	if (n==1) cout <<0; else cout <<calc(n-1);
	return 0;
}
Problem2194

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 262144 + 10;
struct cp{
	double r, i;
};
cp operator + (const cp &a, const cp &b){
	return (cp){a.r + b.r, a.i + b.i};
}
cp operator - (const cp &a, const cp &b){
	return (cp){a.r - b.r, a.i - b.i};
}
cp operator * (const cp &a, const cp &b){
	return (cp){a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r};
}
int rev[N];
void init(int &n){
	int m = 1, l = 0;
	while (m < n) m <<= 1, l++;
	n = m;
	Rep(i,n){
		int t = 0, k = i;
		rep(i,1,l) t = (t << 1) | (k & 1), k >>= 1;
		rev[i] = t;
	}
}
const double pi = acos(-1.0);
void fft(cp *a, int l, int f){
	Rep(i,l) if (rev[i] < i) swap(a[rev[i]], a[i]);
	for(int n = 2; n <= l; n <<= 1){
		int mid = n >> 1;
		cp wn = (cp){cos(2.0 * pi * f / n), sin(2.0 * pi * f / n)};
		for(int i = 0; i < l; i += n){
			cp w = (cp){1,0};
			Rep(j,mid){
				cp t1 = a[i + j], t2 = a[i + j + mid] * w;
				a[i + j] = t1 + t2;
				a[i + j + mid] = t1 - t2;
				w = w * wn;
			}
		}
	}
	//!
	if (f == -1) Rep(i,l) a[i].r /= l;
}
double a[N], b[N], c[N];
cp A[N], B[N];
int main(){
	int n; scanf("%d",&n);
	int m = 2 * n - 1;
	Rep(i,n) scanf("%lf%lf",&a[i],&b[i]);
	Rep(i,n) if (n - 1 - i < i) swap(a[i], a[n - 1 - i]);

	Rep(i,n) A[i].r = a[i], A[i].i = 0;
	Rep(i,n) B[i].r = b[i], B[i].i = 0;
	init(m);
	fft(A, m, 1), fft(B, m, 1);
	Rep(i,m) A[i] = A[i] * B[i];
	fft(A, m, -1);

	Rep(i,n) c[i] = A[i].r;
	Rep(i,n) if (n - 1 - i < i) swap(c[i], c[n - 1 - i]);
	Rep(i,n) printf("%d\n",(int)(c[i]+0.5));
}
Problem2226

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ab(x) (x<0? -x : x)//abs
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

const int N=1000001;
int phi[N],l=0,p[N];
long long f[N];
bool a[N];
void work(){
	int n;scanf("%d",&n);
	long long ans=0;
	for(int i=1;i*i<=n;i++) if (n % i==0){
		if (i*i<n){
			ans+=f[i]+f[n/i];  //phi[k]*n/i=phi[k]*k
		} else {
			ans+=f[i];
		}
	}
	printf("%lld\n",ans*(long long)n);
}
int main(){
	int t;scanf("%d",&t);

	phi[1]=1;memset(a,true,sizeof(a));
	rep(i,2,N-1){
		if (a[i]) {
			p[++l]=i;
			phi[i]=i-1;
		}
		rep(j,1,l){
			if ((long long)i*p[j]>=N) break;
			a[i*p[j]]=false;
			if (i % p[j]==0){
				phi[i*p[j]]=phi[i]*p[j];break;
			} else {
				phi[i*p[j]]=phi[i]*(p[j]-1);
			}
		}
	}
	f[1]=phi[1];f[2]=phi[2];
	rep(i,3,N-1) f[i]=(phi[i]*(long long)i)>>1;
	rep(i,1,t) work();
	return 0;
}
Problem2241

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;
const int N=200;
int a[N][N],vis[N][N],tmp[N][N],m,n;

bool check(int x,int y){
	rep(i,1,m) rep(j,1,n) tmp[i][j]=a[i][j];
	rep(i,1,m) rep(j,1,n){
		if (tmp[i][j]>0 && (m-i+1 < x || n-j+1 < y)) return false;
		if (m-i+1 < x || n-j+1 < y) continue;
		int d=tmp[i][j];
		rep(k,i,i+x-1) rep(t,j,j+y-1) {
			tmp[k][t]-=d;
			if (tmp[k][t]<0) return false;
		}
	}
	return true;
}

int main(){
	scanf("%d%d",&m,&n);
	LL sum=0;
	rep(i,1,m) rep(j,1,n) scanf("%d",&a[i][j]),sum+=(LL)a[i][j];
	LL ans=sum;
	memset(vis,0,sizeof(vis));
	rep(i,1,m)
		rep(j,1,n)
			if (sum % (i*j)==0 && vis[i][j]==0) {
				if (check(i,j)) ans=min(sum/(i*j),ans);else rep(t,2,m/i) rep(k,2,n/j) vis[i*t][j*k]=-1;
			}
	cout <<ans;
}
Problem2242

var
 x1,y1:int64;
 t,k,z,p,i,y,l:longint;
 h:array[0..100009]of longint;
 h_ar,h_r,next:array[1..5000000]of longint;
function get1(y,z,p:longint):int64;
{y^z mod p}
var
 ans,tmp:int64;
 i:longint;
begin
 i:=z;tmp:=y mod p;ans:=1;
 while i>0 do begin
     if i and 1=1 then ans:=(ans*tmp) mod p;
     i:=i shr 1;tmp:=(tmp*tmp) mod p; 
 end;
 exit(ans);
end;
procedure work1(y,z,p:longint);
begin
 writeln(get1(y,z,p));
end;
function extended_gcd(a,b:longint):longint;
var
 t:int64;
begin
 if b=0 then begin
     x1:=1;y1:=0;exit(a);
 end;
 extended_gcd:=extended_gcd(b,a mod b);
 t:=x1;x1:=y1;y1:=t-(a div b)*y1;
end;
procedure work2(y,z,p:longint);
{
   know:y z p unknow:x
   x*y=z (mod p)
   x*y=z+pk
   yx-pk=z
   we need x 
   change:y(x+p)-p(k+y)=z
   为了确保最小 假设x减少了t
   则左边减少了ty
   则p(k+yt/p) 因为p是质数 一定有y或者t是p的约数，所以应当注意到如果y mod p=0，那么如果z<>0那么无解否则为0
}
var
 t:longint;
begin
 y:=y mod p;z:=z mod p;
 t:=extended_gcd(y,p);
 if y mod p=0 then begin if z mod p=0 then writeln(0) else writeln('Orz, I cannot find x!');
     exit;
 end;
 if z mod t>0 then writeln('Orz, I cannot find x!') else begin
     x1:=x1*(z div t); 
	 x1:=x1 mod p;
     if x1<0 then x1:=x1+p;
     writeln(x1);
 end;
end;
function get(x:longint):longint;
begin
 exit(x mod 100009); 
end;
procedure mark(ar,r:longint);
var
 t,g:longint;
begin
 g:=get(ar); 
 t:=h[g];
 inc(l);h_ar[l]:=ar;h_r[l]:=r;
 if t=0 then begin h[g]:=l;exit;end;
 while next[t]>0 do t:=next[t];
 next[t]:=l;
end;
function find(ar:longint):longint;
var
 t,g:longint;
begin
 g:=get(ar); 
 t:=h[g];
 if t=0 then exit(-1);
 while (h_ar[t]<>ar) and (next[t]>0) do t:=next[t];
 if h_ar[t]=ar then exit(h_r[t]) else exit(-1);
end;
procedure init(a,p,m:longint);
var
 i,t:longint;
begin
 t:=1;mark(1,0);
 for i:=1 to m-1 do begin
    t:=(int64(t)*a) mod p;mark(t,i);
 end;
end;
procedure work3(y,z,p:longint);
var
 i,t,f,k,m:longint;
{
 y^x=z mod p 
 y^(sM+r)=z mod p
 y^r=z*y^-(sM) (mod p)
 sM=i
 y^-1=y^(p-2)
 y^-(sM+r)=y^(p-2)^i
}
begin
 if y mod p=0 then begin if z mod p=0 then writeln(1) else writeln('Orz, I cannot find x!');exit;end;
 l:=0;fillchar(h,sizeof(h),0);fillchar(next,sizeof(next),0);
 m:=trunc(sqrt(p));if m=0 then inc(m);
 init(y,p,m);
 i:=0;
 while i<=p do begin
     k:=get1(y,p-2,p);k:=get1(k,i,p);k:=(z*int64(k)) mod p;
     f:=find(k);
     if f<m then if f>=0 then begin writeln(f+i);exit;end;
     i:=i+m;
 end;
 writeln('Orz, I cannot find x!');
end;
begin
 readln(t,k);
 for i:=1 to t do begin
     readln(y,z,p);
     case k of
         1:work1(y,z,p);
         2:work2(y,z,p);
         3:work3(y,z,p);
     end;
 end;
end.
Problem2243

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
using namespace std;
const int N=100100;
int c[N],u[N],dep[N],sz[N],fa[N],top[N],vis[N],son[N];
struct edge{
	int to,pre;
}e[N*2];
int l=0;
void ins(int a,int b){
	e[++l]=(edge){b,u[a]},u[a]=l;
}

#define lch (x << 1)
#define rch (lch+1)
#define mid ((l+r) >> 1)
#define lc lch,l,mid
#define rc rch,mid+1,r
struct segmenttree{
	int s[N*4+1],c[N*4+1],tag[N*4+1];
	segmenttree(){
		rep(i,0,N*4) {
			s[i]=c[i]=0;
			tag[i]=-1;
		}
	}
	void push(int x,int l,int r){
		if (tag[x]!=-1){
			s[x]=tag[x]*(r-l+1);
			if (l!=r) tag[lch]=tag[rch]=tag[x];
			tag[x]=-1;
		}
	}
	void upd(int x,int l,int r){
		push(x,l,r);push(lc);push(rc);
		s[x]=s[lch]+s[rch];
	}
	void modify(int x,int l,int r,int a,int b,int c){
		if (a>b) return;
		if (a<=l && r<=b) tag[x]=c;else{
			push(x,l,r);
			if (a<=mid) modify(lc,a,b,c);
			if (b> mid) modify(rc,a,b,c);
			upd(x,l,r);
		}
	}
	int querry(int x,int l,int r,int a,int b){
		if (a>b) return 0;
		push(x,l,r);
		if (a<=l && r<=b) return s[x];else{
			int ans=0;
			if (a<=mid) ans+=querry(lc,a,b);
			if (b> mid) ans+=querry(rc,a,b);
			return ans;
		}
	}

	void push_c(int x){
		if (c[x]){
			c[lch]=c[rch]=c[x];
			c[x]=0;
		}
	}
	void m_c(int x,int l,int r,int a,int b,int d){
		if (a>b) return;
		if (a<=l && r<=b) c[x]=d;else{
			push_c(x);
			if (a<=mid) m_c(lc,a,b,d);
			if (b> mid) m_c(rc,a,b,d);
		}
	}	
	int q_c(int x,int l,int r,int a){
		if (l==r) return c[x];
		push_c(x);
		if (a<=mid) return q_c(lc,a); else return q_c(rc,a);
	}
}s;

int n;
void dfs(int x){
	sz[x]=1;son[x]=0;
	reg(i,x)if (v != fa[x]){
		fa[v]=x;dep[v]=dep[x]+1;
		dfs(v);
		sz[x]+=sz[v];if (sz[v] > sz[son[x]]) son[x]=v;
	}
}

int dfs_clock=0;
void build(int x){
	vis[x]=++dfs_clock;
	if (son[x]){
		top[son[x]]=top[x];build(son[x]);
	}
	reg(i,x) if (v!=fa[x] && v!=son[x]){
		top[v]=v;build(v);
	}
}
void querry(int a,int b){
	int ta=top[a],tb=top[b],ans=1;
	while(ta!=tb){
		if (dep[ta]<dep[tb]){
			swap(a,b);swap(ta,tb);
		}
		ans+=s.querry(1,1,n,vis[ta],vis[a]-1);
		ans+=((s.q_c(1,1,n,vis[ta])==s.q_c(1,1,n,vis[fa[ta]])) ? 0 : 1);
		a=fa[ta];ta=top[a];
	}
	if (dep[a] > dep[b]) swap(a,b);
	ans+=s.querry(1,1,n,vis[a],vis[b]-1);
	printf("%d\n",ans);
}
void change(int a,int b,int c){
	int ta=top[a],tb=top[b];
	while (ta!=tb){
		if (dep[ta]<dep[tb]){
			swap(a,b);swap(ta,tb);
		}
		s.m_c(1,1,n,vis[ta],vis[a],c);
		s.modify(1,1,n,vis[ta],vis[a]-1,0);
		if (son[a]) s.modify(1,1,n,vis[a],vis[a],((c==s.q_c(1,1,n,vis[son[a]]))? 0 : 1));
		a=fa[ta];ta=top[a];
	}
	if (dep[a] > dep[b]) swap(a,b);
	s.m_c(1,1,n,vis[a],vis[b],c);
	s.modify(1,1,n,vis[a],vis[b]-1,0);
	if (top[a]!=a) s.modify(1,1,n,vis[fa[a]],vis[fa[a]],((c==s.q_c(1,1,n,vis[fa[a]]))? 0 : 1));
	if (son[b]) s.modify(1,1,n,vis[b],vis[b],((c==s.q_c(1,1,n,vis[son[b]]))? 0 : 1));	
}
int main(){
	int m;scanf("%d%d",&n,&m);
	rep(i,1,n) {scanf("%d",&c[i]);c[i]++;}
	rep(i,1,n-1){
		int a,b;scanf("%d%d",&a,&b);
		ins(a,b);ins(b,a);
	}
	dep[1]=1;fa[1]=0;sz[0]=0;dfs(1);
	top[0]=0;top[1]=1;build(1);
	rep(i,1,n) s.m_c(1,1,n,vis[i],vis[i],c[i]);
	rep(i,1,n)if (son[i]){
		if (c[son[i]]!=c[i]) s.modify(1,1,n,vis[i],vis[i],1); else s.modify(1,1,n,vis[i],vis[i],0);
	}else s.modify(1,1,n,vis[i],vis[i],0);
	rep(i,1,m){
		char c=getchar();while(c=='\n' || c==' ' || c=='\r') c=getchar();
		if (c=='Q'){
			int a,b;scanf("%d%d",&a,&b);
			querry(a,b);
		}else{
			int a,b,c;scanf("%d%d%d",&a,&b,&c);
			c++;
			change(a,b,c);
		}
	}
	return 0;
}
Problem2251

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=3100;
char s[N];
int a[N];
int sa[N],t[N],t1[N],c[N];
void buildsa(int n,int m){
	int *x=t,*y=t1;
	rep(i,0,m-1) c[i]=0;
	rep(i,0,n-1) c[x[i]=a[i]]++;
	rep(i,1,m-1) c[i]+=c[i-1];
	dep(i,n-1,0) sa[--c[x[i]]]=i;
	for(int k=1;k<=n;k<<=1){
		int p=0;
		rep(i,n-k,n-1) y[p++]=i;
		rep(i,0,n-1) if (sa[i]>=k) y[p++]=sa[i]-k;
		rep(i,0,m-1) c[i]=0;
		rep(i,0,n-1) c[x[y[i]]]++;
		rep(i,1,m-1) c[i]+=c[i-1];
		dep(i,n-1,0) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		x[sa[0]]=0, p=1;
		rep(i,1,n-1) 
			x[sa[i]]=y[sa[i]]==y[sa[i-1]] && sa[i]+k<n && sa[i-1]+k<n && y[sa[i]+k]==y[sa[i-1]+k] ? p-1 : p++;
		if (p>=n) break;
		m=p;	
	}
}
int h[N],rank[N];
void geth(int n){
	rep(i,0,n-1) rank[sa[i]]=i;
	int k=0;
	rep(i,0,n-1)if (rank[i]){
		if (k) k--;
		int j=sa[rank[i]-1];
		while (s[i+k]==s[j+k]) k++;
		h[rank[i]]=k;
	}
}
int main(){
	int n;scanf("%d",&n);
	scanf("%s",s);
	rep(i,0,n-1) a[i]=s[i]-'0';
	buildsa(n,2);
	geth(n);
	rep(i,0,n-1){
		rep(j,h[i]+1,min(n-sa[i],h[i+1])){
			int t=i+1;
			while (h[t]>=j) t++;
			printf("%d\n",t-i);
		}
	}
	return 0;
}
Problem2257

var
 n,k,i,t,j,tot,l:longint;
 v:array[1..10000]of longint;
 a:array[1..2000000]of longint;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin 
 i:=l;j:=r;m:=a[(l+r) shr 1];
 repeat
  while a[i]>m do inc(i);
  while a[j]<m do dec(j);
  if i<=j then begin 
     t:=a[i];a[i]:=a[j];a[j]:=t;
	 inc(i);dec(j);
  end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin 
 readln(n,k);l:=0;
 for i:=1 to n do begin 
     readln(v[i]);
	 t:=v[i];
	 for j:=1 to trunc(sqrt(t))+1 do if t div j<j then break else if t mod j=0 then begin inc(l);a[l]:=j;if t div j<>j then begin inc(l);a[l]:=t div j; end;end;
 end;
 sort(1,l);tot:=1;
 if k=1 then begin writeln(a[1]);halt;end;
 for i:=2 to l do begin 
     if a[i]=a[i-1] then inc(tot) else tot:=1;
  	 if tot>=k then begin writeln(a[i]);break;end;
 end;
end.
Problem2286

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define v e[i].to
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define ec e[i].c
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
const LL inf=(LL)0x7fffffff*100;
const int N=260000;
struct edge{
  int to,pre,c;
}e[N*2],e1[N*2];
int l=1,u[N],u1[N],l1=1;
void ins(int a,int b,int c){
  e[++l]=(edge){b,u[a],c};u[a]=l;
}
void insert(int a,int b,int c){
  ins(a,b,c);ins(b,a,c);
}
void ins1(int a,int b){
	e1[++l1]=(edge){b,u1[a],0};u1[a]=l1;
}
void insert1(int a,int b){
	ins1(a,b);ins1(b,a);
}
int n;
LL f[N],mn[N];
int fa[N],g[N][21],pre[N],dfs_clock=0,dep[N];
void dfs(int x){
	pre[x]=++dfs_clock;
	reg(i,x) if (v!=fa[x]) {
		fa[v]=x, mn[v]=min(mn[x],(LL)ec), dep[v]=dep[x]+1,dfs(v);
	}
}
void init(){
	fa[1]=dep[1]=0,mn[1]=inf,dfs(1);
	rep(i,1,n) g[i][0]=fa[i];
	rep(j,1,19) rep(i,1,n) g[i][j]=g[g[i][j-1]][j-1];
}
int lca(int a,int b){
	if (dep[a]<dep[b]) swap(a,b);
	dep(i,19,0) if (g[a][i]!=0 && dep[g[a][i]] >=dep[b]) a=g[a][i];
	dep(i,19,0) if (g[a][i]!=0 && g[b][i]!=0 && g[a][i]!=g[b][i]) {
		a=g[a][i], b=g[b][i];
	}
	if (a==b) return a;else return fa[a];//!
}
int a[N],s[N],top;
bool cmp(const int &a,const int &b){
	return pre[a]<pre[b];
}
int t[N];
void dp(int x,int fa){
	LL tmp=0;
	for(int i=u1[x];i;i=e1[i].pre) if (e1[i].to!=fa){
		dp(e1[i].to,x);
		tmp+=f[e1[i].to];
	}
	if (t[x]) f[x]=mn[x];else f[x]=min(mn[x],tmp);
	u1[x]=0;
}
void work(){
	int K;scanf("%d",&K);
	rep(i,1,K) scanf("%d",&a[i]),t[a[i]]=1;
	sort(a+1,a+K+1,cmp);
	s[top=1]=1;
	rep(i,1,K){
		int x=a[i],t=lca(s[top],x),j=top;
		if (t==s[top]) s[++top]=x; else{
			while (dep[s[j]]>dep[t]) j--;
			dep(k,top,j+2) insert1(s[k],s[k-1]),top--;
			insert1(s[top--],t);
			if (s[top]!=t) s[++top]=t;//!
			s[++top]=x;
		}
	}
	dep(i,top,2) insert1(s[i],s[i-1]);
	dp(1,0);
	rep(i,1,K) t[a[i]]=0;
	l1=1;
	printf("%lld\n",f[1]);
}
int main(){
	scanf("%d",&n);
  rep(i,1,n-1){
  	int a,b,c;scanf("%d%d%d",&a,&b,&c);
  	insert(a,b,c);
  }
  init();
  int m;scanf("%d",&m);
  rep(i,1,m) work();
  return 0;
}
Problem2288

#include <iostream>
#include <cstdio>
#include <algorithm>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define lc (x << 1)
#define rc (lc + 1)
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 100000 + 10;
int a[N];
int mx[N * 4], mn[N * 4], lmx[N * 4], lmn[N * 4], rmx[N * 4], rmn[N * 4], s[N * 4], rev[N * 4];
void Rev(int &mx, int &mn){
	swap(mx,mn);
	mx = max(0, -mx);
	mn = min(0, -mn);
}
void push(int x, int l, int r){
	if (rev[x]){
		rev[x] = 0;
		if (l < r) rev[lc] ^= 1, rev[rc] ^= 1;
		s[x] = -s[x];
		Rev(lmx[x], lmn[x]);
		Rev(rmx[x], rmn[x]);
		Rev( mx[x], mn[x] );
	}
}
void upd(int x){
	s[x] = s[lc] + s[rc];
	mx[x] = max(mx[lc], mx[rc]), mx[x] = max(mx[x], rmx[lc] + lmx[rc]);
	mn[x] = min(mn[lc], mn[rc]), mn[x] = min(mn[x], rmn[lc] + lmn[rc]);
	lmx[x] = max(lmx[lc], s[lc] + lmx[rc]);
	lmn[x] = min(lmn[lc], s[lc] + lmn[rc]);
	rmx[x] = max(rmx[rc], s[rc] + rmx[lc]);
	rmn[x] = min(rmn[rc], s[rc] + rmn[lc]);
}
void build(int x, int l, int r){
	if (l == r) {
		rev[x] = 0;
		s[x] = a[l];
		 mn[x] = min(0, a[l]),  mx[x] = max(0, a[l]);
		lmn[x] = min(0, a[l]), lmx[x] = max(0, a[l]), 
		rmn[x] = min(0, a[l]), rmx[x] = max(0, a[l]);
	}else{
		rev[x] = 0;
		build(lcq), build(rcq);
		upd(x);
	}
}
void modi(int x, int l, int r, int a, int b){
	if (a <= l && r <= b) rev[x] ^= 1, push(x, l, r); else{
		push(x, l, r);
		if (a <= mid) modi(lcq, a, b); else push(lcq);
		if (b >  mid) modi(rcq, a, b); else push(rcq);
		upd(x);
	}
}
int ansL, ansR;
int findlmx(int x, int l, int r){
	if (l == r) return l; else{
		push(lcq), push(rcq);
		if (lmx[x] == lmx[lc]) return findlmx(lcq); else return findlmx(rcq);
	}
}
int findrmx(int x, int l, int r){
	if (l == r) return l; else{
		push(lcq), push(rcq);
		if (rmx[x] == rmx[rc]) return findrmx(rcq); else return findrmx(lcq);
	}
}
void find_mx(int x, int l, int r){
	if (l == r) ansL = l, ansR = r;else{
		push(lcq), push(rcq);
		if (mx[x] == mx[lc]) find_mx(lcq);
		else if (mx[x] == mx[rc]) find_mx(rcq);
		else ansL = findrmx(lcq), ansR = findlmx(rcq);
	}
}
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]);
	build(1,1,n);
	int ans = 0;
	rep(i,1,m){
		push(1,1,n);
		int t = mx[1];
		if (t > 0){
			ans += t;
			find_mx(1,1,n);
			modi(1,1,n,ansL,ansR);
		} else break;
	}
	printf("%d\n",ans);
	return 0;
}
Problem2298

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int maxn=1000000;

struct node{
	int l,r;//(l,r]
}q[maxn];
bool cmp(const node &a,const node &b){return (a.r < b.r) || ((a.r == b.r) && (a.l < b.l));}

int f[maxn];
int main(){
	int n;
	scanf("%d",&n);
	rep(i,1,n){
		int a,b;
		scanf("%d%d",&a,&b);
		q[i].l=a;q[i].r=n-b;
	}
	sort(q+1,q+n+1,cmp);
	q[0].l=q[0].r=0;

	int j=1;f[0]=0;
	rep(i,1,n){
		f[i]=f[i-1];
		int sum=0,last=0,t=0;
		while (q[j].r==i && j<=n){
			if (q[j].l >= 0 && q[j].l <i){
				if ((q[last].l != q[j].l) || (q[last].r !=q[j].r)) sum=f[q[j].l],t=0;
				t++;
				if (t <= q[j].r-q[j].l) sum++;
				if (f[i]<sum) f[i]=sum;
				last=j;
			}
			j++;
		}
	}
	printf("%d",n-f[n]);
}
Problem2299

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;

LL gcd(LL a,LL b){
	return (b==0)?a:gcd(b,a%b);
}

LL a,b,x,y,d;

bool check(LL x,LL y){
	return (x % d==0 && y % d==0);
}

void work(){
	scanf("%lld%lld%lld%lld",&a,&b,&x,&y);
	d=gcd(a,b)*2;
	if (check(x,y) || check(x+a,y+b) || check(x+b,y+a) || check(x+a+b,y+b+a)) printf("Y\n"); else printf("N\n"); 
}

int main(){
	int t;scanf("%d",&t);
	rep(i,1,t) work();
}
Problem2300

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <set>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int maxn=100000;
const int maxq=200000;


struct dot{
	int x,y;
}d[maxn];
double operator *(dot a,dot b){
	return (double)a.x*b.y-b.x*a.y;
}
dot operator -(dot a,dot b){
	return (dot){a.x-b.x,a.y-b.y};
}
bool operator <(dot a,dot b){
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
double dis(const dot a,const dot b){
	return sqrt((double)(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
set<dot> P;
bool vis[maxn];
int q[maxq],a[maxq];
double ans=0;
double ans1[maxq];
void insert(dot a){
	set<dot>::iterator r=P.lower_bound(a),l,t;
	l=r;l--;
	dot t1=a-(*l),t2=(*r)-a;
	if (t1*t2 > 0) return;
	ans-=dis(*l,*r);
	while (l!=P.begin()){
		t=l;t--;
		t1=(*l)-(*t);t2=a-(*l);
		if (t1*t2 < 0) break;
		ans-=dis(*l,*t);
		P.erase(l);l=t;
	}
	t=r;t++;
	while (t!=P.end()){
		t1=(*r)-a;t2=(*t-*r);
		if (t1*t2 < 0)break;
		ans-=dis(*r,*t);
		P.erase(r);r=t;t++;
	}
	ans+=dis(a,*l)+dis(a,*r);
	P.insert(a);
}
int main(){
	int n,x,y;
	scanf("%d%d%d",&n,&x,&y);
	int m;
	scanf("%d",&m);
	rep(i,1,m) scanf("%d%d",&d[i].x,&d[i].y);
	int q_n;scanf("%d",&q_n);
	memset(vis,false,sizeof(vis));
	rep(i,1,q_n) {
		scanf("%d",&q[i]);
		if (q[i] == 1) {
			scanf("%d",&a[i]);
			vis[a[i]]=true;
		}
	}
	rep(i,1,m) if (!vis[i]) {q[++q_n]=1;a[q_n]=i;}

	P.insert((dot){0,0});P.insert((dot){n,0});P.insert((dot){x,y});
	ans= dis( (dot) {0,0} , (dot) {x,y} ) + dis( (dot) {x,y}, (dot) {n,0}) ;
	int l=0;
	dep(i,q_n,1){
		if (q[i]==2) ans1[++l]=ans; else insert(d[a[i]]);
	}
	dep(i,l,1) printf("%.2lf\n",ans1[i]);
	return 0;
}
Problem2301

const
 max_p=500000;
var
 n,i,l:longint;
 p,miu,s:array[0..max_p]of longint;
 a:array[1..max_p]of boolean;
procedure init;
var
 i,j:longint;
begin 
 fillchar(miu,sizeof(miu),0);miu[1]:=1;l:=0;fillchar(a,sizeof(a),true);
 for i:=2 to max_p do begin 
     if a[i] then begin 
	     inc(l);p[l]:=i;miu[i]:=-1;
	 end;
	 for j:=1 to l do begin 
	     if p[j]*i>max_p then break;
		 a[p[j]*i]:=false;
		 if i mod p[j]=0 then begin 
		     miu[p[j]*i]:=0;break;
		 end else miu[p[j]*i]:=miu[i]*(-1);
	 end;
 end;
 s[0]:=0;
 for i:=1 to max_p do s[i]:=s[i-1]+miu[i];
end;
function min(a,b:longint):longint;
begin
 if a<b then exit(a) else exit(b); 
end;
function get(a,b,k:longint):int64;
var
 l,r:longint;
 ans:int64;
begin 
 a:=a div k;b:=b div k;
 if (a=0) or (b=0) then exit(0);
 l:=1;ans:=0;
 while l<=min(a,b) do begin 
	 r:=min(a div (a div l),b div (b div l));//!!!!!!!!!!!!!! 5 div 1=1 5 div 1=5
     ans:=ans+(s[r]-s[l-1])*int64(a div l)*int64(b div l); 
	 l:=r+1;
 end;
 exit(ans);
end;
procedure work;
var
 a,b,c,d,k:longint;
begin 
 readln(a,b,c,d,k);
 writeln(get(b,d,k)-get(a-1,d,k)-get(b,c-1,k)+get(a-1,c-1,k));
end;
begin 
 readln(n);
 init;
 for i:=1 to n do work;
end.
Problem2302

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
typedef long long LL;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=1000;
LL pos[N+10];
LL f[N+10][N+10],c[N+10][N+10];
void work(){
	int n,m;
	LL M;
	scanf("%d%d%lld",&n,&m,&M);
	memset(pos,0,sizeof(pos));
	rep(i,1,m) {
		int t1,t2;
		scanf("%d%d",&t1,&t2);
		pos[t2]++;
	}
	if (pos[n]>1){printf("NO\n");return;}
	dep(i,n-1,1){
		pos[i]+=pos[i+1];
		if (pos[i] > n-i+1) {printf("NO\n");return;}
	}

	memset(c,0,sizeof(c));c[0][0]=1;
	rep(i,1,n){
		c[i][0]=c[i][i]=1;
		rep(j,1,i-1)c[i][j]=(c[i-1][j-1]+c[i-1][j]) % M;
	}


	memset(f,0,sizeof(f));f[n+1][0]=1;
	dep(i,n,1){
		rep(j,0,n-i-pos[i]+1)
			rep(k,0,j) f[i][j] =(f[i][j] + (f[i + 1][j - k] * c[j][k]) % M) % M;
	}

	printf("YES %d\n",f[1][n-m]);
}
int main(){
	int t;scanf("%d",&t);
	rep(i,1,t) work();
}
Problem2328

var
 flag,haveans:boolean;
 used:array[1..10000]of boolean;
 k,s:array[1..10000]of extended;
 i,j,t,r:longint;
 ans,a,b,vmax,sig_s,sig_l,v,x,y,f:extended;
function min(a,b:extended):extended;
begin
 if a<b then exit(a) else exit(b);
end;
begin 
 readln(t);
 for i:=1 to t do begin 
    readln(a,b,vmax,f);
    readln(r);sig_s:=0;sig_l:=0;
   for j:=1 to  r do begin 
	   readln(x,y);
       k[j]:=y/x;x:=x/1000;y:=y/1000;
       s[j]:=sqrt(x*x+y*y);
		   sig_s:=sig_s+k[j]*s[j];
	       sig_l:=sig_l+s[j];
   end;
   fillchar(used,sizeof(used),false);haveans:=true;flag:=true;
   while flag and haveans and (sig_l>0) do begin 
	 flag:=false;
      v:=(f-b*sig_s)/(a*sig_l);
	  if v<0 then haveans:=false; 
      if v>vmax then v:=vmax;
	 //writeln(-b*k[r]/a);
	  for j:=1 to r do 
		  if (k[j]<0) and (not used[j]) then  
			  if v<(-b)*k[j]/a then begin 
				  used[j]:=true;flag:=true;
			      sig_s:=sig_s-k[j]*s[j]; 
			      sig_l:=sig_l-s[j];
			  end;
	 end;
	 ans:=0;//writeln(v);
	 for j:=1 to r do begin 
	  if not used[j] then ans:=ans+s[j]/v else ans:=ans+(s[j]/min(((-b)*k[j]/a),vmax));
	 end;
	 if not haveans then writeln('IMPOSSIBLE') else writeln(ans:0:5);
 end;
end.
Problem2330

var
 t,n,k,a,x,b,l,head,tail,i:longint;
 f,g,c:array[0..2000000]of longint;
 h,dis:array[0..1000000]of longint;
 id:array[0..1000000]of boolean;
 d,pre:array[0..10000000]of longint;
 ans:int64;
procedure insert(a,b,v:longint);
begin 
 inc(l);
 f[l]:=a;g[l]:=b;c[l]:=v;
end;

procedure init;
begin
 readln(n,k);l:=0;fillchar(h,sizeof(h),0);
 if k=0 then begin writeln(n);halt;end;
 for i:=1 to k do begin 
	 readln(x,a,b);
     if (x mod 2=0) and(a=b) then begin writeln(-1);halt;end;
     if x=1 then begin 
		 insert(a,b,0);
	     insert(b,a,0);
	 end;
	 if x=2 then begin 
		 insert(a,b,1);
	 end;
	 if x=3 then begin 
		 insert(b,a,0);
	 end;
	 if x=4 then begin 
		 insert(b,a,1);
	 end;
	 if x=5 then begin 
		 insert(a,b,0);
	 end;
 end;
end;

procedure sort(l,r:longint);
var
 m,i,j:longint;
begin
 m:=f[(l+r) div 2];i:=l;j:=r;
 repeat
	 while f[i]<m do inc(i);
	 while f[j]>m do dec(j);
	 if i<=j then begin 
	     t:=f[i];f[i]:=f[j];f[j]:=t;
	     t:=g[i];g[i]:=g[j];g[j]:=t;
	     t:=c[i];c[i]:=c[j];c[j]:=t;
	     inc(i);dec(j);
	 end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;

procedure work;
var
  k:longint;
begin 
 
  head:=0;tail:=n+1;fillchar(id,sizeof(id),true); 
  for i:=1 to n do begin 
	 d[i-1]:=i;pre[i]:=1;dis[i]:=1;
 end;
  repeat
	 k:=d[head];id[k]:=false;if pre[head]>=n then begin writeln(-1);halt;end;
     i:=h[k];
     while f[i]=k do begin 
	     if dis[g[i]]<dis[k]+c[i] then begin 
		     dis[g[i]]:=dis[k]+c[i];
		     if not id[g[i]] then begin 
			     id[g[i]]:=true;
			     d[tail]:=g[i];pre[tail]:=pre[head]+1;inc(tail);tail:=tail mod 1000000;
			 end;
		 end;
	     inc(i);
	 end;
    inc(head);head:=head mod 10000000;
  until head+1>tail;
end;

procedure print;
var
	 i:longint;
begin
	ans:=0;
	for i:=1 to n do ans:=ans+dis[i];
    writeln(ans);
end;

begin 
 init;
 sort(1,l);
 for i:=1 to l do if h[f[i]]=0 then h[f[i]]:=i;
 work;
 print;
end.
Problem2396

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 1000;
int a[N][N], b[N][N], c[N][N], T[N], BT[N], ABT[N], CT[N];
int main(){
	int n;
	while (scanf("%d",&n) == 1){
		rep(i,1,n) rep(j,1,n) scanf("%d",&a[i][j]);
		rep(i,1,n) rep(j,1,n) scanf("%d",&b[i][j]);
		rep(i,1,n) rep(j,1,n) scanf("%d",&c[i][j]);
		bool flag;
		rep(t,1,10){
			rep(i,1,n) T[i] = rand();
			rep(i,1,n){
				BT[i] = 0;
				rep(j,1,n) BT[i] += b[i][j] * T[j];
			}
			rep(i,1,n){
				ABT[i] = 0;
				rep(j,1,n) ABT[i] += a[i][j] * BT[j];
			}
			rep(i,1,n){
				CT[i] = 0;
				rep(j,1,n) CT[i] += c[i][j] * T[j];
			}
			flag = true;
			rep(i,1,n) if (ABT[i] != CT[i]) {flag = false;break;}
			if (!flag) break;
		}
		if (!flag) printf("No\n"); else printf("Yes\n");
	}
	return 0;
}
Problem2431

var
 i,j,t,n,k:longint;
 f:array[0..1,-2000..2000]of int64;
begin 
 readln(n,k);
 fillchar(f,sizeof(f),0); f[1,0]:=1;
 i:=1;
 for t:=2 to n do begin 
   i:=i xor 1;
	 f[i,0]:=1;
   for j:=0 to t-2 do f[i,j+1]:=(f[i,j]+f[i xor 1,j+1])	mod 10000;
	 for j:=t-1 to k-1 do f[i,j+1]:=(f[i,j]-f[i xor 1,j-(t-1)]+f[i xor 1,j+1]) mod 10000;
 end;
 writeln(((f[i,k] mod 10000)+10000) mod 10000);
end.
Problem2434

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=100100;
char c[N];
struct node{
	node *ch[26],*f,*fa;
	int v,ue,uq,l,r,vis;
}T[N],*root=&T[0];
int l=0;
node* pos[N];
#define oc o->ch[c[i]-'a']
node *nn(){
	return &T[++l];
}
void build(){
	node *o=root;int n=strlen(c),tp=0;
	rep(i,0,n-1) 
		if (c[i]=='P'){
			o->v=1;
			pos[++tp]=o;
		} else if (c[i]=='B') o=o->fa;
		else {
			if (!oc) oc=nn();
			oc->fa=o, o=oc;
		}
}
#define xc x->ch[i]
#define xcf xc->f
#define xf x->f
node *q[N];
void calc(){
	node *x=root;int l=0,r=0;
	rep(i,0,25) if (!xc) xc=root; else q[r++]=xc,xcf=root;
	while (l<r){
		x=q[l++];
		rep(i,0,25) if (!xc) xc=xf->ch[i]; else q[r++]=xc,xcf=xf->ch[i];
	}
}
struct edge{
	node *to;
	int pre;
}e[N];
int el=0;
void ins_edge(node *a,node *b){
	e[++el]=(edge){b,a->ue};a->ue=el;
}
int dfs_clock=0;
void dfs(node *x){
	x->l=++dfs_clock;
	for(int i=x->ue;i;i=e[i].pre) dfs(e[i].to);
	x->r=dfs_clock;
}
struct BIT{
	int s[N];
	void add(int x,int d){
		while (x<=dfs_clock){
			s[x]+=d;x+=x&(-x);
		}
	}
	int sum(int x){
		int ans=0;
		while (x>0){
			ans+=s[x];x-=x&(-x);
		}
		return ans;
	}
}b;
struct qry{
	node *x;
	int pre,t;
}qr[N];
int ql=0;
void ins_qry(node *x,node *y,int t){
	qr[++ql]=(qry){x,y->uq,t};y->uq=ql;
}
int ans[N],vis[N];
void solve(){
	int n=strlen(c);node *o=root;
	rep(i,0,n-1){
		if (c[i]=='P'){
			if (!(o->vis)){
				o->vis=1;
				for(int j=o->uq;j;j=qr[j].pre) 
					ans[qr[j].t]=b.sum(qr[j].x->r)-b.sum((qr[j].x->l) -1);
			}
		}else if (c[i]=='B') b.add(o->l,-1),o=o->fa;
		else o=oc, b.add(o->l,1);
	}
}
int main(){
	scanf("%s",c);
	build();
	calc();
	rep(i,1,l) ins_edge(T[i].f,&T[i]);
	dfs(root);
	int m;scanf("%d",&m);
	rep(i,1,m) {
		int a,b;scanf("%d%d",&a,&b);
		ins_qry(pos[a],pos[b],i);
	}
	solve();
	rep(i,1,m) printf("%d\n",ans[i]);
	return 0;
}
Problem2435

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define v e[i].to
#define ec e[i].c
#define reg(i,a) for(int i = u[a];i;i=e[i].pre)
using namespace std;
const int N = 1000010;
struct edge{
	int to, pre, c;
}e[N * 2];
int l = 0, u[N];
void ins(int a,int b,int c){
	e[++l] = (edge) {b, u[a], c}, u[a] = l;
}
void insert(int a,int b,int c){
	ins(a,b,c), ins(b,a,c);
}
int n,sz[N];
typedef long long LL;
LL ans = 0;
int ab(int a){
	return a < 0 ? -a : a;
}
int q[N], f[N], c[N];
void bfs(){
	int l = 0, r = 1; sz[ q[l] = 1 ] = 1;
	while (l != r){
		int x= q[l++];sz[x] = 1;
		reg(i,x) if (v != f[x]) c[v] = ec, f[v] = x, q[r++] = v;
	}
	while (r){
		int x = q[--r];sz[f[x]]+=sz[x];
		ans += c[x] * 1LL * ab(sz[x] - (n - sz[x]));
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n - 1){
		int a, b, c;scanf("%d%d%d",&a,&b,&c);
		insert(a,b,c);
	}
	bfs();
	printf("%lld\n",ans);
	return 0;
}
Problem2440

const
 max_p=500000;
var
 t,i,l:longint;
 a:array[1..max_p]of boolean;
 p,miu:array[1..max_p]of longint;
procedure init;
var
 i,j:longint;
begin 
 l:=0;fillchar(miu,sizeof(miu),0);miu[1]:=1;fillchar(a,sizeof(a),true);
 for i:=2 to max_p do begin 
     if a[i] then begin 
	     inc(l);p[l]:=i;miu[i]:=-1;
	 end;
	 for j:=1 to l do begin 
	     if i*p[j]>max_p then break;
		 a[i*p[j]]:=false;
		 if i mod p[j]=0 then begin 
		     miu[i*p[j]]:=0;
			 break;
		 end else miu[i*p[j]]:=miu[i]*(-1);//!!!!!!!!
	 end;
 end;
end;
function calc(n:int64):int64;
var
 i:longint;
begin
 calc:=0; 
 for i:=1 to round(sqrt(n)) do begin 
     if i*i>n then break;
	 calc:=calc+(n div (i*i))*miu[i];
 end;
end;
procedure work;
var
 l,r,mid,k:int64;
begin 
 readln(k);
 l:=0;r:=k shl 1;
 //(l,r]
 repeat
    mid:=(l+r) shr 1;
	if calc(mid)>=k then r:=mid else l:=mid;
 until l+1=r;
 writeln(r);
end;
begin 
 readln(t);
 init;
 for i:=1 to t do work;
end.
Problem2456

var
 n,i,got,gotn,x:longint;
begin 
 readln(n);got:=0;gotn:=0;
 for i:=1 to n do begin 
	 read(x);
     if gotn=0 then begin got:=x;gotn:=1;end else if x=got then inc(gotn) else dec(gotn);
 end;
 writeln(got);
end.
Problem2482

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;
const int N=100001;
struct qry{
	int l,r,t;
}q[N];
bool operator < (const qry &a,const qry &b){
	return a.r<b.r;
}
#define lc (x << 1)
#define rc (lc + 1)
#define mid ((l+r) >> 1)
int a[N],pre[N],u[N*3];
#define lcq lc,l,mid
#define rcq rc,mid+1,r
#define root 1,1,n
#define wq a,b
int n;
struct segment_tree{
	LL mn[N*4],A[N*4],hmn[N*4],hA[N*4];
	void push(int x,int l,int r){
			if (l!=r){
				hA[lc]=max(A[lc]+hA[x],hA[lc]);hA[rc]=max(A[rc]+hA[x],hA[rc]);
				A[lc]+=A[x];A[rc]+=A[x];
			}
			hmn[x]=max(hmn[x],mn[x]+hA[x]);
			mn[x]+=A[x];
			A[x]=0, hA[x]=0;		
	}
	void mark(int x,int d){
		A[x]+=d;
		hA[x]=max(hA[x],A[x]);
	}
	void upd(int x){
			mn[x]=max(mn[lc],mn[rc]);
			hmn[x]=max(hmn[x],max(hmn[lc],hmn[rc]));
	}
	void ins(int x,int l,int r,int a,int b,int d){
		if (a<=l && r<=b) {mark(x,d);push(x,l,r);return;}
		push(x,l,r);
		if (a <= mid) ins(lcq,wq,d);else push(lcq);//!
		if (b >  mid) ins(rcq,wq,d);else push(rcq);//!
		upd(x);
	}
	void add(int a,int b,int d){
		ins(root,wq,d);	
	}
	LL qry(int x,int l,int r,int a,int b){
		push(x,l,r);
		if (a<=l && r<=b) return hmn[x];
		LL ans=0;
		if (a <= mid) ans=max(ans,qry(lcq,wq));
		if (b >  mid) ans=max(ans,qry(rcq,wq));
		return ans;
	}
	LL gmax(int a,int b){
		return qry(root,wq);
	}
}seg;
void print(int x,int l,int r){
 	cout <<"x:"<<x<<" l:"<<l<<" r:"<<r<<" mn:"<<seg.mn[x]<<" hmn:"<<seg.hmn[x]<<" A:"<<seg.A[x]<<" hA:"<<seg.hA[x]<<endl;
 	if (l!=r) print(lcq),print(rcq);
}
LL ans[N];
int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]),pre[i]=u[a[i]+N],u[a[i]+N]=i;
	int m;scanf("%d",&m);
	rep(i,1,m) scanf("%d%d",&q[i].l,&q[i].r),q[i].t=i;
	sort(q+1,q+m+1);
	q[0].r=0;
	rep(i,1,m){
		rep(j,q[i-1].r+1,q[i].r) {
			seg.add(pre[j]+1,j,a[j]);
			/*cout <<j<<' '<<a[j]<<endl;
			print(root);cout <<endl;*/
		}
		ans[q[i].t]=seg.gmax(q[i].l,q[i].r);
	}
	rep(i,1,m) printf("%lld\n",ans[i]);
	return 0;
}
Problem2527

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define ab(x) (x<0? -x : x)//abs
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef unsigned long long LL;
const int N=800000;
int n,m;
struct BIT{
    LL s[N];
    BIT(){
        memset(s,0,sizeof(s));
    }
    void add(int x,LL d){
        while (x<=m){
            s[x]+=d;x+=x & (-x);
        }
    }
    LL sum(int x){
        LL ans=0;
        while (x>0){
            ans+=s[x];x-=x & (-x);
        }
        return ans;
    }
};
struct BIT2{
    BIT b;//delta b[i]=a[i]-a[i-1]
    void add(int l,int r,LL d){
        b.add(l,d);b.add(r+1,-d);
    }
    LL sum(int x){
        return(b.sum(x));
    }
}B;
struct rain{
    int l,r;
    LL d;
}R[N];
struct station{
    int ith,bel;
}sta[N];
bool cmp(const station &a,const station &b){
    return a.bel<b.bel;
}
struct country{
    int l,r;
    country(){
        l=1;r=0;
    }
    LL wnt;
    LL calc(){
        LL tmp=0;
        rep(i,l,r) tmp+=B.sum(sta[i].ith);
        return tmp;
    }
}c[N];
int ans[N],cty[N],tmp1[N],tmp2[N];
void divide(int l,int r,int a,int b){//[l,r) [a,b]
    int mid=(l+r) >> 1;
    if (l+1==r){
        int i=l;
        if (R[i].l<=R[i].r) B.add(R[i].l,R[i].r,R[i].d); else {B.add(R[i].l,m,R[i].d);B.add(1,R[i].r,R[i].d);}
        rep(i,a,b) if (c[cty[i]].wnt<=c[cty[i]].calc()) ans[cty[i]]=l; else ans[cty[i]]=-1;
        if (R[i].l<=R[i].r) B.add(R[i].l,R[i].r,-R[i].d); else {B.add(R[i].l,m,-R[i].d);B.add(1,R[i].r,-R[i].d);}
    }else{
        rep(i,l,mid-1)
            if (R[i].l<=R[i].r) B.add(R[i].l,R[i].r,R[i].d); 
                else {B.add(R[i].l,m,R[i].d);B.add(1,R[i].r,R[i].d);}
         
        int t1=0,t2=0;
        rep(i,a,b){
            LL calc=c[cty[i]].calc();
            LL wnt=c[cty[i]].wnt;
            if (calc < wnt){
                c[cty[i]].wnt-=calc;tmp2[++t2]=cty[i];
            }else tmp1[++t1]=cty[i];
        }
        int tl=a;
        rep(i,1,t1)cty[tl++]=tmp1[i];
        rep(i,1,t2)cty[tl++]=tmp2[i];
 
        rep(i,l,mid-1)
            if (R[i].l<=R[i].r) B.add(R[i].l,R[i].r,-R[i].d); 
                else {B.add(R[i].l,m,-R[i].d);B.add(1,R[i].r,-R[i].d);}
 
        divide(l,mid,a,a+t1-1);
        divide(mid,r,a+t1,b);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,m) {
        scanf("%d",&sta[i].bel);//the ith space station belong 
        sta[i].ith=i;
    }
    sort(sta+1,sta+m+1,cmp);
    sta[0].bel=sta[m+1].bel=-1;
    rep(i,1,m){
        if (sta[i].bel!=sta[i-1].bel) c[sta[i].bel].l=i;
        if (sta[i].bel!=sta[i+1].bel) c[sta[i].bel].r=i;
    }
    rep(i,1,n) scanf("%lld",&c[i].wnt);//the ith country wanted p[i] kg
    int k;scanf("%d",&k);
    rep(i,1,k) scanf("%d%d%d",&R[i].l,&R[i].r,&R[i].d);
    rep(i,1,n) cty[i]=i;
    divide(1,k+1,1,n);
    rep(i,1,n) if (ans[i]==-1) printf("NIE\n");else printf("%d\n",ans[i]);
    return 0;
}
Problem2595

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int S = (1 << 10) - 1, inf = (1 << 16) * 100 + 1, Q = 11 * 11 * (S + 1); 
int f[11][11][S + 1], a[11][11], pre[11][11][S + 1];
bool inq[11][11][S + 1];

struct F{
	int i, j, s;
}q[Q], pre1[11][11][S + 1], pre2[11][11][S + 1];

int dx[5], dy[5], vis[11][11][S], Vis[11][11], ks;
void dfs(int i, int j, int s){
	vis[i][j][s] = Vis[i][j] = 1;
	if (pre1[i][j][s].i == -1) return; else{
		F x = pre1[i][j][s];
		if (!vis[x.i][x.j][x.s]) dfs(x.i, x.j, x.s);
		x = pre2[i][j][s];
		if (!vis[x.i][x.j][x.s]) dfs(x.i, x.j, x.s);
	}
}

int ans = inf, n, m;
void calc(){
	rep(i,1,n) 
		rep(j,1,m)
			if (f[i][j][ks] == ans) {dfs(i,j,ks); return;}
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
	rep(i,1,n) rep(j,1,m) rep(k,0,S) f[i][j][k] = inf, inq[i][j][k] = 0, pre1[i][j][k] = pre2[i][j][k] = (F){-1, -1, -1}, vis[i][j][k] = Vis[i][j] = 0;
	int k = 0, l = 0, r = 0;
	rep(i,1,n) rep(j,1,m) if (!a[i][j]) 
		k++, 
		f[i][j][1 << (k - 1)] = f[i][j][0] = 0,
		q[r++] = (F){i, j, 1 << (k - 1)}, q[r++] = (F){i, j, 0},
		inq[i][j][1 << (k - 1)] = inq[i][j][0] = 1;
	else 
		f[i][j][0] = a[i][j],
		q[r++] = (F){i, j, 0},
		inq[i][j][0] = 1;


	dx[0] = 0 , dy[0] = 1;
	dx[1] = 0 , dy[1] = -1;
	dx[2] = -1, dy[2] = 0;
	dx[3] = 1 , dy[3] = 0;
	dx[4] = 0 , dy[4] = 0;


	ks = (1 << k) - 1;
	while (l != r){
		F x = q[l++]; inq[x.i][x.j][x.s] = 0, l %= Q;
		int ss = ks - x.s;
		while (true){
			int s = x.s + ss;
			rep(t,0,4){
				int i = x.i + dx[t], j = x.j + dy[t];
				if (i && j && i <= n && j <= m && f[i][j][s - x.s] < inf){ 
					if (f[x.i][x.j][x.s] + f[i][j][s - x.s] < f[i][j][s]){
						f[i][j][s] = f[x.i][x.j][x.s] + f[i][j][s - x.s];
						if (!inq[i][j][s]) q[r++] = (F){i,j,s}, inq[i][j][s] = 1, r %= Q;
						pre1[i][j][s] = x, pre2[i][j][s] = (F){i, j, s - x.s};
					}
					if (f[x.i][x.j][x.s] + f[i][j][s - x.s] < f[x.i][x.j][s]){
						f[x.i][x.j][s] = f[x.i][x.j][x.s] + f[i][j][s - x.s];
						if (!inq[x.i][x.j][s]) q[r++] = (F){x.i, x.j, s}, inq[x.i][x.j][s] = 1, r %= Q;
						pre1[x.i][x.j][s] = x, pre2[x.i][x.j][s] = (F){i, j, s - x.s};
					}
				}
			}
			if (ss == 0) break; else ss = (ss - 1) & (ks - x.s);
		}
	}



	rep(i,1,n) 
		rep(j,1,m)
			ans = min(ans, f[i][j][(1 << k) - 1]);
	printf("%d\n",ans);	

	calc();

	rep(i,1,n){
		rep(j,1,m){
			if (!a[i][j])
				printf("x");
			else if (!Vis[i][j]) 
				printf("_");
			else 
				printf("o");

		}
		printf("\n");
	}
	return 0;
}
Problem2595

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int S = (1 << 10) - 1, inf = (1 << 16) * 100 + 1, Q = 11 * 11 * (S + 1); 
int f[11][11][S + 1], a[11][11], pre[11][11][S + 1];
bool inq[11][11][S + 1];

struct F{
	int i, j, s;
}q[Q], pre1[11][11][S + 1], pre2[11][11][S + 1];

int dx[5], dy[5], vis[11][11][S], Vis[11][11], ks;
void dfs(int i, int j, int s){
	vis[i][j][s] = Vis[i][j] = 1;
	if (pre1[i][j][s].i == -1) return; else{
		F x = pre1[i][j][s];
		if (!vis[x.i][x.j][x.s]) dfs(x.i, x.j, x.s);
		x = pre2[i][j][s];
		if (!vis[x.i][x.j][x.s]) dfs(x.i, x.j, x.s);
	}
}

int ans = inf, n, m;
void calc(){
	rep(i,1,n) 
		rep(j,1,m)
			if (f[i][j][ks] == ans) {dfs(i,j,ks); return;}
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
	rep(i,1,n) rep(j,1,m) rep(k,0,S) f[i][j][k] = inf, inq[i][j][k] = 0, pre1[i][j][k] = pre2[i][j][k] = (F){-1, -1, -1}, vis[i][j][k] = Vis[i][j] = 0;
	int k = 0, l = 0, r = 0;
	rep(i,1,n) rep(j,1,m) if (!a[i][j]) 
		k++, 
		f[i][j][1 << (k - 1)] = f[i][j][0] = 0,
		q[r++] = (F){i, j, 1 << (k - 1)}, q[r++] = (F){i, j, 0},
		inq[i][j][1 << (k - 1)] = inq[i][j][0] = 1;
	else 
		f[i][j][0] = a[i][j],
		q[r++] = (F){i, j, 0},
		inq[i][j][0] = 1;


	dx[0] = 0 , dy[0] = 1;
	dx[1] = 0 , dy[1] = -1;
	dx[2] = -1, dy[2] = 0;
	dx[3] = 1 , dy[3] = 0;
	dx[4] = 0 , dy[4] = 0;


	ks = (1 << k) - 1;
	while (l != r){
		F x = q[l++]; inq[x.i][x.j][x.s] = 0, l %= Q;
		int ss = ks - x.s;
		while (true){
			int s = x.s + ss;
			rep(t,0,4){
				int i = x.i + dx[t], j = x.j + dy[t];
				if (i && j && i <= n && j <= m && f[i][j][s - x.s] < inf){ 
					if (f[x.i][x.j][x.s] + f[i][j][s - x.s] < f[i][j][s]){
						f[i][j][s] = f[x.i][x.j][x.s] + f[i][j][s - x.s];
						if (!inq[i][j][s]) q[r++] = (F){i,j,s}, inq[i][j][s] = 1, r %= Q;
						pre1[i][j][s] = x, pre2[i][j][s] = (F){i, j, s - x.s};
					}
					/*if (f[x.i][x.j][x.s] + f[i][j][s - x.s] < f[x.i][x.j][s]){
						f[x.i][x.j][s] = f[x.i][x.j][x.s] + f[i][j][s - x.s];
						if (!inq[x.i][x.j][s]) q[r++] = (F){x.i, x.j, s}, inq[x.i][x.j][s] = 1, r %= Q;
						pre1[x.i][x.j][s] = x, pre2[x.i][x.j][s] = (F){i, j, s - x.s};
					}*/
				}
			}
			if (ss == 0) break; else ss = (ss - 1) & (ks - x.s);
		}
	}



	rep(i,1,n) 
		rep(j,1,m)
			ans = min(ans, f[i][j][(1 << k) - 1]);
	printf("%d\n",ans);	

	calc();

	rep(i,1,n){
		rep(j,1,m){
			if (!a[i][j])
				printf("x");
			else if (!Vis[i][j]) 
				printf("_");
			else 
				printf("o");

		}
		printf("\n");
	}
	return 0;
}
Problem2693

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ab(x) (x<0? -x : x)//abs
#define mo(x,t) ((x >= 0) ? x % t : ( x % t )+t)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef long long LL;
using namespace std;

const int N=10000011;
const LL P=100000009;//is_prime
LL f[N],p[N],L[N],l=0; //L[x]  :  l^-1(x)
bool a[N];

void work(){
	int n,m;
	scanf("%d%d",&n,&m);
	int t=min(n,m);
	LL ans=0;
	int r;
	for(int l=1;l<=t;l=r+1){
		r=min(n/(n/l),m/(m/l));
		LL tmp=((LL)(n/l+1)*(n/l)/2) % P;
		tmp*=((LL)(m/l+1)*(m/l)/2) % P; tmp %=P;
		tmp*=(f[r]-f[l-1]) % P;tmp%=P;
		ans+=tmp;ans%=P;	
	}
	ans=mo(ans,P);
	printf("%lld\n",ans);
}
int main(){
	int t=N-3;
	memset(a,true,sizeof(a));
	f[1]=1;
	rep(i,2,t){///
		if (a[i]){
			p[++l]=i;
			f[i]=mo(1-i,P);
		}
		rep(j,1,l){
			if (i*p[j] > t) break;
			a[i*p[j]]=false;
			if (i % p[j]==0){
				f[i*p[j]]=f[i];break;
			} else f[i*p[j]]=mo((LL)f[i]*f[p[j]],P);
		}
	}
	f[0]=0;
	rep(i,1,t) f[i]*=((LL)i) % P,f[i]%=P;
	rep(i,1,t) f[i]+=f[i-1],f[i]%=P;
	int n;scanf("%d",&n);
	rep(i,1,n) work();
	return 0;
}
	
Problem2705

{
 sigma(gcd(i/n))
 gcd(i,n)=l => l 是n的约数
 个数小于sqrt(n)
 我们枚举i计算l无果，可以试着枚举l！（挺常用的技巧）
 所以我们枚举gcd
 gcd(i,n)=L => gcd(i/L,n/L)=1 挺重要的结论，很好地体现了gcd的 “最大”
 那么我们枚举L,找gcd(x,n/l)=1 的个数，明显是欧拉函数
}
var
 ans:int64;
 i,n,L:longint;
function phi(n:longint):longint;
var
 i,m:longint;
begin 
 m:=trunc(sqrt(n)+1);
 phi:=n;
 for i:=2 to m do begin 
     if n mod i=0 then phi:=(phi div i)*(i-1);
	 while n mod i=0 do n:=n div i; 
 end;
 if n>1 then 
      phi:=(phi div n)*(n-1);
end;
begin
 readln(n);
 L:=trunc(sqrt(n))+1;ans:=0;
 for i:=1 to l do if n mod i=0 then begin
      if i>n div i then break;
	  inc(ans,phi(i)*(n div i));if i<>n div i then inc(ans,phi(n div i)*i);
 end;
 writeln(ans);
end.
Problem2707

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
#define re1(i,x) for(int i=u1[x];i;i=e1[i].pre)
#define v e[i].to
#define trev e1[i].to

const int N=20000,M=2000000;
using namespace std;
const double eps=0.0000001;
int n,m,s,t;
int u[N],u1[N],d[N];

struct edge{
	int to,pre;
}e[M],e1[M];
int l=0,l1=0;

void ins(int a,int b){
	e[++l]=(edge){b,u[a]};u[a]=l;d[a]++;
}
void ins_rev(int a,int b){
	e1[++l1]=(edge){b,u1[a]};u1[a]=l1;
}

bool fs[N],ft[N];
void dfss(int x){
	fs[x]=true;
	reg(i,x) if (!fs[v]) dfss(v);
}
void dfst(int x){
	ft[x]=true;
	re1(i,x) if (!ft[trev]) dfst(trev);
}

int dfs_clock=0,pre[N],low[N],scc[N],first[N],last[N],nd[N],sta[N],pla[N],top=0,nt=0,cnt=0;
int dfs(int x){
	sta[top++]=x;
	pre[x]=low[x]=++dfs_clock;
	reg(i,x) if ( !pre[v] ) low[x] = min( low[x] , dfs(v) );else if (!scc[v]) low[x]= min( low[x] , low[v] );
	
	if ( low[x]==pre[x] ){
		cnt++, first[cnt] = nt + 1;
		while (sta[top]!=x){
			top--, scc[ sta[ top ] ] = cnt, nd[ ++nt ] = sta[ top ];pla[ sta[top] ]=nt;
		}
		last[cnt]= nt;
	}
	return low[x];
}

double ans[N];
bool vis[N];
#define w nd[j]
#define jd (j-first[x]+1)
#define vd (pla[v]-first[x]+1) 
#define ab(x)  (x>0 ? x : -x )
double mat[105][105]; 
void clearmat(){
	rep(i,0,100) rep(j,0,100) mat[i][j]=0;
}
void solvemat(int n){
	rep(i,1,n){
		int k=i;
		rep(j,i+1,n) if (ab(mat[j][i]) > ab(mat[k][i])) k=j;
		if (k!=i) rep(j,0,n) swap(mat[i][j],mat[k][j]);
		if (ab(mat[i][i])<eps) continue;//! 
		rep(j,i+1,n){
			double f=mat[j][i]/mat[i][i];
			rep(k,0,n) mat[j][k]-=f*mat[i][k];
		} 
		mat[i][0]/=mat[i][i];
		dep(j,n,i) mat[i][j]/=mat[i][i];
	}
	dep(i,n,1) rep(j,1,i-1) mat[j][0]-=mat[j][i]*mat[i][0];
}
void calc(int x){
	if (vis[x]) return;else vis[x]=true;
	rep(j,first[x],last[x]) reg(i,w) calc(scc[v]);
	clearmat();
	rep(j,first[x],last[x]){
		mat[jd][jd]=1;
		if (w==t) {mat[jd][0]=0;continue;}
		reg(i,w)
			if (scc[v]==x){
				mat[jd][vd]+=((double)-1)/d[w];
				mat[jd][0]+=((double)1)/d[w];
			}else mat[jd][0]+=(ans[v]+1)/d[w]; 
	}
	solvemat(last[x]-first[x]+1);
	rep(j,first[x],last[x]) ans[w]=mat[jd][0];
}

int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	rep(i,1,m){
		int a,b;scanf("%d%d",&a,&b);
		ins(a,b);ins_rev(b,a);
	}
	rep(i,1,n) fs[i]=ft[i]=false;
	dfss(s);dfst(t);
	if (fs[t]==false) {cout <<"INF\n";return 0;}
	rep(i,1,n) if (fs[i] && (!ft[i])) {cout <<"INF\n";return 0;}
	
	rep(i,1,n) pre[i]=scc[i]=0;
	dfs(s);

	calc(scc[s]);
	if (ans[s]-eps<0)ans[s]+=eps;
	printf("%.3lf\n",ans[s]);	
	return 0;
}
Problem2728

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define for2(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int maxn=3000;
typedef long long LL;
LL a[maxn];
int f[100],v[100],n,k,cnt=0;
bool check(LL t1,LL t2){
   for2(t,1,n) if ( ((a[t] & t1) ? 1:0) != ( (a[t] & t2) ?1:0)) return false;
   return true;
}
int find(int x){
  f[x]= (f[x]==x ? x : find(f[x]));
  return f[x];
}
//calc[0,n)
LL shl(int a){
  return ((LL)1) << a;
}
LL calc(LL n){
  memset(v,0,sizeof(v));
  LL ans=0;
  if (n >= shl(k)) return shl(cnt);
  int cnt1=cnt;
  for(int i=k;i>=1;i--){
    int q=find(i);LL t=shl(i-1);
    int w= ((n & t) ? 1 : 0);
    if(!v[q]){
      cnt1--;//left
      if (w==1) ans+=shl(cnt1);
      v[q]=w+1;
    } else {
      int tmp=v[q]-1;
      if (tmp>w) return ans;
      if (tmp<w) return ans+shl(cnt1);//2^left
    }
  }
  return ans; 
}
int main(){
  LL l,r;
  scanf("%d%d%lld%lld",&n,&k,&l,&r);
  for2(i,1,n) scanf("%lld",&a[i]);
  for2(i,1,k) f[i]=i;
  for2(i,1,k-1) 
    for2(j,i+1,k){
      int q=find(i),p=find(j);
      if (p!=q) if (check(shl(i-1),shl(j-1))) f[p]=q;
    }
  for2(i,1,k) cnt+= (f[i]==i?1:0);
  printf("%lld",calc(r+1)-calc(l)); 
  return 0;
}
Problem2743

type
 bit=array[1..1000001]of longint;
var
 n,i,j,m,now,cn:longint;
 t:bit;
 l,r,p,c,a,h,ans:array[1..1000001]of longint;
procedure sort(l1,r1:longint);
var
 i,j,m,t:longint;
begin 
 i:=l1;j:=r1;m:=r[(l1+r1) shr 1];
 repeat
	 while r[i]<m do inc(i);
	 while r[j]>m do dec(j);
	 if i<=j then begin 
		 t:=l[i];l[i]:=l[j];l[j]:=t;
	     t:=r[i];r[i]:=r[j];r[j]:=t;
	     t:=h[i];h[i]:=h[j];h[j]:=t;
	     inc(i);dec(j);
	 end;
 until i>j; 
 if l1<j then sort(l1,j);
 if i<r1 then sort(i,r1);
end;
function sum(x:longint):longint;
begin
 sum:=0; if x=0 then exit(0);
 while x<=n do begin 
	 sum:=sum+t[x];x:=x+x and (-x);
 end;
end;
procedure add(x,d:longint);
begin 
  while x>0 do begin 
     t[x]:=t[x]+d;x:=x-x and (-x);
  end;
end;
begin 
 readln(n,cn,m);
 fillchar(c,sizeof(c),0);
 for i:=1 to n do read(a[i]);readln;
 for i:=1 to m do readln(l[i],r[i]);
 for i:=1 to m do h[i]:=i;
 sort(1,m);now:=1;
 for i:=1 to m do begin 
	 for j:=now to r[i] do begin
		 if c[a[j]]>0 then p[j]:=c[a[j]];
	     c[a[j]]:=j;
		 if p[j]>0 then begin 
			 add(p[j],1);
		     if p[p[j]]>0 then add(p[p[j]],-1);
		 end;
	 end;
	 now:=r[i]+1;
	 ans[h[i]]:=sum(l[i]);
 end;
 for i:=1 to m do writeln(ans[i]);
end.
		 
Problem2752

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define for(i,a,b) for(ll i=a;i<=b;i++)
#define maxn 400000 
typedef long long ll;
using namespace std;
struct node{
	ll s,si,sii,d;
};
node T[maxn*8];
ll si[maxn],sii[maxn];
void push(ll x,ll l,ll r){//[l,r]
	if (!T[x].d) return;
	T[x].s+=T[x].d*(r-l+1);
	T[x].si+=T[x].d*(si[r]-si[l-1]);
	T[x].sii+=T[x].d*(sii[r]-sii[l-1]);
	if (l!=r){
		ll lc=x << 1,rc=(x << 1)+1;
		T[lc].d+=T[x].d;
		T[rc].d+=T[x].d;
	}
	T[x].d=0;
}
void update(ll x){
	ll lc=x << 1,rc=(x << 1)+1;
	T[x].s=T[lc].s+T[rc].s;
	T[x].si=T[lc].si+T[rc].si;
	T[x].sii=T[lc].sii+T[rc].sii;
}
void add(ll x,ll l,ll r,ll a,ll b,ll d)//[l,r]
{
	push(x,l,r);
	if  (a>r || b<l) return;
	if  (a<=l && r<=b){T[x].d+=d;return;}
	ll lc=x << 1,rc=(x << 1)+1,mid=(l+r)>>1;
	add(lc,l,mid,a,b,d);add(rc,mid+1,r,a,b,d);
	push(lc,l,mid);push(rc,mid+1,r);update(x);
}
ll sum(ll x,ll l,ll r,ll a,ll b)//[l,r]
{
	push(x,l,r);
	if  (a>r || b<l) return 0;
	if  (a<=l && r<=b) return (b+a-1)*T[x].si-T[x].sii-(a*b-b)*T[x].s;
	ll lc=x << 1,rc=(x << 1)+1,mid=(l+r)>>1;
	return sum(lc,l,mid,a,b)+sum(rc,mid+1,r,a,b);
}
ll gcd(ll a, ll b)
{
  return (!b) ? a : gcd(b, a % b);
}
int main(){
	ll n,m;
	scanf("%lld%lld",&n,&m);
	si[0]=0;sii[0]=0;
	for (i,1,n){
		si[i]=si[i-1]+i;
		sii[i]=sii[i-1]+(ll)i*i;
	};
	for (i,1,m){
		char c;
    	ll l, r;
    	scanf("\n%c%lld%lld", &c, &l, &r);
		if (c=='C'){
			ll v;
			scanf("%lld",&v);
			add(1,1,n,l,r-1,v);
		}
		else{
			ll fz=sum(1,1,n,l,r),fm=(r-l+1)*(r-l)/2;
			ll g=gcd(fm,fz);
			printf("%lld/%lld\n",fz/g,fm/g);
		}
	}
	return 0;
}
Problem2820

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#define maxn 10000005
using namespace std;
bool a[maxn];
int p[maxn],miu[maxn],s[maxn],l,g[maxn];
void get_miu(){
	l=0;memset(a,true,sizeof(a));
	miu[1]=1;g[1]=0;
	for (int i=2;i<=maxn;i++){
		if (a[i]){
			p[++l]=i;miu[i]=-1;g[i]=1;
		}
		for (int j=1;j<=l;j++){
			int t=p[j]*i;
			if (t>maxn) break;
			a[t]=false;
			if (i%p[j]==0){
				g[t]=miu[i];
				miu[t]=0;break;
			} else {
				miu[t]=-miu[i];
				g[t]=miu[i]-g[i];
			}
		}
	}
	s[0]=0;
	for (int i=1;i<=maxn;i++) s[i]=s[i-1]+g[i];
}
long long calc(int n,int m){
	long long ans=0;
	for (int l=1;l<=min(n,m);){
		int r=min(n/(n/l),m/(m/l));
		ans+=(long long)(s[r]-s[l-1])*(n/l)*(m/l);
		l=r+1;
	}
	return ans;
}
int main(){
	int t;scanf("%d",&t);
	get_miu();
	for (int i=1;i<=t;i++){
		int n,m;
		scanf("%d%d",&n,&m);
	    cout <<calc(n,m)<<"\n";
	}
	return 0;
}
Problem2824

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 51;
int n, ans = 0, a[N], b[N];
void rev(int x){
	rep(i,1,x / 2) swap(a[i], a[x - i + 1]);
}
void init(){
	rep(i,1,n) b[i] = a[i];
	dep(i,n,1) if(a[i] != i){
		int pos;
		rep(j,1,i) if (a[j] == i) pos = j;
		if (pos != 1) rev(pos), ans++;
		rev(i), ans++;
	}
	rep(i,1,n) a[i] = b[i];
}
int cnt(){
	int ans = 0;
	rep(i,2,n) if (a[i] != a[i - 1] + 1 && a[i] != a[i - 1] - 1) ans++;
	return ans;
}
#define mp(a,b) make_pair(a,b)
typedef pair<int, int> node;
node q[N * 3][N];
void calc(int t){
	//cout <<t<<' '<<cnt()<<endl;
	if (t + cnt() > ans) return;
	int flag = 1;
	rep(i,1,n - 1) if (a[i] + 1 != a[i + 1]) {flag = 0; break;} 
	if (flag) {ans = t; return;}

	rep(i,2,n){
		rev(i);
		q[t][i] = mp(cnt(), i);
		rev(i);
	}
	sort(q[t] + 2, q[t] + n + 1);
	
	rep(i,2,n){
		int x = q[t][i].second;
		rev(x);
		calc(t + 1);
		rev(x);
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) b[i] = a[i];
	sort(b + 1, b + n + 1);
	rep(i,1,n) rep(j,1,n) if (a[i] == b[j]) a[i] = j;
	init();
	calc(0);
	printf("%d\n",ans);
}
Problem2824

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 51;
int n, ans = 0, a[N], b[N];
void rev(int x){
	rep(i,1,x / 2) swap(a[i], a[x - i + 1]);
}
void init(){
	rep(i,1,n) b[i] = a[i];
	dep(i,n,1) if(a[i] != i){
		int pos;
		rep(j,1,i) if (a[j] == i) pos = j;
		if (pos != 1) rev(pos), ans++;
		rev(i), ans++;
	}
	rep(i,1,n) a[i] = b[i];
}
inline int cnt(){
	int ans = 0;
	rep(i,2,n) if (a[i] != a[i - 1] + 1 && a[i] != a[i - 1] - 1) ans++;
	return ans;
}
#define mp(a,b) make_pair(a,b)
typedef pair<int, int> node;
node q[N * 3][N];
inline void calc(int t){
	//cout <<t<<' '<<cnt()<<endl;
	if (t + cnt() >= ans) return;
	int flag = 1;
	rep(i,1,n - 1) if (a[i] + 1 != a[i + 1]) {flag = 0; break;} 
	if (flag) {ans = t; return;}

	rep(i,2,n){
		rev(i);
		q[t][i] = mp(cnt(), i);
		rev(i);
	}
	sort(q[t] + 2, q[t] + n + 1);
	
	rep(i,2,n){
		int x = q[t][i].second;
		rev(x);
		calc(t + 1);
		rev(x);
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) b[i] = a[i];
	sort(b + 1, b + n + 1);
	rep(i,1,n) rep(j,1,n) if (a[i] == b[j]) a[i] = j;
	init();
	calc(0);
	printf("%d\n",ans);
}
Problem2875

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
typedef pair<LL, LL> mat;
#define x first
#define y second
#define mp(a,b) make_pair(a,b)
LL m,a,c,x0,n,g;
LL mult(LL a,LL b){
	LL ans = 0;
	for(;b;b >>= 1, a = (a << 1) % m) if (b&1) ans = (ans + a) % m;
	return ans;
}
mat operator * (const mat &a,const mat &b){
	return mp(mult(a.x,b.x), (mult(a.x,b.y) + a.y) % m);
}
mat s,w;
mat pow(mat a,LL b){
	w = mp(1,0);
	for(;b;b >>= 1, a = a * a) if (b&1) w = w * a;
	return w;
}
int main(){
	cin >>m>>a>>c>>x0>>n>>g;
	mat t = mp(a,1);
	t = pow(t, n);
	LL ans = mult(x0 ,t.x) +mult(c,t.y);
	ans = ans % m % g;
	cout <<ans<<endl;
}
Problem2876

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const double eps = 0.00000000001;
double calc(double m, double k, double v){
	double l = max(v, 0.0), r = 1000000000.0; int t = 0;
	while (l + eps < r && t++ <= 200){
		double mid = (l + r) / 2;
		if (k * (mid - v) * mid * mid <= m) l = mid; else r = mid;
	}
	return l;
}
const int N = 10010;
double s[N], k[N], v[N], V[N];
int main(){
	int n;scanf("%d",&n);
	double E;scanf("%lf",&E);
	rep(i,1,n) scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
	double l = 0, r = 1000000000.0;
	int t = 0;
	while (l + eps < r && t++ <= 200){
		double mid = (l + r) / 2;
		rep(i,1,n) V[i] = calc(mid, k[i], v[i]);
		double tot = 0;
		rep(i,1,n) {
			tot += k[i] * (V[i] - v[i]) * (V[i] - v[i]) * s[i];
			if (tot > E) break;
		}
		if (tot < E) l = mid; else r = mid;
	}
	double ans = 0;
	rep(i,1,n) ans += s[i]/V[i];
	printf("%.8lf\n",ans);
	return 0;
}
Problem2878

#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define ec e[i].c
#define v e[i].to
#define next(a) (a==cl? 1: a+1)
#define pret(a) (a==1? cl: a-1)
using namespace std;
const int N=200000,M=N*10;
struct edge{
	int to,pre,c;
}e[M];
int l=1;
int u[N];
void ins(int a,int b,int c){
	e[++l]=(edge){b,u[a],c}, u[a]=l;
}
void insert(int a,int b,int c){
	ins(a,b,c), ins(b,a,c);
}
int cnt[N],fa[N];
double down[N],up[N];
void dfs_down(int x){
	down[x]=cnt[x]=0;
	reg(i,x) if (fa[v]==0){
		fa[v]=x; dfs_down(v);
		down[x]+=down[v]+ec, cnt[x]++;
	}
	if (cnt[x]!=0) down[x]/=(double)cnt[x];
}
void dfs_up(int x){
	if (cnt[x]==1 && x==1) {
		reg(i,x) { up[v]=ec;dfs_up(v); }
		return;
	}
	reg(i,x) if (fa[v]==x) { 
		up[v]=(up[x]+down[x]*cnt[x]-(down[v]+ec))/(double)(x==1 ? cnt[x]-1 : cnt[x])+ec;
		dfs_up(v);
	}
}

//! ec del
int f[N],a,b,dep[N],dis[N],ccw;
void ddfs(int x){
	reg(i,x)if (f[v]==0){
		f[v]=x, dep[v]=dep[x]+1, dis[v]=ec;
		ddfs(v);
	}else{
		if (f[x]!=v) a=x,b=v,ccw=ec;
	}
}
void solve_up(int x){
	reg(i,x) if (fa[v]==x){
		up[v]=(up[x]+down[x]*cnt[x]-(down[v]+ec))/cnt[x]+ec;solve_up(v);
	}
}
int c[N],cl=0;
double cup[N],cdown[N];
double cw[N];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	rep(i,1,m) {
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c),insert(a,b,c);
	}
	if (m==n-1){
		rep(i,1,n) fa[i]=0;
		fa[1]=1;dfs_down(1);
		up[1]=0;dfs_up(1);
		double ans=down[1];
		rep(i,2,n) ans+=(up[i]+down[i]*cnt[i])/(cnt[i]+1);
		ans/=n;
		//rep(i,1,n) printf("%.8lf %.8lf\n",up[i],down[i]);
		printf("%.5lf\n",ans);
	}else{
		rep(i,1,n) f[i]=0;
		f[1]=1;dep[1]=0;ddfs(1);
		int a1=a,b1=b;
		while (a!=	b){
			if (dep[a]<dep[b]) swap(a,b);
			c[++cl]=a;a=f[a];
		}
		c[++cl]=a;
		rep(i,1,n) fa[i]=0;
		rep(i,1,cl) fa[c[i]]=-1;
		rep(i,1,cl) dfs_down(c[i]);
		int top=c[cl],t=0;
		while (a1!=top){
			c[++t]=a1;
			cw[t]=dis[a1];
			a1=f[a1];
		}
		c[++t]=top;
		t=cl;
		while (b1!=top){
			c[t--]=b1;cw[t]=dis[b1];
			b1=f[b1];
		}
		cw[cl]=ccw;
		//rep(i,1,cl) cout <<c[i]<<' '<<cw[i]<<endl;
		rep(i,1,cl){
			double cp=cw[i],prob=1;
			int j;
			for(j=next(i);next(j)!=i;j=next(j)){
				int x=c[j];
				cp+=(double)cnt[x]/((double)cnt[x]+1)*down[x]*prob;
				prob/=(double)cnt[x]+1;cp+=(double)prob*cw[j];
			}
			int x=c[j];
			cp+=(double)down[x]*prob;
			cup[c[i]]=cp;
		}
		rep(i,1,cl){
			double cp=cw[pret(i)],prob=1;
			int j;
			for(j=pret(i);pret(j)!=i;j=pret(j)){
				int x=c[j];
				cp+=(double)cnt[x]/((double)cnt[x]+1)*down[x]*prob;
				prob/=(double)cnt[x]+1;cp+=prob*cw[pret(j)];
			}
			int x=c[j];
			cp+=down[x]*prob;
			cdown[c[i]]=cp;
		}
		rep(j,1,cl){
			int x=c[j];
			up[x]=(cup[x]+cdown[x])/2;
			reg(i,x) if (fa[v]==x) {
				up[v]=(up[x]*2 + down[x]*cnt[x] - down[v] - ec)/(double)(cnt[x]+1)+ec;
				solve_up(v);
			}
		}
		double ans=0;
		rep(i,1,n) if (fa[i]==-1) ans+=(cup[i]+cdown[i]+down[i]*cnt[i])/(double)(cnt[i]+2);
		else ans+=(up[i]+down[i]*cnt[i])/((double)cnt[i]+1);
		ans/=n;
		printf("%.5lf",ans);
	}
	return 0;
}
Problem2879

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
#define ew e[i].w
#define ec e[i].c
#define iw e[i^1].w
#define iv e[i^1].to
using namespace std;
const int N=600000,M=1000000,inf=0x7fffffff;
int u[N];
struct edge{
	int to,pre,w,c;
}e[M];
int S,T,l=1;
void ins(int a,int b,int w,int c){
	e[++l]=(edge){b,u[a],w,c};u[a]=l;
}
void insert(int a,int b,int w,int c){
	ins(a,b,w,c);ins(b,a,0,-c);
}
int q[N],inq[N],from[N],h[N];
bool spfa(){
	int l=0,r=1;rep(i,0,T) h[i]=inf,inq[i]=0,from[i]=0;
	h[q[0]=S]=0;
	while (l!=r){
		int x=q[l++];l%=N;inq[x]=0;
		reg(i,x) if (ew && h[x]+ec < h[v]){
			h[v]=h[x]+ec;from[v]=i;
			if (!inq[v]) inq[v]=1,q[r++]=v,r%=N;
		}
	}
	return h[T]!=inf;
}
int ans=0;
int p[N],t[50][200],cnt[N],now[N],n,m,ed;
void mcf(){
	int x=inf;
	for(int i=from[T];i;i=from[iv]) 
		x=min(x,ew);
	for(int i=from[T];i;i=from[iv]) 
		ew-=x,iw+=x,ans+=x*ec;
	int j;for(j=1;j<=m && e[now[j]].w;j++);
	cnt[j]++;ed++;
	rep(i,1,n) insert(i,ed,1,cnt[j]*t[i][j]);
	now[j]=l+1;insert(ed,T,1,0);
}
int main(){
	scanf("%d%d",&n,&m);
	int sum=1;S=0;
	rep(i,1,n) scanf("%d",&p[i]), sum+=p[i],insert(S,i,p[i],0);
	ed=n+m;
	rep(i,1,n) rep(j,1,m) scanf("%d",&t[i][j]),insert(i,n+j,1,t[i][j]);
	T=n+sum+m+1;
	rep(i,1,m) now[i]=l+1,insert(n+i,T,1,0),cnt[i]=1;
	while (spfa()) mcf();
	printf("%d\n",ans);
	return 0;
}
Problem2879

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
#define ew e[i].w
#define ec e[i].c
#define iw e[i^1].w
#define iv e[i^1].to
using namespace std;
const int N=600000,M=1000000,inf=0x7fffffff;
int u[N];
struct edge{
	int to,pre,w,c;
}e[M];
int S,T,l=1;
void ins(int a,int b,int w,int c){
	e[++l]=(edge){b,u[a],w,c};u[a]=l;
}
void insert(int a,int b,int w,int c){
	ins(a,b,w,c);ins(b,a,0,-c);
}
int q[N],inq[N],from[N],h[N];
bool spfa(){
	int l=0,r=1;rep(i,0,T) h[i]=inf,inq[i]=0,from[i]=0;
	h[q[0]=S]=0;
	while (l!=r){
		int x=q[l++];l%=N;inq[x]=0;
		reg(i,x) if (ew && h[x]+ec < h[v]){
			h[v]=h[x]+ec;from[v]=i;
			if (!inq[v]) inq[v]=1,q[r++]=v,r%=N;
		}
	}
	return h[T]!=inf;
}
int ans=0,x;
void mcf(){
	x=inf;
	for(int i=from[T];i;i=from[iv]) x=min(x,ew);
	for(int i=from[T];i;i=from[iv]) ew-=x,iw+=x,ans+=x*ec;
}
int p[N],t[50][200],cnt[N],now[N];
#define food(a) a
#define cook(i,j) (n+(i-1)*sum+j)
int main(){
	int n,m;scanf("%d%d",&n,&m);
	int sum=0;
	rep(i,1,n) scanf("%d",&p[i]), sum+=p[i];
	rep(i,1,n) rep(j,1,m) scanf("%d",&t[i][j]);
	S=0;T=n+sum*m+1;
	rep(i,1,n) insert(S,food(i),p[i],0);
	rep(i,1,m) cnt[i]=now[i]=0;e[0].w=0;
	rep(tt,1,sum){
		rep(j,1,m) if (!e[now[j]].w) {
				cnt[j]++;
				now[j]=l+1;
				insert(cook(j,cnt[j]),T,1,0);
				rep(k,1,n) insert(food(k),cook(j,cnt[j]),1,cnt[j]*t[k][j]);
			}
	 	if (spfa()) mcf();
		if (x==0) break;
	}
	printf("%d",ans);
	return 0;
}
Problem2957

type
 dot=record
     max:extended;
	 s:longint;
 end;
var
 n,m,i,xi,yi:longint;
 T:array[1..500000]of dot;
function  max(a,b:extended):extended;
begin
 if a>b then exit(a) else exit(b); 
end;
function calc(x,l,r:longint;k:extended):longint;//[l,r)
var
 m,lc,rc:longint;
begin 
 m:=(l+r) shr 1;lc:=x shl 1;rc:=lc+1;
 if T[x].max<=k then exit(0);
 if l+1=r then if T[x].max>k then exit(1) else exit(0);
 if T[lc].max>k then exit(T[x].s-T[lc].s+calc(lc,l,m,k));
 if T[lc].max<=k then exit(calc(rc,m,r,k)); 
end;
procedure add(x,l,r,a:longint;d:extended);//[l,r)
var
 m,lc,rc:longint;
begin 
 m:=(l+r) shr 1;lc:=x shl 1;rc:=lc+1;
 if (a<l) or (a>=r) then exit;
 if l+1=r then begin 
     T[x].max:=d;T[x].s:=1;exit;
 end;
 if a<m then add(lc,l,m,a,d) else add(rc,m,r,a,d);
 T[x].max:=max(T[lc].max,T[rc].max);
 T[x].s:=T[lc].s+calc(rc,m,r,T[lc].max);
end;
begin 
 readln(n,m);
 for i:=1 to m do begin 
     readln(xi,yi);
	 add(1,1,n+1,xi,extended(yi/xi));
	 writeln(T[1].s);
 end;
end.
Problem3016

var
 x:char;
 n,t,ans:longint;
 c,s:array[0..100000]of longint;
begin 
 s[0]:=0;n:=0;ans:=0;
 while not seekeoln do begin 
     read(x);inc(n);
     if x='(' then c[n]:=1 else c[n]:=-1;s[n]:=s[n-1]+c[n];
	 if s[n]<0 then begin s[n]:=s[n-1]+1;c[n]:=1;inc(ans);end;
 end;
 if s[n]=0 then begin writeln(ans);halt;end else begin writeln(ans+s[n] div 2);end;
end.
Problem3038

type
	ll=int64;
	bit=array[1..100000]of ll;
var
 b:bit;
 n,m,i,x,l,r,j,t:longint;
 d:array[1..100000]of ll;
function sum(x:longint):ll;
begin 
 sum:=0;
 while x>0 do begin 
	 sum:=sum+b[x];x:=x-(-x) and x;
 end;
end;
procedure add(x:longint;d:ll);
begin 
  while x<=n do begin 
	   b[x]:=b[x]+d;x:=x+(-x) and x;
 end;
end;
begin 
 readln(n);
 for i:=1 to n do begin 
	 read(d[i]);add(i,d[i]);
 end;
 readln;readln(m);
 for i:=1 to m do begin
	 readln(x,l,r);if r<l then begin t:=r;r:=l;l:=t;end;
     if x=1 then writeln(sum(r)-sum(l-1));
	 if x=0 then if sum(r)-sum(l-1)>r-l+1 then for j:=l to r do begin if (d[j]=0) or (d[j]=1) then continue;add(j,trunc(sqrt(d[j]))-d[j]);d[j]:=trunc(sqrt(d[j]));end;
 end;
end.
Problem3083

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
using namespace std;
const int inf=0x7fffffff;
const int N=200000;
int u[N];
struct edge{
	int to,pre;
}e[N*2];
int l=0;
#define lch (x << 1) 
#define rch (lch +1)
#define mid ((l+r) >> 1)
#define lc  lch,l,mid
#define rc  rch,mid+1,r
struct segment_tree{
	int mn[4*N+1],size,tag[4*N+1];
	segment_tree(){
		rep(i,0,N-1) {tag[i]=0;mn[i]=inf;}
	}
	void push(int x){
		if (tag[x]){
			mn[x]=tag[x];
			if (lch<=4*N && rch<=4*N) tag[lch]=tag[rch]=tag[x];
			tag[x]=0;
		}
	}
	void upd(int x){
		push(x);push(lch);push(rch);
		mn[x]=min(mn[lch],mn[rch]);
	}
	void modi(int x,int l,int r,int a,int b,int c){
		if (a<=l && r<=b) tag[x]=c;else{
			push(x);
			if (a <=mid) modi(lc,a,b,c);
			if (b > mid) modi(rc,a,b,c);
			upd(x);
		}
	}
	void modify(int a,int b,int c){
		modi(1,1,size,a,b,c);
	}
	int q_min(int x,int l,int r,int a,int b){
		push(x);
		if (a<=l && r<=b) return mn[x];
		int ans=inf;
		if (a <=mid) ans=min(ans,q_min(lc,a,b));
		if (b > mid) ans=min(ans,q_min(rc,a,b));
		return ans;
	}
	int querry(int a,int b){
		return q_min(1,1,size,a,b);
	}

}s;
void ins(int a,int b){
	e[++l]=(edge){b,u[a]};u[a]=l;
}

int  sz[N],son[N],fa[N],dep[N];
void dfs(int x){
	sz[x]=1;son[x]=0;
	reg(i,x)if (fa[x] != v){
		fa[v]=x, dep[v]=dep[x]+1, dfs(v);
		sz[x]+=sz[v];
		if (sz[v]>sz[son[x]]) son[x]=v;
	}
}
int top[N],vis[N],dfs_clock=0,v2[N];
void build(int x){
	vis[x]=++dfs_clock;//!
	if (son[x]){
		top[son[x]]=top[x];build(son[x]);
	}
	reg(i,x) if (fa[x]!=v && son[x]!=v){
		top[v]=v;build(v);
	}
	v2[x]=dfs_clock;
}
void change(int a,int b,int c){
	int ta=top[a],tb=top[b];
	while (ta!=tb){
		if (dep[ta] < dep[tb]){
			swap(a,b);swap(ta,tb);
		}
		s.modify(vis[ta],vis[a],c);
		a=fa[ta];ta=top[a];
	}
	if (dep[a]>dep[b]) swap(a,b);
	s.modify(vis[a],vis[b],c);
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	s.size=n;
	rep(i,1,n-1){
		int a,b;scanf("%d%d",&a,&b);
		ins(a,b);ins(b,a);
	}
	fa[1]=1;sz[0]=0;dep[1]=1;dfs(1);
	top[1]=1;build(1);
	rep(i,1,n) {
		int w;scanf("%d",&w);
		s.modify(vis[i],vis[i],w);
	}
	int root;scanf("%d",&root);
	rep(i,1,m){
		int op;
		scanf("%d",&op);
		if (op==1) scanf("%d",&root);
		else if (op==2){
			int p1,p2,c;
			scanf("%d%d%d",&p1,&p2,&c);
			change(p1,p2,c);
		}else{
			int x;scanf("%d",&x);
			if (!(vis[x] <= vis[root] && vis[root]<=v2[x])) printf("%d\n",s.querry(vis[x],v2[x]));
			else {
				int ans=inf,t;
				reg(i,x) if (v!=fa[x] && vis[v]<=vis[root] && vis[root]<=v2[v]) {
					t=v;break;
				}
				if (vis[t]>1) ans=min(ans,s.querry(1,vis[t]-1));
				if (v2[t]<n) ans=min(ans,s.querry(v2[t]+1,n));
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
Problem3143

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ab(x) (x<0? -x : x)//abs
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

const int N=600,M=600*600;

int u[N],d[N];
struct edge{
	int to,pre;
}e[M];
int l=0;
void ins(int a,int b){
	e[++l]=(edge){b,u[a]};u[a]=l;
}
void insert(int u,int v){
	ins(u,v);ins(v,u);
	d[u]++;d[v]++;
}


int n,m;
int u1[M],v1[M];
void init(){
	scanf("%d%d",&n,&m);
	memset(u,0,sizeof(u));memset(d,0,sizeof(d));
	rep(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		u1[i]=u;v1[i]=v;
		insert(u,v);
	}
}

struct equation{
	double a[N],ans;
}q[N];

void make_equation(){
	rep(i,1,n-1){
		q[i].ans=0;
		rep(j,1,n) q[i].a[j]=0;
		q[i].a[i]=1;
		for (int j=u[i];j;j=e[j].pre){
			int k=e[j].to;
			q[i].a[k]=((double)-1) /d[k];
		}
	}
	q[1].ans=1;
	rep(i,1,n) q[n].a[i]=0;
	q[n].a[n]=1;q[n].ans=0;
}


void print(){
	rep(i,1,n){
		rep(j,1,n) cout <<q[i].a[j]<<" ";
		cout <<q[i].ans<<"\n";
	}
	cout <<"\n";
}


double f[N];
void solve_equation(){
	//print();
	rep(i,1,n){
		//The bigger the exacter
		int r=i;
		rep(j,i+1,n) if (ab(q[j].a[i])>ab(q[r].a[i])) r=j;
		if (i!=r) swap(q[i],q[r]);

		rep(j,i+1,n){
			double f=q[j].a[i]/q[i].a[i];
			q[j].ans-=q[i].ans*f;
			rep(k,i,n) q[j].a[k]-=q[i].a[k]*f;
		}
		//print();
	}

	dep(i,n,1){
		f[i]=q[i].ans/q[i].a[i];
		rep(j,1,i-1) q[j].ans-=q[j].a[i]*f[i];
	}
}

double t[M];
void print_ans(){
	rep(i,1,m) t[i]=f[u1[i]]/d[u1[i]] + f[v1[i]]/d[v1[i]];
	sort(t+1,t+1+m);
	double ans=0;
	rep(i,1,m) ans+=t[i]*(m-i+1);
	printf("%.3lf",ans);
}

int main(){
	init();
	make_equation();
	solve_equation();
	print_ans();
	return 0;
}
Problem3144

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ab(x) (x<0? -x : x)//abs
#define min(a,b) (a<b ? a : b)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define id(a,b,c) (((0 < a) && (a <= p) && (0 < b) && (b <= q) && (0 < c) && (c <= r+1)) ? (c-1)*p*q + (a-1) *q + b : -1)

int s,t;
const int N=50*50*50;
const int M=N*8;
const int inf=1000000000;
int u[N],cur[N],l=2;
struct edge{
	int to,pre,w;
}e[M];
void ins(int a,int b,int c){
	e[l]=(edge){b,u[a],c};u[a]=l++;
}
void insert(int a,int b,int c){
	//printf("%d %d %d\n",a,b,c);
	ins(a,b,c);ins(b,a,0);
}

int q[N],h[N];
bool bfs(){
	int l=0,r=1;q[l]=s;
	rep(i,s,t) h[i]=-1;h[s]=0;
	while (l<r){
		int k=q[l++];
		for(int i=u[k];i;i=e[i].pre) if (e[i].w && h[e[i].to]==-1){
			h[e[i].to]=h[k]+1;q[r++]=e[i].to;
		}
	}
	return h[t]!=-1;
}

int dfs(int x,int f){
	if (x==t) return f;
	int w=0,used=0;
	for(int i=cur[x];i;i=e[i].pre) if (e[i].w && h[e[i].to]==h[x]+1){
		w=min(f-used,e[i].w);
		w=dfs(e[i].to,w);
		e[i].w-=w;if (e[i].w) cur[x]=i;
		e[i^1].w+=w;
		used+=w;if (used==f) return f;
	}
	if (!used) h[x]=-1;
	return used;
}
int dinic(){
	int ans=0;
	while (bfs()){
		rep(i,s,t) cur[i]=u[i];
		ans+=dfs(s,inf);
	}
	return ans;
}

int main(){
	int p,q,r;scanf("%d%d%d",&p,&q,&r);
	int d;scanf("%d",&d);
	s=0,t=id(p,q,r+1)+1;
	rep(i,1,p)rep(j,1,q) insert(s,id(i,j,1),inf);
	rep(i,1,r)
		rep(j,1,p)
			rep(k,1,q){
				int v;scanf("%d",&v);
				insert(id(j,k,i),id(j,k,i+1),v);
			}
	rep(i,1,p)
		rep(j,1,q)
			insert(id(i,j,r+1),t,inf);
	rep(i,1,p)
		rep(j,1,q)
			rep(k,1,r){
				if (id(i-1,j,k+d)!=-1) insert(id(i-1,j,k+d),id(i,j,k),inf);
				if (id(i,j-1,k+d)!=-1) insert(id(i,j-1,k+d),id(i,j,k),inf);				
				if (id(i+1,j,k+d)!=-1) insert(id(i+1,j,k+d),id(i,j,k),inf);
				if (id(i,j+1,k+d)!=-1) insert(id(i,j+1,k+d),id(i,j,k),inf);
			}
	printf("%d",dinic());
}
Problem3155

type 
  bit=array[0..1000000]of int64;
var
 i,d,x,n,m,j:longint;
 k:char;
 b1,b2:bit;
 a:array[0..1000000]of longint;
procedure add_1(x:longint;d:int64);
begin
 while x<=n do begin 
	 b1[x]:=b1[x]+d;x:=x+(-x) and x;
 end;
end;
procedure add_2(x:longint;d:int64);
begin
 while x<=n do begin 
	 b2[x]:=b2[x]+d;x:=x+(-x) and x;
 end;
end;
function sum_1(x:longint):int64;
begin
 sum_1:=0;
 while x>0 do begin 
	 sum_1:=sum_1+b1[x];x:=x-(-x) and x;
 end;
end;
function sum_2(x:longint):int64;
begin
 sum_2:=0;
 while x>0 do begin 
	 sum_2:=sum_2+b2[x];x:=x-(-x) and x;
 end;
end;
begin 
 readln(n,m);
 for i:=1 to n do read(a[i]);readln;
 fillchar(b1,sizeof(b1),0);fillchar(b2,sizeof(b2),0);
 for i:=1 to n do add_1(i,int64(a[i]));
 for i:=1 to n do add_2(i,int64(a[i])*int64(n-i+1));
 for i:=1 to m do begin 
	 read(k);
     if k='Q' then begin 
		for j:=1 to 5 do read(k);read(d);readln;
		 writeln(sum_2(d)-sum_1(d)*int64(n-d));
    end else begin 
		 for j:=1 to 6 do read(k);read(x,d);readln;
		 add_1(x,int64(d-a[x]));add_2(x,int64(d-a[x])*int64(n-x+1));a[x]:=d;
    end;
 end;
end.
Problem3155

type
  bit=array[1..100000]of int64;
var
 i,d,x,n,m,j:longint;
 k:char;
 b1,b2:bit;
 a:array[1..100000]of int64;
procedure add(var b:bit;x:longint;d:int64);
begin
 while x<=n do begin
     b[x]:=b[x]+d;x:=x+(-x) and x;
 end;
end;
function sum(var b:bit;x:longint):int64;
begin
 sum:=0;
 while x>0 do begin
     sum:=sum+b[x];x:=x-(-x) and x;
 end;
end;
begin
 readln(n,m);
 for i:=1 to n do read(a[i]);readln;
 fillchar(b1,sizeof(b1),0);fillchar(b2,sizeof(b2),0);
 for i:=1 to n do add(b1,i,int64(a[i]));
 for i:=1 to n do add(b2,i,int64(a[i])*int64(n-i+1));
 for i:=1 to m do begin
     read(k);
     if k='Q' then begin
        for j:=1 to 5 do read(k);read(d);readln;
         writeln(sum(b2,d)-sum(b1,d)*int64((n-d)));
    end else begin
         for j:=1 to 6 do read(k);read(x,d);readln;
         add(b1,x,int64(d-a[x]));add(b2,x,int64(d-a[x])*int64(n-x+1));a[x]:=d;
    end;
 end;
end.
		 
Problem3155

type
  bit=array[1..100000]of int64;
var
 i,d,x,n,m,j:longint;
 k:char;
 b1,b2:bit;
 a:array[1..100000]of int64;
procedure add(var b:bit;x:longint;d:int64);
begin
 while x<=n do begin
     b[x]:=b[x]+d;x:=x+(-x) and x;
 end;
end;
function sum(var b:bit;x:longint):int64;
begin
 sum:=0;
 while x>0 do begin
     sum:=sum+b[x];x:=x-(-x) and x;
 end;
end;
begin
 readln(n,m);
 for i:=1 to n do read(a[i]);readln;
 fillchar(b1,sizeof(b1),0);fillchar(b2,sizeof(b2),0);
 for i:=1 to n do add(b1,i,int64(a[i]));
 for i:=1 to n do add(b2,i,int64(a[i])*int64(i));
 for i:=1 to m do begin
     read(k);
     if k='Q' then begin
        for j:=1 to 5 do read(k);read(d);readln;
         writeln(-sum(b2,d)+sum(b1,d)*int64((d+1)));
    end else begin
         for j:=1 to 6 do read(k);read(x,d);readln;
         add(b1,x,int64(d-a[x]));add(b2,x,int64(d-a[x])*int64(x));a[x]:=d;
    end;
 end;
end.
Problem3172

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=2000000,size=26;
struct node{
	node *ch[size],*f,*l;
	int v,cnt;
}T[N],*root=&T[0],*pos[N];
int l=0;
node *nn(){return &T[++l];}
#define oc o->ch[c[i]-'a']
void ins(char *c,int v){
	node *o=root;int n=strlen(c);
	rep(i,0,n-1) {if (!oc) oc=nn();o=oc;o->cnt++;}
	o->v=v;pos[v]=o;
}
node *q[N];
#define xc x->ch[i]
#define xf x->f
#define xcf xc->f
void calc(){
	int l=0,r=0;node *x=root;
	rep(i,0,size-1) if (!xc) xc=root; else q[r++]=xc,xcf=root;
	while (l<r){
		x=q[l++];
		rep(i,0,size-1) if (!xc) xc=xf->ch[i];else
			q[r++]=xc, xcf=xf->ch[i], xc->l=xcf->v?xcf:xcf->l;
	} 
	dep(i,r-1,0) 
		q[i]->f->cnt+=q[i]->cnt;
}
char c[210];
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n){
		scanf("%s",c);
		ins(c,i);
	}
	calc();
	rep(i,1,n) printf("%d\n",pos[i]->cnt);
}
Problem3205

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int N = 502;
int k, n, m, a[N][N], dx[4], dy[4];

typedef pair<int, int> node;
#define mp(a,b) make_pair(a,b)

node rbt[10];

void init(){	
	dx[0] = 0, dy[0] = -1;
	dx[1] = 1, dy[1] = 0;
	dx[2] = 0, dy[2] = 1;
	dx[3] = -1,dy[3] = 0;
	scanf("%d%d%d",&k,&m,&n);
	rep(i,1,n)
		rep(j,1,m){
			char c = getchar();
			while (c != 'x' && c != 'A' && c != '.' && c != 'C' && (c <= '0' || c > '9')) c = getchar();
			if (c == 'x')
				a[i][j] = 2;
			else if (c == 'A')
				a[i][j] = -1;
			else if (c == 'C')
				a[i][j] = 1;
			else
				a[i][j] = 0;
			if (c > '0' && c <= '9') rbt[c - '0'] = mp(i,j);
		}
	a[0][0] = a[0][m + 1] = a[n + 1][0] = a[n + 1][m + 1] = 2;
	rep(i,1,n) a[i][0] = a[i][m + 1] = 2;
	rep(i,1,m) a[0][i] = a[n + 1][i] = 2;
}


node f[N][N][4];
bool inst[N][N][4];

node dfs(int i, int j, int k){
	if (a[i][j] == 2) return mp(-1, -1);
	if (f[i][j][k] != mp(0, 0)) return f[i][j][k];
	if (inst[i][j][k]) return f[i][j][k] = mp(-1, -1);
	inst[i][j][k] = 1;
	int K = (k + a[i][j] + 4) % 4;
	int I = i + dy[K], J = j + dx[K];
	if (a[I][J] == 2) f[i][j][k] = mp(i, j);
	else f[i][j][k] = dfs(I, J, K);
	inst[i][j][k] = 0;
	return f[i][j][k];
}

struct pos{
	int l, r, i, j;
}q1[N * N], q2[N * N];
int F[10][10][N][N], l1, r1, l2, r2;

bool cmp(const pos &a, const pos &b){
	return F[a.l][a.r][a.i][a.j] < F[b.l][b.r][b.i][b.j];
}

int main(){
	init();
	rep(i,1,n) rep(j,1,m) rep(k,0,3) f[i][j][k] = mp(0, 0);
	rep(i,1,n) rep(j,1,m) rep(k,0,3) inst[i][j][k] = 0;
	rep(i,1,n) rep(j,1,m) rep(k,0,3) f[i][j][k] = dfs(i,j,k);//, cout <<i<<' '<<j<<' '<<k<<' '<<f[i][j][k].first<<' '<<f[i][j][k].second<<endl;

	rep(i,1,n) rep(j,1,m) rep(k1,1,k) rep(k2,k1,k) F[k1][k2][i][j] = -1;
	
	rep(i,1,k) 
		F[i][i][rbt[i].first][rbt[i].second] = 0;

	rep(len,0,k - 1){
		rep(l,1,k - len){
			int r = l + len;			
			rep(t, l, r - 1){
				rep(i,1,n)
					rep(j,1,m) if (F[l][t][i][j] != -1 && F[t + 1][r][i][j] != -1){
						if (F[l][r][i][j] == -1) F[l][r][i][j] = F[l][t][i][j] + F[t + 1][r][i][j];
					 	else F[l][r][i][j] = min(F[l][r][i][j], F[l][t][i][j] + F[t + 1][r][i][j]);
					}
			}

			l1 = r1 = 0;
			rep(i,1,n) rep(j,1,m) if (F[l][r][i][j] != -1) q1[r1++] = (pos){l, r, i, j};
			sort(q1, q1 + r1, cmp);

			l2 = r2 = 0;
			while (l2 != r2 || l1 != r1){
				pos x;
				if (l2 == r2) x = q1[l1++];
				else if (l1 == r1) x = q2[l2++];
				else if (cmp(q1[l1], q2[l2])) x = q1[l1++]; else x = q2[l2++];
				rep(t, 0, 3) if (f[x.i][x.j][t] != mp(-1, -1) && f[x.i][x.j][t] != mp(x.i, x.j) && f[x.i][x.j][t] != mp(0,0)){
					node T = f[x.i][x.j][t];
					if (F[l][r][T.first][T.second] == -1 || F[l][r][x.i][x.j] + 1 < F[l][r][T.first][T.second]){
						F[l][r][T.first][T.second] = F[l][r][x.i][x.j] + 1;
						q2[r2++] = (pos){l, r, T.first, T.second};
					}
				}
			}
		}
	}

	int ans = 0x7fffffff;
	rep(i,1,n)
		rep(j,1,m)
			if (F[1][k][i][j] != -1) ans = min(ans, F[1][k][i][j]);	
	if (ans == 0x7fffffff) printf("-1\n"); else printf("%d\n",ans);
}
Problem3205

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int N = 502;
int k, n, m, a[N][N], dx[4], dy[4];

typedef pair<int, int> node;
#define mp(a,b) make_pair(a,b)

node rbt[10];

inline void init(){	
	dx[0] = 0, dy[0] = -1;
	dx[1] = 1, dy[1] = 0;
	dx[2] = 0, dy[2] = 1;
	dx[3] = -1,dy[3] = 0;
	scanf("%d%d%d",&k,&m,&n);
	rep(i,1,n)
		rep(j,1,m){
			char c = getchar();
			while (c != 'x' && c != 'A' && c != '.' && c != 'C' && (c <= '0' || c > '9')) c = getchar();
			if (c == 'x')
				a[i][j] = 2;
			else if (c == 'A')
				a[i][j] = -1;
			else if (c == 'C')
				a[i][j] = 1;
			else
				a[i][j] = 0;
			if (c > '0' && c <= '9') rbt[c - '0'] = mp(i,j);
		}
	a[0][0] = a[0][m + 1] = a[n + 1][0] = a[n + 1][m + 1] = 2;
	rep(i,1,n) a[i][0] = a[i][m + 1] = 2;
	rep(i,1,m) a[0][i] = a[n + 1][i] = 2;
}


node f[N][N][4];
bool inst[N][N][4];

inline node dfs(int i, int j, int k){
	if (a[i][j] == 2) return mp(-1, -1);
	if (f[i][j][k] != mp(0, 0)) return f[i][j][k];
	if (inst[i][j][k]) return f[i][j][k] = mp(-1, -1);
	inst[i][j][k] = 1;
	int K = (k + a[i][j] + 4) % 4;
	int I = i + dy[K], J = j + dx[K];
	if (a[I][J] == 2) f[i][j][k] = mp(i, j);
	else f[i][j][k] = dfs(I, J, K);
	inst[i][j][k] = 0;
	return f[i][j][k];
}

struct pos{
	int l, r, i, j;
}q1[N * N], q2[N * N];
int F[10][10][N][N], l1, r1, l2, r2;

bool cmp(const pos &a, const pos &b){
	return F[a.l][a.r][a.i][a.j] < F[b.l][b.r][b.i][b.j];
}

int main(){
	init();
	rep(i,1,n) rep(j,1,m) rep(k,0,3) f[i][j][k] = mp(0, 0);
	rep(i,1,n) rep(j,1,m) rep(k,0,3) inst[i][j][k] = 0;
	rep(i,1,n) rep(j,1,m) rep(k,0,3) f[i][j][k] = dfs(i,j,k);//, cout <<i<<' '<<j<<' '<<k<<' '<<f[i][j][k].first<<' '<<f[i][j][k].second<<endl;

	rep(i,1,n) rep(j,1,m) rep(k1,1,k) rep(k2,k1,k) F[k1][k2][i][j] = -1;
	
	rep(i,1,k) 
		F[i][i][rbt[i].first][rbt[i].second] = 0;

	rep(len,0,k - 1){
		rep(l,1,k - len){
			int r = l + len;			
			rep(t, l, r - 1){
				rep(i,1,n)
					rep(j,1,m) if (F[l][t][i][j] != -1 && F[t + 1][r][i][j] != -1){
						if (F[l][r][i][j] == -1) F[l][r][i][j] = F[l][t][i][j] + F[t + 1][r][i][j];
					 	else F[l][r][i][j] = min(F[l][r][i][j], F[l][t][i][j] + F[t + 1][r][i][j]);
					}
			}

			l1 = r1 = 0;
			rep(i,1,n) rep(j,1,m) if (F[l][r][i][j] != -1) q1[r1++] = (pos){l, r, i, j};
			sort(q1, q1 + r1, cmp);

			l2 = r2 = 0;
			while (l2 != r2 || l1 != r1){
				pos x;
				if (l2 == r2) x = q1[l1++];
				else if (l1 == r1) x = q2[l2++];
				else if (cmp(q1[l1], q2[l2])) x = q1[l1++]; else x = q2[l2++];
				rep(t, 0, 3) if (f[x.i][x.j][t] != mp(-1, -1) && f[x.i][x.j][t] != mp(x.i, x.j) && f[x.i][x.j][t] != mp(0,0)){
					node T = f[x.i][x.j][t];
					if (F[l][r][T.first][T.second] == -1 || F[l][r][x.i][x.j] + 1 < F[l][r][T.first][T.second]){
						F[l][r][T.first][T.second] = F[l][r][x.i][x.j] + 1;
						q2[r2++] = (pos){l, r, T.first, T.second};
					}
				}
			}
		}
	}

	int ans = 0x7fffffff;
	rep(i,1,n)
		rep(j,1,m)
			if (F[1][k][i][j] != -1) ans = min(ans, F[1][k][i][j]);	
	if (ans == 0x7fffffff) printf("-1\n"); else printf("%d\n",ans);
}
Problem3209

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int M=10000007;
typedef long long LL;
LL ans=1;
LL f[55][55];
void init(){
	f[0][0]=1;
	rep(i,1,50){
		f[i][0]=1;
		rep(j,1,50) f[i][j]=f[i-1][j]+f[i-1][j-1];
	}
}
int pow(int a,LL b)//a^b
{
	if (b==0) return 1;
	if (b==1) return a;
	LL t=pow(a,b >> 1);
	if (b%2) return t*t*a%M; else return t*t % M;
}
int a[55],l=0;
int cmp(LL x){
	int cnt;
	for(cnt=0;x;cnt+=x&1,x>>=1);
	return cnt;
}
LL solve(LL n,int b){
	LL ans= ( cmp(n)==b );
	l=0;
	while (n) a[++l]=n&1,n>>=1;
	int tmp=0;
	dep(i,l,1){
		if (tmp>b) break;
		int t=a[i];
		if (t!=0){
			ans+=f[i-1][b-tmp];
			tmp++;
		}
	}
	return ans;
}
int main(){
	LL n;cin >>n;
	init();
	rep(i,1,50){
		if (((LL)1 << i)-1 > n) break;
		ans=ans*pow(i,solve(n,i))%M;
	}
	cout <<ans<<endl;
	return 0;
}
Problem3211

type
	ll=int64;
	bit=array[1..1000000]of ll;
var
 b:bit;
 n,m,i,x,l,r,j,t:longint;
 f:array[1..1000000]of longint;
 d:array[1..1000000]of ll;
function sum(x:longint):ll;
begin 
 sum:=0;
 while x>0 do begin 
	 sum:=sum+b[x];x:=x-(-x) and x;
 end;
end;
procedure add(x:longint;d:ll);
begin 
  while x<=n do begin 
	   b[x]:=b[x]+d;x:=x+(-x) and x;
 end;
end;
function find(x:longint):longint;
begin
  if f[x]=x then exit(x);
  find:=find(f[x]);f[x]:=find;
end;
begin 
 readln(n);
 for i:=1 to n do begin 
	 read(d[i]);add(i,d[i]);
	 if d[i]<=1  then f[i]:=i+1 else f[i]:=i;
 end;
 f[n+1]:=n+1;
 readln;readln(m);
 for i:=1 to m do begin
	 readln(x,l,r);if r<l then begin t:=r;r:=l;l:=t;end;
     if x=1 then writeln(sum(r)-sum(l-1))
	else begin 
		 j:=find(l);
	     while j<=r do begin 
			  add(j,trunc(sqrt(d[j]))-d[j]);d[j]:=trunc(sqrt(d[j]));
		      if (d[j]=1) then f[j]:=j+1;
			  j:=find(j+1);
		 end;
	 end;
 end;
end. 
Problem3211

{$A+,B-,D-,E-,F-,G+,I-,L-,N+,O-,P+,Q-,R-,S-,T-,V-,X+,Y-}
{$M 65520,0,655360}
{$inline on}
type
	ll=int64;
	bit=array[1..1000000]of ll;
var
 b:bit;
 n,m,i,x,l,r,j,t:longint;
 f:array[1..1000000]of longint;
 d:array[1..1000000]of ll;
function sum(x:longint):ll;
begin 
 sum:=0;
 while x>0 do begin 
	 sum:=sum+b[x];x:=x-(-x) and x;
 end;
end;
procedure add(x:longint;d:ll);
begin 
  while x<=n do begin 
	   b[x]:=b[x]+d;x:=x+(-x) and x;
 end;
end;
function find(x:longint):longint;
begin
  if f[x]=x then exit(x);
  find:=find(f[x]);f[x]:=find;
end;
begin 
 readln(n);
 for i:=1 to n do begin 
	 read(d[i]);add(i,d[i]);
	 if d[i]<=1  then f[i]:=i+1 else f[i]:=i;
 end;
 f[n+1]:=n+1;
 readln;readln(m);
 for i:=1 to m do begin
	 readln(x,l,r);if r<l then begin t:=r;r:=l;l:=t;end;
     if x=1 then writeln(sum(r)-sum(l-1))
	else begin 
		 j:=find(l);
	     while j<=r do begin 
			  add(j,trunc(sqrt(d[j]))-d[j]);d[j]:=trunc(sqrt(d[j]));
		      if (d[j]=1) then f[j]:=j+1;
			  j:=find(j+1);
		 end;
	 end;
 end;
end. 
Problem3211

{$A+,B-,D-,E-,F-,G+,I-,L-,N+,O-,P+,Q-,R-,S-,T-,V-,X+,Y-}
{$M 65520,0,655360}
{$inline on}
type
	ll=int64;
	bit=array[1..1000000]of ll;
var
 b:bit;
 n,m,i,x,l,r,j,t:longint;
 f:array[1..1000000]of longint;
 d:array[1..1000000]of ll;
function sum(x:longint):ll;inline;
begin 
 sum:=0;
 while x>0 do begin 
	 sum:=sum+b[x];x:=x-(-x) and x;
 end;
end;
procedure add(x:longint;d:ll);inline;
begin 
  while x<=n do begin 
	   b[x]:=b[x]+d;x:=x+(-x) and x;
 end;
end;
function find(x:longint):longint;
begin
  if f[x]=x then exit(x);
  find:=find(f[x]);f[x]:=find;
end;
begin 
 readln(n);
 for i:=1 to n do begin 
	 read(d[i]);add(i,d[i]);
	 if d[i]<=1  then f[i]:=i+1 else f[i]:=i;
 end;
 f[n+1]:=n+1;
 readln;readln(m);
 for i:=1 to m do begin
	 readln(x,l,r);if r<l then begin t:=r;r:=l;l:=t;end;
     if x=1 then writeln(sum(r)-sum(l-1))
	else begin 
		 j:=find(l);
	     while j<=r do begin 
			  add(j,trunc(sqrt(d[j]))-d[j]);d[j]:=trunc(sqrt(d[j]));
		      if (d[j]=1) then f[j]:=j+1;
			  j:=find(j+1);
		 end;
	 end;
 end;
end. 
Problem3223

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
struct node *null;
struct node{
	node *f,*ch[2];
	int s,k,fl;
	int d(){return f->ch[1]==this;}
	void st(node *c,int d){ch[d]=c,c->f=this;}
	void upd(){s=1+ch[0]->s+ch[1]->s;}
	void push(){
		if (this==null) return;
		if (fl==1){
			fl=0;
			ch[0]->fl^=1;
			ch[1]->fl^=1;
			swap(ch[0],ch[1]);
		}
	}
}T[500000];
node *root;
void rot(node *x){
	node *f=x->f;int d=x->d();
	if(f->f!=null) f->f->st(x,f->d()); else x->f=f->f;
	f->st(x->ch[!d],d), x->st(f,!d);
	f->upd();
	if (f==root) root=x;
}
void fix(node *x){
	if (x->f!=null) fix(x->f);
	x->push();
}
void splay(node *x,node *f){
	fix(x);
	while (x->f!=f){
		if (x->f->f==f) rot(x);
		else (x->d()==x->f->d()) ? (rot(x->f),rot(x)):(rot(x),rot(x));
	}
	x->upd();
}
node *find(node *o,int k){
	o->push();
	int s=o->ch[0]->s+1;
	if (s==k) return o;
	if (k < s) return find(o->ch[0],k); else return find(o->ch[1],k-s);
}
int l=0;
node *newnode(int k){
	node *x=&T[l++];
	x->s=1,x->k=k,x->f=x->ch[0]=x->ch[1]=null;
	x->fl=0;
	return x;
}
void init(){
	null=&T[l++];
	null->s=0,null->f=null->ch[0]=null->ch[1]=null;
	root=newnode(0);
	node *x=newnode(0);
	root->st(x,1);
}
void get(int l,int r){
	splay(find(root,l),null);splay(find(root,r+2),root);
}
void ins(int t,int a){
	node *x=newnode(a);
	get(t,t-1);
	root->ch[1]->st(x,0);
	root->ch[1]->upd();
	root->upd();
}
void p(node *x){
	if (x==null) return;
	x->push();
	p(x->ch[0]);
	printf("%d ",x->k);
	p(x->ch[1]);
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	init();
	rep(i,1,n) ins(i,i);
	rep(j,1,m){
		int l,r;scanf("%d%d",&l,&r);
		get(l,r);
		root->ch[1]->ch[0]->fl^=1;
	}
	get(1,n);
	p(root->ch[1]->ch[0]);
}
Problem3223

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
struct node *null;
struct node{
	node *ch[2],*f;
	int k,s,fl;
	void st(node *c,int d){ch[d]=c;c->f=this;}
	void upd(){s=ch[0]->s+ch[1]->s+1;}
	int d(){return f->ch[1]==this;}
	void push(){
		if (fl){
			fl=0;
			ch[0]->fl^=1;ch[1]->fl^=1;
			swap(ch[0],ch[1]);
		}
	}
}T[1000000];
node *root;
int l=0;
node* newnode(int a){
	node *o=&T[l++];
	o->s=1;o->f=o->ch[0]=o->ch[1]=null;
	o->k=a;o->fl=0;
	return o;
}
void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->f!=null) f->f->st(o,f->d()); else o->f=f->f;
	f->st(o->ch[d^1],d);o->st(f,d^1);
	f->upd();
	if (f==root) root=o;
}
void fix(node *o){
	if (o->f!=null) fix(o->f);
	o->push();
}
void splay(node *o,node *f=null){
	fix(o);
	while (o->f!=f){
		if (o->f->f==f) rot(o);else (o->f->d()==o->d())?(rot(o->f),rot(o)):(rot(o),rot(o));
	}
	o->upd();
}
node *find(node *o,int k){
	o->push();
	int s=o->ch[0]->s+1;
	if (s==k) return o;
	if (k < s) return find(o->ch[0],k); else return find(o->ch[1],k-s);
}
void get(int l,int r){
	splay(find(root,l)), splay(find(root,r+2),root);
}
void ins(int x,int a){
	node *o=newnode(a);
	get(x,x-1);
	root->ch[1]->st(o,0);
	root->ch[1]->upd();
	root->upd();
}
void init(){
	null=&T[l++];
	null->s=0;null->f=null->ch[0]=null->ch[1]=null;
	root=newnode(0);
	root->st(newnode(0),1);
}
void p(node *o){
	if (o==null) return;
	o->push();
	p(o->ch[0]);
	printf("%d ",o->k);
	p(o->ch[1]);
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	init();
	rep(i,1,n) ins(i,i);
	rep(j,1,m){
		int l,r;scanf("%d%d",&l,&r);
		get(l,r);
		root->ch[1]->ch[0]->fl^=1;
	}
	get(1,n);
	p(root->ch[1]->ch[0]);
	return 0;
}
Problem3233

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int inf = 5000000;
int a[51], g[100010], f[100010];
int main(){
	int n; scanf("%d",&n);
	int t = 0;
	rep(i,1,n) scanf("%d",&a[i]), t = max(t, a[i]);
	rep(i,1,t) rep(j,1,n) g[i] += a[j] / i;
	rep(i,1,t) f[i] = inf;
	f[1] = g[1];
	rep(i,1,t)
		rep(j,2,t / i)
			f[i * j] = min(f[i * j], f[i] - g[i * j] * (j - 1));
	int ans = inf;
	rep(i,1,t) ans = min(ans, f[i]);
	printf("%d\n",ans);
}
Problem3237

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n, m;
const int N = 200000 + 10;

int c[N], q[N][6], cnt = 0;
bool vis[N];

struct edge{int a, b;}e[N];
int f[N], h[N];
int tl = 0;
int find(int x){return f[x] == x ? x : find(f[x]);}
struct node{
	int fa, fb, ha;
}st[20 * N];
void ins(int a, int b){
	int fa = find(a), fb = find(b);
	if (fa != fb){
		if (h[fa] < h[fb]) swap(fa, fb);
		st[++tl] = (node){fa, fb, h[fa]};
		f[fb] = fa; if (h[fa] == h[fb]) h[fa] = h[fb] + 1;
		cnt--;
	}
}
void resume(){
	node x = st[tl--];
	f[x.fb] = x.fb;
	h[x.fa] = x.ha;
	cnt++;
}
void cdq(int l, int r){
	if (!cnt){
		rep(i,l,r) printf("Connected\n");
		return;
	}
	if (l == r) {if (!cnt) printf("Connected\n"); else printf("Disconnected\n");return;}
	
	int mid = (l + r) >> 1;

	int cur = tl + 1;
	rep(i,l,r) rep(j,1,c[i]) vis[q[i][j]] = 0;
	rep(i,l,mid) rep(j,1,c[i]) vis[q[i][j]] = 1;
	rep(i,mid + 1, r) rep(j,1,c[i]) if (!vis[q[i][j]]) ins(e[q[i][j]].a, e[q[i][j]].b), vis[q[i][j]] = 1;
	
	cdq(l, mid);
	int tmp = tl;//resume will modify tl!
	rep(i,cur,tmp) resume();


	cur = tl + 1; 
	rep(i,l,r) rep(j,1,c[i]) vis[q[i][j]] = 0;
	rep(i,mid + 1, r) rep(j,1,c[i]) vis[q[i][j]] = 1;
	rep(i,l,mid) rep(j,1,c[i]) if (!vis[q[i][j]]) ins(e[q[i][j]].a, e[q[i][j]].b), vis[q[i][j]] = 1;
	
	cdq(mid + 1, r);
	tmp = tl;//resume will modify tl!
	rep(i,cur,tmp) resume();
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d", &e[i].a, &e[i].b);
	int Q; scanf("%d",&Q);
	rep(i,1,Q) {
		scanf("%d", &c[i]);
		rep(j,1,c[i]) scanf("%d",&q[i][j]), vis[q[i][j]] = 1;
	}
	rep(i,1,n) f[i] = i, h[i] = 1;
	cnt = n - 1;
	rep(i,1,m) if (!vis[i]) ins(e[i].a, e[i].b); else vis[i] = 0;
	cdq(1,Q);
	return 0;
}

//教训：小心for循环rep(I,A,B)的时候 循环内的语句会不会更改a和b的值
Problem3240

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
const int M=1000000007;
struct mat{
    LL a[2];
};
mat c,d;
mat operator *(const mat &a,const mat &b){
    c.a[0] = a.a[0] * b.a[0] % M, c.a[1] = (a.a[0] * b.a[1] % M+ a.a[1]) % M;
    return c;
}
void prt(mat &a){
        rep(j,0,1) printf("%lld ",a.a[j]);
        printf("\n");
    printf("\n");
}
mat z[10],y,ty,tyy;
 
mat fast_pow(mat a,int* b){
    d.a[0] = 1, d.a[1] = 0;
    z[0] = d;
    rep(i,1,9) z[i] = z[i-1] * a;
    dep(i, b[0], 1){
            y = d * d;
            ty = y * y;
            tyy = ty * ty;
            d = tyy * y;
            d = d * z[b[i]];
    }
    return d;
}
mat a1,a2,a3,a4,a5;
int n[2000000],m[2000000];
void gethint(int *h){//h > 0
    char c=getchar();
    while (c < '0' || c > '9') c=getchar();
    h[0]=0;
    while (c >= '0' && c <= '9') h[++h[0]] = c-'0', c=getchar();
    rep(i,1,h[0]>>1) swap(h[i],h[h[0]-i+1]);
}
void dec(int *h){
    h[1]--;
    for(int i=1;h[i] < 0;i++) h[i] += 10, h[i+1]--;
    if (h[h[0]]==0) h[0]--;
}
int main(){
    int a,b,c,d;
    gethint(n), gethint(m), dec(n), dec(m);
    scanf("%d%d%d%d",&a,&b,&c,&d);
    a1.a[0]=a, a1.a[1]=b;
    a2.a[0]=c, a2.a[1]=d;
    a5 = fast_pow(a1,m);
    a3 = a2 * a5;
    a4 = a5 * fast_pow(a3,n);
    printf("%lld\n",(1LL * a4.a[0] + a4.a[1]) % M);
    return 0;
}
Problem3243

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N2 = 20000 + 10, D2 = 100 + 10, N3 = 100000 + 10, D3 = 100 + 10;
int n, d, k;
int a2[N2][D2], a3[N3][D3], T[N3], C[D2 * D2], AC[N3], FT[N3];
#define A2(i,j) a2[i][j]//n*d
#define B2(i,j) a2[j][i]//d*n
#define A3(i,j) a3[i][j]//n*d
#define B3(i,j) a3[j][i]//d*n
void findans2(int i){
	rep(j,1,n) if (j != i){
		int sum = 0;
		rep(k,1,d) sum ^= A2(i,k) & B2(k,j);
		if (sum == 0){
			if (i > j) swap(i,j);
			printf("%d %d\n",i, j);
			return;
		}
	}
}
void findans3(int i){
	rep(j,1,n) if (i != j){
		int sum = 0;
		rep(k,1,d) sum += A3(i,k) * B3(k,j);
		sum %= 3;
		if (sum == 0){
			if (i > j) swap(i,j);
			printf("%d %d\n",i,j);
			return;
		}
	}
}
int id[D3][D3];
typedef pair<int, int> node;
node pos[D3 * D3];
#define mp(a,b) make_pair(a,b)
#define x first
#define y second 
#define A(i,j) (A3(i, pos[j].x) * A3(i, pos[j].y)) 
#define B(i,j) (B3(pos[i].x, j) * B3(pos[i].y, j))

bool check2(){
	rep(i,1,n) T[i] = rand() & 1;//n*1
	//calc B * T = C //d*1
	rep(i,1,d){
		C[i] = 0;
		rep(j,1,n) C[i] ^= B2(i,j) & T[j];
	}
	//calc A * C = AC //n*1
	rep(i,1,n){
		AC[i] = 0;
		rep(j,1,d) AC[i] ^= A2(i,j) & C[j];
	}
	//calc F * T = FT //n*1
	int sum = 0;
	rep(i,1,n) sum ^= T[i];
	rep(i,1,n){
		int ag = 0;
		rep(j,1,d) ag ^= A2(i,j) & B2(j,i);
		FT[i] = (sum + (2 - T[i]) + ag * T[i]) & 1;
	}
	//cmp
	rep(i,1,n)
		if (FT[i] != AC[i]) {
			findans2(i);return true;
		}
	return false;
}
bool check3(){
	rep(i,1,n) T[i] = rand() % 3;
	//calc AC  //in fact (AB_{i}{j} ^ 2) * T
	rep(i,1,d * d){
		C[i] = 0;
		rep(j,1,n)
			C[i] += B(i,j) * T[j];
		C[i] %= 3;
	}
	rep(i,1,n){
		AC[i] = 0;
		rep(j,1,d * d)
			AC[i] += A(i,j) * C[j];
		AC[i] %= 3;
	}
	//calc FT
	int sum = 0;
	rep(i,1,n) sum += T[i];
	sum %= 3;
	rep(i,1,n){
		int ag = 0;
		rep(j,1,d) ag += A3(i,j) * B3(j,i);
		ag %= 3;
		ag = ag * ag % 3;
		FT[i] = (sum + (3 - T[i]) + ag * T[i]) % 3;
	}
	//cmp
	rep(i,1,n) 
		if (FT[i] != AC[i]){
			findans3(i); return true;
		}
	return false;
}
void work2(){
	rep(i,1,n) rep(j,1,d) {
		int t;
		scanf("%d",&t), a2[i][j] = t & 1;
	}
	int t = 30000000 / n / d;
	rep(i,1,t) if (check2()) return;
	printf("-1 -1\n");
}

void init(){
	int l = 0;
	rep(i,1,d) rep(j,1,d) id[i][j] = ++l, pos[l] = mp(i,j);
}
void work3(){
	rep(i,1,n) rep(j,1,d) {
		int t;
		scanf("%d",&t), a3[i][j] = t % 3;
	}
	init();
	int t = 30000000 / n / d;
	rep(i,1,t) if (check3()) return;
	printf("-1 -1\n");
}
int main(){
	srand(9914);
	scanf("%d%d%d",&n,&d,&k);
	if (k == 2)  work2(); else work3();
}
Problem3261

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 710000, M = 25;
struct node{
	node *ch[2];
	int s;
}T[N*(M + 1)];
node *null = &T[0];
int l = 0;
node *nn(){
	l++;
	T[l].ch[0] = T[l].ch[1] = null;
	T[l].s = 0;
	return &T[l];
}
node* rt[N];
#define oc o->ch[d]
node* ins(node *o, int a, int cur){
		node *k = nn();*k = *o;
		(k->s)++;
		if (cur + 1) {
			int d = a >> cur & 1;
			k -> ch[d] = ins(oc, a, cur - 1);
		}
		return k;
} 
node *rtl,*rtr;
#define c0(o) o->ch[t]
#define c1(o) o->ch[t^1]
#define s(o) o->s
int qry(int x, int cur){
	if (cur + 1){
		int t = x >> cur & 1;
		if (s(c1(rtr)) - s(c1(rtl))) {
			rtl = c1(rtl), rtr = c1(rtr);
			return (1 << cur) + qry(x, cur - 1);
		}else{
			rtl = c0(rtl), rtr = c0(rtr);
			return qry(x, cur - 1);
		}
	}else return 0;
}
#undef s
int a[N];
int main(){
	null->s = 0, null->ch[0]=null->ch[1] = null;
	int n,m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]);
	a[0] = 0;
	rep(i,1,n) a[i]^=a[i-1];
	rt[0] = nn();
	rep(i,0,n) rt[i + 1] = ins(rt[i], a[i], M);
	rep(i,1,m){
		char c = getchar(); while (c!='A' && c!='Q') c = getchar();
		if (c == 'A'){
			int t; scanf("%d",&t);
			n++, a[n] = a[n - 1] ^ t;
			rt[n + 1] = ins(rt[n], a[n], M);
		}else{
			int l, r, x; scanf("%d%d%d",&l, &r, &x);
			x = x ^ a[n];
			rtr = rt[r], rtl = rt[l - 1];
			printf("%d\n",qry(x, M));
		}
	}
	return 0;
}
Problem3282

#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define read(a) a=getint()
#define print(a) printf("%d", a)
#define dbg(x) cout << (#x) << " = " << (x) << endl
#define printarr2(a, b, c) for1(_, 1, b) { for1(__, 1, c) cout << a[_][__]; cout << endl; }
#define printarr1(a, b) for1(_, 1, b) cout << a[_] << '\t'; cout << endl
inline const int getint() { int r=0, k=1; char c=getchar(); for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; return k*r; }
inline const int max(const int &a, const int &b) { return a>b?a:b; }
inline const int min(const int &a, const int &b) { return a<b?a:b; }
 
const int N=300005;
struct node *null;
struct node {
    int v, rev, w;
    node *ch[2], *fa;
    node(const int _v=0) : v(_v), rev(0), w(0) { ch[0]=ch[1]=fa=null; }
    bool d() { return fa->ch[1]==this; }
    bool check() { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void setc(node* c, int d) { ch[d]=c; c->fa=this; }
    void pushup() { w=ch[0]->w^ch[1]->w^v; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=1;
            ch[1]->rev^=1;
            swap(ch[0], ch[1]);
            rev=0;
        }
    }
}*t[N];
void rot(node* x) {
    node* fa=x->fa; bool d=x->d();
    if(!fa->check()) fa->fa->setc(x, fa->d());
    else x->fa=fa->fa;
    fa->setc(x->ch[!d], d);
    x->setc(fa, !d);
    fa->pushup();
}
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
void splay(node* x) {
    fix(x);
    while(!x->check())
        if(x->fa->check()) rot(x);
        else x->d()==x->fa->d()?(rot(x->fa), rot(x)):(rot(x), rot(x));
    x->pushup();
}
node* access(node* x) {
    node* y=null;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    return y;
}
void mkroot(node* x) { access(x)->rev^=1; splay(x); }
void link(node* x, node* y) { mkroot(x); x->fa=y; }
void cut(node* x, node* y) {
    mkroot(x); access(y); splay(y);
    y->ch[0]->fa=null; y->ch[0]=null;
}
node* findrt(node* x) {
    access(x); splay(x);
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
void init() { null=new node; null->ch[0]=null->ch[1]=null->fa=null; }
int n, m;
 
int main() {
    init();
    read(n); read(m);
    for1(i, 1, n) t[i]=new node(getint());
    rep(i, m) {
        int c=getint(), x=getint(), y=getint();
        if(c==0) { mkroot(t[x]); access(t[y]); splay(t[y]); printf("%d\n", t[y]->w); }
        else if(c==1) { if(findrt(t[x])!=findrt(t[y])) link(t[x], t[y]); }
        else if(c==2) { if(findrt(t[x])==findrt(t[y])) cut(t[x], t[y]); }
        else if(c==3) { mkroot(t[x]); t[x]->v=y; t[x]->pushup(); }
    }
    return 0;
}
Problem3282

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}

const int N=300000;
struct node{
	node *ch[2],*f;
	int fl,s,v;
	void upd(){s= (ch[0]->s) ^ (ch[1]->s) ^ v; }
	int d(){return f->ch[1]==this;}
	bool c(){return f->ch[0]==this || f->ch[1]==this;}
	void st(node *c,int d){ch[d]=c;c->f=this;}
	void push(){
		if (fl){
			ch[0]->fl^=1;ch[1]->fl^=1;
			swap(ch[0],ch[1]);
			fl=0;
		}
	}
}T[N],*null;
void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->c()) f->f->st(o,f->d()); else o->f=f->f;
	f->st(o->ch[d^1],d);o->st(f,d^1);
	f->upd();
}
void fix(node *o){
	if (o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (o->c())
		if (!o->f->c()) rot(o); else 
			(o->d()==o->f->d()) ? (rot(o->f),rot(o)) : (rot(o),rot(o));
	o->upd();
}
void access(node *o){
	node *c=null,*t=o;
	for(;o!=null;o=o->f){
		splay(o);
		o->ch[1]=c, o->upd();
		c=o;
	}
	splay(t);
}
node *findrt(node *o){
	access(o);
	while (o->ch[0]!=null) o=o->ch[0];
	return o;
}
void mroot(node *o){
	access(o);o->fl^=1;
}
void link(node *x,node *y){
	mroot(x);x->f=y;
}
void cut(node *x,node *y){
	mroot(x);access(y);
	if (y->ch[0]==x) x->f=y->ch[0]=null;
}
int main(){
	int n=read(),m=read();
	null=&T[0], null->s=null->fl=0, null->ch[0]=null->ch[1]=null->f=null;
	rep(i,1,n) T[i].ch[0]=T[i].ch[1]=T[i].f=null, T[i].fl=0, T[i].s=T[i].v=read();
	rep(i,1,m){
		int tp=read(),x1=read(),y1=read();
		node *x=&T[x1],*y=tp==3 ? null :&T[y1];
		if (tp==0) mroot(x),access(y),printf("%d\n",y->s);
		else if (tp==1) { if (findrt(x)!=findrt(y)) link(x,y); }
		else if (tp==2) { if (findrt(x)==findrt(y)) cut(x,y); }
		else if (tp==3){
			mroot(x);x->v=y1;x->upd();
		}
	}
}
Problem3282

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
 
const int N=300000;
struct node{
    node *ch[2],*f;
    int fl,s,v;
    void upd(){s= (ch[0]->s) ^ (ch[1]->s) ^ v; }
    int d(){return f->ch[1]==this;}
    bool c(){return f->ch[0]==this || f->ch[1]==this;}
    void st(node *c,int d){ch[d]=c;c->f=this;}
    void push(){
        if (fl){
            ch[0]->fl^=1;ch[1]->fl^=1;
            swap(ch[0],ch[1]);
            fl=0;
        }
    }
}T[N],*null;
void rot(node *o){
    node *f=o->f;int d=o->d();
    if (f->c()) f->f->st(o,f->d()); else o->f=f->f;
    f->st(o->ch[d^1],d);o->st(f,d^1);
    f->upd();
}
void fix(node *o){
    if (o->c()) fix(o->f);
    o->push();
}
void splay(node *o){
    fix(o);
    while (o->c())
        if (!o->f->c()) rot(o); else
            (o->d()==o->f->d()) ? (rot(o->f),rot(o)) : (rot(o),rot(o));
    o->upd();
}
void access(node *o){
    node *c=null,*t=o;
    for(;o!=null;o=o->f){
        splay(o);
        o->ch[1]=c, o->upd();
        c=o;
    }
    splay(t);
}
node *findrt(node *o){
    access(o);
    while (o->ch[0]!=null) o=o->ch[0];
    return o;
}
void mroot(node *o){
    access(o);o->fl^=1;
}
void link(node *x,node *y){
    mroot(x);x->f=y;
}
void cut(node *x,node *y){
    mroot(x);access(y);
    if (y->ch[0]==x) x->f=y->ch[0]=null;
}
int main(){
    int n=read(),m=read();
    null=&T[0], null->s=null->fl=0, null->ch[0]=null->ch[1]=null->f=null;
    rep(i,1,n) T[i].ch[0]=T[i].ch[1]=T[i].f=null, T[i].fl=0, T[i].s=T[i].v=read();
    rep(i,1,m){
        int tp=read(),x1=read(),y1=read();
        node *x=&T[x1],*y=tp==3 ? null :&T[y1];
        if (tp==0) mroot(x),access(y),printf("%d\n",y->s);
        else if (tp==1) {
            mroot(x);if (findrt(y)!=x) x->f=y;
        }else if (tp==2) { if (findrt(x)==findrt(y)) cut(x,y); }
        else if (tp==3){
            mroot(x);x->v=y1;x->upd();
        }
    }
}
Problem3282

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
 
const int N=300000;
struct node{
    node *ch[2],*f;
    int fl,s,v;
    void upd(){s= (ch[0]->s) ^ (ch[1]->s) ^ v; }
    int d(){return f->ch[1]==this;}
    bool c(){return f->ch[0]==this || f->ch[1]==this;}
    void st(node *c,int d){ch[d]=c;c->f=this;}
    void push(){
        if (fl){
            ch[0]->fl^=1;ch[1]->fl^=1;
            swap(ch[0],ch[1]);
            fl=0;
        }
    }
}T[N],*null;
void rot(node *o){
    node *f=o->f;int d=o->d();
    if (f->c()) f->f->st(o,f->d()); else o->f=f->f;
    f->st(o->ch[d^1],d);o->st(f,d^1);
    f->upd();
}
void fix(node *o){
    if (o->c()) fix(o->f);
    o->push();
}
void splay(node *o){
    fix(o);
    while (o->c())
        if (!o->f->c()) rot(o); else
            (o->d()==o->f->d()) ? (rot(o->f),rot(o)) : (rot(o),rot(o));
    o->upd();
}
void access(node *o){
    node *c=null,*t=o;
    for(;o!=null;o=o->f){
        splay(o);
        o->ch[1]=c, o->upd();
        c=o;
    }
    splay(t);
}
node *findrt(node *o){
    access(o);
    while (o->ch[0]!=null) o=o->ch[0];
    return o;
}
void mroot(node *o){
    access(o);o->fl^=1;
}
void link(node *x,node *y){
    mroot(x);x->f=y;
}
void cut(node *x,node *y){
    mroot(x);access(y);
    if (y->ch[0]==x) x->f=y->ch[0]=null;
}
int main(){
    int n=read(),m=read();
    null=&T[0], null->s=null->fl=0, null->ch[0]=null->ch[1]=null->f=null;
    rep(i,1,n) T[i].ch[0]=T[i].ch[1]=T[i].f=null, T[i].fl=0, T[i].s=T[i].v=read();
    rep(i,1,m){
        int tp=read(),x1=read(),y1=read();
        node *x=&T[x1],*y=tp==3 ? null :&T[y1];
        if (tp==0) mroot(x),access(y),printf("%d\n",y->s);
        else if (tp==1) {
            mroot(x);if (findrt(y)!=x) x->f=y;
        }else if (tp==2) {
            mroot(x);access(y);
            if (y->ch[0]==x) y->ch[0]=null,x->f=null;
        }else if (tp==3){
            mroot(x);x->v=y1;x->upd();
        }
    }
}
Problem3282

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
 
const int N=300000;
struct node{
    node *ch[2],*f;
    int fl,s,v;
    void upd(){s= (ch[0]->s) ^ (ch[1]->s) ^ v; }
    int d(){return f->ch[1]==this;}
    bool c(){return f->ch[0]==this || f->ch[1]==this;}
    void st(node *c,int d){ch[d]=c;c->f=this;}
    void push(){
        if (fl){
            ch[0]->fl^=1;ch[1]->fl^=1;
            swap(ch[0],ch[1]);
            fl=0;
        }
    }
}T[N],*null;
void rot(node *o){
    node *f=o->f;int d=o->d();
    if (f->c()) f->f->st(o,f->d()); else o->f=f->f;
    f->st(o->ch[d^1],d);o->st(f,d^1);
    f->upd();
}
void fix(node *o){
    if (o->c()) fix(o->f);
    o->push();
}
void splay(node *o){
    fix(o);
    while (o->c())
        if (!o->f->c()) rot(o); else
            (o->d()==o->f->d()) ? (rot(o->f),rot(o)) : (rot(o),rot(o));
    o->upd();
}
void access(node *o){
    node *c=null,*t=o;
    for(;o!=null;o=o->f){
        splay(o);
        o->ch[1]=c, o->upd();
        c=o;
    }
    splay(t);
}
node *findrt(node *o){
    access(o);
    while (o->ch[0]!=null) o=o->ch[0];
    return o;
}
void mroot(node *o){
    access(o);o->fl^=1;
}
void link(node *x,node *y){
    mroot(x);x->f=y;
}
void cut(node *x,node *y){
    mroot(x);access(y);
    if (y->ch[0]==x) x->f=y->ch[0]=null;
}
int main(){
    int n=read(),m=read();
    null=&T[0], null->s=null->fl=0, null->ch[0]=null->ch[1]=null->f=null;
    rep(i,1,n) T[i].ch[0]=T[i].ch[1]=T[i].f=null, T[i].fl=0, T[i].s=T[i].v=read();
    rep(i,1,m){
        int tp=read(),x1=read(),y1=read();
        node *x=&T[x1],*y=tp==3 ? null :&T[y1];
        if (tp==0) mroot(x),access(y),printf("%d\n",y->s);
        else if (tp==1) {
            mroot(x);if (findrt(y)!=x) x->f=y;
        }else if (tp==2) {
            mroot(x);access(y);
            if (y->ch[0]==x) y->ch[0]=null,x->f=null;
        }else if (tp==3){
            access(x);x->v=y1;x->upd();
        }
    }
}
Problem3282

#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define read(a) a=getint()
#define print(a) printf("%d", a)
#define dbg(x) cout << (#x) << " = " << (x) << endl
#define printarr2(a, b, c) for1(_, 1, b) { for1(__, 1, c) cout << a[_][__]; cout << endl; }
#define printarr1(a, b) for1(_, 1, b) cout << a[_] << '\t'; cout << endl
inline const int getint() { int r=0, k=1; char c=getchar(); for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; return k*r; }
inline const int max(const int &a, const int &b) { return a>b?a:b; }
inline const int min(const int &a, const int &b) { return a<b?a:b; }
 
const int N=300005;
struct node *null;
struct node {
    int v, rev, w;
    node *ch[2], *fa;
    node(const int _v=0) : v(_v), rev(0), w(0) { ch[0]=ch[1]=fa=null; }
    bool d() { return fa->ch[1]==this; }
    bool check() { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void setc(node* c, int d) { ch[d]=c; c->fa=this; }
    void pushup() { w=ch[0]->w^ch[1]->w^v; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=1;
            ch[1]->rev^=1;
            swap(ch[0], ch[1]);
            rev=0;
        }
    }
}*t[N];
void rot(node* x) {
    node* fa=x->fa; bool d=x->d();
    if(!fa->check()) fa->fa->setc(x, fa->d());
    else x->fa=fa->fa;
    fa->setc(x->ch[!d], d);
    x->setc(fa, !d);
    fa->pushup();
}
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
void splay(node* x) {
    fix(x);
    while(!x->check())
        if(x->fa->check()) rot(x);
        else x->d()==x->fa->d()?(rot(x->fa), rot(x)):(rot(x), rot(x));
    x->pushup();
}
node* access(node* x) {
    node* y=null;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    return y;
}
void mkroot(node* x) { access(x)->rev^=1; splay(x); }
void link(node* x, node* y) { mkroot(x); x->fa=y; }
void cut(node* x, node* y) {
    mkroot(x); access(y); splay(y);
    y->ch[0]->fa=null; y->ch[0]=null;
}
node* findrt(node* x) {
    access(x); splay(x);
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
void init() { null=new node; null->ch[0]=null->ch[1]=null->fa=null; }
int n, m;
 
int main() {
    init();
    read(n); read(m);
    for1(i, 1, n) t[i]=new node(getint());
    rep(i, m) {
        int c=getint(), x=getint(), y=getint();
        if(c==0) { mkroot(t[x]); access(t[y]); splay(t[y]); printf("%d\n", t[y]->w); }
        else if(c==1) { if(findrt(t[x])!=findrt(t[y])) link(t[x], t[y]); }
        else if(c==2) { if(findrt(t[x])==findrt(t[y])) cut(t[x], t[y]); }
        else if(c==3) {splay(t[x]); t[x]->v=y; t[x]->pushup(); }
    }
    return 0;
}
Problem3282

#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define read(a) a=getint()
#define print(a) printf("%d", a)
#define dbg(x) cout << (#x) << " = " << (x) << endl
#define printarr2(a, b, c) for1(_, 1, b) { for1(__, 1, c) cout << a[_][__]; cout << endl; }
#define printarr1(a, b) for1(_, 1, b) cout << a[_] << '\t'; cout << endl
inline const int getint() { int r=0, k=1; char c=getchar(); for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; return k*r; }
inline const int max(const int &a, const int &b) { return a>b?a:b; }
inline const int min(const int &a, const int &b) { return a<b?a:b; }
  
const int N=300005;
struct node *null;
struct node {
    int v, rev, w;
    node *ch[2], *fa;
    node(const int _v=0) : v(_v), rev(0), w(0) { ch[0]=ch[1]=fa=null; }
    bool d() { return fa->ch[1]==this; }
    bool check() { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void setc(node* c, int d) { ch[d]=c; c->fa=this; }
    void pushup() { w=ch[0]->w^ch[1]->w^v; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=1;
            ch[1]->rev^=1;
            swap(ch[0], ch[1]);
            rev=0;
        }
    }
}*t[N];
void rot(node* x) {
    node* fa=x->fa; bool d=x->d();
    if(!fa->check()) fa->fa->setc(x, fa->d());
    else x->fa=fa->fa;
    fa->setc(x->ch[!d], d);
    x->setc(fa, !d);
    fa->pushup();
}
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
void splay(node* x) {
    fix(x);
    while(!x->check())
        if(x->fa->check()) rot(x);
        else x->d()==x->fa->d()?(rot(x->fa), rot(x)):(rot(x), rot(x));
    x->pushup();
}
node* access(node* x) {
    node* y=null;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    return y;
}
void mkroot(node* x) { access(x); splay(x);x->rev^=1; }
void link(node* x, node* y) { mkroot(x); x->fa=y; }
void cut(node* x, node* y) {
    mkroot(x); access(y); splay(y);
    y->ch[0]->fa=null; y->ch[0]=null;
}
node* findrt(node* x) {
    access(x); splay(x);
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
void init() { null=new node; null->ch[0]=null->ch[1]=null->fa=null; }
int n, m;
  
int main() {
    init();
    read(n); read(m);
    for1(i, 1, n) t[i]=new node(getint());
    rep(i, m) {
        int c=getint(), x=getint(), y=getint();
        if(c==0) { mkroot(t[x]); access(t[y]); splay(t[y]); printf("%d\n", t[y]->w); }
        else if(c==1) { if(findrt(t[x])!=findrt(t[y])) link(t[x], t[y]); }
        else if(c==2) { if(findrt(t[x])==findrt(t[y])) cut(t[x], t[y]); }
        else if(c==3) {splay(t[x]); t[x]->v=y; t[x]->pushup(); }
    }
    return 0;
}
Problem3282

#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define read(a) a=getint()
#define print(a) printf("%d", a)
#define dbg(x) cout << (#x) << " = " << (x) << endl
#define printarr2(a, b, c) for1(_, 1, b) { for1(__, 1, c) cout << a[_][__]; cout << endl; }
#define printarr1(a, b) for1(_, 1, b) cout << a[_] << '\t'; cout << endl
inline const int getint() { int r=0, k=1; char c=getchar(); for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; return k*r; }
inline const int max(const int &a, const int &b) { return a>b?a:b; }
inline const int min(const int &a, const int &b) { return a<b?a:b; }
  
const int N=300005;
struct node *null;
struct node {
    int v, rev, w;
    node *ch[2], *fa;
    node(const int _v=0) : v(_v), rev(0), w(0) { ch[0]=ch[1]=fa=null; }
    bool d() { return fa->ch[1]==this; }
    bool check() { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void setc(node* c, int d) { ch[d]=c; c->fa=this; }
    void pushup() { w=ch[0]->w^ch[1]->w^v; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=1;
            ch[1]->rev^=1;
            swap(ch[0], ch[1]);
            rev=0;
        }
    }
}*t[N];
void rot(node* x) {
    node* fa=x->fa; bool d=x->d();
    if(!fa->check()) fa->fa->setc(x, fa->d());
    else x->fa=fa->fa;
    fa->setc(x->ch[!d], d);
    x->setc(fa, !d);
    fa->pushup();
}
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
void splay(node* x) {
    fix(x);
    while(!x->check())
        if(x->fa->check()) rot(x);
        else x->d()==x->fa->d()?(rot(x->fa), rot(x)):(rot(x), rot(x));
    x->pushup();
}
void access(node* x) {
    node* y=null,*t=x;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    splay(t);
}
void mkroot(node* x) { access(x);x->rev^=1; }
void link(node* x, node* y) { mkroot(x); x->fa=y; }
void cut(node* x, node* y) {
    mkroot(x); access(y); 
    y->ch[0]->fa=null; y->ch[0]=null;
}
node* findrt(node* x) {
    access(x); 
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
void init() { null=new node; null->ch[0]=null->ch[1]=null->fa=null; }
int n, m;
  
int main() {
    init();
    read(n); read(m);
    for1(i, 1, n) t[i]=new node(getint());
    rep(i, m) {
        int c=getint(), x=getint(), y=getint();
        if(c==0) { mkroot(t[x]); access(t[y]); printf("%d\n", t[y]->w); }
        else if(c==1) { if(findrt(t[x])!=findrt(t[y])) link(t[x], t[y]); }
        else if(c==2) { if(findrt(t[x])==findrt(t[y])) cut(t[x], t[y]); }
        else if(c==3) {splay(t[x]); t[x]->v=y; t[x]->pushup(); }
    }
    return 0;
}
Problem3282

#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define read(a) a=getint()
#define print(a) printf("%d", a)
#define dbg(x) cout << (#x) << " = " << (x) << endl
#define printarr2(a, b, c) for1(_, 1, b) { for1(__, 1, c) cout << a[_][__]; cout << endl; }
#define printarr1(a, b) for1(_, 1, b) cout << a[_] << '\t'; cout << endl
inline const int getint() { int r=0, k=1; char c=getchar(); for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; return k*r; }
inline const int max(const int &a, const int &b) { return a>b?a:b; }
inline const int min(const int &a, const int &b) { return a<b?a:b; }
  
const int N=300005;
struct node *null;
struct node {
    int v, rev, w;
    node *ch[2], *fa;
    node(const int _v=0) : v(_v), rev(0), w(0) { ch[0]=ch[1]=fa=null; }
    bool d() { return fa->ch[1]==this; }
    bool check() { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void setc(node* c, int d) { ch[d]=c; c->fa=this; }
    void pushup() { w=ch[0]->w^ch[1]->w^v; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=1;
            ch[1]->rev^=1;
            swap(ch[0], ch[1]);
            rev=0;
        }
    }
}*t[N];
void rot(node* x) {
    node* fa=x->fa; bool d=x->d();
    if(!fa->check()) fa->fa->setc(x, fa->d());
    else x->fa=fa->fa;
    fa->setc(x->ch[!d], d);
    x->setc(fa, !d);
    fa->pushup();
}
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
void splay(node* x) {
    fix(x);
    while(!x->check())
        if(x->fa->check()) rot(x);
        else x->d()==x->fa->d()?(rot(x->fa), rot(x)):(rot(x), rot(x));
    x->pushup();
}
void access(node* x) {
    node* y=null,*t=x;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    splay(t);
}
void mkroot(node* x) { access(x);x->rev^=1; }
void link(node* x, node* y) { mkroot(x); x->fa=y; }
void cut(node* x, node* y) {
    mkroot(x); access(y);
    y->ch[0]->fa=null,y->ch[0]=null;
}
node* findrt(node* x) {
    access(x);
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
void init() { null=new node; null->ch[0]=null->ch[1]=null->fa=null; }
int n, m;
  
int main() {
    init();
    read(n); read(m);
    for1(i, 1, n) t[i]=new node(getint());
    rep(i, m) {
        int c=getint(), x=getint(), y=getint();
        if(c==0) { mkroot(t[x]); access(t[y]);printf("%d\n", t[y]->w); }
        else if(c==1) { if(findrt(t[x])!=findrt(t[y])) link(t[x], t[y]); }
        else if(c==2) { if(findrt(t[x])==findrt(t[y])) cut(t[x], t[y]); }
        else if(c==3) { splay(t[x]); t[x]->v=y; t[x]->pushup(); }
    }
    return 0;
}
Problem3282

#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define read(a) a=getint()
#define print(a) printf("%d", a)
#define dbg(x) cout << (#x) << " = " << (x) << endl
#define printarr2(a, b, c) for1(_, 1, b) { for1(__, 1, c) cout << a[_][__]; cout << endl; }
#define printarr1(a, b) for1(_, 1, b) cout << a[_] << '\t'; cout << endl
inline const int getint() { int r=0, k=1; char c=getchar(); for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; return k*r; }
inline const int max(const int &a, const int &b) { return a>b?a:b; }
inline const int min(const int &a, const int &b) { return a<b?a:b; }
  
const int N=300005;
struct node *null;
struct node {
    int v, rev, w;
    node *ch[2], *fa;
    node(const int _v=0) : v(_v), rev(0), w(0) { ch[0]=ch[1]=fa=null; }
    bool d() { return fa->ch[1]==this; }
    bool check() { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void setc(node* c, int d) { ch[d]=c; c->fa=this; }
    void pushup() { w=ch[0]->w^ch[1]->w^v; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=1;
            ch[1]->rev^=1;
            swap(ch[0], ch[1]);
            rev=0;
        }
    }
}*t[N];
void rot(node* x) {
    node* fa=x->fa; bool d=x->d();
    if(!fa->check()) fa->fa->setc(x, fa->d());
    else x->fa=fa->fa;
    fa->setc(x->ch[!d], d);
    x->setc(fa, !d);
    fa->pushup();
}
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
void splay(node* x) {
    fix(x);
    while(!x->check())
        if(x->fa->check()) rot(x);
        else x->d()==x->fa->d()?(rot(x->fa), rot(x)):(rot(x), rot(x));
    x->pushup();
}
void access(node* x) {
    node* y=null,*t=x;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    splay(t);
}
void mkroot(node* x) { access(x);x->rev^=1; }
void link(node* x, node* y) { mkroot(x); x->fa=y; }
void cut(node* x, node* y) {
    mkroot(x); access(y); 
    y->ch[0]->fa=null; y->ch[0]=null;
}
node* findrt(node* x) {
    access(x); 
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
void init() { null=new node; null->ch[0]=null->ch[1]=null->fa=null; }
int n, m;
  
int main() {
    init();
    read(n); read(m);
    for1(i, 1, n) t[i]=new node(getint());
    rep(i, m) {
        int c=getint(), x=getint(), y=getint();
        if(c==0) { mkroot(t[x]); access(t[y]); printf("%d\n", t[y]->w); }
        else if(c==1){
            mkroot(t[x]);if (findrt(t[y])!=t[x]) t[x]->fa=t[y]; 
        }else if(c==2){
            if(findrt(t[x])==findrt(t[y])){
                mkroot(t[x]); access(t[y]); 
                (t[y]->ch[0])->fa=null; (t[y]->ch[0])=null;
            } 
        }else if(c==3) {splay(t[x]); t[x]->v=y; t[x]->pushup(); }
    }
    return 0;
}
Problem3282

#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define rep(i, n) for(int i=0; i<(n); ++i)
#define for1(i,a,n) for(int i=(a);i<=(n);++i)
#define for2(i,a,n) for(int i=(a);i<(n);++i)
#define for3(i,a,n) for(int i=(a);i>=(n);--i)
#define for4(i,a,n) for(int i=(a);i>(n);--i)
#define CC(i,a) memset(i,a,sizeof(i))
#define read(a) a=getint()
#define print(a) printf("%d", a)
#define dbg(x) cout << (#x) << " = " << (x) << endl
#define printarr2(a, b, c) for1(_, 1, b) { for1(__, 1, c) cout << a[_][__]; cout << endl; }
#define printarr1(a, b) for1(_, 1, b) cout << a[_] << '\t'; cout << endl
inline const int getint() { int r=0, k=1; char c=getchar(); for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; return k*r; }
inline const int max(const int &a, const int &b) { return a>b?a:b; }
inline const int min(const int &a, const int &b) { return a<b?a:b; }
  
const int N=300005;
struct node *null;
struct node {
    int v, rev, w;
    node *ch[2], *fa;
    node(const int _v=0) : v(_v), rev(0), w(0) { ch[0]=ch[1]=fa=null; }
    bool d() { return fa->ch[1]==this; }
    bool check() { return fa->ch[0]!=this && fa->ch[1]!=this; }
    void setc(node* c, int d) { ch[d]=c; c->fa=this; }
    void pushup() { w=ch[0]->w^ch[1]->w^v; }
    void pushdown() {
        if(rev) {
            ch[0]->rev^=1;
            ch[1]->rev^=1;
            swap(ch[0], ch[1]);
            rev=0;
        }
    }
}*t[N];
void rot(node* x) {
    node* fa=x->fa; bool d=x->d();
    if(!fa->check()) fa->fa->setc(x, fa->d());
    else x->fa=fa->fa;
    fa->setc(x->ch[!d], d);
    x->setc(fa, !d);
    fa->pushup();
}
void fix(node* x) {
    if(!x->check()) fix(x->fa);
    x->pushdown();
}
void splay(node* x) {
    fix(x);
    while(!x->check())
        if(x->fa->check()) rot(x);
        else x->d()==x->fa->d()?(rot(x->fa), rot(x)):(rot(x), rot(x));
    x->pushup();
}
void access(node* x) {
    node* y=null,*t=x;
    for(; x!=null; y=x, x=x->fa) {
        splay(x);
        x->ch[1]=y;
    }
    splay(t);
}
void mkroot(node* x) { access(x);x->rev^=1; }
void link(node* x, node* y) { mkroot(x); x->fa=y; }
void cut(node* x, node* y) {
    mkroot(x); access(y); 
    y->ch[0]->fa=null; y->ch[0]=null;
}
node* findrt(node* x) {
    access(x); 
    while(x->ch[0]!=null) x=x->ch[0];
    return x;
}
void init() { null=new node; null->ch[0]=null->ch[1]=null->fa=null; }
int n, m;
  
int main() {
    init();
    read(n); read(m);
    for1(i, 1, n) t[i]=new node(getint());
    rep(i, m) {
        int c=getint(), x=getint(), y=getint();
        if(c==0) { mkroot(t[x]); access(t[y]); printf("%d\n", t[y]->w); }
        else if(c==1){
            mkroot(t[x]);if (findrt(t[y])!=t[x]) t[x]->fa=t[y]; 
        }else if(c==2){
            mkroot(t[x]);access(t[y]);
            if (t[y]->ch[0]==t[x]) t[y]->ch[0]=null,t[x]->fa=null;
        }else if(c==3) {splay(t[x]); t[x]->v=y; t[x]->pushup(); }
    }
    return 0;
}
Problem3282

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}

const int N=300100;
struct node{
	node *ch[2],*f;
	int fl,s,v;
	void upd(){s= (ch[0]->s) ^ (ch[1]->s) ^ v; }
	int d(){return f->ch[1]==this;}
	bool c(){return f->ch[0]==this || f->ch[1]==this;}
	void st(node *c,int d){ch[d]=c;c->f=this;}
	void push(){
		if (fl){
			ch[0]->fl^=1;ch[1]->fl^=1;
			swap(ch[0],ch[1]);
			fl=0;
		}
	}
}T[N],*null;
void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->c()) f->f->st(o,f->d()); else o->f=f->f;
	f->st(o->ch[d^1],d);o->st(f,d^1);
	f->upd();
}
void fix(node *o){
	if (o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (o->c())
		if (!o->f->c()) rot(o); else 
			(o->d()==o->f->d()) ? (rot(o->f),rot(o)) : (rot(o),rot(o));
	o->upd();
}
void access(node *o){
	node *c=null,*t=o;
	for(;o!=null;o=o->f){
		splay(o);
		o->ch[1]=c, o->upd();
		c=o;
	}
	splay(t);
}
node *findrt(node *o){
	access(o);
	while (o->ch[0]!=null) o=o->ch[0];
	return o;
}
void mroot(node *o){
	access(o);o->fl^=1;
}
int main(){
	int n=read(),m=read();
	null=&T[0], null->s=null->fl=0, null->ch[0]=null->ch[1]=null->f=null;
	rep(i,1,n) T[i].ch[0]=T[i].ch[1]=T[i].f=null, T[i].fl=0, T[i].s=T[i].v=read();
	rep(i,1,m){
		int tp=read(),x1=read(),y1=read();
		node *x=&T[x1],*y=tp==3 ? null :&T[y1];
		if (tp==0) mroot(x),access(y),printf("%d\n",y->s);
		else if (tp==1) {
			mroot(x);if (findrt(y)!=x) x->f=y;
		}else if (tp==2) {
			mroot(x);access(y);
			if (y->ch[0]==x) y->ch[0]=null,x->f=null;
		}else if (tp==3){
			splay(x);x->v=y1;x->upd();
		}
	}
}
Problem3282

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}

const int N=300100;
struct node{
	node *ch[2],*f;
	int fl,s,v;
	inline void upd(){s= (ch[0]->s) ^ (ch[1]->s) ^ v; }
	inline int d(){return f->ch[1]==this;}
	inline bool c(){return f->ch[0]==this || f->ch[1]==this;}
	inline void st(node *c,int d){ch[d]=c;c->f=this;}
	inline void push(){
		if (fl){
			ch[0]->fl^=1;ch[1]->fl^=1;
			swap(ch[0],ch[1]);
			fl=0;
		}
	}
}T[N],*null;
inline void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->c()) f->f->st(o,f->d()); else o->f=f->f;
	f->st(o->ch[d^1],d);o->st(f,d^1);
	f->upd();
}
inline void fix(node *o){
	if (o->c()) fix(o->f);
	o->push();
}
inline void splay(node *o){
	fix(o);
	while (o->c())
		if (!o->f->c()) rot(o); else 
			(o->d()==o->f->d()) ? (rot(o->f),rot(o)) : (rot(o),rot(o));
	o->upd();
}
inline void access(node *o){
	node *c=null,*t=o;
	for(;o!=null;o=o->f){
		splay(o);
		o->ch[1]=c, o->upd();
		c=o;
	}
	splay(t);
}
inline node *findrt(node *o){
	access(o);
	while (o->ch[0]!=null) o=o->ch[0];
	return o;
}
inline void mroot(node *o){
	access(o);o->fl^=1;
}
int main(){
	int n=read(),m=read();
	null=&T[0], null->s=null->fl=0, null->ch[0]=null->ch[1]=null->f=null;
	rep(i,1,n) T[i].ch[0]=T[i].ch[1]=T[i].f=null, T[i].fl=0, T[i].s=T[i].v=read();
	rep(i,1,m){
		int tp=read(),x1=read(),y1=read();
		node *x=&T[x1],*y=tp==3 ? null :&T[y1];
		if (tp==0) mroot(x),access(y),printf("%d\n",y->s);
		else if (tp==1) {
			mroot(x);if (findrt(y)!=x) x->f=y;
		}else if (tp==2) {
			mroot(x);access(y);
			if (y->ch[0]==x) y->ch[0]=null,x->f=null;
		}else if (tp==3){
			splay(x);x->v=y1;x->upd();
		}
	}
}
Problem3282

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}

const int N=300100;
struct node{
	node *ch[2],*f;
	int fl,s,v;
	inline void upd(){s= (ch[0]->s) ^ (ch[1]->s) ^ v; }
	inline int d(){return f->ch[1]==this;}
	inline bool c(){return f->ch[0]==this || f->ch[1]==this;}
	inline void st(node *c,int d){ch[d]=c;c->f=this;}
	inline void push(){
		if (fl){
			ch[0]->fl^=1;ch[1]->fl^=1;
			swap(ch[0],ch[1]);
			fl=0;
		}
	}
}T[N],*null;
inline void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->c()) f->f->st(o,f->d()); else o->f=f->f;
	f->st(o->ch[d^1],d);o->st(f,d^1);
	f->upd();
}
void fix(node *o){
	if (o->c()) fix(o->f);
	o->push();
}
inline void splay(node *o){
	fix(o);
	while (o->c())
		if (!o->f->c()) rot(o); else 
			(o->d()==o->f->d()) ? (rot(o->f),rot(o)) : (rot(o),rot(o));
	o->upd();
}
inline void access(node *o){
	node *c=null,*t=o;
	for(;o!=null;o=o->f){
		splay(o);
		o->ch[1]=c, o->upd();
		c=o;
	}
	splay(t);
}
inline node *findrt(node *o){
	access(o);
	while (o->ch[0]!=null) o=o->ch[0];
	return o;
}
inline void mroot(node *o){
	access(o);o->fl^=1;
}
int main(){
	int n=read(),m=read();
	null=&T[0], null->s=null->fl=0, null->ch[0]=null->ch[1]=null->f=null;
	rep(i,1,n) T[i].ch[0]=T[i].ch[1]=T[i].f=null, T[i].fl=0, T[i].s=T[i].v=read();
	rep(i,1,m){
		int tp=read(),x1=read(),y1=read();
		node *x=&T[x1],*y=tp==3 ? null :&T[y1];
		if (tp==0) mroot(x),access(y),printf("%d\n",y->s);
		else if (tp==1) {
			mroot(x);if (findrt(y)!=x) x->f=y;
		}else if (tp==2) {
			mroot(x);access(y);
			if (y->ch[0]==x) y->ch[0]=null,x->f=null;
		}else if (tp==3){
			splay(x);x->v=y1;x->upd();
		}
	}
}
Problem3289

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

typedef long long LL;
const int maxn=501000;


struct node{
	int a,b;	
} a[maxn];
bool cmp(const node &a,const node &b){return a.a<b.a;}


int s[maxn];//size


struct querry{
	int l,r,t;
}q[maxn];
int sqn;
bool cmp_q(const querry &a,const querry &b){
	return (a.l / sqn) < (b.l / sqn) || ((a.l / sqn) == (b.l / sqn) && a.r < b.r);
}	

int maxs;
struct BIT{
	int s[maxn];
	void clear(){
		memset(s,0,sizeof(s));
	}
	int lowbit(int x){
		return (-x) & x;
	}
	void add(int x,int d){
		while (x<=maxs){
			s[x]+=d;x+=lowbit(x);
		}
	}
	int sum(int x){
		int ans=0;
		while (x>0){
			ans+=s[x];x-=lowbit(x);
		}
		return ans;
	}
}b;


LL ans[maxn];
int cnt=0;


int main(){
	int n;scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i].a),a[i].b=i;
	sort(a+1,a+1+n,cmp);
	int tmp,t;
	a[1].a=1;
	rep(i,2,n){
		t=a[i].a;
		if (a[i].a==tmp) a[i].a=a[i-1].a; else a[i].a=a[i-1].a+1;
		tmp=t;
	}
	maxs=a[n].a;
	rep(i,1,n) s[a[i].b]=a[i].a;

	int m;scanf("%d",&m);
	rep(i,1,m) scanf("%d%d",&q[i].l,&q[i].r),q[i].t=i;
	sqn=(int)sqrt(n);if (sqn==0) sqn=1;
	sort(q+1,q+m+1,cmp_q);

	int l=1,r=1;
	LL cnt=0;
	b.clear();b.add(s[1],1);
	rep(i,1,m){
		if (l < q[i].l){
			rep(j, l, q[i].l-1){
				b.add(s[j], -1);
				cnt-=(LL) b.sum(s[j]-1);
			}
			l=q[i].l;
		}else if (l > q[i].l){
			dep(j,l-1,q[i].l){
				cnt+=(LL) b.sum(s[j]-1);
				b.add(s[j], 1);
			}
			l=q[i].l;
		};
		if (r > q[i].r){
			dep(j,r,q[i].r+1){
				b.add(s[j],-1);
				cnt-=(LL) b.sum(maxs)-b.sum(s[j]);
			}
			r=q[i].r;
		}else if (r < q[i].r){
			rep(j,r+1,q[i].r){
				cnt+=(LL) b.sum(maxs)-b.sum(s[j]);
				b.add(s[j],1);
			}
			r=q[i].r;
		}
		ans[q[i].t]=cnt;
	}

	rep(i,1,m) printf("%lld\n",ans[i]);
	return 0;
}
Problem3295

    #include <iostream>
    #include <cstdio>
    #include <cmath>
    #include <cstring>
    #include <algorithm>
    typedef long long LL;
    using namespace std;
    int n;
    const int maxn=100010; 
    struct  BIT{
        int s[maxn];
        void clear(){
            for (int i=0;i<=n;i++) s[i]=0;
        }
        void add(int x,int d){
            while (x<=n){
                s[x]+=d;x+=x & (-x);    
            }
        }
        int sum(int x){
            int ans=0;
            while (x>0){
                ans+=s[x];x-=x & (-x);
            }
            return ans;
        }
    };
    BIT b;
    struct querry{
        int val,pos,t;
    };
    bool cmp(const querry &a,const querry &b){return a.pos<b.pos;}
    querry q[maxn],tmp[maxn];
    bool vis[maxn];
    LL ans[maxn];
    int a[maxn],pos[maxn];
    void cdq(int l,int r){
        if (l==r) return;
        int mid=(l+r) >> 1;
        int t1=l,t2=mid+1,i,j;
        for (i=l;i<=r;i++) if (q[i].t<=mid) tmp[t1++]=q[i]; else tmp[t2++]=q[i];
        for (i=l;i<=r;i++) q[i]=tmp[i];
        for (i=mid+1,j=l;i<=r;i++){
            while (q[j].pos<q[i].pos && j<=mid) b.add(q[j].val,1),j++;
            ans[q[i].t]+=b.sum(n)-b.sum(q[i].val-1);
        }
        for (i=l;i<j;i++) b.add(q[i].val,-1);
        for (i=r,j=mid;i>=mid+1;i--){
            while (q[j].pos>q[i].pos && j>=l) b.add(q[j].val,1),j--;
            ans[q[i].t]+=b.sum(q[i].val-1);
        }
        for (i=j+1;i<=mid;i++) b.add(q[i].val,-1);
        cdq(l,mid);cdq(mid+1,r);
    }
    int main(){
         memset(ans,0,sizeof(ans));
         int m;
         scanf("%d%d",&n,&m);
         for (int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            pos[a[i]]=i;
         }
         memset(vis,false,sizeof(vis));
         for (int i=1;i<=m;i++){
            int t;
            scanf("%d",&t);
            vis[t]=true;
            q[i].val=t;
            q[i].pos=pos[t];
            q[i].t=n-i+1;
         }
         int j=0;
         for (int i=1;i<=n;i++)
            if (!vis[a[i]]){
                j++;
                q[j+m].val=a[i];
                q[j+m].pos=i;
                q[j+m].t=j;
            }
         sort(q+1,q+n+1,cmp);
         b.clear();
         cdq(1,n);
         for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
         for(int i=n;n-i+1<=m;i--) printf("%lld\n",ans[i]);
         return 0;
    }
Problem3296

var
  n,m,l,i,j,k,ans,ll:longint;
  u:array[1..100000]of longint;
  v,pre:array[1..800000]of longint;
 visited:array[1..100000]of boolean;
procedure insert(a,b:longint);
begin 
  inc(l);v[l]:=b;
  pre[l]:=u[a];u[a]:=l;
end;
procedure floodfill(x:longint);
var
 i:longint;
begin
 if visited[x] then exit else visited[x]:=true;
 i:=u[x];
 while i<>0 do begin 
     floodfill(v[i]);i:=pre[i];
 end;
end;
begin 
 readln(n,m);
 for i:=1 to n do begin 
     read(k);
	 for j:=1 to k do begin 
	     read(ll);insert(i,ll+n);insert(ll+n,i);
	 end;
    readln;
 end;
 ans:=0;
 fillchar(visited,sizeof(visited),false);
 for i:=1 to n do if not visited[i] then begin inc(ans);floodfill(i);end;
 writeln(ans-1);
end.
Problem3307

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=100010;
struct edge{
	int to,pre;
}e[N*2];
int l=0,u[N],dep[N],f[N];
inline void ins(int a,int b){
	e[++l]=(edge){b,u[a]};u[a]=l;
}
int pre[N],s[N],top[N],son[N],dfs_clock=0;
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
inline void dfs(int x,int fa){
	s[x]=1;son[x]=0;f[x]=fa;
	reg(i,x)if (v!=fa) {
		dep[v]=dep[x]+1;
		dfs(v,x);
		if (s[v]>s[son[x]]) son[x]=v;
		s[x]+=s[v];
	}
}
inline void build(int x){
	pre[x]=++dfs_clock;
	if (son[x]) top[son[x]]=top[x],build(son[x]);
	reg(i,x) if (v!=f[x] && v!=son[x])
		top[v]=v, build(v);
}
int x[N],y[N],z[N],tmp[N],M;
inline int find(int x){
	int l=0,r=M;
	while (l+1<r){
		int mid=(l+r) >> 1;
		if (tmp[mid] < x) l=mid; else r=mid;
	}
	return r;
}
int ud[N];
struct Ud{
	int z,d,pre;
}ad[N*20];
int ld=0;
void add(int x,int z,int d){
	ad[++ld]=(Ud){z,d,ud[x]};ud[x]=ld;
}
void work(int a,int b,int c){
	int ta=top[a],tb=top[b];
	while (ta!=tb){
		if (dep[ta]<dep[tb]) swap(a,b),swap(ta,tb);
		add(pre[a]+1,c,-1);
		add(pre[ta],c,1);
		a=f[ta];ta=top[a];
	}
	if (dep[a]>dep[b]) swap(a,b);
	add(pre[a],c,1);
	add(pre[b]+1,c,-1);
}
#define lcq lc,l,mid
#define rcq rc,mid+1,r
struct seg{
	int mx[N*5+10],s[N*5+10];
	inline void upd(int x){
		int lc=x << 1,rc=lc+1;
		if (s[lc]>=s[rc]) 
			s[x]=s[lc],mx[x]=mx[lc];
		else
			s[x]=s[rc],mx[x]=mx[rc]; 
	}
	inline void modi(int x,int l,int r,int a,int d){
		if (l==r) mx[x]=l,s[x]+=d;else{
			int lc=x << 1, rc=lc+1, mid=(l+r) >> 1;
			if (a <= mid) modi(lcq,a,d);
			if (a > mid) modi(rcq,a,d);
			upd(x);
		}
	}
	inline void add(int a,int d){
		modi(1,1,M,a,d);
	}
	inline int qry(){
		if (s[1]==0) return 0; else return mx[1];
	}
}B;
#define rag(j,a) for(int j=ud[a];j;j=ad[j].pre)
#define zd ad[j].z
#define dd ad[j].d
int ans[N];

inline int read()

{

    int x=0,f=1;char ch=getchar();

    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}

    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}

    return x*f;

}
int main(){
	int n=read(),m=read();
	int a,b;
	rep(i,1,n-1) {a=read();b=read();ins(a,b);ins(b,a);}
	dep[1]=1;dfs(1,0);
	top[1]=1;build(1);
	rep(i,1,m) x[i]=read(),y[i]=read(),z[i]=read(),tmp[i]=z[i];
	sort(tmp+1,tmp+m+1);
	M=(unique(tmp+1,tmp+m+1)-tmp)-1;
	rep(i,1,m){
		z[i]=find(z[i]);
		work(x[i],y[i],z[i]);
	}
	rep(i,1,n){
		rag(j,i) B.add(zd,dd);
		ans[i]=tmp[B.qry()];
	}
	rep(i,1,n) printf("%d\n",ans[pre[i]]);
	return 0;
}
Problem3307

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define v e[i].to
using namespace std;
const int N=100100;
int u[N],n;
struct edge{
    int to,pre;
}e[N*2];
int l=0;
void ins(int a,int b){
    e[++l]=(edge){b,u[a]};u[a]=l;
}
int f[N],depth[N],times=0;
void dfs(int x,int fa){
	f[x]=fa;
	reg(i,x)if (v!=fa) {
		depth[v]=depth[x]+1;
		dfs(v,x);
	}
}
int g[N][20];
void init(){
    rep(i,1,n) g[i][0]=f[i];
    rep(j,1,19) rep(i,1,n) g[i][j]=g[g[i][j-1]][j-1];
}
int tlca(int u,int V){
    if (depth[u]<depth[V]) swap(u,V);
    dep(i,19,0) if (g[u][i] && depth[g[u][i]]>=depth[V]) u=g[u][i];
    dep(i,19,0) if (g[u][i]!=g[V][i]) u=g[u][i], V=g[V][i];
    return u==V ? u : f[u];
}
int x[N],y[N],z[N],tmp[N],M;
int find(int x){
    int l=0,r=M;
    while (l+1<r){
        int mid=(l+r) >> 1;
        if (tmp[mid] < x) l=mid; else r=mid;
    }
     return r;
}
int ud[N];
struct Ud{
    int tp,d,pre;
}ad[N*4];
int ld=0;
void add(int x,int tp,int d){
    ad[++ld]=(Ud){tp,d,ud[x]};ud[x]=ld;
}
struct seg_nod{
    int ch[2],mx,mxa;
}T[5000000];
int st[5000000],top;
inline int nn(){
    int t=st[--top];
    T[t].ch[0]=T[t].ch[1]=0;
    T[t].mx=T[t].mxa=0;
    return t;
}
inline void del(int x){
    st[top++]=x;
}
#define lc T[x].ch[0]
#define rc T[x].ch[1]
#define xm T[x].mx
#define xa T[x].mxa
#define lm T[lc].mx
#define la T[lc].mxa
#define rm T[rc].mx
#define ra T[rc].mxa
inline void upd(int x){
    if (la >= ra) xa = la, xm = lm; else xa = ra, xm = rm; 
}
void modi(int x,int l,int r,int a,int d){
    if (l == r) xm=l, xa+=d;else{
        int mid = (l + r) >> 1;
        if (a <= mid){
            if (!lc) lc=nn();
            modi(lc,l,mid,a,d);
        }else{
            if (!rc) rc=nn();
            modi(rc,mid+1,r,a,d);
        }
        upd(x);
    }
}
int merge(int a,int b){
    if (!a || !b) return a+b;
    if (T[a].ch[0]==0 && T[a].ch[1]==0 && T[b].ch[0]==0 && T[b].ch[1]==0) T[a].mxa+=T[b].mxa;else{
        T[a].ch[0]=merge(T[a].ch[0],T[b].ch[0]);
        T[a].ch[1]=merge(T[a].ch[1],T[b].ch[1]);
        upd(a);
    }
    del(b);
    return a;
}
#define rag(i,a) for(int i=ud[a];i;i=ad[i].pre)
#define atp ad[i].tp
#define atd ad[i].d
int ans[N];
int dfs1(int x,int fa){
    int t=nn();
    reg(i,x) if (v!=fa) t=merge(dfs1(v,x),t);
    rag(i,x) modi(t,1,M,atp,atd);
    if (T[t].mxa==0) T[t].mx=0;
    ans[x]=tmp[T[t].mx];
    return t;
}
inline int read(){
	char c=getchar();int x=0,f=1;
	while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0' && c<='9') {x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main(){
	n=read();int m=read();
	int a,b;
	rep(i,1,n-1) {a=read();b=read();ins(a,b);ins(b,a);}
    depth[1]=1, dfs(1,0);
    init();
	rep(i,1,m) x[i]=read(),y[i]=read(),z[i]=read(),tmp[i]=z[i];
    sort(tmp+1,tmp+m+1);
    M=(unique(tmp+1,tmp+m+1)-tmp)-1;
    rep(i,1,m) {
        z[i]=find(z[i]),add(x[i],z[i],1),add(y[i],z[i],1);
        int t=tlca(x[i],y[i]);
        add(t,z[i],-1);
        if (f[t]) add(f[t],z[i],-1);
    }
    top=0;
    rep(i,1,5000000-1) del(i);
    dfs1(1,0);
    rep(i,1,n) printf("%d\n",ans[i]);
    return 0;
}
Problem3309

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define e(x) (x==1 ? 1 : 0)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
const int T=10005,N=10000010;
int p[N],l=0,c1[N],c2[N],c3[N];//c1:max c2:now(smallest) c3[N]:t;
int A[N];
LL g[N];
bool a[N];
void init(int n){
    memset(a,true,sizeof(a));
    g[1]=0;
    rep(i,2,n){
        if (a[i]){
            p[++l]=i;
            g[i]=1;
            c1[i]=0;c2[i]=1;c3[i]=1;
        }
        rep(j,1,l){
            if(((LL)p[j]*i) > n) break;
            int k=p[j]*i;
            a[k]=false;
            if (i % p[j]==0){//p[j] is the smallest in i
                if (c1[i]==-1){
                    c1[k]=c2[k]=c3[k]=-1;
                    g[k]=0;
                } else{
                    c1[k]=c1[i];
                    c2[k]=c2[i]+1;
                    c3[k]=c3[i];
                    if (c1[k]==c2[k] || c1[k]==0) g[k]=(c3[k] % 2==1) ? 1 : -1;
                    if (c1[k] != 0   &&   c1[k] < c2[k])c1[k]=c2[k]=c3[k]=-1,g[k]=0; 
                }
                break;
            } else {
                if (c1[i]==-1 || (c1[i]!=c2[i] && c1[i]!=0)){
                    c1[k]=c2[k]=c3[k]=-1;
                    g[k]=0;
                } else{
                    c1[k]=c2[i];
                    c2[k]=1;
                    c3[k]=c3[i]+1;
                    if (c1[k]==c2[k]) g[k]=(c3[k] % 2==1) ? 1 : -1; else g[k]=0;
                }
            }
        }
    }
    g[0]=g[1]=0;
    rep(i,1,n) g[i]+=g[i-1];
}	
void work(int n,int m){
    LL ans=0;
    int r;
    for(int l=1;l<=n && l<=m;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=((LL)g[r]-g[l-1])*(LL)(n/l)*(LL)(m/l);
    }
    printf("%lld\n",ans);
}

int q_a[T],q_b[T];
int main(){
	int t,maxq=0;scanf("%d",&t);
	rep(i,1,t) {
		scanf("%d%d",&q_a[i],&q_b[i]);
		maxq=max(maxq,max(q_a[i],q_b[i]));
	}
	init(maxq);
	rep(i,1,t) work(q_a[i],q_b[i]);
	return 0;
}
/*{
	n=p_1^max * p_2^max.........p_t^max * p_(t+1)^q_(t+1).........p_m^q_m
A=p_1 * p_2.........p_t
B=n/(A^max)

(f*miu)(n)=sigma(miu(d)*f(n/d)[d|n])
miu(d)!=0  when  d SQF
f(n/d)=max or max-1
f(n/d)=max-1 when A|d

(f*miu)(n)=max * sigma(miu(d)[d|n]) - 1 * sigma(miu(d * A) [d|B] )
		  =max*e(n) - miu(A)*sigma(miu(d)[d|B])  (d|B,(A,B)=1 ===> (A,d)=1)
		  =max*e(n) - miu(A) * e(B)
          所以只有e(n) 或者 e(B) 不等于0时(f*miu)(n)不为0
          e(n)不等于0当n=1 不能指望它233
          e(B)不等于0当B=1 (f*miu)(n)=-miu(A)=(-1)^(t+1)
*/
Problem3339

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
Problem3399

var
 n,x,y,ans,i:longint;
 a,b:array[1..2500000]of longint;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin
 i:=l;j:=r;m:=a[(l+r) shr 1];
 repeat
    while a[i]<m do inc(i);
	while a[j]>m do dec(j);
	if i<=j then begin 
	    t:=a[i];a[i]:=a[j];a[j]:=t;
		inc(i);dec(j);
	end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
procedure sort1(l,r:longint);
var
 i,j,m,t:longint;
begin
 i:=l;j:=r;m:=b[(l+r) shr 1];
 repeat
    while b[i]<m do inc(i);
	while b[j]>m do dec(j);
	if i<=j then begin 
	    t:=b[i];b[i]:=b[j];b[j]:=t;
		inc(i);dec(j);
	end;
 until i>j;
 if l<j then sort1(l,j);
 if i<r then sort1(i,r);
end;
function get(a,b:longint):longint;
begin 
 if a<b then exit((b-a)*x) else exit((a-b)*y);
end;
begin 
 readln(n,x,y);
 for i:=1 to n do readln(a[i],b[i]);
 sort(1,n);
 sort1(1,n);
 ans:=0;
 for i:=1 to n do ans:=ans+get(a[i],b[i]);
 writeln(ans);
end.
Problem3400

const
 mo=100000000;
var
 n,m,c,i,j:longint;
 f:array[0..2000,0..1000]of longint;
begin 
  readln(n,m);
 f[0,0]:=1;
 for i:=1 to n do begin 
     readln(c);
     for j:=0 to m-1 do begin 
		   f[i,(j+c) mod m]:=(f[i-1,(j+c) mod m]+f[i-1,j]) mod mo;
	 end;
 end;
 writeln(f[n,0]-1);//-1 means not empty
end.
Problem3401

var
  stack:array[1..100000]of longint;
 l,n,i:longint;
 h:array[1..100000]of longint;
 ans:array[1..100000]of longint;
begin 
 readln(n);l:=0;
 for i:=1 to n do readln(h[i]);
 for i:=n downto 1 do begin 
      while (l>0) and (h[stack[l]]<=h[i]) do dec(l);
	 if l=0 then ans[i]:=0 else ans[i]:=stack[l];
	 inc(l);stack[l]:=i;
 end;
 for i:=1 to n do writeln(ans[i]);
end.
Problem3402

var
 n,m,l,max,ans,i,a,b:longint;
 q:array[0..30000]of longint;
 u,dis:array[1..50000]of longint;
 v,pre:array[1..500000]of longint;
procedure ins(a,b:longint);
begin
   inc(l);v[l]:=b;
	pre[l]:=u[a];u[a]:=l;
end;
procedure bfs;
var
 i,t,w,x:longint;
begin
     t:=0;w:=1;q[0]:=1;
	 fillchar(dis,sizeof(dis),0);
	 dis[1]:=1;
	 repeat
	      x:=q[t];inc(t);
		 i:=u[x];
		 while i>0 do begin 
		      if dis[v[i]]=0 then begin 
				 dis[v[i]]:=dis[x]+1;
				 q[w]:=v[i];inc(w);
			  end;
			 i:=pre[i];
		 end;
	 until t=w;
end;
begin
 readln(n,m);
 for i:=1 to m do begin 
      readln(a,b);
	 ins(a,b);ins(b,a);
 end;
 bfs;max:=1;
 for i:=2 to n do if dis[i]>dis[max] then max:=i;
 write(max,' ',dis[max]-1,' ');
 ans:=0;
 for i:=1 to n do if dis[i]=dis[max] then inc(ans);
 writeln(ans);
end.
Problem3403

const
 mo=800000;
var
 q:array[0..mo]of longint;
 l,r,n,s,k,i:longint;
 c,tmp:char;
procedure insert_left;
begin
  dec(l);l:=l mod mo;if l<0 then l:=l+mo;
  inc(n);
  q[l]:=n;
end;
procedure insert_right;
begin
  inc(r);r:=r mod mo;
  inc(n);
  q[r]:=n;
end;
procedure del_left(k:longint);
begin
 inc(l,k);l:=l mod mo; 
end;
procedure del_right(k:longint);
begin
 dec(r,k);r:=r mod mo; if r<0 then r:=r+mo;
end;
procedure print;
var
 i:longint;
begin 
 i:=l-1;
 repeat
     inc(i);i:=i mod mo;
	  writeln(q[i]);
 until i=r;
end;
begin 
 readln(s);l:=0;r:=-1;
 for i:=1 to s do begin 
     read(c);read(tmp);
	 if c='A' then begin 
	     read(c);
		  if c='L' then insert_left else if c='R' then insert_right;
	 end else if c='D' then begin 
	     read(c);read(tmp);read(k);
		 if c='L' then del_left(k) else if c='R' then del_right(k);
	 end;
	 readln;
 end;
 print;
end.
Problem3404

var
   g,max,k,i:longint;
   f:array[0..1000000]of boolean;//先手是否必胜
procedure work(l,r:longint);
var
 i,t,k,max,min:longint;
begin
 for i:=l to r do begin 
     t:=i;max:=0;min:=maxlongint;
	 while t>0 do begin 
	     k:=t mod 10;if k>max then max:=k;if (k<min) and (k>0) then min:=k;
		 t:=t div 10;
	 end;
	 if f[i-max] and f[i-min] then f[i]:=false else f[i]:=true;
 end; 
end;
begin 
   readln(g);
   max:=0;f[0]:=false;
	for i:=1 to g do begin 
         readln(k);
		  if k>max then begin 
			     work(max+1,k);
				 max:=k;
		   end;
			if f[k] then writeln('YES') else writeln('NO');
	end;
end.
Problem3433

var
 n,i,j,k,ans:longint;
 a,b:array[0..150]of longint;
 f:array[0..150,0..150]of longint;
procedure sort(l,r:longint);
var
 i,j,t,m:longint;
begin 
 i:=l;j:=r;m:=b[(l+r) shr 1];
 repeat
     while b[i]<m do inc(i);
	 while b[j]>m do dec(j);
	 if i<=j then begin
          t:=b[i];b[i]:=b[j];b[j]:=t;
          t:=a[i];a[i]:=a[j];a[j]:=t;	 
	     inc(i);dec(j);
	 end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin 
 readln(n);
 for i:=1 to n do readln(a[i],b[i]);
 sort(1,n);ans:=0;
 fillchar(f,sizeof(f),0);
 a[0]:=0;b[0]:=0;
 for i:=0 to n do  
     for j:=0 to n do begin 
		 if (i=0) and (j=0) then continue;
        if i>j then for k:=0 to i-1 do if b[k]>a[i] then break else if f[k,j]+1>f[i,j] then f[i,j]:=f[k,j]+1;
		 if j>i then for k:=0 to j-1 do if b[k]>a[j] then break else if f[i,k]+1>f[i,j] then f[i,j]:=f[i,k]+1;
		 if f[i,j]>ans then ans:=f[i,j];
	 end;
  writeln(ans);
end.
Problem3437

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mp(a,b) make_pair(a,b)
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 1200000;
typedef long long LL;
LL a[N],b[N],f[N],S[N],s[N];
typedef pair<LL, LL> node;
#define x first
#define y second
struct queue{
	node q[N];
	int l,r;
	queue(){
		l = r = 0;
	}
	bool cmp(const node &a, const node &b, const node &c){
		return (c.y - b.y)*(b.x - a.x) > (b.y - a.y)*(c.x - b.x);
	}
	void push(const node &a){
		while (r - l >= 2 && !cmp(q[r - 2], q[r - 1], a)) r--;
		q[r++] = a;
	}
	bool cmp1(const node &a, const node &b, int k){
		return (b.y - b.x * k) < (a.y - a.x * k); 
	}
	LL top(int k){
		while (r - l >= 2 && cmp1(q[l], q[l + 1], k)) l++;
		return q[l].y - q[l].x * k;
	}
}q;
#undef x
#undef y
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	f[0] = s[0] = S[0] = 0;
	rep(i,1,n) scanf("%d",&b[i]), s[i] = s[i-1] + b[i], S[i] = S[i-1] + b[i] * i;
	rep(i,1,n){
		q.push(mp(s[i - 1], f[i - 1] + S[i - 1]));
		LL t = q.top(i);
		f[i] = t + s[i] * i - S[i] + a[i];
	}
	printf("%lld\n",f[n]);
	return 0;
}
Problem3477

#include<algorithm>
#include<cstdio>
#define For(i,a,b) for ( int i = a ; i < b ; i++ )
using namespace std;
typedef double db;
const db eps=1e-5;
const int maxn=100000+10;
int a[maxn],n;
bool ok(db mid) {
	db sum,ret,tot=a[0]+a[1]+a[n-1];
	ret=sum=a[1]-mid;
	For(i,2,n-1) {
		tot+=(db)a[i];
		sum=max(sum,0.0);
		sum+=(db)a[i]-mid;
		ret=max(ret,sum);
	} 
	return ret>=tot-(db)mid*n;
}
int main() {
	scanf("%d",&n);
	For(i,0,n) scanf("%d",&a[i]);
	db left=1.0,right=1000000000.0,middle=(left+right)/2;
	while (left<=right-eps) {
		middle=(left+right)/2;
		if (ok(middle)) right=middle;
		else left=middle;
	}
	printf("%.3lf\n",left);
	return 0 ;
}
Problem3506

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int inf=100000000;
using namespace std;
struct nod{
	int a,x;
}a[100200];
bool cmp(const nod &a,const nod &b){
	return a.a < b.a || (a.a==b.a && a.x < b.x);
}
struct node *null,*root;
struct node{
	node *ch[2],*f;
	int s,k,m,fl;
	int d(){return f->ch[1]==this;}
	void st(node *c,int d){ch[d]=c;c->f=this;}
	void push(){
		if (fl){
			fl=0;
			ch[0]->fl^=1;ch[1]->fl^=1;
			swap(ch[0],ch[1]);
		}
	}
	void upd(){
		s=ch[0]->s+ch[1]->s+1;
		m=min(ch[0]->m,ch[1]->m);
		m=min(m,k);
	}
}T[100200];
int l=0;
node *newnode(int a){
	node *o=&T[l++];
	o->s=1, o->k= o->m = a, o->ch[0]=o->ch[1]=o->f=null, o->fl=0;
	return o;
}
void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->f!=null) f->f->st(o,f->d());else o->f=f->f;
	f->st(o->ch[d^1],d), o->st(f,d^1);
	f->upd();
	if (f==root) root=o;//!
}
void fix(node *o){
	if (o->f!=null) fix(o->f);
	o->push();
}
void splay(node *o,node *f=null){
	fix(o);
	while (o->f!=f)
		if (o->f->f==f) rot(o);
		else (o->f->d()==o->d())?(rot(o->f),rot(o)):(rot(o),rot(o));
	o->upd();
}
node *find(node *o,int k){
	o->push();
	int s=o->ch[0]->s+1;
	if (k==s) return o;
	if (k < s) return find(o->ch[0],k); else return find(o->ch[1],k-s);
}
void get(int l,int r){
	splay(find(root,l));splay(find(root,r+2),root);
}
void ins(int x,int a){
	node *o=newnode(a);
	get(x,x-1);
	root->ch[1]->st(o,0);
	root->ch[1]->upd();
	root->upd();
}
void init(){
	null=&T[l++];
	null->k=null->m=inf;null->s=0;null->ch[0]=null->ch[1]=null->f=null;
	root=newnode(inf);
	root->st(newnode(inf),1);	
}
int fm(node *o){
	o->push();
	int s=o->ch[0]->s+1;
	if (o->m==o->k) return s;
	if (o->m==o->ch[0]->m) return fm(o->ch[0]); else return fm(o->ch[1])+s;
}
void p(node *o){
	if (o==null) return;
	o->push();
	p(o->ch[0]);printf("%d ",o->k);p(o->ch[1]);
}
bool cmp1(const nod &a,const nod &b){
	return a.x < b.x;
}
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i].a),a[i].x=i;
	sort(a+1,a+n+1,cmp);
	init();
	rep(i,1,n) a[i].a=i;
	sort(a+1,a+n+1,cmp1);
	rep(i,1,n) ins(a[i].x,a[i].a);
	rep(i,1,n){
		get(i,n);
		int t=fm(root->ch[1]->ch[0]);t+=i-1;
		printf("%d",t);if (i!=n) printf(" ");
		get(i,t);
		root->ch[1]->ch[0]->fl^=1;
	}
}
/*debug
    when find() push() first!
    if (f==root) o=root!
*/
Problem3512

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#define Rep(i,a,b) for(int i=a;i<=b;i++)
#define Dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
int n, m;
const int N = 100010, MAX = 1000000, M = 1000000000 + 7;

bool a[MAX + 10];
int p[MAX + 10], phi[MAX + 10], sum[MAX + 10], l = 0;
void init_calc(){
	Rep(i,2,MAX){
		if (!a[i]) p[++l] = i, phi[i] = i - 1;
		Rep(j,1,l){
			int k = p[j] * i;
			if (k > MAX) break;
			a[k] = 1;
			if (i % p[j]) phi[k] = (p[j] - 1) * phi[i];
			else{
				phi[k] = p[j] * phi[i];
				break;
			}
		}
	}
	phi[1] = 1, sum[0] = 0;
	Rep(i,1,MAX) sum[i] = (sum[i - 1] + phi[i]) % M;


}

map<int, int> S[N];
inline int calc(int n){
	if (n <= MAX) return sum[n];
	if (S[1].find(n) != S[1].end()) return S[1][n];
	int l = 2, r;
	int ans = ((1LL * n * (n + 1)) / 2) % M;
	while (l <= n){
		r = n / (n / l);
		ans -= 1LL * (r - l + 1) * calc(n / l) % M, ans %= M;
		l = r + 1;
	}
	return S[1][n] = ans;
}

int P[N], pm[N];
typedef vector<int>::iterator vit;
#define pb(a) push_back(a)
vector<int> d[N];
void init_p(){
	Rep(i,2,n){
		int tmp = i; pm[i] = 1;
		for(int j = 2; j * j <= tmp; j++) if (tmp % j == 0){
			P[i] = j, tmp /= j;
			while (tmp % j == 0) pm[i] *= j, tmp /= j;
			break;
		}
		if (P[i] == 0) P[i] = tmp;
		for(int j = 2; j * j <= tmp; j++) if (tmp % j == 0){
			tmp /= j;
			while (tmp % j == 0) pm[i] *= j, tmp /= j;
		}
	}
	Rep(i,2,n)
		for(int j = 1; j * j <= i; j++) if (i % j == 0){
			d[i].pb(j);
			if (j * j < i) d[i].pb(i / j);
		}
}
int s(int a, int b){
	if (a == 0 || b == 0) return 0;
	if (a == 1) return calc(b);
	if (S[a].find(b) != S[a].end()) return S[a][b];
	if(pm[a] == 1){
		int ans = 0;
		for(vit i = d[a].begin();i!=d[a].end();i++) ans += 1LL * phi[a/ *i] * s(*i, b / *i) % M, ans %= M;
		return S[a][b] = ans;
	}
	else 
		return 1LL * pm[a] * s(a / pm[a], b) % M;
}

int main(){
	scanf("%d%d",&n,&m);
	init_calc();
	init_p();
	int ans = 0;
	Rep(i,1,n) ans += s(i,m), ans %= M;
	if (ans < 0) ans += M;
	printf("%d\n",ans);
	return 0;
}
Problem3512

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#define Rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
int n, m;
const int N = 100010, MAX = 1000000, M = 1000000000 + 7;
 
bool a[MAX + 10];
int p[MAX + 10], phi[MAX + 10], sum[MAX + 10], l = 0;
void init_calc(){
    Rep(i,2,MAX){
        if (!a[i]) p[++l] = i, phi[i] = i - 1;
        Rep(j,1,l){
            int k = p[j] * i;
            if (k > MAX) break;
            a[k] = 1;
            if (i % p[j]) phi[k] = (p[j] - 1) * phi[i];
            else{
                phi[k] = p[j] * phi[i];
                break;
            }
        }
    }
    phi[1] = 1, sum[0] = 0;
    Rep(i,1,MAX) sum[i] = (sum[i - 1] + phi[i]) % M;
}
 
map<int, int> S[N];
int calc(int n){
    if (n <= MAX) return sum[n];
    if (S[1].find(n) != S[1].end()) return S[1][n];
    int l = 2, r;
    int ans = ((1LL * n * (n + 1)) / 2) % M;
    while (l <= n){
        r = n / (n / l);
        ans -= 1LL * (r - l + 1) * calc(n / l) % M, ans %= M;
        l = r + 1;
    }
    return S[1][n] = ans;
}
 
int P[N], pm[N];
void init_p(){
    Rep(i,2,n){
        int tmp = i; pm[i] = 1;
        for(int j = 2; j * j <= tmp; j++) if (tmp % j == 0){
            P[i] = j, tmp /= j;
            while (tmp % j == 0) pm[i] *= j, tmp /= j;
            break;
        }
        if (P[i] == 0) P[i] = tmp;
        for(int j = 2; j * j <= tmp; j++) if (tmp % j == 0){
            P[i] = j;
            tmp /= j;
            while (tmp % j == 0) pm[i] *= j, tmp /= j;
        }
    }
}
 
int tl = 0;
int s(int a, int b){
    if (a == 0 || b == 0) return 0;
    if (a == 1) return calc(b);
    if (S[a].find(b) != S[a].end()) return S[a][b];
    if(pm[a] == 1){
        tl++;
        if (tl <= 1200000) 
            return S[a][b] = (1LL * (P[a] - 1) * s(a / P[a], b) % M + s(a, b / P[a])) % M;
        else return (1LL * (P[a] - 1) * s(a / P[a], b) % M + s(a, b / P[a])) % M;
    }
    else
        return 1LL * pm[a] * s(a / pm[a], b) % M;
}
 
int main(){
    scanf("%d%d",&n,&m);
    init_calc();
    init_p();
    int ans = 0;
    Rep(i,1,n) ans += s(i,m), ans %= M;
    if (ans < 0) ans += M;
    printf("%d\n",ans);
    return 0;
}
Problem3527

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define Rep(i,a) for(int i = 0; i < a; i++)
const int N = 262144 + 10;
using namespace std;
const double pi = acos(-1.0);
struct cp{
	double r, i;
};
cp operator + (const cp &a, const cp &b){
	return (cp){a.r + b.r, a.i + b.i};
}
cp operator - (const cp &a, const cp &b){
	return (cp){a.r - b.r, a.i - b.i};
}
cp operator * (const cp &a, const cp &b){
	return (cp){a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r};
}
int rev[N];
void init(int &n){
	int m = 1, l = 0;
	while (m < n) m <<= 1, l++;
	n = m;
	Rep(i,n){
		int t = 0, k = i;
		rep(j,1,l) t = (t << 1) | (k & 1), k >>= 1;
		rev[i] = t;
	}
}
void fft(cp *a, int l, int f){
	Rep(i,l) if (rev[i] < i) swap(a[rev[i]], a[i]);
	for(int n = 2; n <= l; n <<= 1){
		int mid = n >> 1;
		cp wn = (cp){cos(2.0 * pi * f / n), sin(2.0 * pi * f / n)};
		for(int i = 0; i < l; i += n){
			cp w = (cp){1, 0};
			Rep(j,mid){
				cp t1 = a[i + j], t2 = a[i + j + mid] * w;
				a[i + j] = t1 + t2;
				a[i + j + mid] = t1 - t2;
				w = w * wn;
			}
		}
	}
	if (f == -1) Rep(i,l) a[i].r /= l;
}
cp a[N], b[N], q[N];
double ans[N];
int main(){	
	int n; scanf("%d",&n);int t1 = n;
	Rep(i,n) scanf("%lf",&q[i].r), b[i] = q[i];
	
	n = n * 2 - 1;
	init(n);
	rep(i, 1, t1 - 1) a[i].r = (double)1.0 / i / i, a[i].i = 0;
	fft(a, n, 1);fft(q, n, 1);
	Rep(i,n) a[i] = a[i] * q[i];
	fft(a, n, -1);
	Rep(i,t1) ans[i] = a[i].r;

	Rep(i,n) a[i].r = a[i].i = 0;
	Rep(i,n) q[i].r = q[i].i = 0;

	Rep(i,t1) q[i] = b[i];
	Rep(i,t1) if (t1 - 1 - i < i) swap(q[i], q[t1 - 1 - i]);
	rep(i, 1, t1 - 1) a[i].r = (double)1.0 / i / i, a[i].i = 0;
	fft(a, n, 1); fft(q, n, 1);
	Rep(i,n) a[i] = a[i] * q[i];
	fft(a, n, -1);
	Rep(i,t1) if (t1 - 1 - i < i) swap(a[i], a[t1 - 1 - i]);

	Rep(i,t1) ans[i] -= a[i].r;
	Rep(i,t1) printf("%.3lf\n",ans[i]);
	return 0;
}
Problem3529

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
const int N=100100,Mod=0x7fffffff;
struct querry{
	int n,m,pos;
	LL a;
}q[20010];
struct G{
	LL pos,val;
}g[N];
bool cmpq(const querry &a,const querry &b){
	return a.a<b.a;
}
bool cmp(const G &a,const G &b){
	return a.val<b.val;
}
bool a[N];
int p[N],l=0;
LL c1[N],c2[N];
LL miu[N];
LL ans[N];
void init(){
	memset(a,true,sizeof(a));
	g[1]=(G){1,1};miu[1]=1;
	rep(i,2,100000){
		g[i].pos=i;
		if (a[i]){
			p[++l]=i;
			g[i].val=i+1;
			c1[i]=1;
			c2[i]=i;
			miu[i]=-1;
		}
		rep(j,1,l){
			int k=p[j]*i;
			if (k>100000) break;
			a[k]=false;
			if (i % p[j]==0){
				c1[k]=c1[i];
				c2[k]=c2[i]*p[j];
				g[k].val=g[i].val+c1[k]*c2[k];
				miu[k]=0;
				break;
			}else{
				g[k].val=g[i].val*(p[j]+1);
				c1[k]=g[i].val;
				c2[k]=p[j];
				miu[k]=-miu[i];
			}
		}
	}
	//rep(i,1,20) cout <<g[i].val<<" "<<miu[i]<<"\n";
}
struct BIT{
	LL s[N];
	BIT(){
		memset(s,0,sizeof(s));
	}
	inline int lowbit(int x){
		return x & (-x);
	}
	inline void add(int x,LL d){
		while (x<=N){
			s[x]+=d;
			x+=lowbit(x);
		}
	}
	inline LL sum(int x){
		LL ans=0;
		while (x>0){
			ans+=s[x];
			x-=lowbit(x);
		}
		return ans;
	}
}f;
int main(){
	int Q;scanf("%d",&Q);
	rep(i,1,Q) scanf("%d%d%lld",&q[i].n,&q[i].m,&q[i].a),q[i].pos=i;
	sort(q+1,q+Q+1,cmpq);
	init();
	sort(g+1,g+100001,cmp);
	int j=1;
	rep(i,1,Q){
		for(;g[j].val <= q[i].a && j<=100000;j++){
			int t=g[j].pos;
			for(int k=1;k*t<=100000;k++) f.add(k*t,miu[k]*g[j].val);
		}
		int r;
		LL tmp=0;
		int n=q[i].n,m=q[i].m;
		for (int l=1;l<=n && l<=m;l=r+1){
			r=min(n/(n/l),m/(m/l));
			tmp+=(f.sum(r)-f.sum(l-1))*(LL)(n/l)*(LL)(m/l);
		}
		ans[q[i].pos]=tmp;
	}
	rep(i,1,Q) printf("%d\n",ans[i] & 0x7fffffff);
}

/*
	Debug: BIT ans要初始化清0
*/
Problem3530

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
struct node{
	node *ch[10],*f;
	int v;
}T[1600],*rt=&T[0],*q[1600];
int l=0;
node *nn(){
	return &T[++l];
}
#define oc o->ch[c[i]-'0']
void ins(char *c){
	int n=strlen(c);node *o=rt;
	rep(i,0,n-1) {if (!oc) oc=nn();o=oc;}
	o->v=1;
}
#define xc x->ch[i]
#define xf x->f
#define xcf xc->f
void clac(){
	int l=0,r=0;node *x=rt;rt->f=rt;
	rep(i,0,9) if (!xc) xc=rt; else q[r++]=xc,xcf=rt;
	while (l<r){
		x=q[l++];
		rep(i,0,9) if (!xc) xc=xf->ch[i]; else
			q[r++]=xc, xcf=xf->ch[i], xc->v = (xc->v) || (xcf->v);
	}
}
char s[1600],c[1600];
int f[1600][1600],g[1600][1600];
#define si (s[i]-'0')
#define tc ((T[j].ch[k])-T)
const int M=1000000007;
#define Mod(a) if (a>M) a-=M;
int main(){
	scanf("%s",s);int n=strlen(s);
	int m;scanf("%d",&m);
	rep(i,1,m){
		scanf("%s",c);ins(c);
	}
	clac();
	node *ss=nn();
	rep(i,1,9) ss->ch[i]=rt->ch[i];
	ss->ch[0]=ss;
	f[0][l]=1;
	rep(i,0,n-1) 
		rep(j,0,l)if (!T[j].v) {
			f[i+1][(T[j].ch[si])-T]+=f[i][j];
			Mod(f[i+1][(T[j].ch[si])-T]);
			rep(k,0,9){
				g[i+1][tc]+=g[i][j];Mod(g[i+1][tc]);
				if (k<si) {g[i+1][tc]+=f[i][j];Mod(g[i+1][tc]);}
			}
		}
	int ans=-1;
	rep(j,0,l) if (!T[j].v) 
			{ans+=f[n][j];Mod(ans);ans+=g[n][j];Mod(ans);}
	if (ans<0) ans=0;Mod(ans);
	printf("%d\n",ans);
	return 0;
}
Problem3579

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 1010, M = 1000003;
int d[N], c[N][N];
void work(){
	int n,m; 
	scanf("%d%d",&n,&m);
	
	rep(i,1,n) d[i] = 0;
	rep(i,1,m){
		int x, y;
		scanf("%d%d",&x,&y);
		d[x]++, d[y]++;
	}

	sort(d+1, d+n+1);
	rep(i,1,n/2) swap(d[i], d[n - i + 1]);

	rep(i,1,n){
		c[i][0] = c[i][i] = 1;
		rep(j,1,i - 1) c[i][j] = c[i - 1][j] +c[i - 1][j - 1], c[i][j] %= M;
	}

	d[0] = -1;
	int ans = 0;
	rep(i,1,n) if (d[i] != d[i-1]){
		int sum1 = 0, sum2 = 0, cnt1 = 0, cnt = 0;
		rep(j,1,n)
	 		if (d[j] > d[i]) sum1 += d[j], cnt1++;
	 		else if (d[j] < d[i]) sum2 += d[j];
	 		else cnt++;
		rep(j,1,cnt){
			if (cnt1 + j == n) break;
			if (sum1 + d[i] * j - sum2 - d[i] * (cnt - j) == (cnt1 + j) * (cnt1 + j - 1)) ans += c[cnt][j], ans %= M;
		}
	}
	printf("%d\n",ans);
}
int main(){
	int T; 
	scanf("%d",&T);
	while (T--) work();
}
Problem3580

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;

const int N = 1000000 + 10;

int a[N], s[N], n, b[N];
LL k;
void add(int x){
	for(;x <= n;x += (-x) & x) s[x]++;
}
int sum(int x){
	int ans = 0;
	for(;x;x -= (-x) & x) ans += s[x];
	return ans;
}

int up[N];
int main(){
	scanf("%d%lld",&n,&k);
	rep(i,1,n) scanf("%d",&a[i]), s[i] = 0;
	LL Sum = 0;
	rep(i,1,n){
		up[i] = (i - 1) - sum(a[i]), Sum += up[i];
		add(a[i]);
	}
	if (Sum < k) {printf("Impossible!\n");return 0;}

	int l = 0, r = n;//[l,r)
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		LL cnt = 0;
		rep(i,1,n) cnt += min(mid, up[i]);
		if (cnt <= k) l = mid; else r = mid;
	}
	LL cnt = k;
	rep(i,1,n) cnt -= min(l, up[i]);
	rep(i,1,n) if (up[i] >= l){
		b[i - l] = a[i];
		a[i] = n + 1;
	}
	sort(a + 1, a + n + 1);
	int j = 1;
	rep(i,1,n) if (!b[i]) b[i] = a[j++];
	rep(j,1,n - l){
		if (!cnt) break;
		if (b[j] > b[j + 1]) swap(b[j], b[j + 1]), cnt--;
	}
	rep(i,1,n - 1) printf("%d ", b[i]);
	printf("%d\n",b[n]);
	return 0;
}
Problem3580

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;

const int N = 1000000 + 10;

int a[N], s[N], n, b[N];
LL k;
void add(int x){
	for(;x <= n;x += (-x) & x) s[x]++;
}
int sum(int x){
	int ans = 0;
	for(;x;x -= (-x) & x) ans += s[x];
	return ans;
}

int up[N];
int main(){
	scanf("%d%lld",&n,&k);
	rep(i,1,n) scanf("%d",&a[i]), s[i] = 0;
	rep(i,1,n)
		up[i] = (i - 1) - sum(a[i]), add(a[i]);

	int l = -1, r = n + 1;//(l,r]
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		LL cnt = 0;
		rep(i,1,n) cnt += min(mid, up[i]);
		if (cnt >= k) r = mid; else l = mid;
	}
	if (l == n) {printf("Impossible!\n");return 0;}

	LL cnt = k;
	rep(i,1,n) cnt -= min(l, up[i]);
	rep(i,1,n) if (up[i] >= l){
		b[i - l] = a[i];
		a[i] = n + 1;
	}
	sort(a + 1, a + n + 1);
	int j = 1;
	rep(i,1,n) if (!b[i]) b[i] = a[j++];
	rep(j,1,n - l){
		if (!cnt) break;
		if (b[j] > b[j + 1]) swap(b[j], b[j + 1]), cnt--;
	}
	rep(i,1,n - 1) printf("%d ", b[i]);
	printf("%d\n",b[n]);
	return 0;
}
Problem3583

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

const int N = 1000 + 10, K = 20 + 5, M = 1000000007;

int n, k;

struct mat{
	int a[K][K];
};
mat w;
mat operator + (const mat &a, const mat &b){
	rep(i, 1, k) rep(j, 1, k) w.a[i][j] = (a.a[i][j] + b.a[i][j]) % M;
	return w;
}
mat operator * (const mat &a, const mat &b){
	rep(i, 1, k) rep(j, 1, k) w.a[i][j] = 0;
	rep(i, 1, k) rep(j, 1, k){
		w.a[i][j] = 0;
		rep(t, 1, k) w.a[i][j] = (w.a[i][j] + 1LL * a.a[i][t] * b.a[t][j] % M) % M;
	}
	return w;
}

int A[N][K], B[K][N], BA[K][K];

mat f[32], g[32];
void init(){
	rep(i,1,k) rep(j,1,k){
		BA[i][j] = 0;
		rep(t,1,n) BA[i][j] += 1LL * B[i][t] * A[t][j] % M, BA[i][j] %= M;
	}

	rep(i,1,k) rep(j,1,k) f[0].a[i][j] = g[0].a[i][j] = BA[i][j];

	rep(i,1,31){
		f[i] = f[i - 1] * f[i - 1];
		g[i] = g[i - 1] * f[i - 1] + g[i - 1];
	}
}

mat tmp, ans;
int a1[N][N], a2;
int main(){
	scanf("%d%d",&n,&k);
	rep(i, 1, n){
		rep(j, 1, k) scanf("%d",&A[i][j]);
		rep(j, 1, k) scanf("%d",&B[j][i]);
	}
	init();
	int m; scanf("%d",&m);
	rep(i, 1, m){
		int a, b, d; scanf("%d%d%d", &a, &b, &d);
		if (d == 0) printf("%d\n",(a == b) ? 1 : 0); else{
			rep(i,1,k) rep(j,1,k) tmp.a[i][j] = (i == j);
			rep(i,1,k) rep(j,1,k) ans.a[i][j] = 0;
			dep(j,31,0) if ((d - 1) >> j & 1){
				ans = ans + (tmp * g[j]);
				tmp = tmp * f[j];
			}

			rep(i,1,k) rep(j,1,k) ans.a[i][j]+=(i==j), ans.a[i][j] %= M;

			rep(i,1,n) rep(j,1,k){
				a1[i][j] = 0;
				rep(t,1,k) a1[i][j] = (a1[i][j] + 1LL * A[i][t] * ans.a[t][j] % M) % M;
			}

			a2 = (a == b);
			rep(t,1,k) a2 = (a2 + 1LL * a1[a][t] * B[t][b] % M) % M;

			printf("%d\n", a2);
		}
	}
	return 0;
}
Problem3585

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
Problem3586

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 8 + 10, L = 6 + 10;


struct node{
	node *ch[10], *f; 
	int v;
}T[N * L], *root;
int l;
node *nn(){
	l++;
	rep(i,0,9) T[l].ch[i] = NULL;
	T[l].f = NULL;T[l].v = 0;
	return &T[l];
}
#define oc o->ch[c[i] - 'a']
void ins(char *c, int t){
	node *o = root;
	int l = strlen(c);
	rep(i,0,l - 1) {if (!oc) oc = nn(); o = oc;}
	o->v = 1 << t;
}
node *q[N * L];
#define xc x->ch[i]
#define xcf xc->f
#define xf x->f
int n, l1, t1;
void build(){
	int l = 0, r = 0;
	node *x = root;
	rep(i,0,t1 - 1) if (xc) q[r++] = xc, xcf = root; else xc = root;
	while (l < r){
		node *x = q[l++];
		rep(i,0,t1 - 1) if (!xc) xc = xf->ch[i]; else 
			q[r++] = xc, xcf = xf->ch[i];
	}
}

char s[10];
int p[10];

typedef long double ld;
struct equ{
	ld x[N * L];
}e[N * L];

ld E[N * L][256 + 10];
void sol_equ(){
	rep(i,0,l){
		int t = i;
		rep(j,i + 1, l)
			if (fabs(e[j].x[i]) > fabs(e[t].x[i])) t = j;
		swap(e[i], e[t]);
		rep(j,i + 1, l){
			double f = e[j].x[i] / e[i].x[i];
			rep(k,i,l + 1) e[j].x[k] -= e[i].x[k] * f;
		}
	}
	dep(i,l,0){
		rep(k, i + 1, l) e[i].x[l + 1] -= e[k].x[l + 1] * e[i].x[k];
		e[i].x[l + 1] /= e[i].x[i];
	}
}
void calc(int t){
	rep(i,0,l) rep(j,0,l) e[i].x[j] = 0;
	rep(i,0,l)if ((T[i].v & t) == 0 && T[i].v){
		e[i].x[i] = 1, e[i].x[l + 1] = E[i][t ^ T[i].v];
	}else {
		e[i].x[i] = 1;
		rep(j,0,t1 - 1) e[i].x[T[i].ch[j] - T] -= (long double) p[j] / 10000.0; //j may appear twice or more times
		e[i].x[l + 1] = 1;
	}
	sol_equ();
	rep(i,0,l) E[i][t] = e[i].x[l + 1];
}
void work(){
	l = 0;
	scanf("%d%d%d",&n,&l1,&t1);
	root = &T[0]; rep(i,0,t1) root->ch[i] = NULL; root->f = root; root->v = 0;
	rep(i,0,n - 1) scanf("%s",s), ins(s, i);
	build();
	rep(i,0,t1 - 1) scanf("%d",&p[i]);
	rep(i,0,l) E[(1 << n) - 1][i] = 0;
	dep(i,(1 << n) - 2,0) calc(i);
	printf("%.10Lf\n",E[0][0]);
}
int main(){
	int c; scanf("%d",&c);
	while (c--) work();
}
Problem3586

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 8 + 1, L = 6 + 1;


struct node{
	node *ch[10], *f; 
	int v;
}T[N * L], *root;
int l;
node *nn(){
	l++;
	rep(i,0,9) T[l].ch[i] = NULL;
	T[l].f = NULL;T[l].v = 0;
	return &T[l];
}
#define oc o->ch[c[i] - 'a']
void ins(char *c, int t){
	node *o = root;
	int l = strlen(c);
	rep(i,0,l - 1) {if (!oc) oc = nn(); o = oc;}
	o->v = 1 << t;
}
node *q[N * L];
#define xc x->ch[i]
#define xcf xc->f
#define xf x->f
int n, l1, t1;
void build(){
	int l = 0, r = 0;
	node *x = root;
	rep(i,0,t1 - 1) if (xc) q[r++] = xc, xcf = root; else xc = root;
	while (l < r){
		node *x = q[l++];
		rep(i,0,t1 - 1) if (!xc) xc = xf->ch[i]; else 
			q[r++] = xc, xcf = xf->ch[i];
	}
}

char s[10];
int p[10];

typedef long double ld;
struct equ{
	ld x[N * L + 1000];
}e[N * L + 1000];

ld E[N * L + 1000][256 + 10];
void sol_equ(){
	rep(i,0,l){
		int t = i;
		rep(j,i + 1, l)
			if (fabs(e[j].x[i]) > fabs(e[t].x[i])) t = j;
		swap(e[i], e[t]);
		rep(j,i + 1, l){
			double f = e[j].x[i] / e[i].x[i];
			rep(k,i,l + 1) e[j].x[k] -= e[i].x[k] * f;
		}
	}
	dep(i,l,0){
		rep(k, i + 1, l) e[i].x[l + 1] -= e[k].x[l + 1] * e[i].x[k];
		e[i].x[l + 1] /= e[i].x[i];
	}
}
void calc(int t){
	rep(i,0,l) rep(j,0,l) e[i].x[j] = 0;
	rep(i,0,l)if ((T[i].v & t) == 0 && T[i].v){
		e[i].x[i] = 1, e[i].x[l + 1] = E[i][t ^ T[i].v];
	}else {
		e[i].x[i] = 1;
		rep(j,0,t1 - 1) e[i].x[T[i].ch[j] - T] -= (long double) p[j] / 10000.0; //j may appear twice or more times
		e[i].x[l + 1] = 1;
	}
	sol_equ();
	rep(i,0,l) E[i][t] = e[i].x[l + 1];
}
void work(){
	l = 0;
	scanf("%d%d%d",&n,&l1,&t1);
	root = &T[0]; rep(i,0,t1) root->ch[i] = NULL; root->f = root; root->v = 0;
	rep(i,0,n - 1) scanf("%s",s), ins(s, i);
	build();
	rep(i,0,t1 - 1) scanf("%d",&p[i]);
	rep(i,0,l) E[(1 << n) - 1][i] = 0;
	dep(i,(1 << n) - 2,0) calc(i);
	printf("%.10Lf\n",E[0][0]);
}
int main(){
	int c; scanf("%d",&c);
	while (c--) work();
}
Problem3586

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 8 + 1, L = 6 + 1;


struct node{
	node *ch[10], *f; 
	int v;
}T[N * L], *root;
int l;
node *nn(){
	l++;
	rep(i,0,9) T[l].ch[i] = NULL;
	T[l].f = NULL;T[l].v = 0;
	return &T[l];
}
#define oc o->ch[c[i] - 'a']
void ins(char *c, int t){
	node *o = root;
	int l = strlen(c);
	rep(i,0,l - 1) {if (!oc) oc = nn(); o = oc;}
	o->v = 1 << t;
}
node *q[N * L];
#define xc x->ch[i]
#define xcf xc->f
#define xf x->f
int n, l1, t1;
void build(){
	int l = 0, r = 0;
	node *x = root;
	rep(i,0,t1 - 1) if (xc) q[r++] = xc, xcf = root; else xc = root;
	while (l < r){
		node *x = q[l++];
		rep(i,0,t1 - 1) if (!xc) xc = xf->ch[i]; else 
			q[r++] = xc, xcf = xf->ch[i];
	}
}

char s[10];
int p[10];

typedef long double ld;
struct equ{
	ld x[N * L + 100];
}e[N * L + 100];

ld E[N * L + 1000][256 + 10];
void sol_equ(){
	rep(i,0,l){
		int t = i;
		rep(j,i + 1, l)
			if (fabs(e[j].x[i]) > fabs(e[t].x[i])) t = j;
		swap(e[i], e[t]);
		rep(j,i + 1, l){
			double f = e[j].x[i] / e[i].x[i];
			rep(k,i,l + 1) e[j].x[k] -= e[i].x[k] * f;
		}
	}
	dep(i,l,0){
		rep(k, i + 1, l) e[i].x[l + 1] -= e[k].x[l + 1] * e[i].x[k];
		e[i].x[l + 1] /= e[i].x[i];
	}
}
void calc(int t){
	rep(i,0,l) rep(j,0,l) e[i].x[j] = 0;
	rep(i,0,l)if ((T[i].v & t) == 0 && T[i].v){
		e[i].x[i] = 1, e[i].x[l + 1] = E[i][t ^ T[i].v];
	}else {
		e[i].x[i] = 1;
		rep(j,0,t1 - 1) e[i].x[T[i].ch[j] - T] -= (long double) p[j] / 10000.0; //j may appear twice or more times
		e[i].x[l + 1] = 1;
	}
	sol_equ();
	rep(i,0,l) E[i][t] = e[i].x[l + 1];
}
void work(){
	l = 0;
	scanf("%d%d%d",&n,&l1,&t1);
	root = &T[0]; rep(i,0,t1) root->ch[i] = NULL; root->f = root; root->v = 0;
	rep(i,0,n - 1) scanf("%s",s), ins(s, i);
	build();
	rep(i,0,t1 - 1) scanf("%d",&p[i]);
	rep(i,0,l) E[(1 << n) - 1][i] = 0;
	dep(i,(1 << n) - 2,0) calc(i);
	printf("%.10Lf\n",E[0][0]);
}
int main(){
	int c; scanf("%d",&c);
	while (c--) work();
}
Problem3586

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 8 + 1, L = 6 + 1;


struct node{
	node *ch[10], *f; 
	int v;
}T[N * L], *root;
int l;
node *nn(){
	l++;
	rep(i,0,9) T[l].ch[i] = NULL;
	T[l].f = NULL;T[l].v = 0;
	return &T[l];
}
#define oc o->ch[c[i] - 'a']
void ins(char *c, int t){
	node *o = root;
	int l = strlen(c);
	rep(i,0,l - 1) {if (!oc) oc = nn(); o = oc;}
	o->v = 1 << t;
}
node *q[N * L];
#define xc x->ch[i]
#define xcf xc->f
#define xf x->f
int n, l1, t1;
void build(){
	int l = 0, r = 0;
	node *x = root;
	rep(i,0,t1 - 1) if (xc) q[r++] = xc, xcf = root; else xc = root;
	while (l < r){
		node *x = q[l++];
		rep(i,0,t1 - 1) if (!xc) xc = xf->ch[i]; else 
			q[r++] = xc, xcf = xf->ch[i];
	}
}

char s[10];
int p[10];

typedef long double ld;
struct equ{
	ld x[N * L];
}e[N * L];

ld E[N * L + 1000][256 + 10];
void sol_equ(){
	rep(i,0,l){
		int t = i;
		rep(j,i + 1, l)
			if (fabs(e[j].x[i]) > fabs(e[t].x[i])) t = j;
		swap(e[i], e[t]);
		rep(j,i + 1, l){
			double f = e[j].x[i] / e[i].x[i];
			rep(k,i,l + 1) e[j].x[k] -= e[i].x[k] * f;
		}
	}
	dep(i,l,0){
		rep(k, i + 1, l) e[i].x[l + 1] -= e[k].x[l + 1] * e[i].x[k];
		e[i].x[l + 1] /= e[i].x[i];
	}
}
void calc(int t){
	rep(i,0,l) rep(j,0,l) e[i].x[j] = 0;
	rep(i,0,l)if ((T[i].v & t) == 0 && T[i].v){
		e[i].x[i] = 1, e[i].x[l + 1] = E[i][t ^ T[i].v];
	}else {
		e[i].x[i] = 1;
		rep(j,0,t1 - 1) e[i].x[T[i].ch[j] - T] -= (long double) p[j] / 10000.0; //j may appear twice or more times
		e[i].x[l + 1] = 1;
	}
	sol_equ();
	rep(i,0,l) E[i][t] = e[i].x[l + 1];
}
void work(){
	l = 0;
	scanf("%d%d%d",&n,&l1,&t1);
	root = &T[0]; rep(i,0,t1) root->ch[i] = NULL; root->f = root; root->v = 0;
	rep(i,0,n - 1) scanf("%s",s), ins(s, i);
	build();
	rep(i,0,t1 - 1) scanf("%d",&p[i]);
	rep(i,0,l) E[(1 << n) - 1][i] = 0;
	dep(i,(1 << n) - 2,0) calc(i);
	printf("%.10Lf\n",E[0][0]);
}
int main(){
	int c; scanf("%d",&c);
	while (c--) work();
}
Problem3586

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 8 + 1, L = 6 + 1;


struct node{
	node *ch[10], *f; 
	int v;
}T[N * L], *root;
int l;
node *nn(){
	l++;
	rep(i,0,9) T[l].ch[i] = NULL;
	T[l].f = NULL;T[l].v = 0;
	return &T[l];
}
#define oc o->ch[c[i] - 'a']
void ins(char *c, int t){
	node *o = root;
	int l = strlen(c);
	rep(i,0,l - 1) {if (!oc) oc = nn(); o = oc;}
	o->v = 1 << t;
}
node *q[N * L];
#define xc x->ch[i]
#define xcf xc->f
#define xf x->f
int n, l1, t1;
void build(){
	int l = 0, r = 0;
	node *x = root;
	rep(i,0,t1 - 1) if (xc) q[r++] = xc, xcf = root; else xc = root;
	while (l < r){
		node *x = q[l++];
		rep(i,0,t1 - 1) if (!xc) xc = xf->ch[i]; else 
			q[r++] = xc, xcf = xf->ch[i];
	}
}

char s[10];
int p[10];

typedef long double ld;
struct equ{
	ld x[N * L];
}e[N * L];

ld E[N * L][256];
void sol_equ(){
	rep(i,0,l){
		int t = i;
		rep(j,i + 1, l)
			if (fabs(e[j].x[i]) > fabs(e[t].x[i])) t = j;
		swap(e[i], e[t]);
		rep(j,i + 1, l){
			double f = e[j].x[i] / e[i].x[i];
			rep(k,i,l + 1) e[j].x[k] -= e[i].x[k] * f;
		}
	}
	dep(i,l,0){
		rep(k, i + 1, l) e[i].x[l + 1] -= e[k].x[l + 1] * e[i].x[k];
		e[i].x[l + 1] /= e[i].x[i];
	}
}
void calc(int t){
	rep(i,0,l) rep(j,0,l) e[i].x[j] = 0;
	rep(i,0,l)if ((T[i].v & t) == 0 && T[i].v){
		e[i].x[i] = 1, e[i].x[l + 1] = E[i][t ^ T[i].v];
	}else {
		e[i].x[i] = 1;
		rep(j,0,t1 - 1) e[i].x[T[i].ch[j] - T] -= (long double) p[j] / 10000.0; //j may appear twice or more times
		e[i].x[l + 1] = 1;
	}
	sol_equ();
	rep(i,0,l) E[i][t] = e[i].x[l + 1];
}
void work(){
	l = 0;
	scanf("%d%d%d",&n,&l1,&t1);
	root = &T[0]; rep(i,0,t1) root->ch[i] = NULL; root->f = root; root->v = 0;
	rep(i,0,n - 1) scanf("%s",s), ins(s, i);
	build();
	rep(i,0,t1 - 1) scanf("%d",&p[i]);
	rep(i,0,l) E[i][(1 << n) - 1] = 0;
	dep(i,(1 << n) - 2,0) calc(i);
	printf("%.10Lf\n",E[0][0]);
}
int main(){
	int c; scanf("%d",&c);
	while (c--) work();
}
Problem3588

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 800 + 10, M = 1000000007;
char a[N], b[N];
int A[N], B[N], tmp[N], lena, lenb, t;
void init(){
	scanf("%s%s",a,b);
	rep(i,0,N - 1) A[i] = B[i] = 0;
	lena = strlen(a), lenb = strlen(b);
	rep(i,0,lena - 1) A[lena - 1 - i] = a[i] - '0';
	rep(i,0,lenb - 1) B[lenb - 1 - i] = b[i] - '0';
	int j = 0;
	rep(i,0,lena - 1){
		A[i] += j;
		j = A[i] >> 1;
		A[i] &= 1;
	}
	while (j) A[lena++] = j & 1, j >>= 1;
}
int f[N][11][2];
void work(){
	init();
	rep(i,0,lena) rep(j,0,9) f[i][j][0] = f[i][j][1] = 0;
	if (lenb > lena) 
		f[lena][0][0] = 1;
	else 
		f[lena][0][1] = 1;

	dep(i,lena - 1,0){
		rep(j, 0, 9){
			rep(k, 0, 9){
				int t = j * 2 + A[i] - k;
				if (t < 0) break;
				if (t > 9) t = 9;
				if (k == B[i]) f[i][t][1] += f[i + 1][j][1], f[i][t][1] %= M;
				f[i][t][0] += f[i + 1][j][0], f[i][t][0] %= M;
				if (k < B[i]) f[i][t][0] += f[i + 1][j][1], f[i][t][0] %= M;
			}
		}
		//rep(j,0,9) cout <<i<<' '<<j<<' '<<f[i][j][0]<<' '<<f[i][j][1]<<' '<<endl;cout <<endl;
	}

	int ans = 0;
	rep(i,0,9) ans += f[0][i][0], ans %= M, ans += f[0][i][1], ans %= M;
	printf("Case #%d: %d\n",t,ans);
}
int main(){
	int m;
	scanf("%d",&m);
	while (t < m) t++, work();
}
Problem3588

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 800 + 10, M = 1000000007;
char a[N], b[N];
int A[N], B[N], tmp[N], lena, lenb, t;
void init(){
	scanf("%s%s",a,b);
	lena = strlen(a), lenb = strlen(b);
	int l = max(lena, lenb);
	rep(i,0,l) A[i] = B[i] = 0;
	rep(i,0,lena - 1) A[lena - 1 - i] = a[i] - '0';
	rep(i,0,lenb - 1) B[lenb - 1 - i] = b[i] - '0';
	int j = 0;
	rep(i,0,lena - 1){
		A[i] += j;
		j = A[i] >> 1;
		A[i] &= 1;
	}
	while (j) A[lena++] = j & 1, j >>= 1;
}
int f[N][11][2];
void work(){
	init();
	rep(i,0,lena) rep(j,0,9) f[i][j][0] = f[i][j][1] = 0;
	if (lenb > lena) 
		f[lena][0][0] = 1;
	else 
		f[lena][0][1] = 1;

	dep(i,lena - 1,0){
		rep(j, 0, 9){
			rep(k, 0, 9){
				int t = j * 2 + A[i] - k;
				if (t < 0) break;
				if (t > 9) t = 9;
				if (k == B[i]) f[i][t][1] += f[i + 1][j][1], f[i][t][1] %= M;
				f[i][t][0] += f[i + 1][j][0], f[i][t][0] %= M;
				if (k < B[i]) f[i][t][0] += f[i + 1][j][1], f[i][t][0] %= M;
			}
		}
		//rep(j,0,9) cout <<i<<' '<<j<<' '<<f[i][j][0]<<' '<<f[i][j][1]<<' '<<endl;cout <<endl;
	}

	int ans = 0;
	rep(i,0,9) ans += f[0][i][0], ans %= M, ans += f[0][i][1], ans %= M;
	printf("Case #%d: %d\n",t,ans);
}
int main(){
	int m;
	scanf("%d",&m);
	while (t < m) t++, work();
}
Problem3589

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N = 300000 + 10;
struct edge{
	int to, pre;
}e[N * 2];
#define reg(i,a) for(int i=u[a]; i; i = e[i].pre)
#define v e[i].to
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
int fa[N], s[N], son[N], dep[N];
void dfs(int x, int f){
	s[x] = 1, son[x] = 0;
	reg(i,x) if (v != f){
		dep[v] = dep[x] + 1;
		fa[v] = x;
		dfs(v, x);
		s[x] += s[v];
		if (s[v] > s[son[x]]) son[x] = v;
	}
}
int pre[N], dfs_clock = 0, top[N], ed[N];
void dfs1(int x, int f){
	pre[x] = ++dfs_clock;
	if (son[x]) top[son[x]] = top[x], dfs1(son[x], x);
	reg(i,x) if (v != f && v != son[x]) 
		top[v] = v, dfs1(v, x);
	ed[x] = dfs_clock;
}

int S[N * 4], tag[N * 4];
#define mid ((l + r) >> 1)
#define lc  (x << 1)
#define rc  (lc + 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
void push(int x, int l, int r){
	if (tag[x]){
		if (l < r) tag[lc] += tag[x], tag[rc] += tag[x];
		S[x] += (r - l + 1) * tag[x], tag[x] = 0;	
	}
}
void upd(int x){
	S[x] = S[lc] + S[rc];
}
void add(int x, int l, int r, int a, int b, int d){
	if (a <= l && r <= b) {tag[x] += d, push(x, l, r);return;}
	push(x, l, r);
	if (a <= mid) add(lcq, a, b, d); else push(lcq);
	if (b >  mid) add(rcq, a, b, d); else push(rcq);
	upd(x);
}
int qry(int x, int l, int r, int a, int b){
	push(x, l, r);
	if (a <= l && r <= b) return S[x];
	int ans = 0;
	if (a <= mid) ans += qry(lcq, a, b);
	if (b >  mid) ans += qry(rcq, a, b);
	return ans;
}
typedef pair<int, int> node;
node q[N];
#define mp(a,b) make_pair(a,b)
int ql, ans = 0;
void Qry(int a, int b){
	int ta = top[a], tb = top[b];
	while (ta != tb){
		if (dep[ta] < dep[tb]) swap(a,b), swap(ta, tb);
		q[++ql] = mp(pre[ta], pre[a]);
		a = fa[ta], ta = top[a];
	}
	if (dep[a] > dep[b]) swap(a, b);
	q[++ql] = mp(pre[a], pre[b]);
}
int n;
void calc(){
	ans = 0;
	sort(q + 1, q + ql + 1);
	int t = q[1].first, mx = q[1].second;
	rep(i,2,ql) if (q[i].first > mx + 1){
		ans += qry(1, 1, n, t, mx);
		t = q[i].first, mx = q[i].second;
	}else mx = max(q[i].second, mx);
	ans += qry(1, 1, n, t, mx);
	//cout <<ql<<endl;
	//rep(i,1,ql) cout <<q[i].first<<' '<<q[i].second<<endl;
	//cout <<endl;
}
int main(){
	scanf("%d",&n);
	rep(i,1,n - 1){
		int a, b; scanf("%d%d",&a,&b);
		ins(a, b), ins(b, a);
	}
	fa[1] = 0, dep[1] = 1, dfs(1, 0);
	top[1] = 1, dfs1(1, 0);
	int Q; scanf("%d",&Q);
	rep(i,1,Q){
		int op; scanf("%d",&op);
		if (op == 0){
			int u, d; scanf("%d%d",&u,&d);
			add(1, 1, n, pre[u], ed[u], d);
		}else{
			ql = 0;
			int k; scanf("%d",&k);
			rep(i,1,k){
				int a, b; scanf("%d%d",&a,&b);
				Qry(a, b);
			}
			calc();
			printf("%d\n",ans & 2147483647);
		}
	}
	return 0;
}
Problem3594

{考虑每次拔高[i,j]
一定不比[i,n]更优
于是我们考虑拔高[i,n]
f[i,j]表示拔高j次之后以i结尾的最长不下降子序列长度
拔高[i,n] 此时第i个的高度为h[i]+j 然后考虑前一个是什么？
假如是k 应该有h[k]+t<=h[i]+j
f[i,j]=max(f[k,t]| ① h[k]+t<=h[i]+j ② 1<=k<i ③1<=t<=j) 注意这里的查询是一个前缀可以直接上树状数组
对于比较容易达到的1<=k<i(它没有等于啊……) 
for i:=1 to n 维护即可
对于 ① ③ 使用二维树状数组来做}
var
 i,j,n,k,ans,max_h:longint;
 f,h:array[1..10000]of integer;
 bit:array[1..5500,1..10020]of integer;
procedure add(a,b,d:longint);
var
 t:longint;
begin 
 while a<=max_h+k do begin 
   t:=b;
   while t<=n+1 do begin
     if d>bit[a,t] then bit[a,t]:=d;   
     t:=t+t and (-t);
   end;
   a:=a+a and (-a);
 end;
end;
function max(a,b:longint):longint;
var
 t:longint;
begin 
 max:=0;
 while a>0 do begin 
   t:=b;
   while t>0 do begin 
     if bit[a,t]>max then max:=bit[a,t];
	 t:=t-t and (-t);
   end;
   a:=a-a and (-a);
 end;
end;
begin 
 readln(n,k);ans:=0;max_h:=0;
 for i:=1 to n do begin read(h[i]);if h[i]>max_h then max_h:=h[i];end;
 for i:=1 to n do begin 
    for j:=0 to k do begin 
	  f[j]:=max(h[i]+j,j+1)+1;if f[j]>ans then ans:=f[j];
	end;
	for j:=0 to k do add(h[i]+j,j+1,f[j]);
 end;
 writeln(ans);
end.
Problem3622

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
const int N = 2000 + 10, M = 1000000000 + 9;
using namespace std;

int a[N], b[N], f[N][N], frac[N], c[N][N], g[N];
int main(){
	int n, k; scanf("%d%d",&n,&k);
	k = (n + k) >> 1;
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) scanf("%d",&b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	c[0][0] = 1;
	rep(i,1,n){
		c[i][0] = c[i][i] = 1;
		rep(j,1,i-1) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % M;
	}
	int t = 0;
	f[0][0] = 1;
	rep(i,1,n){
		while (t < n && b[t + 1] < a[i]) t++;
		int ed = min(t, i);
		f[i][0] = f[i - 1][0];
		rep(j,1,ed)
			f[i][j] = (f[i - 1][j] + 1LL * f[i - 1][j - 1] * (t - (j - 1)) % M) % M;
	}
	frac[0] = 1;
	rep(i,1,n) frac[i] = 1LL * frac[i - 1] * i % M;
	rep(i,0,n) f[n][i] = 1LL * f[n][i] * frac[n - i] % M;
	int ans = 0;
	g[n] = f[n][n];
	dep(i,n - 1,0){
		g[i] = f[n][i];
		rep(j,i + 1, n) g[i] = (g[i] - 1LL * g[j] * c[j][i] % M + M) % M;
	}
	if (0 <= k && k <= n) ans = g[k]; else ans = 0;
	printf("%d\n",ans);
}
Problem3622

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
const int N = 2000 + 10, M = 1000000000 + 9;
using namespace std;

int a[N], b[N], f[N][N], frac[N], c[N][N], g[N];
int main(){
	int n, k; scanf("%d%d",&n,&k);
	k = (n + k) >> 1;
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) scanf("%d",&b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	c[0][0] = 1;
	rep(i,1,n){
		c[i][0] = c[i][i] = 1;
		rep(j,1,i-1) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % M;
	}
	int t = 0;
	f[0][0] = 1;
	rep(i,1,n){
		while (t < n && b[t + 1] < a[i]) t++;
		int ed = min(t, i);
		f[i][0] = f[i - 1][0];
		rep(j,1,ed)
			f[i][j] = (f[i - 1][j] + 1LL * f[i - 1][j - 1] * (t - (j - 1)) % M) % M;
	}
	frac[0] = 1;
	rep(i,1,n) frac[i] = 1LL * frac[i - 1] * i % M;
	rep(i,0,n) f[n][i] = 1LL * f[n][i] * frac[n - i] % M;
	int ans = 0;
	if (0 <= k && k <= n) 
		rep(i, k, n)
			ans = (ans + 1LL * (((i - k) & 1 == 1) ? -1 : 1) * c[i][k] * f[n][i] % M + M) % M;
	printf("%d\n",ans);
}
Problem3626

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
using namespace std;
const int N = 100010, M = 201314;
struct edge{
	int to, pre;
}e[N*2];
int u[N], l = 0;
void ins(int a, int b){
	e[++l] = (edge) {b, u[a]}, u[a] = l;
}
int sz[N], son[N], n, q;
void dfs(int x){
	sz[x] = 1, son[x] = n;
	reg(i,x){
		dfs(v), sz[x] += sz[v];
		if (sz[v] > sz[son[x]]) son[x] = v;
	}
}
int top[N], pre[N], dfs_clock = 0;
void build(int x){
	pre[x] = ++dfs_clock;
	if (son[x] < n) top[son[x]] = top[x], build(son[x]);
	reg(i,x) if (v != son[x]) top[v] = v, build(v);
}
struct query{
	int l,r,z;
	int ans;
}Q[N];
struct qry1{
	int x,z,f,t;
}q1[N*2];
bool cmp(const qry1 &a, const qry1 &b){
	return a.x < b.x;
}
#define lc (x << 1)
#define rc (lc + 1)
#define lcq lc,l,mid
#define rcq rc,mid+1,r
struct segment{
	int s[N * 4], tag[N * 4];//!
	segment(){
		rep(i,0,N-1) s[i] = tag[i] = 0;
	}
	void push(int x, int l, int r){
		s[x] += tag[x] * (r - l + 1) % M, s[x] %= M;
		if (l < r) tag[lc] += tag[x], tag[rc] += tag[x], tag[lc] %= M, tag[rc] %= M;
		tag[x] = 0;
	}
	void upd(int x){
		s[x] = (s[lc] + s[rc]) % M;
	}
	void add(int x, int l, int r, int a, int b){
		if (a <= l && b >= r) { 
			tag[x] ++, push(x, l, r);
			return;
		}
		push(x, l, r);//!
		int mid = (l + r) >> 1;
		if (a <= mid) add(lcq,a,b); else push(lcq);
		if (b >  mid) add(rcq,a,b); else push(rcq);
		upd(x);
	}
	int sum(int x, int l, int r, int a, int b){
		push(x, l, r);
		if (a <= l && b >= r) return s[x];
		int mid = (l + r) >> 1;
		int ans = 0;
		if (a <= mid) ans += sum(lcq,a,b);
		if (b >  mid) ans += sum(rcq,a,b);
		return ans % M;
	}
}s;
int f[N];
int qry(int x){
	int ans = 0;
	while (x + 1){
		int tx = top[x];
		ans += s.sum(1,1,n,pre[tx],pre[x]), ans %= M;
		x = f[tx];
	}
	return ans;
}
void add(int x){
	while (x + 1){
		int tx = top[x];
		s.add(1,1,n,pre[tx], pre[x]);
		x = f[tx];
	}
}
int main(){
	scanf("%d%d", &n, &q); f[0] = -1;
	rep(i,1,n-1) scanf("%d",&f[i]), ins(f[i],i);
	sz[n] = 0, dfs(0);
	top[0] = 0, build(0);
	rep(i,1,q) scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].z);
	rep(i,1,q) q1[(i << 1) - 1] = (qry1){Q[i].l - 1, Q[i].z, -1, i}, q1[i << 1] = (qry1){Q[i].r, Q[i].z, 1, i};
	sort(q1 + 1, q1 + q * 2 + 1, cmp);
	int j = 1;
	rep(i,0,n){
		while (j <= (q << 1) && q1[j].x == i - 1) Q[q1[j].t].ans += q1[j].f * qry(q1[j].z), j++;
		if (i < n) add(i);
	}
	rep(i,1,q) printf("%d\n",(Q[i].ans % M + M) % M);
	return 0;
}
Problem3631

var
 n,i,l,k,j,c:longint;
 a,u,v,dep,f,g,ans,h:array[1..600000]of longint;
 b:array[0..300000,0..20]of longint;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin
 i:=l;j:=r;m:=u[(l+r) shr 1];
 repeat
     while u[i]<m do inc(i);
     while u[j]>m do dec(j);
     if i<=j then begin
         t:=u[i];u[i]:=u[j];u[j]:=t;
         t:=v[i];v[i]:=v[j];v[j]:=t;
         inc(i);dec(j);
     end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
procedure dfs(x:longint);
var
 i:longint;
begin
  i:=h[x];
  while u[i]=x do begin
     if dep[v[i]]=0 then begin
         dep[v[i]]:=dep[x]+1;f[v[i]]:=x;dfs(v[i]);
     end;
     inc(i);
  end;
end;
function lca(u,v:longint):longint;
var 
 i,t:longint;
begin
 if dep[u]<dep[v] then begin 
     t:=u;u:=v;v:=t;
 end;
 for i:=l downto 0 do if (b[u,i]<>0) and (dep[b[u,i]]>=dep[v]) then u:=b[u,i];
 for i:=l downto 0 do
     if (b[u,i]<>b[v,i]) and (b[u,i]<>0) then begin 
	     u:=b[u,i];v:=b[v,i];
	 end;
 if u=v then exit(u) else exit(f[u]);
end;
procedure dfs2(x:longint);
var
 i:longint;
begin
  i:=h[x];ans[x]:=g[x];
  while u[i]=x do begin
     if dep[v[i]]>dep[x] then begin
         dfs2(v[i]);ans[x]:=ans[x]+ans[v[i]];
     end;
     inc(i);
  end;
end;
begin
 readln(n);
 for i:=1 to n do read(a[i]);readln;
 for i:=1 to n-1 do begin
     readln(u[i],v[i]);u[n+i-1]:=v[i];v[n+i-1]:=u[i];
 end;
 sort(1,2*(n-1));
 for i:=2*(n-1) downto 1 do h[u[i]]:=i;
 dep[1]:=1;f[1]:=0;dfs(1);
 l:=1;k:=2;
 while k<n do begin inc(l);k:=k shl 1;end;
 for i:=1 to n do b[i,0]:=f[i];
 for i:=1 to l do
     for j:=1 to n do
         if (b[j,i-1]<>0) and (b[b[j,i-1],i-1]<>0) then b[j,i]:=b[b[j,i-1],i-1];
 for i:=1 to n-1 do begin
     inc(g[a[i]]);inc(g[a[i+1]]);
     c:=lca(a[i],a[i+1]);
     dec(g[c]);
     if f[c]<>0 then dec(g[f[c]]);
 end;
 dfs2(1);
 for i:=2 to n do dec(ans[a[i]]);
 for i:=1 to n do writeln(ans[i]);
end.
Problem3653

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
using namespace std;
const int N = 300010;
typedef long long LL;
struct edge{
	int to,pre;
}e[N * 2];
int l = 0, u[N];
void ins(int a,int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
int pre[N], dep[N], dfs_clock = 0, last[N], sz[N];
void dfs(int x,int f){
	pre[x] = ++dfs_clock, sz[x] = 1;
	reg(i,x) if (v != f){
		dep[v] = dep[x] + 1, dfs(v,x), sz[x] += sz[v];
	}
	last[x] = dfs_clock;
}
#define mp(a,b) make_pair(a,b)
pair<int,int> y[N];
struct query{
	int l,r,t,pos,szp,dep,k;//(l,r]
}q[N];
LL ans[N];
bool cmp(const query &a, const query &b){
	return a.t < b.t;
}
int n;
struct BIT{
	LL s[N];
	BIT(){
		rep(i,0,N-1) s[i] = 0;
	}
	void add(int x, int d){
		while (x <= n){
			s[x] += d;
			x += (-x) & x;
		}
	}
	LL sum(int x){
		LL ans = 0;
		while (x > 0){
			ans += s[x];
			x -= (-x) & x;
		}
		return ans;
	}
}b;
#undef v
int main(){
	int Q;scanf("%d%d",&n,&Q);
	rep(i,1,n-1){
	    int u,v; scanf("%d%d",&u,&v);
		ins(u,v), ins(v,u);
	}
	dep[1] = 1;dfs(1,0);
	rep(i,1,n) y[i] = mp(dep[i],i);
	sort(y+1, y+n+1);
	rep(i,1,Q){
		int p, k;scanf("%d%d",&p,&k);
		q[i] = (query){pre[p], last[p], dep[p] + k, i, sz[p], dep[p], k};
	}
	sort(q+1, q+Q+1, cmp);

	int j = 1;
	rep(i,1,Q){
		for(;y[j].first <= q[i].t && j <= n; j++) {
			int x = y[j].second;
			b.add(pre[x], sz[x] - 1);
		}
		ans[q[i].pos] = b.sum(q[i].r) - b.sum(q[i].l) +1LL * min(q[i].k, q[i].dep - 1) * (q[i].szp - 1);
	}
	rep(i,1,Q) printf("%lld\n", ans[i]);
}
Problem3653

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
using namespace std;
const int N = 300010;
typedef long long LL;
struct edge{
	int to,pre;
}e[N * 2];
int l = 0, u[N];
inline void ins(int a,int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
int pre[N], dep[N], dfs_clock = 0, last[N], sz[N];
void dfs(int x,int f){
	pre[x] = ++dfs_clock, sz[x] = 1;
	reg(i,x) if (v != f){
		dep[v] = dep[x] + 1, dfs(v,x), sz[x] += sz[v];
	}
	last[x] = dfs_clock;
}
#define mp(a,b) make_pair(a,b)
pair<int,int> y[N];
struct query{
	int l,r,t,pos,szp,dep,k;//(l,r]
}q[N];
LL ans[N];
inline bool cmp(const query &a, const query &b){
	return a.t < b.t;
}
int n;
struct BIT{
	LL s[N];
	inline void add(int x, int d){
		while (x <= n){
			s[x] += d;
			x += (-x) & x;
		}
	}
	inline LL sum(int x){
		LL ans = 0;
		while (x > 0){
			ans += s[x];
			x -= (-x) & x;
		}
		return ans;
	}
}b;
#undef v
int main(){
	int Q;scanf("%d%d",&n,&Q);
	rep(i,1,n-1){
	    int u,v; scanf("%d%d",&u,&v);
		ins(u,v), ins(v,u);
	}
	dep[1] = 1;dfs(1,0);
	rep(i,1,n) y[i] = mp(dep[i],i);
	sort(y+1, y+n+1);
	rep(i,1,Q){
		int p, k;scanf("%d%d",&p,&k);
		q[i] = (query){pre[p], last[p], dep[p] + k, i, sz[p], dep[p], k};
	}
	sort(q+1, q+Q+1, cmp);

	int j = 1;
	rep(i,1,Q){
		for(;y[j].first <= q[i].t && j <= n; j++) {
			int x = y[j].second;
			b.add(pre[x], sz[x] - 1);
		}
		ans[q[i].pos] = b.sum(q[i].r) - b.sum(q[i].l) +1LL * min(q[i].k, q[i].dep - 1) * (q[i].szp - 1);
	}
	rep(i,1,Q) printf("%lld\n", ans[i]);
}
Problem3653

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
using namespace std;
const int N = 300010;
typedef long long LL;
struct edge{
	int to,pre;
}e[N * 2];
int l = 0, u[N];
inline void ins(int a,int b){
	e[++l] = (edge){b, u[a]}, u[a] = l;
}
int pre[N], dep[N], dfs_clock = 0, last[N], sz[N];
void dfs(int x,int f){
	pre[x] = ++dfs_clock, sz[x] = 1;
	reg(i,x) if (v != f){
		dep[v] = dep[x] + 1, dfs(v,x), sz[x] += sz[v];
	}
	last[x] = dfs_clock;
}
#define mp(a,b) make_pair(a,b)
pair<int,int> y[N];
struct query{
	int l,r,t,pos,szp,dep,k;//(l,r]
}q[N];
LL ans[N];
inline bool cmp(const query &a, const query &b){
	return a.t < b.t;
}
inline int read()

{

    int x=0,f=1;char ch=getchar();

    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}

    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}

    return x*f;

}
int n;
struct BIT{
	LL s[N];
	inline void add(int x, int d){
		while (x <= n){
			s[x] += d;
			x += (-x) & x;
		}
	}
	inline LL sum(int x){
		LL ans = 0;
		while (x > 0){
			ans += s[x];
			x -= (-x) & x;
		}
		return ans;
	}
}b;
#undef v
int main(){
	int Q;n = read(); Q= read();
	rep(i,1,n-1){
	    int u,v;
	    u = read(),v = read();
		ins(u,v), ins(v,u);
	}
	dep[1] = 1;dfs(1,0);
	rep(i,1,n) y[i] = mp(dep[i],i);
	sort(y+1, y+n+1);
	rep(i,1,Q){
		int p, k;p = read(), k =read();
		q[i] = (query){pre[p], last[p], dep[p] + k, i, sz[p], dep[p], k};
	}
	sort(q+1, q+Q+1, cmp);

	int j = 1;
	rep(i,1,Q){
		for(;y[j].first <= q[i].t && j <= n; j++) {
			int x = y[j].second;
			b.add(pre[x], sz[x] - 1);
		}
		ans[q[i].pos] = b.sum(q[i].r) - b.sum(q[i].l) +1LL * min(q[i].k, q[i].dep - 1) * (q[i].szp - 1);
	}
	rep(i,1,Q) printf("%lld\n", ans[i]);
}
Problem3668

var
 c,c1:char;
 i,n:longint;
 m,t,k,a,b,ans:longint;
begin 
 readln(n,m);
 a:=0;b:=1;
 while b<=m do b:=b shl 1;k:=b shr 1;
 b:=b-1;
 for i:=1 to n do begin
	 read(c);
     if c='A' then begin 
		 read(c1);read(c1);readln(t);
	     a:=a and t;b:=b and t;
	 end;
	 if c='O' then begin 
		 read(c1);readln(t);
		 a:=a or t;b:=b or t;
	 end;
	 if c='X' then begin 
		 read(c1);read(c1);readln(t);
		 a:=a xor t;b:=b xor t;
	 end;
 end;
 ans:=0;
 if k=0 then k:=1;//attention!
 while k<a do k:=k shl 1;
 while k>0 do begin 
     if a and k>0 then ans:=ans+k else begin 
		 if (b and k>0) and (m-k>=0) then begin ans:=ans+k;m:=m-k;end;
	 end;
	 k:=k shr 1;
 end;
 writeln(ans);
end.
Problem3669

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}
const int N=50010,M=100100;
struct edge{
	int x,y,a,b;
}e[M];
struct node{
	node *ch[2],*f;
	int fl,v,w,a;
	int d(){return f->ch[1]==this;}
	bool c(){return f->ch[0]!=this && f->ch[1]!=this;}
	void st(node *c,int d){ch[d]=c, c->f=this;}
	void push(){
		if (fl){
			ch[0]->fl^=1;ch[1]->fl^=1;
			swap(ch[0],ch[1]);
			fl=0;
		}
	}
	void upd();
}*null,T[N],T1[M];
void node::upd(){
	w=max(ch[0]->w,ch[1]->w);w=max(w,v);
	if (w==ch[0]->w) a=ch[0]->a;
	else if (w==ch[1]->w) a=ch[1]->a;
	else if (w==v) a=(this-T1);
}
void rot(node *o){
	node *f=o->f;int d=o->d();
	if (f->c()) o->f=f->f;else f->f->st(o,f->d());
	f->st(o->ch[!d],d);o->st(f,!d);
	f->upd();
}
void fix(node *o){
	if (!o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (!o->c())
		if (o->f->c()) rot(o); else
			(o->d()==o->f->d())? (rot(o->f), rot(o)) : (rot(o), rot(o));
	o->upd();
}
void access(node *o){
	node *t=o;
	for(node *c=null;o!=null;c=o, o=o->f){
		splay(o);
		o->ch[1]=c;
	}
	splay(t);
}
void mroot(node *o){access(o);o->fl^=1;}
node* findrt(node *o){//access ed
	while (o->ch[0]!=null) o=o->ch[0];
	return o;
}
bool cmp(const edge &a,const edge &b){
	return a.a < b.a;
}
void cut(node *e,node *a,node *b){
	mroot(e);
	access(a);e->f=a->ch[0]=null;
	access(b);e->f=b->ch[0]=null;
}
void link(node *e,node *a,node *b){
	mroot(a);a->f=e;
	mroot(b);b->f=e;
}
int main(){
	int n=read(),m=read();
	rep(i,1,m) e[i].x=read(),e[i].y=read(),e[i].a=read(),e[i].b=read();
	sort(e+1,e+1+m,cmp);
	null=&T[0];
	null->ch[0]=null->ch[1]=null->f=null;
	null->w=null->a=null->v=0;
	rep(i,1,n) T[i]=*null;

	int ans=1000001;
	rep(i,1,m)if (e[i].x!=e[i].y){
		node *x=&T[e[i].x],*y=&T[e[i].y];
		mroot(x);access(y);bool t= (findrt(y)!=x);
		if ( e[i].b < (y->w) || t){
			if (!t){
				int a=y->a;
				cut(&T1[a],&T[e[a].x],&T[e[a].y]);
			}

			T1[i].v=T1[i].w=e[i].b;
			T1[i].ch[0]=T1[i].ch[1]=T1[i].f=null;
			T1[i].a=i;
			link(&T1[i],x,y);

			mroot(&T[1]);access(&T[n]);
			if (findrt(&T[n])==&T[1]) ans=min(T[n].w+e[i].a,ans);
		}
	}
	if (ans>1000000) ans=-1;
	printf("%d\n",ans);
	return 0;
}
Problem3670

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=1000100;
char s[N];
int p[N],h[N],cnt[N];
void work(){
	int n=0;
	for(char c=getchar();c!='\n' && c!='\r';c=getchar()) s[++n]=c;
	p[0]=-1,cnt[0]=0;
	rep(i,1,n){
		int j;
		for(j=p[i-1];s[j+1]!=s[i] && j!=-1;j=p[j]);
		p[i]=j+1;cnt[i]=cnt[j+1]+1;
	}
	unsigned long long ans=1;
	int j=0;
	rep(i,1,n) {
		for(;j!=-1 && s[j+1]!=s[i];j=p[j]);j++;
		for(;(j<<1)>i;j=p[j]);
		ans*=(cnt[j]+1);ans%=1000000007;
	}  
	cout <<ans<<endl;
}
int main(){
	int n;scanf("%d\n",&n);
	rep(i,1,n) work();
	return 0;
}
Problem3671

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while (c<'0' || c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}
int x[5001*5001],t[5001*5001],x1[10010],x2[10010],y1[10010],y2[10010];
bool w[10010];
typedef long long LL;
#define max(a,b) (a>b ? a : b)
#define min(a,b) (a>b ? b : a)
int main(){
	x[0]=read();int a=read(),b=read(),c=read(),d=read();
	int n=read(),m=read(),q=read();
	LL tmp=x[0];
	rep(i,1,n*m) {
		tmp=(a*tmp*tmp%d+b*tmp+c)%d;
		x[i]=tmp;
	}
	rep(i,1,n*m) t[i]=i;
	rep(i,1,n*m) swap(t[i],t[x[i]%i+1]);
	rep(i,1,q) {
		int a=read(),b=read();
		swap(t[a],t[b]);
	}
	rep(i,1,n*m) x[t[i]]=i;
	rep(i,1,n+m-1) x2[i]=m, y2[i]=n;
	int cnt=0;
	rep(i,1,n*m){
		int tx=(x[i]-1) % m+1,ty=(x[i]-1)/m+1,pos=tx+ty-1;
		if (x1[pos]<=tx && tx<=x2[pos] && y1[pos]<=ty && ty<=y2[pos] && !w[pos]){
			w[pos]=1;x[i]=-1;cnt++;if (cnt==n+m-1) break;
			for(int j=pos-1;j>0 && !w[j];j--) x2[j]=min(x2[j],tx),y2[j]=min(y2[j],ty);
			for(int j=pos+1;j<n+m && !w[j];j++) x1[j]=max(x1[j],tx), y1[j]=max(y1[j],ty);
		}
	}
	cnt=0;
	rep(i,1,n*m)if (x[i]==-1){
		printf("%d",i);cnt++;
		if (cnt==n+m-1) break;else printf(" ");
	}
	printf("\n");
	return 0;
}
Problem3673

#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
struct node{
    node* ch[2];
    int f;
};
int n,m;
node T[1000000];
int ll=0,i;
node* root[80000];
void build(node* &o,int l,int r){
    //cout <<o<<' '<<l<<' '<<r<<'\n';
    o=&T[ll++];
    //cout <<o<<' '<<l<<' '<<r<<'\n';
    if (l==r) o->f=l; else {
        int mid = ( l + r ) >> 1;
        build( o -> ch[0] , l , mid );
        build( o -> ch[1] , mid+1, r);
    }
}
int find(node* &o,int l,int r,int x){
    if (l==r) {
        return  (o->f == x)?x:find(root[i],1,n,o->f); 
    } else {
        int mid = ( l + r ) >> 1;
        return x<=mid? find(o->ch[0],l,mid,x):find(o->ch[1],mid+1,r,x);
    }
}
void change(node* &o,int l,int r,int x,int y)//f[x]->y
{
    //cout <<o<<' '<<l<<' '<<r<<'\n';
    T[ll]=*o;o=&T[ll++];
    if (l==r) o->f=y; else {
        int mid=(l+r) >> 1;
        if (x<=mid) change(o->ch[0],l,mid,x,y); else change(o->ch[1],mid+1,r,x,y);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    root[0]=NULL;
    build(root[0],1,n);
    for (i=1;i<=m;i++){
        root[i]=root[i-1];
        int op;
        scanf("%d",&op);
        if (op==1){
            int a,b;
            scanf("%d%d",&a,&b);
            int q=find(root[i],1,n,a),p=find(root[i],1,n,b);
            if (q!=p) change(root[i],1,n,p,q);//f[p]->q
        }else if (op==2){
            int k;
            scanf("%d",&k);
            root[i]=root[k];
        }else {
            int a,b;
            scanf("%d%d",&a,&b);
            int q=find(root[i],1,n,a),p=find(root[i],1,n,b);
            printf("%d\n",q==p ? 1 : 0);
        }
    }
    return 0;
}
Problem3673

#include <iostream> 
#include <cmath> 
#include <cstdio> 
using namespace std; 
struct node{ 
    node* ch[2]; 
    int f; 
}; 
int n,m; 
node T[1000000]; 
int ll=0,i; 
node* root[80000]; 
void build(node* &o,int l,int r){ 
    //cout <<o<<' '<<l<<' '<<r<<'\n'; 
    o=&T[ll++]; 
    //cout <<o<<' '<<l<<' '<<r<<'\n'; 
    if (l==r) o->f=l; else { 
        int mid = ( l + r ) >> 1; 
        build( o -> ch[0] , l , mid ); 
        build( o -> ch[1] , mid+1, r); 
    } 
} 
int find(node* &o,int l,int r,int x){ 
    if (l==r) { 
        if (o->f==x) return x;
        T[ll]=*o;o=&T[ll++];
        o->f=find(root[i],1,n,o->f);  
        return o->f;
    } else { 
        int mid = ( l + r ) >> 1; 
        if (x<=mid){
            node* tmp=o->ch[0];
            int t=find(tmp,l,mid,x);
            if (tmp!=o->ch[0]){
                T[ll]=*o;o=&T[ll++];
                o->ch[0]=tmp;
            }
            return t; 
        } else {
            node* tmp=o->ch[1];
            int t=find(tmp,mid+1,r,x);
            if (tmp!=o->ch[1]){
                T[ll]=*o;o=&T[ll++];
                o->ch[1]=tmp;
            }
            return t;
        } 
    } 
} 
void change(node* &o,int l,int r,int x,int y)//f[x]->y 
{ 
    //cout <<o<<' '<<l<<' '<<r<<'\n'; 
    T[ll]=*o;o=&T[ll++]; 
    if (l==r) o->f=y; else { 
        int mid=(l+r) >> 1; 
        if (x<=mid) change(o->ch[0],l,mid,x,y); else change(o->ch[1],mid+1,r,x,y); 
    } 
} 
int main(){ 
    scanf("%d%d",&n,&m); 
    root[0]=NULL; 
    build(root[0],1,n); 
    for (i=1;i<=m;i++){ 
        root[i]=root[i-1]; 
        int op; 
        scanf("%d",&op); 
        if (op==1){ 
            int a,b; 
            scanf("%d%d",&a,&b); 
            int q=find(root[i],1,n,a),p=find(root[i],1,n,b); 
            if (q!=p) change(root[i],1,n,p,q);//f[p]->q 
        }else if (op==2){ 
            int k; 
            scanf("%d",&k); 
            root[i]=root[k]; 
        }else { 
            int a,b; 
            scanf("%d%d",&a,&b); 
            int q=find(root[i],1,n,a),p=find(root[i],1,n,b); 
            printf("%d\n",q==p ? 1 : 0); 
        } 
    } 
    return 0; 
}
Problem3674

#include <iostream> 
#include <cmath> 
#include <cstdio> 
using namespace std; 
struct node{ 
    node* ch[2]; 
    int f; 
}; 
int n,m; 
node T[10000000]; 
int ll=0,i; 
node* root[200010]; 
void build(node* &o,int l,int r){ 
    //cout <<o<<' '<<l<<' '<<r<<'\n'; 
    o=&T[ll++]; 
    //cout <<o<<' '<<l<<' '<<r<<'\n'; 
    if (l==r) o->f=l; else { 
        int mid = ( l + r ) >> 1; 
        build( o -> ch[0] , l , mid ); 
        build( o -> ch[1] , mid+1, r); 
    } 
} 
int find(node* &o,int l,int r,int x){ 
    if (l==r) { 
        if (o->f==x) return x;
        T[ll]=*o;o=&T[ll++];
        o->f=find(root[i],1,n,o->f);  
        return o->f;
    } else { 
        int mid = ( l + r ) >> 1; 
        if (x<=mid){
            node* tmp=o->ch[0];
            int t=find(tmp,l,mid,x);
            if (tmp!=o->ch[0]){
                T[ll]=*o;o=&T[ll++];
                o->ch[0]=tmp;
            }
            return t; 
        } else {
            node* tmp=o->ch[1];
            int t=find(tmp,mid+1,r,x);
            if (tmp!=o->ch[1]){
                T[ll]=*o;o=&T[ll++];
                o->ch[1]=tmp;
            }
            return t;
        } 
    } 
} 
void change(node* &o,int l,int r,int x,int y)//f[x]->y 
{ 
    //cout <<o<<' '<<l<<' '<<r<<'\n'; 
    T[ll]=*o;o=&T[ll++]; 
    if (l==r) o->f=y; else { 
        int mid=(l+r) >> 1; 
        if (x<=mid) change(o->ch[0],l,mid,x,y); else change(o->ch[1],mid+1,r,x,y); 
    } 
} 
int main(){ 
    int lastans=0;
    scanf("%d%d",&n,&m); 
    root[0]=NULL; 
    build(root[0],1,n); 
    for (i=1;i<=m;i++){ 
        root[i]=root[i-1]; 
        int op; 
        scanf("%d",&op); 
        if (op==1){ 
            int a,b; 
            scanf("%d%d",&a,&b); 
            a^=lastans;
            b^=lastans;
            int q=find(root[i],1,n,a),p=find(root[i],1,n,b); 
            if (q!=p) change(root[i],1,n,p,q);//f[p]->q 
        }else if (op==2){ 
            int k; 
            scanf("%d",&k);
            k^=lastans; 
            root[i]=root[k]; 
        }else { 
            int a,b; 
            scanf("%d%d",&a,&b); 
            a^=lastans;
            b^=lastans;
            int q=find(root[i],1,n,a),p=find(root[i],1,n,b); 
            printf("%d\n",q==p ? 1 : 0); 
        } 
    } 
    return 0; 
}
Problem3675

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
const int N = 100100;
int a[N];
LL s[N];
LL f[2][N];
typedef pair<LL, LL> node;
#define x first
#define y second
struct queue{
	node q[N];
	int l,r;
	void clr(){
		l = r = 0;
	}
	queue(){
		clr();
	}
	bool cmp(const node &a, const node &b, const node &c){
		return (c.y - b.y) * (b.x - a.x) - (c.x - b.x) * (b.y - a.y) > 0;
	}
	void push(const node &a){
		while (r - l >= 2 && !cmp(q[r - 2], q[r - 1], a)) r--;
		q[r++] = a;
	}
	bool cmp(const node &a, const node &b, int k){
		return a.y - k * a.x < b.y - k * b.x;
	}
	LL top(int k){
		while (r - l >= 2 && !cmp(q[l], q[l + 1], k)) l++;
		return q[l].y - k * q[l].x;
	}
}q;
#undef x
#undef y
#define mp(a,b) make_pair(a,b)
int main(){
	int n,k;scanf("%d%d",&n,&k);
	s[0] = 0;
	rep(i,1,n) scanf("%d",&a[i]), s[i] = s[i-1] + a[i];
	LL ans = 1LL * s[n] * s[n];
	rep(i,1,n) f[0][i] =1LL * s[i] * s[i];
	int pos = 0;
	rep(i,1,k){
		pos ^= 1;
		rep(j,i + 1,n){
			q.push(mp(s[j - 1],f[pos ^ 1][j - 1] + 1LL * s[j - 1] * s[j - 1]));
			LL t = q.top(s[j] << 1);
			f[pos][j] = t + 1LL * s[j] * s[j];
		}
		q.clr();
	}
	ans -= f[pos][n];
	printf("%lld\n",ans >> 1);
}
Problem3675

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
const int N = 100100;
int a[N];
int s[N];
LL f[2][N];
typedef pair<LL, LL> node;
#define x first
#define y second
struct queue{
	node q[N];
	int l,r;
	void clr(){
		l = r = 0;
	}
	queue(){
		clr();
	}
	bool cmp(const node &a, const node &b, const node &c){
		return (c.y - b.y) * (b.x - a.x) - (c.x - b.x) * (b.y - a.y) > 0;
	}
	void push(const node &a){
		while (r - l >= 2 && !cmp(q[r - 2], q[r - 1], a)) r--;
		q[r++] = a;
	}
	bool cmp(const node &a, const node &b, int k){
		return a.y - k * a.x < b.y - k * b.x;
	}
	LL top(int k){
		while (r - l >= 2 && !cmp(q[l], q[l + 1], k)) l++;
		return q[l].y - k * q[l].x;
	}
}q;
#undef x
#undef y
#define mp(a,b) make_pair(a,b)
int main(){
	int n,k;scanf("%d%d",&n,&k);
	s[0] = 0;
	rep(i,1,n) scanf("%d",&a[i]), s[i] = s[i-1] + a[i];
	LL ans = 1LL * s[n] * s[n];
	rep(i,1,n) f[0][i] =1LL * s[i] * s[i];
	int pos = 0;
	rep(i,1,k){
		pos ^= 1;
		rep(j,i + 1,n){
			q.push(mp(s[j - 1],f[pos ^ 1][j - 1] + 1LL * s[j - 1] * s[j - 1]));
			LL t = q.top(s[j] << 1);
			f[pos][j] = t + 1LL * s[j] * s[j];
		}
		q.clr();
	}
	ans -= f[pos][n];
	printf("%lld\n",ans >> 1);
}
Problem3675

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
const int N = 100100;
int a[N],s[N];
LL f[2][N];
typedef pair<int, LL> node;
#define x first
#define y second
struct queue{
	node q[N];
	int l,r;
	void clr(){
		l = r = 0;
	}
	queue(){
		clr();
	}
	bool cmp(const node &a, const node &b, const node &c){
		return (c.y - b.y) * (b.x - a.x) - (c.x - b.x) * (b.y - a.y) > 0;
	}
	void push(const node &a){
		while (r - l >= 2 && !cmp(q[r - 2], q[r - 1], a)) r--;
		q[r++] = a;
	}
	bool cmp(const node &a, const node &b, int k){
		return a.y - 1LL * k * a.x < b.y - 1LL * k * b.x;
	}
	LL top(int k){
		while (r - l >= 2 && !cmp(q[l], q[l + 1], k)) l++;
		return q[l].y - 1LL * k * q[l].x;
	}
}q;
#undef x
#undef y
#define mp(a,b) make_pair(a,b)
int main(){
	int n,k;scanf("%d%d",&n,&k);
	s[0] = 0;
	rep(i,1,n) scanf("%d",&a[i]), s[i] = s[i-1] + a[i];
	LL ans = 1LL * s[n] * s[n];
	rep(i,1,n) f[0][i] =1LL * s[i] * s[i];
	int pos = 0;
	rep(i,1,k){
		pos ^= 1;
		rep(j,i + 1,n){
			q.push(mp(s[j - 1],f[pos ^ 1][j - 1] + 1LL * s[j - 1] * s[j - 1]));
			LL t = q.top(s[j] << 1);
			f[pos][j] = t + 1LL * s[j] * s[j];
		}
		q.clr();
	}
	ans -= f[pos][n];
	printf("%lld\n",ans >> 1);
}
Problem3687

#include <iostream>
#include <cstdio>
#include <bitset>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
bitset<2000010> f;
int sum=0;
int main(){
	int n;scanf("%d",&n);
	f[0]=1;
	while (n--){
		int a;scanf("%d",&a);
		f^=(f << a);sum+=a;
	}
	int ans=0;
	rep(i,1,sum) if (f[i]) ans^=i;
	printf("%d\n",ans);
}
Problem3697

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
#define ec e[i].c
typedef long long LL;
using namespace std;
const int N=300005; 
struct edge{
	int to,pre,c;
}e[N*2];
int l=1,u[N],n,root;
void ins(int a,int b,int c){
	e[++l]=(edge){b,u[a],c};u[a]=l;
}
void insert(int a,int b,int c){
	ins(a,b,c);ins(b,a,c);
}
int sum,mx[N],size[N],vis[N];
void getroot(int x,int fa){
	mx[x]=0;size[x]=1;
	reg(i,x) if ((!vis[v]) && (v!=fa)){
		getroot(v,x);
		size[x]+=size[v];
		mx[x]=max(mx[x],size[v]);
	}
	mx[x]=max(mx[x],sum-size[x]);
	if (mx[x] < mx[root]) root=x;
}

LL ans,g[N*2][2],f[N*2][2];
int maxdep,dep[N],dis[N];
int t[N*2];
void dfs(int x,int fa){
	maxdep=max(maxdep,dep[x]);
	if (t[dis[x]]) f[dis[x]][1]++; else f[dis[x]][0]++;
	t[dis[x]]++;
	reg(i,x) if ((!vis[v]) && (v!=fa)){
		dep[v]=dep[x]+1, dis[v]=dis[x]+ec;
		dfs(v,x);
	}
	t[dis[x]]--;
}
void work(int x){
	vis[x]=1, g[n][0]=1;
	int mx=0;
	reg(i,x)if (!vis[v]){
		dep[v]=1, dis[v]=n+ec, maxdep=1;
		dfs(v,x);mx=max(mx,maxdep);
		ans+=(g[n][0]-1)*f[n][0];
		rep(j,-maxdep,maxdep) 
			ans+=g[n-j][1]*f[n+j][1]+g[n-j][0]*f[n+j][1]+g[n-j][1]*f[n+j][0];
		rep(j,n-maxdep,n+maxdep) 
	        g[j][0]+=f[j][0], g[j][1]+=f[j][1], f[j][0]=f[j][1]=0;
	}
	rep(i,n-mx,n+mx) g[i][0]=g[i][1]=0;
	reg(i,x) if (!vis[v]){
		root=0, sum=size[v];
		getroot(v,x);
		work(root);
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int a,b,c;scanf("%d%d%d",&a,&b,&c);
		if (!c) c=-1;
		insert(a,b,c);
	}
	sum=mx[0]=n;
	getroot(1,0);
	work(root);
	cout <<ans<<endl;
	return 0;
}
Problem3697

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define ret(i,a) reg(i,a)if ((v!=fa) && (!vis[v]))
#define v e[i].to
#define ec e[i].c
using namespace std;
typedef long long LL;
const int N=500000;
struct edge{
    int to,pre,c;
}e[N*2];
int l=1,u[N],n;
void ins(int a,int b,int c){
    e[++l]=(edge){b,u[a],c};u[a]=l;
}
void insert(int a,int b,int c){
    ins(a,b,c);ins(b,a,c);
}
 
int sz[N],s[N],sum,vis[N],root=0;
void getroot(int x,int fa){
    s[x]=0, sz[x]=1;
    ret(i,x) {
        getroot(v,x);
        sz[x]+=sz[v];
        s[x]=max(s[x],sz[v]);
    }
    s[x]=max(s[x],sum-sz[x]);
    if (s[x] < s[root]) root=x;
}
 
int maxdep,t[N*2];
long long f[N*2][2],g[N*2][2],ans=0;
void dfs(int x,int fa,int dep,int dis){
    if (dep>maxdep) maxdep=dep;
    if (t[dis]) g[dis][1]++; else g[dis][0]++;
    t[dis]++;
    ret(i,x) dfs(v,x,dep+1,dis+ec);
    t[dis]--;
}
void work(int x){
    vis[x]=1;int mx=1;f[n][0]=1;
    reg(i,x) if (!vis[v]) {
        maxdep=1;dfs(v,x,1,n+ec);mx=max(mx,maxdep);
        ans+=(f[n][0]-1)*g[n][0];
        rep(j,-maxdep,maxdep)
            ans+=f[n+j][0]*g[n-j][1]+f[n+j][1]*g[n-j][0]+f[n+j][1]*g[n-j][1];           
        rep(j,n-maxdep,n+maxdep) {
            f[j][0]+=g[j][0];
            f[j][1]+=g[j][1];
            g[j][0]=g[j][1]=0;
        }
    }
    rep(j,n-mx,n+mx) f[j][0]=f[j][1]=0;
    reg(i,x) if (!vis[v]){
        sum=sz[v], root=0;
        getroot(v,x);
        work(root);
    }
}
int main(){
    scanf("%d",&n);
    rep(i,1,n-1){
        int a,b,c;scanf("%d%d%d",&a,&b,&c);
        if (!c) c=-1;
        insert(a,b,c);
    }
    sum=s[0]=n;
    getroot(1,0);
    work(root);
    cout <<ans<<endl;
    return 0;
}
Problem3709

var
 z:int64;
 n,a,b,i:longint;
 l1,l2:longint;
 a1,b1,a2,b2,c1,c2:array[1..1000000]of int64;
procedure print_no;
begin
 writeln('NIE');halt; 
end;
procedure swap(var a,b:int64);
var
 c:int64;
begin
 c:=a;a:=b;b:=c; 
end;
procedure sort_1(l,r:longint);
var
 i,j,m:longint;
begin 
 i:=l;j:=r;m:=a1[(l+r) shr 1];
 repeat
  while a1[i]<m do inc(i);
  while a1[j]>m do dec(j);
  if i<=j then begin    
      swap(a1[i],a1[j]);swap(b1[i],b1[j]);swap(c1[i],c1[j]); 	 inc(i);dec(j);
  end;
 until i>j;
 if l<j then sort_1(l,j);
 if i<r then sort_1(i,r);
end;
procedure sort_2(l,r:longint);
var
 i,j,m:longint;
begin 
 i:=l;j:=r;m:=b2[(l+r) shr 1];
 repeat
  while b2[i]>m do inc(i);
  while b2[j]<m do dec(j);
  if i<=j then begin 
     swap(a2[i],a2[j]);swap(b2[i],b2[j]);swap(c2[i],c2[j]); 	 inc(i);dec(j);
  end;
 until i>j;
 if l<j then sort_2(l,j);
 if i<r then sort_2(i,r);
end;
begin 
 readln(n,z);l1:=0;l2:=0;
 for i:=1 to n do begin 
     readln(a,b);
	 if b>=a then begin 
	     inc(l1);
		 a1[l1]:=a;b1[l1]:=b;c1[l1]:=i;
	 end;
	 if b<a then begin 
	     inc(l2);
		 a2[l2]:=a;b2[l2]:=b;c2[l2]:=i;
	 end;
 end;
 sort_1(1,l1);
 sort_2(1,l2);	
 for i:=1 to l1 do begin 
     if a1[i]>=z then print_no;
	 z:=z-a1[i]+b1[i];
 end;
 for i:=1 to l2 do begin 
     if a2[i]>=z then print_no;
	 z:=z-a2[i]+b2[i];
 end;
 writeln('TAK');
 for i:=1 to l1 do write(c1[i],' ');
 for i:=1 to l2 do write(c2[i],' ');
end.
Problem3732

uses math;
var
 n,m,i,q,u,v,k,fx,fy,ans:longint;
 x,y,z:array[1..500000]of longint; 
 f,h,r,g,t,tv:array[1..100000]of longint;
procedure sort(l,r:longint);
var
 i,j,m,t:longint;
begin
 i:=l;j:=r;m:=z[(l+r) shr 1];
 repeat
	  while z[i]<m do inc(i);
	  while z[j]>m do dec(j);
	  if i<=j then begin 
		  t:=z[i];z[i]:=z[j];z[j]:=t;
	      t:=x[i];x[i]:=x[j];x[j]:=t;
	      t:=y[i];y[i]:=y[j];y[j]:=t;
	     inc(i);dec(j);
	  end;
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
function find(x:longint):longint;
begin
 if f[x]=x then exit(x) else exit(find(f[x])); 
end;
procedure gether(a,b,c:longint);
begin
 if h[a]<h[b] then begin f[a]:=b;r[a]:=c;end else begin 
	f[b]:=a;r[b]:=c;if h[b]+1>h[a] then h[a]:=h[b]+1;
 end;
end;
begin 
 readln(n,m,q);
 for i:=1 to m do 
	  readln(x[i],y[i],z[i]);
 sort(1,m);
 for i:=1 to n do begin 
	  f[i]:=i;h[i]:=1;r[i]:=0;
 end;                       
 for i:=1 to m do begin 
	 fx:=find(x[i]);fy:=find(y[i]);
     if fx=fy then continue;
	 gether(fx,fy,z[i]);
 end;
 for i:=1 to q do begin 
	 readln(u,v);ans:=-1;
	 g[u]:=i;t[u]:=0;
     while f[u]<>u do begin 
		 k:=f[u];t[k]:=max(t[u],r[u]);
	     u:=k;g[u]:=i;
	 end;
	 tv[v]:=0;
	 if g[v]=i then ans:=t[v] else  
	 while (f[v]<>v) and (ans=-1) do begin 
		 k:=f[v];tv[k]:=max(tv[v],r[v]);
	     v:=k;if g[v]=i then ans:=max(tv[v],t[v]);
	 end;
	 writeln(ans);
 end;
end.
Problem3784

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#define ec e[i].c
#define v e[i].to
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
#define ret(i,x) reg(i,x)if ((!vis[v]) && (v!=fa))
using namespace std;
const int N=100000,inf=0x7fffffff;
struct edge{
	int to,pre,c;
}e[N*2];
int l=1,u[N];
void ins(int a,int b,int c){
	e[++l]=(edge){b,u[a],c}, u[a]=l;
}
void insert(int a,int b,int c){
	ins(a,b,c);ins(b,a,c);
}

int sum,sz[N],sm[N],root,vis[N];
void getrt(int x,int fa){
	sz[x]=1, sm[x]=0;
	ret(i,x) getrt(v,x), sz[x]+=sz[v], sm[x]=max(sm[x],sz[v]);
	sm[x]=max(sm[x],sum-sz[x]);
	if (sm[x] < sm[root]) root=x;
}
struct node{
	int dis,l,r,m,t;
}f[6000000];
int fl=0,t1,t2;
void dfs(int x,int fa,int dis){
	f[++fl]=(node){dis,t1,t2,0,0};
	ret(i,x) dfs(v,x,dis+ec);
}
void work(int x){
	vis[x]=1, t1=++fl, t2=t1;
	f[t1]=(node){0,0,0,0,0};
	reg(i,x)if (!vis[v]) {dfs(v,0,ec);t2=fl;}
	reg(i,x)if (!vis[v]){
		root=0;sum=sz[v];
		getrt(v,0);
		work(root);
	}
}
priority_queue<node> q;
bool operator < (const node &a,const node &b){
	return a.m < b.m;
}
int s[5000000];
#define lc (x << 1)
#define rc (lc+1)
#define mid ((l+r) >> 1)
void build(int x,int l,int r){
	if (l==r) s[x]=l;else {
		build(lc,l,mid),build(rc,mid+1,r);
		if (f[s[lc]].dis < f[s[rc]].dis) s[x]=s[rc]; else s[x]=s[lc];
	}
}
int qry(int x,int l,int r,int a,int b){//dis!
	if (a<=l && r<=b) return s[x];else {
		int ans=0;
		if (a<=mid){
			int t=qry(lc,l,mid,a,b);
			if (f[ans].dis < f[t].dis) ans=t;
		} 
		if (b> mid){
			int t=qry(rc,mid+1,r,a,b); 
			if (f[ans].dis < f[t].dis) ans=t;
		}
		return ans;
	}
}
int qy(int a,int b){
	return qry(1,1,fl,a,b);
}
int main(){
	f[0].dis=-1;
	int n,k;scanf("%d%d",&n,&k);
	rep(i,1,n-1){
		int a,b,c;scanf("%d%d%d",&a,&b,&c);insert(a,b,c);
	}
	sum=sm[0]=n;root=0;
	getrt(1,0);
	work(root);
	build(1,1,fl);
	rep(i,1,fl) if (f[i].l) {
		int t=qy(f[i].l,f[i].r);
		f[i].t=t;
		f[i].m=f[t].dis+f[i].dis;
		q.push(f[i]);
	}
	rep(i,1,k) {
		node x=q.top();q.pop();
		int t=x.t,t1,t2;
		if (x.l < t) {
			t1=qy(x.l,t-1); 
			q.push((node){x.dis,x.l,t-1,x.dis+f[t1].dis,t1});
		}
		if (t < x.r) {
			t2=qy(t+1,x.r);
			q.push((node){x.dis,t+1,x.r,x.dis+f[t2].dis,t2});
		}
		printf("%d\n",x.m);
	}
	return 0;
}
Problem3790

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 500010;
char c[N];
int p[N], l[N], r[N];
pair<int, int> seg[N];
#define l first
#define r second
#define mp(a,b) make_pair(a,b)
void work(){
	int len = strlen(c + 1);
	dep(i,len,1) c[i << 1] = c[i];
	len = (len << 1) + 1;
	rep(i,1,len) if (i & 1) c[i] = '#';	
	p[1] = 0; int mx = 1, j = 1;
	rep(i,2,len){
		if (mx > i) p[i] = min(p[j * 2 - i], mx - i); else p[i] = 0;
		while (i - p[i] - 1 > 0 && i + p[i] + 1 <= len && c[i - p[i] - 1] == c[i + p[i] + 1]) p[i]++;
		if (i + p[i] > mx) mx = i + p[i], j = i;
	}
	rep(i,1,len) seg[i] = mp(i - p[i], i + p[i]);
	sort(seg + 1, seg + len + 1);
	int cur = 1, i = 1, ans = -1;
	while (cur <= len){
		int mr = 0;
		while (seg[i].l <= cur){
			mr = max(seg[i].r, mr);
			i++;
		}
		cur = mr + 1;
		ans++;
	}
	printf("%d\n",ans);
}
int main(){
	while (scanf("%s", c + 1) != EOF) work();
}
Problem3812

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 15, M = 1000000000 + 7;
int e_in[1 << 15], e_out[1 << 15], a[N * N], b[N * N];
int f[1 << 15], g[1 << 15], ways[1 << 15], h[1 << 15], pow[N * N], cnt[1 << 15];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m){
		scanf("%d%d",&a[i],&b[i]);
		a[i]--, b[i]--;
		e_out[1 << a[i]] |= 1 << b[i];
		e_in [1 << b[i]] |= 1 << a[i];
	}
	
	pow[0] = 1;
	rep(i,1,N * N) pow[i] = (pow[i - 1] << 1) % M;

	int l = (1 << n) - 1;
	cnt[0] = 0;
	rep(i,1,l) cnt[i] = cnt[i ^ (i & (-i))] + 1;

	h[0] = 0;
	rep(i,1,l){
		int u = i & (-i), v = i ^ u;
		h[i] = h[v] + cnt[e_in[u] & i] + cnt[e_out[u] & i];

		g[i] = 0;
		for(int j = v; j; j = (j - 1) & v)
			g[i] -= 1LL * f[i ^ j] * g[j] % M, g[i] %= M;

		ways[i] = 0;
		for(int j = i - 1; j; j = (j - 1) & i){
			int u = (i ^ j) & (-(i ^ j)), v = j ^ u;
			ways[j] = ways[v] + cnt[e_out[u] & j] - cnt[e_in[u] & (i ^ j)];
		}

		f[i] = pow[h[i]];
		for(int j = i; j; j = (j - 1) & i){
			f[i] -= 1LL * pow[ways[j]] * pow[h[i ^ j]] % M * g[j] % M, f[i] %= M;
		}
		
		g[i] += f[i], g[i] %= M;
	}
	if (f[l] < 0) f[l] += M;
	printf("%d\n",f[l]);
	return 0;
}
Problem3813

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int n = 100000, N = 100000 + 10, M = 19961993;
typedef long long LL;
LL inv[70], p[70];
LL S[N * 4], P[N * 4];
LL pow(LL a, int b){
	LL w = 1;
	for(;b;b >>= 1, a = a * a % M) if (b & 1) w = w * a % M;
	return w;
}
int l = 0;
#define lc (x << 1)
#define rc (lc + 1)
#define mid ((l + r) >> 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r
void build(int x, int l, int r){
	if (l == r) S[x] = 3, P[x] = 1 << 1;else{
		build(lcq), build(rcq);
		S[x] = S[lc] * S[rc] % M;
		P[x] = P[lc] | P[rc];
	}
}
typedef pair<LL, LL> node;
#define mp(a,b) make_pair(a,b)
node qry(int x, int l, int r, int a, int b){
	if (a <= l && r <= b) return mp(S[x], P[x]);
	node ans = mp(1, 0);
	if (a <= mid){
		node t = qry(lcq, a, b);
		ans.first = ans.first * t.first % M;
		ans.second |= t.second;
	}
	if (b >  mid){
		node t = qry(rcq, a, b);
		ans.first = ans.first * t.first % M;
		ans.second |= t.second;
	}
	return ans;
}
void modi(int x, int l, int r, int a, LL s, LL p){
	if (l == r) S[x] = s, P[x] = p; else{
		if (a <= mid) modi(lcq,a,s,p); else modi(rcq,a,s,p);
		S[x] = S[lc] * S[rc] % M;
		P[x] = P[lc] | P[rc];
	}
}
void init(){
	rep(i,2,281){
		bool flag = true;
		rep(j,2,i - 1) if (i % j == 0) {flag = false;break;}
		if (flag) p[l++] = i;
	}
	rep(i,0,l - 1) inv[i] = pow(p[i], M - 2);
	build(1,1,n);
}
int main(){
	init();
	int Q;scanf("%d",&Q);
	rep(i,1,Q){
		int a, b, c; scanf("%d%d%d",&a,&b,&c);
		if (a == 0){
			node ans = qry(1, 1, n, b, c);
			LL a1 = ans.first, a2 = ans.second;
			rep(j,0,l - 1) if ((a2 >> j) & 1) a1 = a1 * (p[j] - 1) % M * inv[j] % M; //cout <<'-'<<p[j]<<endl;
			printf("%lld\n", a1);
		}else{
			LL p1 = 0;
			rep(j,0,l - 1) if (c % p[j] == 0) p1 |= 1LL << j; // 1LL !!! j <= 60 !
			modi(1,1,n,b,c,p1);
		}
	}
}
Problem3873

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define wd(i) (w[i]-w[i-1])
#define id(i,j,k) (i && j && k ? (w[i-1]+k-1) *n+j : 0)
#define ad(i,j,k) a[id(i,j,k)]
#define asum(i,t,b,k) (ad(i,b,k)-ad(i,t-1,k))
using namespace std;
int s,n,m;
const int N=3000000;
int a[N],w[N];

void init(){
	scanf("%d%d",&s,&n);
	w[0]=a[0]=0;
	rep(i,1,s){
		scanf("%d",&w[i]);
		w[i]+=w[i-1];
		rep(j,1,n) 
			rep(k,1,wd(i)){
				char c=getchar();while (c==' '||c=='\r' || c=='\n') c=getchar();
				ad(i,j,k)=c-'0';
			}
		rep(j,1,n)rep(k,1,wd(i)) ad(i,j,k)+=ad(i,j-1,k);
	} 
	m=w[s];
}
#define ud(i,j,k) up[id(i,j,k)]
int up[N];
struct line{
	int t,b;//top bottom
}L[N];
int ls;
void calc(){
	up[0]=1;
	rep(i,1,s)
		rep(j,1,n)
			rep(k,1,wd(i))
				if (asum(i,j,j,k)==0) {
					ud(i,j,k)=ud(i,j-1,k);
					L[++ls]=(line){ud(i,j,k),j};
				}
				else ud(i,j,k)=j+1;

}
bool cmp(const line &a,const line &b){
	return a.t < b.t || (a.t==b.t && a.b < b.b);
}
void work(){
	ls=0;
	init();calc();
	sort(L+1,L+ls+1,cmp);
	int ans=0;
	L[0].t=L[0].b=-1;
	rep(i,1,ls) if (cmp(L[i-1],L[i])){
		int t=L[i].t,b=L[i].b;
		//inside
		rep(j,1,s){
			int tmp=0;
			rep(k,1,wd(j)){
				if (asum(j,t,b,k)==0) tmp++;else tmp=0;
				ans=max(ans,tmp*(b-t+1));
			}
		}
		//outside(?)
		int th=0,lm,rm,lmax=0,rmax=0,lmn,rmn,lmax1=0,rmax1=0;
		rep(j,1,s){
			lm=0;rm=wd(j)+1;
			rep(l,1,wd(j)) if (asum(j,t,b,l)==0) lm=l;else break;
			dep(r,wd(j),1) if (asum(j,t,b,r)==0) rm=r;else break;
			rm=wd(j)-rm+1;
			if (lm==wd(j)) th+=wd(j);else{
				if (lm>=lmax){
					lmax1=lmax, lmax=lm, lmn=j;
				}else lmax1=lm;
				if (rm>=rmax){
					rmax1=rmax, rmax=rm, rmn=j;
				}else rmax1=rm;
			}
		}
		if (lmn!=rmn) th+=lmax+rmax;else th+=max(lmax+rmax1,rmax+lmax1);
		ans=max(ans,th*(b-t+1));
	}
	printf("%d\n",ans);
}
int main(){
	int t;scanf("%d",&t);
	rep(i,1,t) work();
	return 0;
}
Problem3873

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define wd(i) (w[i]-w[i-1])
#define id(i,j,k) (i && j && k ? (w[i-1]+k-1) *n+j : 0)
#define ad(i,j,k) a[id(i,j,k)]
#define asum(i,t,b,k) (ad(i,b,k)-ad(i,t-1,k))
using namespace std;
int s,n,m;
const int N=3000000;
int a[N],w[N];

void init(){
	scanf("%d%d",&s,&n);
	w[0]=a[0]=0;
	rep(i,1,s){
		scanf("%d",&w[i]);
		w[i]+=w[i-1];
		rep(j,1,n) 
			rep(k,1,wd(i)){
				char c=getchar();while (c==' '||c=='\r' || c=='\n') c=getchar();
				ad(i,j,k)=c-'0';
			}
		rep(j,1,n)rep(k,1,wd(i)) ad(i,j,k)+=ad(i,j-1,k);
	} 
	m=w[s];
}
#define ud(i,j,k) up[id(i,j,k)]
int up[N];
struct line{
	int t,b;//top bottom
}L[N];
int ls;
void calc(){
	up[0]=1;
	rep(i,1,s)
		rep(j,1,n)
			rep(k,1,wd(i))
				if (asum(i,j,j,k)==0) {
					ud(i,j,k)=ud(i,j-1,k);
					L[++ls]=(line){ud(i,j,k),j};
				}
				else ud(i,j,k)=j+1;

}
inline bool cmp(const line &a,const line &b){
	return a.t < b.t || (a.t==b.t && a.b < b.b);
}
void work(){
	ls=0;
	init();calc();
	sort(L+1,L+ls+1,cmp);
	int ans=0;
	L[0].t=L[0].b=-1;
	rep(i,1,ls) if (cmp(L[i-1],L[i])){
		int t=L[i].t,b=L[i].b;
		//inside
		rep(j,1,s){
			int tmp=0;
			rep(k,1,wd(j)){
				if (asum(j,t,b,k)==0) tmp++;else tmp=0;
				ans=max(ans,tmp*(b-t+1));
			}
		}
		//outside(?)
		int th=0,lm,rm,lmax=0,rmax=0,lmn,rmn,lmax1=0,rmax1=0;
		rep(j,1,s){
			lm=wd(j);rm=1;
			rep(l,1,wd(j)) if (asum(j,t,b,l)!=0) {lm=l-1;break;}
			if (lm==wd(j)) th+=wd(j);else{
				dep(r,wd(j),1) if (asum(j,t,b,r)!=0) {rm=r+1;break;}
				rm=wd(j)-rm+1;
				if (lm>=lmax){
					lmax1=lmax, lmax=lm, lmn=j;
				}else lmax1=lm;
				if (rm>=rmax){
					rmax1=rmax, rmax=rm, rmn=j;
				}else rmax1=rm;
			}
		}
		if (lmn!=rmn) th+=lmax+rmax;else th+=max(lmax+rmax1,rmax+lmax1);
		ans=max(ans,th*(b-t+1));
	}
	printf("%d\n",ans);
}
int main(){
	int t;scanf("%d",&t);
	rep(i,1,t) work();
	return 0;
}
Problem3873

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define wd(i) (w[i]-w[i-1])
#define id(i,j,k) (i && j && k ? (w[i-1]+k-1) *n+j : 0)
#define ad(i,j,k) a[id(i,j,k)]
#define asum(i,t,b,k) (ad(i,b,k)-ad(i,t-1,k))
using namespace std;
int s,n,m;
const int N=100001;
int a[N],w[N];

inline void init(){
	scanf("%d%d",&s,&n);
	w[0]=a[0]=0;
	rep(i,1,s){
		scanf("%d",&w[i]);
		w[i]+=w[i-1];
		rep(j,1,n) 
			rep(k,1,wd(i)){
				char c=getchar();while (c==' '||c=='\r' || c=='\n') c=getchar();
				ad(i,j,k)=c-'0';
			}
		rep(j,1,n)rep(k,1,wd(i)) ad(i,j,k)+=ad(i,j-1,k);
	} 
	m=w[s];
}
#define ud(i,j,k) up[id(i,j,k)]
int up[N];
struct line{
	int t,b;//top bottom
}L[N];
int ls;
inline void calc(){
	up[0]=1;
	rep(i,1,s)
		rep(j,1,n)
			rep(k,1,wd(i))
				if (asum(i,j,j,k)==0) {
					ud(i,j,k)=ud(i,j-1,k);
					L[++ls]=(line){ud(i,j,k),j};
				}
				else ud(i,j,k)=j+1;

}
inline bool cmp(const line &a,const line &b){
	return a.t < b.t || (a.t==b.t && a.b < b.b);
}
inline void work(){
	ls=0;
	init();calc();
	sort(L+1,L+ls+1,cmp);
	int ans=0;
	L[0].t=L[0].b=-1;
	rep(i,1,ls) if (cmp(L[i-1],L[i])){
		int t=L[i].t,b=L[i].b;
		//inside
		rep(j,1,s){
			int tmp=0;
			rep(k,1,wd(j)){
				if (asum(j,t,b,k)==0) tmp++;else tmp=0;
				ans=max(ans,tmp*(b-t+1));
			}
		}
		//outside(?)
		int th=0,lm,rm,lmax=0,rmax=0,lmn,rmn,lmax1=0,rmax1=0;
		rep(j,1,s){
			lm=wd(j);rm=1;
			rep(l,1,wd(j)) if (asum(j,t,b,l)!=0) {lm=l-1;break;}
			if (lm==wd(j)) th+=wd(j);else{
				dep(r,wd(j),1) if (asum(j,t,b,r)!=0) {rm=r+1;break;}
				rm=wd(j)-rm+1;
				if (lm>=lmax){
					lmax1=lmax, lmax=lm, lmn=j;
				}else lmax1=lm;
				if (rm>=rmax){
					rmax1=rmax, rmax=rm, rmn=j;
				}else rmax1=rm;
			}
		}
		if (lmn!=rmn) th+=lmax+rmax;else th+=max(lmax+rmax1,rmax+lmax1);
		ans=max(ans,th*(b-t+1));
	}
	printf("%d\n",ans);
}
int main(){
	int t;scanf("%d",&t);
	rep(i,1,t) work();
	return 0;
}
Problem3873

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define wd(i) (w[i]-w[i-1])
#define id(i,j,k) (i && j && k ? (w[i-1]+k-1) *n+j : 0)
#define ad(i,j,k) a[id(i,j,k)]
#define asum(i,t,b,k) (ad(i,b,k)-ad(i,t-1,k))
using namespace std;
int s,n,m;
const int N=3000000;
int a[N],w[N];

inline void init(){
	scanf("%d%d",&s,&n);
	w[0]=a[0]=0;
	rep(i,1,s){
		scanf("%d",&w[i]);
		w[i]+=w[i-1];
		rep(j,1,n) 
			rep(k,1,wd(i)){
				char c=getchar();while (c==' '||c=='\r' || c=='\n') c=getchar();
				ad(i,j,k)=c-'0';
			}
		rep(j,1,n)rep(k,1,wd(i)) ad(i,j,k)+=ad(i,j-1,k);
	} 
	m=w[s];
}
#define ud(i,j,k) up[id(i,j,k)]
int up[N];
struct line{
	int t,b;//top bottom
}L[N];
int ls;
inline void calc(){
	up[0]=1;
	rep(i,1,s)
		rep(j,1,n)
			rep(k,1,wd(i))
				if (asum(i,j,j,k)==0) {
					ud(i,j,k)=ud(i,j-1,k);
					L[++ls]=(line){ud(i,j,k),j};
				}
				else ud(i,j,k)=j+1;

}
inline bool cmp(const line &a,const line &b){
	return a.t < b.t || (a.t==b.t && a.b < b.b);
}
inline void work(){
	ls=0;
	init();calc();
	sort(L+1,L+ls+1,cmp);
	int ans=0;
	L[0].t=L[0].b=-1;
	rep(i,1,ls) if (cmp(L[i-1],L[i])){
		int t=L[i].t,b=L[i].b;
		//inside
		rep(j,1,s){
			int tmp=0;
			rep(k,1,wd(j)){
				if (asum(j,t,b,k)==0) tmp++;else tmp=0;
				ans=max(ans,tmp*(b-t+1));
			}
		}
		//outside(?)
		int th=0,lm,rm,lmax=0,rmax=0,lmn,rmn,lmax1=0,rmax1=0;
		rep(j,1,s){
			lm=wd(j);rm=1;
			rep(l,1,wd(j)) if (asum(j,t,b,l)!=0) {lm=l-1;break;}
			if (lm==wd(j)) th+=wd(j);else{
				dep(r,wd(j),1) if (asum(j,t,b,r)!=0) {rm=r+1;break;}
				rm=wd(j)-rm+1;
				if (lm>=lmax){
					lmax1=lmax, lmax=lm, lmn=j;
				}else lmax1=lm;
				if (rm>=rmax){
					rmax1=rmax, rmax=rm, rmn=j;
				}else rmax1=rm;
			}
		}
		if (lmn!=rmn) th+=lmax+rmax;else th+=max(lmax+rmax1,rmax+lmax1);
		ans=max(ans,th*(b-t+1));
	}
	printf("%d\n",ans);
}
int main(){
	int t;scanf("%d",&t);
	rep(i,1,t) work();
	return 0;
}
Problem3874

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef long long LL;
const int N=500;
struct food{
	LL p,s;
	int next;
}f[N];
bool cmp(const food &a,const food &b){
	return a.p < b.p || (a.p == b.p && a.s > b.s);
}
LL m,F;
LL calc(LL n){
	LL tmp=m-F*n,ans=0;
	LL days=0;
	for(int i=1;i;i=f[i].next){
		LL t=min(tmp/f[i].p/n,f[i].s+1-days);
		if (t>0){
			days+=t, ans+=t*n, tmp-=t*f[i].p*n;
		}
		if (tmp/f[i].p/n==0 && f[i].s >= days){
			ans+=tmp/f[i].p;break;
		}
	}
	return ans;
}

int main(){
	int n;scanf("%lld%lld%d",&m,&F,&n);
	rep(i,1,n) scanf("%lld%lld",&f[i].p,&f[i].s);
	sort(f+1,f+n+1,cmp);
	int max=1;
	rep(i,1,n) f[i].next=0;
	rep(i,1,n)if (f[i].s > f[max].s) {f[max].next=i;max=i;}
	LL l=0,r=m/F+1;
	while (l+1<r){
		LL mid=(l+r) >> 1;
		if (calc(mid) < calc(mid+1)) l=mid; else r=mid;
	}
	printf("%lld\n",calc(r));
	return 0;
}
Problem3875

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define reg1(i,a) for(int i=u1[a];i;i=e1[i].pre)
#define reg2(i,a) for(int i=u2[a];i;i=e2[i].pre)
typedef long long LL;
using namespace std;
const int N=200010,M=3000000;
int u1[N],u2[N];
struct edge{
	int to,pre;
}e1[M],e2[M];
int l1=0,l2=0;
void ins1(int a,int b){
	e1[++l1]=(edge){b,u1[a]}, u1[a]=l1;
}
void ins2(int a,int b){
	e2[++l2]=(edge){b,u2[a]}, u2[a]=l2;
}
int q[N];
bool h[N];
LL s[N],k[N];
#define u e1[i].to
#define v e2[i].to
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n){
		int r;
		scanf("%lld%lld%d",&k[i],&s[i],&r);
		rep(j,1,r){
			int t;scanf("%d",&t);
			ins1(i,t);ins2(t,i);
		} 
	}
	int top=0,tail=n;
	rep(i,0,n-1) h[i+1]=true,q[i]=i+1;
	int x;
	while (top!=tail){
		x=q[top++];top%=N;h[x]=false;
		LL tmp=k[x];
		reg1(i,x) tmp+=s[u];
		if (tmp < s[x]){
			s[x]=tmp;
			reg2(i,x) if (!h[v]) {q[tail++]=v;tail%=N;h[v]=true;}
		}
	}	
	printf("%lld\n",s[1]);
	return 0;
}
Problem3876

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
#define ew e[i].w
#define ec e[i].c
#define iw e[i^1].w
#define iv e[i^1].to
using namespace std;
const int N=400,M=500000,inf=0x7fffffff;
int u[N];
struct edge{
	int to,pre,w,c;
}e[M];
int S,T,l=1;
void ins(int a,int b,int w,int c){
	e[++l]=(edge){b,u[a],w,c};u[a]=l;
}
void insert(int a,int b,int w,int c){
	ins(a,b,w,c);ins(b,a,0,-c);
}
int n;
int q[N],inq[N],from[N],h[N];
bool spfa(){
	int l=0,r=1;rep(i,0,n+1) h[i]=inf,inq[i]=0,from[i]=0;
	h[q[0]=S]=0;
	while (l!=r){
		int x=q[l++];l%=N;inq[x]=0;
		reg(i,x) if (ew && h[x]+ec < h[v]){
			h[v]=h[x]+ec;from[v]=i;
			if (!inq[v]) inq[v]=1,q[r++]=v,r%=N;
		}
	}
	return h[T]!=inf;
}
int ans=0;
void mcf(){
	int x=inf;
	for(int i=from[T];i;i=from[iv]) x=min(x,ew);
	for(int i=from[T];i;i=from[iv]) ew-=x,iw+=x,ans+=x*ec;
}
int in[N];
int main(){
	scanf("%d",&n);
	int low_sum_cost=0;
	rep(i,1,n){
		int m;scanf("%d",&m);
		rep(j,1,m){
			int a,b;scanf("%d%d",&a,&b);
			low_sum_cost+=b;
			insert(i,a,inf,b);
			in[i]--,in[a]++;
		}
		insert(i,1,inf,0);
	}
	S=0, T=n+1;
	rep(i,1,n) if (in[i]>0) insert(S,i,in[i],0); else insert(i,T,-in[i],0);
	while (spfa()) mcf();
	printf("%d\n",ans+low_sum_cost);
	return 0;
}
/*Debug:
    It should be "for(int i=from[T];i;i=from[iv])"  not    "for(int i=from[T];i;i=iv)".
*/
Problem3878

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;
const int N=140010;
struct modify{
    int t,a;
}m[N];
LL s[N];
int t1[N*4],t2[N*4],t3[N*4],t4[N*4];
struct tt{
    int x,pos;
}t[N];
int ans[N];
inline bool cmp(const tt &a,const tt &b){
    return a.x<b.x;
}
inline void prod(int x,int a){
    t1[x]*=a;t2[x]*=a;t3[x]*=a;
}
inline void push(int x){
    int lc=x << 1,rc=lc+1;
    if (t4[x]!=0) {t4[lc]=t4[rc]=t4[x];t4[x]=t2[lc]=t2[rc]=t3[lc]=t3[rc]=0;t1[lc]=t1[rc]=1;}
    prod(lc,t1[x]);prod(rc,t1[x]);
    t2[lc]+=t2[x];t2[rc]+=t2[x];
    t3[lc]+=t3[x];t3[rc]+=t3[x];
    t1[x]=1;t2[x]=t3[x]=t4[x]=0;
}
inline LL find1(int x,int l,int r,int a){
    if (l==r){
        if (t4[x]!=0) {s[l]=t4[x];t4[x]=0;}
        s[l]=s[l]*t1[x]+t2[x]+t3[x]*t[a].x;
        t1[x]=1;t2[x]=t3[x]=0;
        return s[l];
    }
    push(x);
    int mid=(l+r) >> 1,lc=x << 1,rc=lc+1;
    if (a<=mid) return find1(lc,l,mid,a); else return find1(rc,mid+1,r,a);
}
inline void set(int x,int l,int r,int a,int b,int d){
    if (l==r){
        t1[x]=1;t2[x]=t3[x]=t4[x]=0;s[l]=d;
    }   
    if (a<=l && r<=b) {t1[x]=1;t2[x]=t3[x]=0;t4[x]=d;return;}
    int mid=(l+r) >> 1,lc=x << 1,rc=lc+1;
    push(x);
    if (a<=mid) set(lc,l,mid,a,b,d);if (b>mid) set(rc,mid+1,r,a,b,d);
}
int main(){
    int n,Q,L,R,T=1;
    scanf("%d%d%d",&n,&L,&R);
    rep(i,1,n) {
        char c=getchar();
        while (c==' ' || c=='\n' || c=='\r')c=getchar();
        scanf("%d",&m[i].a);
        if (c=='+')m[i].t=1;
        if (c=='-')m[i].t=2;
        if (c=='*')m[i].t=3;
        if (c=='@')m[i].t=4;
    }
    scanf("%d",&Q);
    while ((T << 1) <= Q) T=T << 1;
    rep(i,1,Q) scanf("%d",&t[i].x),t[i].pos=i;
    sort(t+1,t+Q+1,cmp);
    rep(i,1,Q) s[i]=t[i].x;
    rep(i,1,N*4-1) t1[i]=1;memset(t2,0,sizeof(t2));memset(t3,0,sizeof(t3));memset(t4,0,sizeof(t4));
    rep(i,1,n){
        if (t4[1]!=0) push(1);
        if (m[i].t==1) t2[1]=m[i].a;    
        else if (m[i].t==2) t2[1]=-m[i].a;
        else if (m[i].t==3) t1[1]=m[i].a;
        else if (m[i].t==4) t3[1]=m[i].a;
        {int x=0;
        for(int j=T;j;j=j >> 1) if (x+j<=Q) if (find1(1,1,Q,x+j)<L) x+=j;
        if (1<=x) set(1,1,Q,1,x,L);}
        {int x=0;
        for(int j=T;j;j=j >> 1) if (x+j<=Q) if (find1(1,1,Q,Q-(x+j)+1)>R) x+=j;
        if (Q-x+1<=Q) set(1,1,Q,Q-x+1,Q,R);}
    }
    rep(i,1,Q) ans[t[i].pos]=find1(1,1,Q,i);
    rep(i,1,Q) printf("%d\n",ans[i]);
    return 0;
}
Problem3944

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;
 
const int N=2000000;
bool a[N+10];
LL phi[N+10],miu[N+10];
int p[N+10],l=0;
inline void init(){
    rep(i,1,N) a[i]=1;
    phi[1]=miu[1]=1;
    rep(i,2,N) {
        if (a[i]) p[++l]=i,phi[i]=i-1,miu[i]=-1;
        rep(j,1,l){
            int k=i*p[j];
            if (k>N) break;
            a[k]=0;
            if (i%p[j]==0) {
                miu[k]=0, phi[k]=phi[i]*p[j]; 
                break;
            }else phi[k]=phi[i]*(p[j]-1),miu[k]=-miu[i];
        }
    }
    miu[0]=phi[0]=0;
    rep(i,1,N) miu[i]+=miu[i-1],phi[i]+=phi[i-1];
}
 
struct node{
    int x,pre;
    LL sum;
};
const int M=1999993;
struct hash{
    node s[1999993];
    int u[M],l;
    inline hash(){
        l=0;rep(i,0,M-1) u[i]=0;
    }
    inline void ins(int x,LL sum){
        s[++l]=(node){x,u[x%M],sum}; u[x%M]=l;
    }
    inline LL find(int x){
        for(int i=u[x%M];i;i=s[i].pre) if (s[i].x==x) return s[i].sum;
        return -1;
    }
}sp,sm;
 
LL sump(int n){
    if (n<=N) return phi[n];
    LL t=sp.find(n);if (t!=-1) return t;
    t=(((LL)n+1)*n) >> 1;
    int l=1,r;
    while (l<n){
        l++;
        r=n/(n/l);
        t-=((LL)r-l+1)*sump(n/l);
        l=r;
    }
    sp.ins(n,t);
    return t;
}
 
LL summ(int n){
    if (n<=N) return miu[n];
    LL t=sm.find(n);if (t!=-1) return t;
    t=1;
    int l=1,r;
    while(l<n){
        l++;
        r=n/(n/l);
        t-=((LL)r-l+1)*summ(n/l);
        l=r;
    }
    sm.ins(n,t);
    return t;
}
 
void work(){
    int n;scanf("%d",&n);
    printf("%lld %lld\n",sump(n),summ(n));
}
 
int main(){
    int T;scanf("%d",&T);
    init();
    rep(i,1,T) work();
    return 0;
}
Problem3944

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;

const int N=2000000;
bool a[N+1000];
LL phi[N+1000],miu[N+1000];
int p[N+1000],l=0;
inline void init(){
	rep(i,1,N) a[i]=1;
	phi[1]=miu[1]=1;
	rep(i,2,N) {
		if (a[i]) p[++l]=i,phi[i]=i-1,miu[i]=-1;
		rep(j,1,l){
			int k=i*p[j];
			if (k>N) break;
			a[k]=0;
			if (i%p[j]==0) {
				miu[k]=0, phi[k]=phi[i]*p[j]; 
				break;
			}else phi[k]=phi[i]*(p[j]-1),miu[k]=-miu[i];
		}
	}
	miu[0]=phi[0]=0;
	rep(i,1,N) miu[i]+=miu[i-1],phi[i]+=phi[i-1];
}

struct node{
	int x,pre;
	LL sum;
};
const int M=1999993;
struct hash{
	node s[100000];
	int u[M],l;
	inline hash(){
		l=0;rep(i,0,M-1) u[i]=0;
	}
	inline void ins(int x,LL sum){
		s[++l].x=x;
		s[l].pre=u[x%M],s[l].sum=sum; 
		u[x%M]=l;
	}
	inline LL find(int x){
		for(int i=u[x%M];i;i=s[i].pre) if (s[i].x==x) return s[i].sum;
		return -1;
	}
}sp,sm;

inline LL sump(int n){
	if (n<=N) return phi[n];
	LL t=sp.find(n);if (t!=-1) return t;
	t=(((LL)n+1)*n) >> 1;
	int l,r=1;
	while (r<n){
		l=r+1;
		r=n/(n/l);
		t-=((LL)r-l+1)*sump(n/l);
	}
	sp.ins(n,t);
	return t;
}

inline LL summ(int n){	 
	if (n<=N) return miu[n];
	LL t=sm.find(n);if (t!=-1) return t;
	t=1;
	int l,r=1;
	while(r<n){
		l=r+1;
		r=n/(n/l);
		t-=((LL)r-l+1)*summ(n/l);
	}
	sm.ins(n,t);
	return t;
}

void work(){
	int n;scanf("%d",&n);
	printf("%lld %lld\n",sump(n),summ(n));
}

int main(){
	int T;scanf("%d",&T);
	init();
	rep(i,1,T) work();
	return 0;
}
Problem3944

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;

const int N=2000000;
bool a[N+1000];
LL phi[N+1000],miu[N+1000];
int p[N+1000],l=0;
inline void init(){
	rep(i,1,N) a[i]=1;
	phi[1]=miu[1]=1;
	rep(i,2,N) {
		if (a[i]) p[++l]=i,phi[i]=i-1,miu[i]=-1;
		rep(j,1,l){
			int k=i*p[j];
			if (k>N) break;
			a[k]=0;
			if (i%p[j]==0) {
				miu[k]=0, phi[k]=phi[i]*p[j]; 
				break;
			}else phi[k]=phi[i]*(p[j]-1),miu[k]=-miu[i];
		}
	}
	miu[0]=phi[0]=0;
	rep(i,1,N) miu[i]+=miu[i-1],phi[i]+=phi[i-1];
}

struct node{
	int x,pre;
	LL sum;
};
const int M=1999993;
struct hash{
	node s[100000];
	int u[M],l;
	inline hash(){
		l=0;rep(i,0,M-1) u[i]=0;
	}
	inline void ins(int x,LL sum){
		s[++l].x=x;
		s[l].pre=u[x%M],s[l].sum=sum; 
		u[x%M]=l;
	}
	inline LL find(int x){
		for(int i=u[x%M];i;i=s[i].pre) if (s[i].x==x) return s[i].sum;
		return -1;
	}
}sp,sm;

LL sump(int n){
	if (n<=N) return phi[n];
	LL t=sp.find(n);if (t!=-1) return t;
	t=(((LL)n+1)*n) >> 1;
	int l,r=1;
	while (r<n){
		l=r+1;
		r=n/(n/l);
		t-=((LL)r-l+1)*sump(n/l);
	}
	sp.ins(n,t);
	return t;
}

LL summ(int n){	 
	if (n<=N) return miu[n];
	LL t=sm.find(n);if (t!=-1) return t;
	t=1;
	int l,r=1;
	while(r<n){
		l=r+1;
		r=n/(n/l);
		t-=((LL)r-l+1)*summ(n/l);
	}
	sm.ins(n,t);
	return t;
}

void work(){
	int n;scanf("%d",&n);
	printf("%lld %lld\n",sump(n),summ(n));
}

int main(){
	int T;scanf("%d",&T);
	init();
	rep(i,1,T) work();
	return 0;
}
Problem3944

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;

const int N=3000000;
bool a[N+1000];
LL phi[N+1000],miu[N+1000];
int p[N+1000],l=0;
inline void init(){
	rep(i,1,N) a[i]=1;
	phi[1]=miu[1]=1;
	rep(i,2,N) {
		if (a[i]) p[++l]=i,phi[i]=i-1,miu[i]=-1;
		rep(j,1,l){
			int k=i*p[j];
			if (k>N) break;
			a[k]=0;
			if (i%p[j]==0) {
				miu[k]=0, phi[k]=phi[i]*p[j]; 
				break;
			}else phi[k]=phi[i]*(p[j]-1),miu[k]=-miu[i];
		}
	}
	miu[0]=phi[0]=0;
	rep(i,1,N) miu[i]+=miu[i-1],phi[i]+=phi[i-1];
}

struct node{
	int x,pre;
	LL sum;
};
const int M=1999993;
struct hash{
	node s[100000];
	int u[M],l;
	inline hash(){
		l=0;rep(i,0,M-1) u[i]=0;
	}
	inline void ins(int x,LL sum){
		s[++l].x=x;
		s[l].pre=u[x%M],s[l].sum=sum; 
		u[x%M]=l;
	}
	inline LL find(int x){
		for(int i=u[x%M];i;i=s[i].pre) if (s[i].x==x) return s[i].sum;
		return -1;
	}
}sp,sm;

LL sump(int n){
	if (n<=N) return phi[n];
	LL t=sp.find(n);if (t!=-1) return t;
	t=(((LL)n+1)*n) >> 1;
	int l,r=1;
	while (r<n){
		l=r+1;
		r=n/(n/l);
		t-=((LL)r-l+1)*sump(n/l);
	}
	sp.ins(n,t);
	return t;
}

LL summ(int n){	 
	if (n<=N) return miu[n];
	LL t=sm.find(n);if (t!=-1) return t;
	t=1;
	int l,r=1;
	while(r<n){
		l=r+1;
		r=n/(n/l);
		t-=((LL)r-l+1)*summ(n/l);
	}
	sm.ins(n,t);
	return t;
}

void work(){
	int n;scanf("%d",&n);
	printf("%lld %lld\n",sump(n),summ(n));
}

int main(){
	int T;scanf("%d",&T);
	init();
	rep(i,1,T) work();
	return 0;
}
Problem3944

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
typedef long long LL;
using namespace std;

const int N=4000000;
bool a[N+1000];
LL phi[N+1000],miu[N+1000];
int p[N+1000],l=0;
inline void init(){
	rep(i,1,N) a[i]=1;
	phi[1]=miu[1]=1;
	rep(i,2,N) {
		if (a[i]) p[++l]=i,phi[i]=i-1,miu[i]=-1;
		rep(j,1,l){
			int k=i*p[j];
			if (k>N) break;
			a[k]=0;
			if (i%p[j]==0) {
				miu[k]=0, phi[k]=phi[i]*p[j]; 
				break;
			}else phi[k]=phi[i]*(p[j]-1),miu[k]=-miu[i];
		}
	}
	miu[0]=phi[0]=0;
	rep(i,1,N) miu[i]+=miu[i-1],phi[i]+=phi[i-1];
}

struct node{
	int x,pre;
	LL sum;
};
const int M=27673;
struct hash{
	node s[20000];
	int u[M],l;
	inline hash(){
		l=0;rep(i,0,M-1) u[i]=0;
	}
	inline void ins(int x,LL sum){
		s[++l].x=x;
		s[l].pre=u[x%M],s[l].sum=sum; 
		u[x%M]=l;
	}
	inline LL find(int x){
		for(int i=u[x%M];i;i=s[i].pre) if (s[i].x==x) return s[i].sum;
		return -1;
	}
}sp,sm;

LL sump(int n){
	if (n<=N) return phi[n];
	LL t=sp.find(n);if (t!=-1) return t;
	t=(((LL)n+1)*n) >> 1;
	int l,r=1;
	while (r<n){
		l=r+1;
		r=n/(n/l);
		t-=((LL)r-l+1)*sump(n/l);
	}
	sp.ins(n,t);
	return t;
}

LL summ(int n){	 
	if (n<=N) return miu[n];
	LL t=sm.find(n);if (t!=-1) return t;
	t=1;
	int l,r=1;
	while(r<n){
		l=r+1;
		r=n/(n/l);
		t-=((LL)r-l+1)*summ(n/l);
	}
	sm.ins(n,t);
	return t;
}

void work(){
	int n;scanf("%d",&n);
	printf("%lld %lld\n",sump(n),summ(n));
}

int main(){
	int T;scanf("%d",&T);
	init();
	rep(i,1,T) work();
	return 0;
}
Problem3990

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
int n, t, a[5000][16], z[16];
LL ans=0;
void dfs(int x,int qt){
	int tx = 1 << (n - x);
	if (x) 
		rep(i,1,tx) 
			if (a[(i << 1) - 1][x -1] +1 != a[i << 1][x - 1]) return; 
				else a[i][x] = a[i << 1][x - 1] >> 1;

	if (x == n) {ans += z[qt];/*cout <<'-'<<qt<<endl;*/return;}
	dfs(x + 1,qt);
	int tmp[5],tot=0;
	for(int i=1;i <= tx;i+=2)
		if (a[i][x] + 1 != a[i+1][x]){
			tmp[++tot] = i, tmp[++tot] = i + 1;
			if (tot > 4) {tot = 0; break;}
		}
	if (!tot) return;
	rep(i,1,tot)
		rep(j,i+1,tot){
			swap(a[tmp[i]][x], a[tmp[j]][x]);
			dfs(x + 1,qt+1);
			swap(a[tmp[i]][x], a[tmp[j]][x]);
		}
}
int main(){
	z[0] = 1;
	rep(i, 1, 12) z[i] = z[i-1] * i;
	scanf("%d", &n);
	t = 1 << n;
	rep(i,1,t) scanf("%d",&a[i][0]);
	dfs(0,0);
	cout <<ans<<endl;
	return 0;
}
Problem3992

#include <iostream>
#include <cstdio>
#include <algorithm>
#define Rep(i,a) for(int i=0;i<a;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 32768 + 10, P = 1004535809;
int rev[N], w[2][N];
int pow(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % P) if (b & 1) w = 1LL * w * a % P;
	return w;
}
void init(int &n){
	int m = 1, l = 0;
	while (m < n) m <<= 1, l++;
	n = m;
	Rep(i,n){
		int t = 0, k = i;
		rep(j,1,l) t = (t << 1) | (k & 1), k >>= 1;
		rev[i] = t;
	}
	w[1][n] = pow(3, (P - 1) >> l);
	dep(i,l - 1,1) w[1][1 << i] = (1LL * w[1][1 << (i + 1)] * w[1][1 << (i + 1)]) % P;
	w[0][n] = pow(w[1][n], P - 2);
	dep(i,l - 1,1) w[0][1 << i] = (1LL * w[0][1 << (i + 1)] * w[0][1 << (i + 1)]) % P;
}
void ntt(int *a, int l, int f){
	if (f == -1) f = 0;
	Rep(i,l) if (rev[i] < i) swap(a[i], a[rev[i]]);
	for(int n = 2; n <= l; n <<= 1){
		int mid = n >> 1, wn = w[f][n];
		for(int i = 0; i < l; i += n){
			int w = 1;
			Rep(j,mid){
				int t1 = a[i + j], t2 = 1LL * a[i + j + mid] * w % P;
				a[i + j] = (t1 + t2) % P;
				a[i + j + mid] = (t1 - t2) % P;
				w = 1LL * w * wn % P;
			}
		}
	}
	int invl = pow(l, P - 2);
	if (!f) Rep(i,l) a[i] = 1LL * a[i] * invl % P;
}


int n, m, X, s, ind[N], d[N], dl = 0;
int powm(int a, int b){
	int w = 1;
	for(;b;b >>= 1, a = 1LL * a * a % m) if (b & 1) w = 1LL * w * a % m;
	return w;
}
void init_p(){
	int g, t = m - 1;
	for(int i = 2; i * i <= t; i++) if (t % i == 0){
		d[++dl] = (m - 1) / i;
		while (t % i == 0) t /= i;
	}
	if (t > 1) d[++dl] = t;
	rep(i,2,m - 1){
		bool flag = true;
		rep(j,1,dl) if (powm(i, d[j]) == 1) {flag = false;break;}
		if (flag) {g = i; break;}
	}
	int k = 1;
	ind[1] = 0;
	rep(i,1,m - 2) k = k * g % m, ind[k] = i;
}
int a[N], w1[N];
int main(){
	scanf("%d%d%d%d",&n,&m,&X,&s);
	int l = 2 * (m - 1) - 1;
	init(l);
	init_p();
	if (X == 0) X = -1; else X = ind[X];
	int cnt0 = 0;
	rep(i,1,s){
		int tmp; scanf("%d",&tmp); tmp %= m;
		if (tmp == 0) cnt0++; else a[ind[tmp]]++;
	}

	if (X != -1){
		w1[0] = 1;
		for(int i = n; i; i >>= 1){
			ntt(a, l, 1);
			if (i & 1){ 
				ntt(w1, l, 1);
				Rep(i,l) w1[i] = 1LL * w1[i] * a[i] % P;
				ntt(w1, l, -1);
				rep(i, m - 1, l - 1) w1[i - (m - 1)] = (w1[i - (m - 1)] + w1[i]) % P, w1[i] = 0;
			}
			Rep(i,l) a[i] = 1LL * a[i] * a[i] % P;
			ntt(a, l, -1);
			rep(i, m - 1 ,l - 1) a[i - (m - 1)] = (a[i - (m - 1)] + a[i]) % P, a[i] = 0;
	}

		w1[X] = (w1[X] + P) % P;
		printf("%d\n",w1[X]);//ans was in w1 not a
	} else {
		int ans = (pow(n, s) - pow(n, s - cnt0)) % P;
		if (ans < 0) ans += P;
		printf("%d\n",ans);
	}
}
/*
	有两个易错点:
		1.答案是w而不是a
		2.不能直接把0~m-2项之外的直接清0, 要mod m-1，也就是把它们加到 i - (m - 1) 上
*/
Problem3993

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ab(x) (x > 0? x : -x)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define v e[i].to
#define ec e[i].c
#define ic e[i^1].c
#define ecf (ec > eps)
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define ceg(i,a) for(int i=cur[a];i;i=e[i].pre)
using namespace std;
const int N=1000, M=300000;
int S,T,a[N],b[N];
const double eps=0.00000001;
int sum=0;
struct edge{
	int to,pre;
	double c;
}e[M];
int h[N],q[N],cur[N],u[N],l;//init l=1!
void ins(int a,int b,double c){
	e[++l]=(edge){b,u[a],c}, u[a]=l;
}
void insert(int a,int b,double c){
	ins(a,b,c), ins(b,a,0);
}
bool bfs(){
	int l=0, r=1;
	rep(i,S,T) h[i]=-1;
	q[h[S]=0]=S;
	while (l<r){
		int x=q[l++];
		reg(i,x) if (ecf && h[v]==-1) h[v]=h[x]+1, q[r++]=v;
	}
	return h[T]!=-1;
}
double dfs(int x,double f){
	if (x==T) return f;
	double used=0,w;
	ceg(i,x) if (h[x]+1==h[v] && ecf){
		w=min(ec,f-used);w=dfs(v,w);
		ec-=w;if (ecf) cur[x]=i;
		ic+=w;
		used+=w;if (f-used<eps) break;
	}
	if (used<eps) h[x]=-1;
	return used;
}
const double inf=100000000.0;
double dinic(){
	double ans=0;
	while (bfs()){
		rep(i,S,T) cur[i]=u[i];
		ans+=dfs(S,inf);
	}
	return ans;
}
#define rb(x) (x+1)
#define wp(x) (x+n+1)
bool att[N][N];
int n,m;
void build(double t){
	S=1, T=n+m+2;
	l=1;rep(i,S,T) u[i]=0;
	rep(i,1,m) insert(S,wp(i),t*b[i]);
	rep(i,1,n) insert(rb(i),T,a[i]);
	rep(i,1,m) rep(j,1,n) if (att[i][j]) insert(wp(i),rb(j),inf);
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]), sum+=a[i];
	rep(i,1,m) scanf("%d",&b[i]);
	rep(i,1,m) rep(j,1,n) scanf("%d",&att[i][j]);
	double l=0.0,r=inf;
	int t=0;
	while (l+eps<r && t<=10000){
		double mid = (l+r) / 2;
		build(mid);
		double ans=dinic();
		if (ans+eps>sum) r=mid; else l=mid;
	}
	printf("%.6lf\n",l);
	return 0;
}
Problem3994

#include <iostream>
#include <cstdio>
#include <cmath>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long LL;
const int N=50000;
bool a[N+10];
int mu[N+10],p[N+10],t[N+10],l=0;
LL d[N+10];
void init(){
  mu[1]=d[1]=1;t[1]=0;
  rep(i,2,N) a[i]=1;
  rep(i,2,N){
  	if (a[i]){
  		mu[i]=-1,d[i]=2;
  		p[++l]=i;t[i]=1;
  	}
  	rep(j,1,l){
  		int k=p[j]*i;
  		if (k>N) break;
  		a[k]=0;
  		if (i%p[j]){
  			mu[k]=-mu[i];
  			d[k]=d[i]*2;
  			t[k]=1;
  		}else{
  			mu[k]=0;
  			t[k]=t[i]+1;
  			d[k]=d[i]/(t[i]+1)*(t[k]+1);
  			break;
  		}
  	}
  	//if (i<=10) cout <<mu[i]<<' '<<d[i]<<endl;
  }
  mu[0]=d[0]=0;
  rep(i,1,N) mu[i]+=mu[i-1],d[i]+=d[i-1];
}
void work(){
	int n,m;scanf("%d%d",&n,&m);
	int l=1,r;
	LL ans=0;
	for(;l<=n && l<=m;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans+=(LL)(mu[r]-mu[l-1])*d[n/l]*d[m/l];
	}
	printf("%lld\n",ans);
}
int main(){
	int T;scanf("%d",&T);
	init();
	rep(i,1,T) work();
}
Problem3997

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
const int N = 1010;
LL f[N][N];
int a[N][N];
void work(){
	int n,m; scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
	dep(i,n,1) 
		rep(j,1,m)
			f[i][j] = max( max(f[i+1][j],f[i+1][j-1] + a[i][j]), f[i][j-1]);
	printf("%lld\n",f[1][m]);
}
int main(){
	int T; scanf("%d",&T);
	while (T--) work();
	return 0;
}
Problem4008

#include <iostream>
#include <cstdio>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 300;
double p[N], f[N][N], P[N][N];
int d[N];
void work(){
	int n,r;scanf("%d%d",&n,&r);
	rep(i,1,n) scanf("%lf%d",&p[i],&d[i]);
	rep(i,0,r - 1) f[1][i] = 0;f[1][r] = 1;
	rep(i,1,n) {
		P[i][0] = 1.0;
		rep(j,1,r) P[i][j] = P[i][j - 1] * (1 - p[i]);
	}//P : not to be
	double ans=0;
	rep(i,2,n){
		f[i][r] = f[i - 1][r] * P[i - 1][r];
		rep(j,0,r - 1) f[i][j] = f[i - 1][j] * P[i - 1][j] + f[i - 1][j + 1] * (1 - P[i - 1][j + 1]);
	}	
	rep(i,1,n){
		double e = 0;
		rep(j,1,r) e += f[i][j] * (1 - P[i][j]);
		e *= d[i];
		ans += e;
	}
	printf("%.10lf\n",ans);
}
int main(){
	int T;scanf("%d",&T);
	while (T--) work();
	return 0;
}
Problem4011

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#define dep(i, a, b) for(int i = a; i >= b; i--)
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp(a,b) make_pair(a,b) 
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;

inline int read(){
	int x = 0, f = 1;char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}
const int N=100000+10,M=1000000007;
int d[N],tmp[N];

struct edge{
	int to, pre;
}e[2*N];
int u[N], l=1;
void ins(int a, int b){
	d[b]++;
	e[++l] = (edge){b, u[a]}, u[a] = l;
}

int q[N], r;
#define v e[i].to
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
int n;
void init(){
	int l=0; r=0;
	rep(i,1,n) {
		tmp[i] = d[i];if (d[i]==0) q[r++] = i;
	}
	while (l < r){
		int x=q[l++];
		reg(i,x) {
			tmp[v]--;
			if (tmp[v]==0) q[r++] = v;
		}
	}
	r--;
}
LL ans=0,f[N];
LL powe(LL a,int b){
	LL ans = 1;
	for(;b;a=a * a % M, b >>= 1) 
		if (b&1) ans = ans * a % M;
	return ans;
}
LL inv[N];
int main(){
	n=read();
	int m=read(), x=read(), y=read();
	rep(i,1,m) {
		int a=read(),b=read();
		ins(a,b);//如果写成ins(read(),read()) 读入顺序会反掉,吓傻了！
	}
	init();
	ans=1;
	d[y]++;
	rep(i,2,n) ans*=d[i], ans%=M;
	rep(i,1,n) f[i] = 0;
	rep(i,1,n+1) inv[i]=powe(i,M-2);
	if (y==1) f[1] = ans; else f[y]=ans*inv[d[y]] % M;
	rep(j,1,r) if (f[q[j]]) 
		reg(i,q[j]) f[v] += f[q[j]] *inv[d[v]] % M, f[v] %= M;
	ans-=f[x];ans%=M;
	if (ans < 0)  ans+=M;
	printf("%lld\n",ans);
}
Problem4025

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
Problem4025

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
bool cmp(const edge &a, const edge &b){
	return a.s < b.s || (a.s == b.s && a.t > b.t);
}

const int inf = N * 10;
struct node *null;
struct node{
	node *ch[2], *f;
	int s, t, v;
	node* mt;
	bool rev;
	void push(){if (rev) rev = 0, swap(ch[0], ch[1]), ch[0]->rev ^= 1, ch[1]->rev ^= 1;}
	void upd(){
		s = ch[0]->s + ch[1]->s + v;
		mt = ch[0]->mt;
		if (ch[1]->mt->t < mt->t) mt = ch[1]->mt;
		if (v && t < mt->t) mt = this;
	}
	void st(node *o, int d){ch[d] = o, o->f = this;}
	bool c(){return f == null || (f->ch[0] != this && f->ch[1] != this);}
	bool d(){return f->ch[1]==this;}
}T[N * 3];

void rot(node *o){
	node *f = o->f; int d = o -> d();
	if (f->c()) o->f = f->f; else f->f->st(o,f->d());//upd(f->f)?
	f->st(o->ch[d^1], d), o->st(f, d^1);
	f->upd();
}
void fix(node *o){
	if (!o->c()) fix(o->f);
	o->push();
}
void splay(node *o){
	fix(o);
	while (!o->c())
		if (o->f->c()) rot(o); else
			(o->f->d() == o->d()) ? (rot(o->f), rot(o)): (rot(o), rot(o));
	o->upd();
}
void access(node *o){
	node *t = o;
	for(node *c = null; o != null; o = o->f){
		splay(o);
		o->st(c, 1), o->upd();
		c = o;
	}
	splay(t);
}
void mroot(node *o){
	access(o), o->rev ^= 1;//access!
}
void link(node *u, node *v){
	mroot(v), v->f = u, access(v);
}
void cut(node *v){
	access(v), v->ch[0]->f = null, v->ch[0] = null, v->upd();
}
node *findrt(node *o){
	access(o);o->push();
	while (o->ch[0] != null) o = o->ch[0], o->push();
	splay(o);
	return o;
}
node *qry(node *u, node *v){
	mroot(u), access(v);
	return v->mt;
}
int dis(node *u, node *v){
	mroot(u), access(v);
	return v->ch[0]->s;
}
void init(){
	null = &T[0];
	null->ch[0] = null->ch[1] = null->f = null->mt = null;
	null->s = 0, null->t = inf, null->v = null -> rev = 0;
}

#define dot(a) (a + m)
int mxt = 0;
int main(){
	int n, m, t1; scanf("%d%d%d",&n,&m,&t1);
	rep(i,1,m) scanf("%d%d%d%d",&e[i].a,&e[i].b,&e[i].s,&e[i].t), e[i].s++;
	sort(e + 1, e + m + 1, cmp);
	init();
	rep(i,1,n) T[dot(i)] = *null;
	int i = 1;
	rep(j,1,t1){
		for(;i <= m && e[i].s <= j; i++){
			T[i].ch[0] = T[i].ch[1] = T[i].f = null;
			T[i].mt = &T[i];
			T[i].s = T[i].v = 1, T[i].t = e[i].t, T[i].rev = 0;
			if (findrt(&T[dot(e[i].a)]) == findrt(&T[dot(e[i].b)])){
				node *t = qry(&T[dot(e[i].a)], &T[dot(e[i].b)]);
				int tt = t - T;
				int ds = dis(&T[dot(e[i].a)], &T[dot(e[i].b)]);

				if (t->t < e[i].t){
					mroot(t), cut(&T[dot(e[tt].a)]), cut(&T[dot(e[tt].b)]);
					link(&T[i], &T[dot(e[i].a)]), link(&T[i], &T[dot(e[i].b)]);
					if ((ds & 1) == 0) mxt = max(mxt, t->t);
				}else 
					if ((ds & 1) == 0) mxt = max(mxt, e[i].t);
			}else
				link(&T[i], &T[dot(e[i].a)]), link(&T[i], &T[dot(e[i].b)]);
		}
		if (mxt < j) printf("Yes\n"); else printf("No\n");
	}
	return 0;
}
Problem4033

#include <iostream>
#include <cstdio>
#include <algorithm>
#define v e[i].to
#define ds e[i].dis
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
using namespace std;
typedef long long LL;
const int N = 3010;
const LL inf = (1LL << 60);
struct edge{
	int to,pre,dis;
}e[N*2];
int u[N], l=1;
void ins(int a,int b,int dis){
	e[++l]=(edge){b, u[a], dis}, u[a] = l;
}
void insert(int a,int b,int dis){
	ins(a,b,dis), ins(b,a,dis);
}
LL f[N][N];
int sz[N],n,k;
LL tmp[N];
void dfs(int x,int fa){
	sz[x]=1;
	rep(i,2,n) f[x][i]=-inf;
	reg(i,x) if (v!=fa){
		dfs(v,x);
		rep(j,0,n) tmp[j]=f[x][j];
		rep(j,0,n) f[x][j] = -inf;
		rep(j,0,sz[x])
			rep(q,0,sz[v])
				f[x][j+q] = max(f[x][j+q],tmp[j] + f[v][q] + (1LL * q * (k - q) + 1LL *(sz[v] - q) * (n - sz[v] - (k - q))) * ds);
		sz[x]+=sz[v];
	}
}
int main(){
	scanf("%d%d",&n,&k);
	rep(i, 1, n-1){
		int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
		insert(a, b, dis);
	}
	dfs(1,0);
	printf("%lld\n",f[1][k]);
}
Problem4033

#include <iostream>
#include <cstdio>
#include <algorithm>
#define v e[i].to
#define ds e[i].dis
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
using namespace std;
typedef long long LL;
const int N = 3010;
const LL inf = (1LL << 60);
struct edge{
	int to,pre,dis;
}e[N*2];
int u[N], l=1;
void ins(int a,int b,int dis){
	e[++l]=(edge){b, u[a], dis}, u[a] = l;
}
void insert(int a,int b,int dis){
	ins(a,b,dis), ins(b,a,dis);
}
LL f[N][N];
int sz[N],n,k;
LL tmp[N];
void dfs(int x,int fa){
	sz[x]=1;
	rep(i,2,n) f[x][i]=0;
	reg(i,x) if (v!=fa){
		dfs(v,x);
		rep(j,0,n) tmp[j]=f[x][j];
		rep(j,0,n) f[x][j] = 0;
		rep(j,0,sz[x])
			rep(q,0,sz[v])
				f[x][j+q] = max(f[x][j+q],tmp[j] + f[v][q] + (1LL * q * (k - q) + 1LL *(sz[v] - q) * (n - sz[v] - (k - q))) * ds);
		sz[x]+=sz[v];
	}
}
int main(){
	scanf("%d%d",&n,&k);
	rep(i, 1, n-1){
		int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
		insert(a, b, dis);
	}
	dfs(1,0);
	printf("%lld\n",f[1][k]);
}
Problem4033

#include <iostream>
#include <cstdio>
#include <algorithm>
#define v e[i].to
#define ds e[i].dis
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
using namespace std;
typedef long long LL;
const int N = 3010;
const LL inf = (1LL << 60);
struct edge{
	int to,pre,dis;
}e[N*2];
int u[N], l=1;
void ins(int a,int b,int dis){
	e[++l]=(edge){b, u[a], dis}, u[a] = l;
}
void insert(int a,int b,int dis){
	ins(a,b,dis), ins(b,a,dis);
}
LL f[N][N];
int sz[N],n,k;
LL tmp[N];
void dfs(int x,int fa){
	sz[x]=1;
	reg(i,x) if (v!=fa){
		dfs(v,x);
		rep(j,0,n) tmp[j]=f[x][j];
		rep(j,0,n) f[x][j] = 0;
		int t=min(sz[x],k);
        rep(j,0,t){
            int t1=min(sz[v],k-j);
			rep(q,0,t1) f[x][j+q] = max(f[x][j+q],tmp[j] + f[v][q] + (1LL * q * (k - q) + 1LL *(sz[v] - q) * (n - sz[v] - (k - q))) * ds);
		}
		sz[x]+=sz[v];
	}
}
int main(){
	scanf("%d%d",&n,&k);
	rep(i, 1, n-1){
		int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
		insert(a, b, dis);
	}
	dfs(1,0);
	printf("%lld\n",f[1][k]);
}
Problem4033

#include <iostream>
#include <cstdio>
#include <algorithm>
#define v e[i].to
#define ds e[i].dis
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
using namespace std;
typedef long long LL;
const int N = 3010;
const LL inf = (1LL << 60);
struct edge{
    int to,pre,dis;
}e[N*2];
int u[N], l=1;
void ins(int a,int b,int dis){
    e[++l]=(edge){b, u[a], dis}, u[a] = l;
}
void insert(int a,int b,int dis){
    ins(a,b,dis), ins(b,a,dis);
}
LL f[N][N];
int sz[N],n,k;
LL tmp[N];
void dfs(int x,int fa){
    sz[x]=1;
    rep(i,2,n) f[x][i]=0;
    reg(i,x) if (v!=fa){
        dfs(v,x);
        rep(j,0,n) tmp[j]=f[x][j];
        rep(j,0,n) f[x][j] = 0;
        dep(j,sz[x],0)
            dep(q,sz[v],0)
                f[x][j+q] = max(f[x][j+q],tmp[j] + f[v][q] + (1LL * q * (k - q) + 1LL *(sz[v] - q) * (n - sz[v] - (k - q))) * ds);
        sz[x]+=sz[v];
    }
}
int main(){
    scanf("%d%d",&n,&k);
    rep(i, 1, n-1){
        int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
        insert(a, b, dis);
    }
    dfs(1,0);
    printf("%lld\n",f[1][k]);
}
Problem4033

#include <iostream>
#include <cstdio>
#include <algorithm>
#define v e[i].to
#define ds e[i].dis
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
using namespace std;
typedef long long LL;
const int N = 3010;
const LL inf = (1LL << 60);
struct edge{
	int to,pre,dis;
}e[N*2];
int u[N], l=1;
void ins(int a,int b,int dis){
	e[++l]=(edge){b, u[a], dis}, u[a] = l;
}
void insert(int a,int b,int dis){
	ins(a,b,dis), ins(b,a,dis);
}
LL f[N][N];
int sz[N],n,k;
LL tmp[N];
void dfs(int x,int fa){
	sz[x]=1;
	reg(i,x) if (v!=fa){
		dfs(v,x);
		rep(j,0,n) tmp[j]=f[x][j];
		rep(j,0,n) f[x][j] = 0;
		int t=min(sz[x],k);
        dep(j,t,0){
            int t1=min(sz[v],k-j);
			dep(q,t1,0) f[x][j+q] = max(f[x][j+q],tmp[j] + f[v][q] + (1LL * q * (k - q) + 1LL *(sz[v] - q) * (n - sz[v] - (k - q))) * ds);
		}
		sz[x]+=sz[v];
	}
}
int main(){
	scanf("%d%d",&n,&k);
	rep(i, 1, n-1){
		int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
		insert(a, b, dis);
	}
	dfs(1,0);
	printf("%lld\n",f[1][k]);
}
Problem4033

#include <iostream>
#include <cstdio>
#include <algorithm>
#define v e[i].to
#define ds e[i].dis
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define reg(i,x) for(int i=u[x];i;i=e[i].pre)
using namespace std;
typedef long long LL;
const int N = 3010;
const LL inf = (1LL << 60);
struct edge{
    int to,pre,dis;
}e[N*2];
int u[N], l=1;
void ins(int a,int b,int dis){
    e[++l]=(edge){b, u[a], dis}, u[a] = l;
}
void insert(int a,int b,int dis){
    ins(a,b,dis), ins(b,a,dis);
}
LL f[N][N];
int sz[N],n,k;
LL tmp[N];
void dfs(int x,int fa){
    sz[x]=1;
    reg(i,x) if (v!=fa){
        dfs(v,x);
        rep(j,0,n) tmp[j]=f[x][j];
        rep(j,0,n) f[x][j] = 0;
        int t=min(sz[x],k);
        dep(j,t,0){
            int t1=min(sz[v],k-j);
            dep(q,t1,0) f[x][j+q] = max(f[x][j+q],tmp[j] + f[v][q] + (1LL * q * (k - q) + 1LL *(sz[v] - q) * (n - sz[v] - (k - q))) * ds);
        }
        sz[x]+=sz[v];
    }
}
int main(){
    scanf("%d%d",&n,&k);
    rep(i, 1, n-1){
        int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
        insert(a, b, dis);
    }
    dfs(1,0);
    printf("%lld\n",f[1][k]);
}
Problem4036

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20,M=1 << 21;
double p[M];
int main(){
	int n; scanf("%d",&n);int t=(1 << n) - 1;
	rep(i, 0, t) scanf("%lf",&p[i]);
	rep(i, 0, n - 1)
		rep(j, 0, t)
			if (j >> i & 1) p[j] += p[j ^ (1 << i)];
	double ans = 0;
	rep(j, 0, t - 1){
		int cnt = 0;
		rep(i, 0, n - 1) if (j >> i & 1) cnt++;
		double tmp = ((n - cnt) % 2 == 0) ? 1 : -1;
		if (p[j] == 1){
			printf("INF\n");return 0;
		}else{
			ans+=tmp * 1.0 / (p[j] - 1.0);
		}
	}
	printf("%.10lf\n",ans);
}
Problem4036

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20,M=1 << 20;
double p[M];
int main(){
	int n; scanf("%d",&n);int t=(1 << n) - 1;
	rep(i, 0, t) scanf("%lf",&p[i]);
	rep(i, 0, n - 1)
		rep(j, 0, t)
			if (j >> i & 1) p[j] += p[j ^ (1 << i)];
	double ans = 0;
	rep(j, 0, t - 1){
		int cnt = 0;
		rep(i, 0, n - 1) if (j >> i & 1) cnt++;
		double tmp = ((n - cnt) % 2 == 0) ? 1 : -1;
		if (p[j] == 1){
			printf("INF\n");return 0;
		}else{
			ans+=tmp * 1.0 / (p[j] - 1.0);
		}
	}
	printf("%.10lf\n",ans);
}
Problem4036

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20,M=1 << 20;
double p[M];
int main(){
	int n; scanf("%d",&n);int t=(1 << n) - 1;
	rep(i, 0, t) scanf("%lf",&p[i]);
	rep(i, 0, n - 1)
		rep(j, 0, t)
			if (j & (1 << i)) p[j] += p[j ^ (1 << i)];
	double ans = 0;
	rep(j, 0, t - 1){
		int cnt = 0;
		rep(i, 0, n - 1) if (j & (1 << i)) cnt++;
		double tmp = ((n - cnt) % 2 == 0) ? 1 : -1;
		if (p[j] == 1){
			printf("INF\n");return 0;
		}else{
			ans+=tmp * 1.0 / (p[j] - 1.0);
		}
	}
	printf("%.10lf\n",ans);
}
Problem4036

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=20,M=1 << 20;
double p[M];
int main(){
	int n; scanf("%d",&n);int t=(1 << n) - 1;
	rep(i, 0, t) scanf("%lf",&p[i]);
	rep(i, 0, n - 1)
		rep(j, 0, t)
			if (j & (1 << i)) p[j] += p[j ^ (1 << i)];
	double ans = 0;
	rep(j, 0, t - 1){
		int cnt = 0;
		rep(i, 0, n - 1) if (j & (1 << i)) cnt++;
		double tmp = ((n - cnt) % 2 == 0) ? 1 : -1;
		if (p[j] == 1){
			printf("INF\n");return 0;
		}else{
			ans+=tmp * 1 / (p[j] - 1);
		}
	}
	printf("%.10lf\n",ans);
}
Problem4069

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <bitset>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long LL;
const int N = 2000 + 10;
int n, l, r, a[N];
LL ans;
bitset<N> f[N];
LL s[N];
void work1(){
	ans = (1ull << 61) - 1;
	dep(t,60,0){
		ans -= (1LL << t);
		rep(i,0,n) f[i] = 0;
		f[0][0] = 1;
		rep(i,1,n) rep(j,0,i - 1) if (((s[i] - s[j]) | ans) == ans){
			f[i] |= f[j] << 1;
			f[i][r + 1] = 0;
		}
		bool flag = 0;
		rep(i,l,r) if (f[n][i]) flag = 1;
		if (!flag) ans += (1LL << t);
	}
	printf("%lld\n",ans);
}
int F[N];
#define min(a,b) ((a) < (b) ? (a) : (b))
void work2(){	
	ans = (1ull << 61) - 1;
	dep(t,60,0){
		ans -= (1LL << t);
		rep(i,1,n) F[i] = r + 1;
		F[0] = 0;
		rep(i,1,n) rep(j,0,i - 1) 
			if (((s[i] - s[j]) | ans) == ans) F[i] = min(F[i], F[j] + 1);
		if (F[n] > r) ans += (1LL << t);
	}
	printf("%lld\n",ans);

}
int main(){
	scanf("%d%d%d",&n,&l,&r);
	s[0] = 0;
	rep(i,1,n) scanf("%d",&a[i]), s[i] = s[i - 1] + a[i];
	if (l == 1) work2(); else work1();
	return 0;
}
Problem4070

#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
const int N = 30000 + 10, M = 6000000;
int b[N], p[N], c[N], cl = 0;

struct edge{
	int to, pre, c;
}e[M + N];
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
#define v e[i].to
#define ec e[i].c
int u[M], l = 0;
void ins(int a, int b, int c){
	//cout <<a<<' '<<b<<' '<<c<<endl;
	e[++l] = (edge){b, u[a], c}, u[a] = l;
}

int h[M], bel[M], maxnode;
int qn, n, m, pos[200];
typedef pair<int, int> node;
priority_queue<node> q;
#define mp(a,b) make_pair(a,b)
void bfs(){
	int l = 0, r = 1, S = b[1], T = b[2];
	rep(i,1,maxnode) h[i] = -1;
	h[S] = 0;
	q.push(mp(0, S));
	while (!q.empty()){
		int x = q.top().second;
		while (h[x] < -q.top().first){
			q.pop(); if (q.empty()) break;
			x = q.top().second;
		}
		if (q.empty()) break; else q.pop();
		reg(i,x) 
			if (h[v] == -1 || h[v] > h[x] + ec) 
				h[v] = h[x] + ec, q.push(mp(-h[v], v));//, cout <<v<<endl;
		if (bel[x]){
			int p = bel[x], j = x - pos[p], t = pos[p] + j - p;
			if (j - p >  0 && (h[t] == -1 || h[t] > h[x] + 1))
				h[t] = h[x] + 1, q.push(mp(-h[t], t));
			t = pos[p] + j + p;
			if (j + p <= n && (h[t] == -1 || h[t] > h[x] + 1))
				h[t] = h[x] + 1, q.push(mp(-h[t], t));
			if (h[j] == -1 || h[j] > h[x]) 
				h[j] = h[x], q.push(mp(-h[j], j));
		}
	}
	//rep(i,1,maxnode) cout <<i<<' '<<h[i]<<endl;
	printf("%d\n",h[T]);
}
void build_sqrtn(){
	maxnode = n;
	rep(i, 1, cl) if(c[i] <= qn){
		int p = c[i];
		pos[p] = n * i;
		maxnode = n * (i + 1);
		rep(j, 1, n){
			bel[pos[p] + j] = p;
			//if (j - p > 0) ins(pos[p] + j, pos[p] + j - p, 1);
			//if (j + p <= n) ins(pos[p] + j, pos[p] + j + p, 1);
			//ins(pos[p] + j, j, 0);
		}
	}else break;
	rep(i,1,m)if (p[i] <= qn) 
		ins(b[i], pos[p[i]] + b[i], 0); //m edges
}
void build(){
	rep(i,1,m) if (p[i] > qn){
		int t = 0;
		for(int j = b[i] - p[i]; j >  0; j -= p[i]) ins(b[i], j, ++t);//a1
		t = 0;
		for(int j = b[i] + p[i]; j <= n; j += p[i]) ins(b[i], j, ++t);//a2
		//a1 + a2 == msqrt(n) edges
	}
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d",&b[i],&p[i]), c[++cl] = p[i], b[i]++;
	
	sort(c + 1, c + cl + 1);
	cl = (int)(unique(c + 1, c + cl + 1) - c) - 1;
	
	qn = (int)(sqrt(n)); if (!qn) qn++;
	build_sqrtn();
	build();
	bfs();
	return 0;
}
Problem4103

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 1010, M = 300100;
int x[N], y[M], s[N][31];
struct node{
	node *ch[2];
	int s;
	node(){
		ch[0] = ch[1] = NULL;
		s = 0;
	}
}T[11000000];
int l=0;
node *nn(){
	return &T[l++];
}
#define oc (o? o->ch[t] : o)
#define ks k->s 

node *rt[M];
node *rt0[N], *rt1[N];

#define rs(x) (x ? x->s : 0)
#define rc(x,t0) (x ? x->ch[t ^ (t0)] : x)
#define r0(x,t0) (x ? rs(x->ch[0 ^ (t0)]) : 0)

int qry(int u, int D, int k, int d){
	int s0 = 0;
	if (!(d + 1)) return 0;
	rep(i,u,D) s0 += r0(rt1[i],x[i] >> d & 1) - r0(rt0[i],x[i] >> d & 1);
	int t = k > s0;    
	rep(i,u,D) rt0[i] = rc(rt0[i], x[i] >> d & 1), rt1[i] = rc(rt1[i], x[i] >> d & 1);
	return (t << d) + qry(u, D, k - t * s0, d - 1);
}

node* ins(node *o, int y, int d){
	node *k = nn(); if (o) *k = *o;
	ks++;
	if (d + 1){
		int t = y >> d & 1;	
		k -> ch[t] = ins(oc, y, d - 1);
	}
	return k;
}


int main(){
	int n,m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d", &x[i]);
	rep(i,1,m) scanf("%d", &y[i]);
	rt[0] = nn();
	rep(i,1,m) rt[i] = ins(rt[i-1], y[i], 30);
	int q; scanf("%d",&q);
	rep(i,1,q){
		int u,d,l,r,k;scanf("%d%d%d%d%d", &u, &d, &l, &r, &k);
		rep(i,u,d) rt0[i] = rt[l - 1], rt1[i] = rt[r];
		printf("%d\n", qry(u, d, (r - l + 1) * (d - u + 1)  - k + 1, 30));
	}
	return 0;
}
Problem4103

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 1010, M = 300100;
int x[N], y[M], s[N][31];
struct node{
	node *ch[2];
	int s;
}T[11000000];
int l=0;
inline node *nn(){
	return &T[l++];
}
#define oc (o? o->ch[t] : o)
#define ks k->s 

node *rt[M];
node *rt0[N], *rt1[N];

#define rs(x) (x ? x->s : 0)
#define rc(x,t0) (x ? x->ch[t ^ (t0)] : x)
#define r0(x,t0) (x ? rs(x->ch[0 ^ (t0)]) : 0)

inline int qry(int u, int D, int k, int d){
	int s0 = 0;
	if (!(d + 1)) return 0;
	rep(i,u,D) s0 += r0(rt1[i],x[i] >> d & 1) - r0(rt0[i],x[i] >> d & 1);
	int t = k > s0;    
	rep(i,u,D) rt0[i] = rc(rt0[i], x[i] >> d & 1), rt1[i] = rc(rt1[i], x[i] >> d & 1);
	return (t << d) + qry(u, D, k - t * s0, d - 1);
}

inline node* ins(node *o, int y, int d){
	node *k = nn(); if (o) *k = *o;
	ks++;
	if (d + 1){
		int t = y >> d & 1;	
		k -> ch[t] = ins(oc, y, d - 1);
	}
	return k;
}


int main(){
	int n,m; scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d", &x[i]);
	rep(i,1,m) scanf("%d", &y[i]);
	rt[0] = nn();
	rep(i,1,m) rt[i] = ins(rt[i-1], y[i], 30);
	int q; scanf("%d",&q);
	rep(i,1,q){
		int u,d,l,r,k;scanf("%d%d%d%d%d", &u, &d, &l, &r, &k);
		rep(i,u,d) rt0[i] = rt[l - 1], rt1[i] = rt[r];
		printf("%d\n", qry(u, d, (r - l + 1) * (d - u + 1)  - k + 1, 30));
	}
	return 0;
}
Problem4104

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=200010;
pair<int,int> b[N];
int a[N],next[N];
int main(){
	int n,m;scanf("%d%d",&n,&m);n++;
	rep(i,1,n) scanf("%d",&a[i]),b[i].first=a[i],b[i].second=i;
	sort(b+1,b+n+1);
	rep(i,1,n) next[i]=b[i].second;
	for(int i=next[b[1].second];i!=b[1].second;i=next[i]) printf("%d ",a[i]);
	return 0; 	
}
Problem4236

#include <iostream>
#include <cstdio> 
#include <algorithm>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N = 2 * 100000 + 10, M = 1007;
typedef pair<int, int> node;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
struct hash{
	int h[M][M], l, pre[N], s[N];
	node q[N];
	hash(){
		l = 0;
	}
	int ins(node a, int s1){
		for(int i = h[a.x % M][a.y % M]; i; i = pre[i]) 
			if (q[i] == a) return s[i];
		q[++l] = a, s[l] = s1;
		pre[l] = h[a.x % M][a.y % M], h[a.x % M][a.y % M] = l;
		return s1;
	}
}h;
int main(){
	int n; scanf("%d",&n);
	int J = 0, O = 0, I = 0, ans = 0;
	h.ins(mp(n,n),0);
	rep(i,1,n){
		char c = getchar();
		while (c != 'J' && c != 'O' && c != 'I') c = getchar();
		if (c == 'J') J++;
		if (c == 'O') O++;
		if (c == 'I') I++;
		int tmp = h.ins(mp(J - O + n, O - I + n), i);
		if (i - tmp > ans) ans = i - tmp;
	}
	printf("%d\n",ans);
}
Problem4237

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
/*struct N1{
	int first, second;
};
bool operator < (const N1 &a, const N1 &b){
	return (a.x && b.x) ? a.x < b.x : a.y < b.y;
}
set<N1> s;
typedef set<N1>::iterator sit;*/
bool cmp(const node &a, const node &b){
	return a.y < b.y;
}
LL ans = 0;
node s[N], s2[N];
int top, t2;
void cdq(int l, int r){
	if (l == r) return;
	int mid = (l + r) >> 1, mx = t[mid].x;
	sort(t + l, t + r + 1,cmp);
	/*s.clear();
	rep(i,l,r) if (t[i].x <= mx){
		sit it = s.insert((N1){t[i].x, t[i].y}).first, l;
		while (it != s.begin() && (*(l = it, --l)).y > t[i].y) s.erase(l);
	}else{
		sit it = s.find(N1{0, })
	}*/
	top = t2 = 0;
	int L = l, R = r;
	rep(i,L,R) if (t[i].x <= mx){
		while (top && s[top - 1].x < t[i].x) top--;
		s[top++] = t[i]; 
	}else{
		while (t2 && s2[t2 - 1].x > t[i].x) t2--;
		int my = (t2 == 0) ? -1 : s2[t2 - 1].y;
		s2[t2++] = t[i];

		int l = -1, r = top;//[l,r)
		while (l + 1 < r){
			int mid = (l + r) >> 1;
			if (s[mid].y < my) l = mid; else r = mid;
		}

		ans += top - 1 - l;
	}
	sort(t + l, t + r + 1);
	cdq(L, mid), cdq(mid + 1, R);
}
int main(){
	int n; scanf("%d",&n);
	rep(i,1,n) {
		int a, b;
		scanf("%d%d",&a,&b);
		t[i] = mp(a,b);
	}
	sort(t + 1, t + n + 1);
	cdq(1, n);
	printf("%lld\n",ans);
}
Problem4237

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
void cdq(int l, int r){
	if (l == r) return;
	int mid = (l + r) >> 1;
	top = t2 = 0;
	int L = l, R = r;
	rep(i,L,R) if (t[i].x <= mid){
		while (top && s[top - 1].x < t[i].x) top--;
		s[top++] = t[i]; 
	}else{
		while (t2 && s2[t2 - 1].x > t[i].x) t2--;
		int my = (t2 == 0) ? -1 : s2[t2 - 1].y;
		s2[t2++] = t[i];

		int l = -1, r = top;//[l,r)
		while (l + 1 < r){
			int mid = (l + r) >> 1;
			if (s[mid].y < my) l = mid; else r = mid;
		}

		ans += top - 1 - l;
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
Problem4237

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
int find(int x){
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
Problem4237

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
Problem4237

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
inline bool cmp(const node &a, const node &b){
    return a.y < b.y;
}
LL ans = 0;
node s[N], s2[N], t1[N], T2[N];
int top, t2;
void cdq(int l, int r){
    if (l == r) return;
    int mid = (l + r) >> 1;
    top = t2 = 0;
    int L = l, R = r;
    rep(i,L,R) if (t[i].x <= mid){
        while (top && s[top - 1].x < t[i].x) top--;
        s[top++] = t[i]; 
    }else{
        while (t2 && s2[t2 - 1].x > t[i].x) t2--;
        int my = (t2 == 0) ? -1 : s2[t2 - 1].y;
        s2[t2++] = t[i];
 
        int l = -1, r = top;//[l,r)
        while (l + 1 < r){
            int mid = (l + r) >> 1;
            if (s[mid].y < my) l = mid; else r = mid;
        }
 
        ans += top - 1 - l;
    }
    int l1 = 0, l2 = 0;
    rep(i,L,R) if (t[i].x <= mid) t1[++l1] = t[i]; else T2[++l2] = t[i];
    int l3 = L;
    rep(i,1,l1) t[l3++] = t1[i];
    rep(i,1,l2) t[l3++] = T2[i];
    cdq(L, mid), cdq(mid + 1, R);
}
int n; 
inline void init(){
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
Problem4237

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
inline bool cmp(const node &a, const node &b){
    return a.y < b.y;
}
LL ans = 0;
node s[N], s2[N], t1[N], T2[N];
int top, t2;
inline void cdq(int l, int r){
    if (l == r) return;
    int mid = (l + r) >> 1;
    top = t2 = 0;
    int L = l, R = r;
    rep(i,L,R) if (t[i].x <= mid){
        while (top && s[top - 1].x < t[i].x) top--;
        s[top++] = t[i]; 
    }else{
        while (t2 && s2[t2 - 1].x > t[i].x) t2--;
        int my = (t2 == 0) ? -1 : s2[t2 - 1].y;
        s2[t2++] = t[i];
 
        int l = -1, r = top;//[l,r)
        while (l + 1 < r){
            int mid = (l + r) >> 1;
            if (s[mid].y < my) l = mid; else r = mid;
        }
 
        ans += top - 1 - l;
    }
    int l1 = 0, l2 = 0;
    rep(i,L,R) if (t[i].x <= mid) t1[++l1] = t[i]; else T2[++l2] = t[i];
    int l3 = L;
    rep(i,1,l1) t[l3++] = t1[i];
    rep(i,1,l2) t[l3++] = T2[i];
    cdq(L, mid), cdq(mid + 1, R);
}
int n; 
inline void init(){
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
Problem4238

#include <iostream>
#include <cstdio>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 100000 + 10, M = 200000 * 2 + 10;
int n, m, a[M], b[M];
struct edge{
    int to, pre;
}e[M];
int u[N], l = 1;
#define v e[i].to
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
void ins(int a, int b){
    e[++l] = (edge) {b, u[a]}, u[a] = l;
}
int dep[N], good_cnt = 0, bad_cnt = 0, vis[N], good[N], bad[N];
void dfs(int x, int fa){
    vis[x] = 1;good[x] = bad[x] = 0;
    reg(i,x) if (i ^ fa ^ 1){
        if (!vis[v])
            dep[v] = dep[x] + 1, dfs(v, i), good[x] += good[v], bad[x] += bad[v];
        else if (dep[v] <= dep[x]){
            if (dep[x] - dep[v] & 1){
                good_cnt++;
                good[x]++, good[v]--;
            }else{
                bad_cnt++;
                bad[x]++, bad[v]--;
            }
        }
    }
}
int t[N];
int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,m) {
        scanf("%d%d",&a[i],&b[i]);
        ins(a[i],b[i]);
        if (a[i] != b[i]) ins(b[i],a[i]);
    }
    rep(i,1,n) if (!vis[i]) dep[i] = 0, dfs(i, 0), t[i] = 1; else t[i] = 0;
    int ans = 0;
    rep(i,1,n) if (!t[i] && !good[i] && bad[i] == bad_cnt) ans++;
    if (bad_cnt == 1) ans++;
    printf("%d\n",ans);
    return 0;
}
Problem4238

#include <iostream>
#include <cstdio>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 100000 + 10, M = 200000 * 2 + 10;
int n, m, a[M], b[M];
struct edge{
    int to, pre;
}e[M];
int u[N], l = 1;
#define v e[i].to
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
void ins(int a, int b){
    e[++l] = (edge) {b, u[a]}, u[a] = l;
}
int dep[N], good_cnt = 0, bad_cnt = 0, vis[N], good[N], bad[N];
void dfs(int x, int fa){
    vis[x] = 1;good[x] = bad[x] = 0;
    reg(i,x) if (i ^ fa ^ 1){
        if (!vis[v])
            dep[v] = dep[x] + 1, dfs(v, i), good[x] += good[v], bad[x] += bad[v];
        else if (dep[v] <= dep[x]){
            if ((dep[v] ^ dep[x]) & 1){
                good_cnt++;
                good[x]++, good[v]--;
            }else{
                bad_cnt++;
                bad[x]++, bad[v]--;
            }
        }
    }
}
int t[N];
int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,m) {
        scanf("%d%d",&a[i],&b[i]);
        ins(a[i],b[i]);
        if (a[i] != b[i]) ins(b[i],a[i]);
    }
    rep(i,1,n) if (!vis[i]) dep[i] = 0, dfs(i, 0), t[i] = 1; else t[i] = 0;
    int ans = 0;
    rep(i,1,n) if (!t[i] && !good[i] && bad[i] == bad_cnt) ans++;
    if (bad_cnt == 1) ans++;
    printf("%d\n",ans);
    return 0;
}
Problem4239

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define binary(a,L) for(l=head[a], r=head[a + 1]; l + 1 < r; mid = (l + r) >> 1, (y[mid] <= L ? (l = mid) : (r = mid)))
using namespace std;
const int M = 300000 + 10;
struct bus{
	int a, b, x, y, num;
}b[M];
bool cmp1(const bus &a, const bus &b){
	return a.b < b.b || (a.b == b.b && a.y < b.y) || (a.a == b.b && a.y == b.y && a.num < b.num);
}
bool cmp2(const bus &a, const bus &b){
	return a.y < b.y ||  (a.y == b.y && a.num < b.num); 
}
int y[M], f[M], s[M], head[M];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d%d%d",&b[i].a, &b[i].b, &b[i].x, &b[i].y), b[i].num = i;
	 
	sort(b + 1, b + m + 1, cmp1);
	rep(i,1,m) b[i].num = i, y[i] = b[i].y;
	b[0].b = 0;
	rep(i,1,m) if (b[i].b != b[i - 1].b) head[b[i].b] = i;
	head[n + 1] = m + 1;
	dep(i,n,1) if (head[i] == 0) head[i] = head[i + 1];

	sort(b + 1, b + m + 1, cmp2);
	rep(i,1,m) f[i] = s[i] = -1;
	rep(i,1,m){
		int x = b[i].num;
	 	if (b[i].a == 1) {
	 		f[x] = b[i].x;
	 		if (head[b[i].b] == x) s[x] = f[x]; else s[x] = max(s[x - 1], f[x]);
	 	}else{
	 		int l,r,mid;//[l,r)
	 		binary(b[i].a, b[i].x);
	 		if (l == r){
	 			f[x] = -1;
		 		if (head[b[i].b] == x) s[x] = f[x]; else s[x] = max(s[x - 1], f[x]);
	 		}else if (y[l] <= b[i].x){
	 			f[x] = s[l];
		 		if (head[b[i].b] == x) s[x] = f[x]; else s[x] = max(s[x - 1], f[x]);
	 		}else{
	 			f[x] = -1;
		 		if (head[b[i].b] == x) s[x] = f[x]; else s[x] = max(s[x - 1], f[x]);
	 		}
	 	}
	}
	int Q; scanf("%d",&Q);
	rep(i,1,Q) {
	 	int L; scanf("%d",&L);
	 	int l, r, mid;
	 	binary(n, L);
	 	if (l == r) printf("-1\n"); else if (y[l] <= L) printf("%d\n",s[l]); else printf("-1\n");
	}
	return 0;
}
Problem4239

#include <iostream>
#include <cstdio>
#include <algorithm>
#define max(a,b) ((a) < (b) ? (b) : (a))
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define get(L) ((l < r && y[l] <= L) ? s[l] : -1)
#define upd() s[x] = (head[b[i].b] == x) ? f[x] : max(s[x - 1], f[x]);
#define binary(a,L) for(l=head[a], r=head[a + 1]; l + 1 < r; mid = (l + r) >> 1, (y[mid] <= L ? (l = mid) : (r = mid)))
using namespace std;
const int M = 300000 + 10;
struct bus{
	int a, b, x, y, num;
}b[M];
bool cmp1(const bus &a, const bus &b){
	return a.b < b.b || (a.b == b.b && a.y < b.y) || (a.a == b.b && a.y == b.y && a.num < b.num);
}
bool cmp2(const bus &a, const bus &b){
	return a.y < b.y ||  (a.y == b.y && a.num < b.num); 
}
int y[M], f[M], s[M], head[M];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	rep(i,1,m) scanf("%d%d%d%d",&b[i].a, &b[i].b, &b[i].x, &b[i].y), b[i].num = i;
	 
	sort(b + 1, b + m + 1, cmp1);
	rep(i,1,m) b[i].num = i, y[i] = b[i].y;
	b[0].b = 0;
	rep(i,1,m) if (b[i].b != b[i - 1].b) head[b[i].b] = i;
	head[n + 1] = m + 1;
	dep(i,n,1) if (head[i] == 0) head[i] = head[i + 1];

	sort(b + 1, b + m + 1, cmp2);
	rep(i,1,m) f[i] = s[i] = -1;
	rep(i,1,m){
		int x = b[i].num;
	 	if (b[i].a == 1) {
	 		f[x] = b[i].x;
	 		if (head[b[i].b] == x) s[x] = f[x]; else s[x] = max(s[x - 1], f[x]);
	 	}else{
	 		int l,r,mid;//[l,r)
	 		binary(b[i].a, b[i].x);
	 		f[x] = get(b[i].x);
	 		upd();
	 	}
	}
	int Q; scanf("%d",&Q);
	rep(i,1,Q) {
	 	int L; scanf("%d",&L);
	 	int l, r, mid;
	 	binary(n, L);
	 	printf("%d\n",get(L));
	}
	return 0;
}
Problem4240

#include <iostream>
#include <cstdio>
#include <algorithm>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 300000 + 10;
typedef pair<int, int> node;
#define h first
#define num second
int s[N], n;
void add(int x){
	for(; x <= n; x += (-x) & x) s[x]++;
}
int sum(int x){
	int ans = 0;
	for(; x; x -= (-x) & x) ans += s[x];
	return ans;
}
node a[N];
typedef long long LL;
int main(){
	LL ans = 0;
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i].h), a[i].h = -a[i].h, a[i].num = i;
	sort(a + 1, a + n + 1);
	a[n + 1].h = 0;
	int tt = 0;
	rep(i,1,n){
		int t = sum(a[i].num);
		ans += min(t, tt - t);
		if (a[i + 1].h != a[i].h) {
			dep(j,i,1) {if (a[j].h == a[i].h) add(a[j].num); else break;}
			tt = i;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
Problem4241

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 100015, M = 350;
typedef long long LL;
LL f[M][M];
int a[N], bel[N], cnt[M][N], b[N], n, q, l, L[M], R[M], c[N];
int find(int x){
	int l = 1, r = n + 1;//[l,r)
	while (l + 1 < r){
		int mid = (l + r) >> 1;
		if (b[mid] <= x) l = mid; else r = mid;
	}
	return l;
}
int main(){
	scanf("%d%d",&n,&q);
	rep(i,1,n) scanf("%d",&a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1);
	rep(i,1,n) a[i] = find(a[i]);

	int len = sqrt(n), m;
	if (len == 0) len++;
	rep(i,1,n) {
		bel[i] = (i - 1) / len + 1;
		if (i % len == 1) L[bel[i]] = i;
		if (i % len == 0) R[bel[i]] = i;
	}
	m = bel[n], R[m] = n;


	rep(i,1,n) cnt[bel[i]][a[i]]++;
	rep(i,2,m) rep(j,1,n) cnt[i][j] += cnt[i - 1][j];
	
	rep(i,1,m)
		rep(j,i,m){
			f[i][j] = f[i][j - 1];
			rep(k,L[j],R[j]){
				int t = a[k];
				LL t1 = (long long)(cnt[j][t] - cnt[i - 1][t]) * b[t];
				f[i][j] = max(t1, f[i][j]); 
			}
		}


	rep(i,1,q){
		int l, r; scanf("%d%d",&l,&r);
		int l1 = bel[l], r1 = bel[r];
		LL ans = 0;
		if (l1 == r1){
			rep(i,l,r) {
				int t = a[i];
				c[t]++, ans = max(1LL * c[t] * b[t], ans);
			}
			printf("%lld\n",ans);
			rep(i,l,r) c[a[i]]--;
		}else{
			r1--;
			ans = f[l1 + 1][r1];
			rep(i,l,R[l1]) {
				int t = a[i];
				c[t]++, ans = max(1LL * (c[t] + cnt[r1][t] - cnt[l1][t]) * b[t], ans);
			}
			rep(i,R[r1] + 1, r){
				int t = a[i];
				c[t]++, ans = max(1LL * (c[t] + cnt[r1][t] - cnt[l1][t]) * b[t], ans);				
			}
			printf("%lld\n",ans);
			rep(i,l,R[l1]) c[a[i]]--;
			rep(i,R[r1] + 1,r) c[a[i]]--;
		}
	}
	return 0;
}
Problem4242

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 2000 + 10, M = 200000 + 10;
char mp[N][N];
typedef pair<int, int> node;
#define x first
#define y second
#define mp(a,b) make_pair(a,b)
int dx[5], dy[5];
node bd[M], q[N * N], v[N][N];
int r = 0;
void init(){
	dx[0] = 0, dy[0] = 1;
	dx[1] = 1, dy[1] = 0;
	dx[2] = 0, dy[2] = -1;
	dx[3] = -1,dy[3] = 0;
}

vector<node> edge[N * N];
#define pb(a) push_back(a)

int n, m, p, Q;
void bfs(){
	int l = 0;
	while (l < r){
		node a = q[l++];
		rep(i,0,3){
			node b = mp(a.x + dx[i], a.y + dy[i]);
			if (b.x && b.x <= n && b.y && b.y <= m && mp[b.x][b.y] != '#'){
				node &va = v[a.x][a.y], &vb = v[b.x][b.y];
				if (vb == mp(0,0)) 
					vb = mp(va.x + 1, va.y), q[r++] = b;
				else if (va.y != vb.y)
				edge[va.x + vb.x].pb(mp(va.y, vb.y));//be careful with the definition of the distance
			}
		}
	}
}

struct edg{
	int to, pre, c;
}e[M * 2];
int u[M], l = 0;
void ins(int a, int b, int c){
	e[++l] = (edg){b, u[a], c}, u[a] = l;
}
void insert(int a, int b, int c){
	ins(a,b,c), ins(b,a,c);
}
#define v e[i].to
#define ec e[i].c
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)

int f[M], fa[M], vis[M], R[M];
int find(int x){
	return f[x] == x ? x : f[x] = find(f[x]);
}
void kruskal(){
	rep(i,1,p) f[i] = i;
	rep(i,0,n * m)
		for(vector<node>::iterator it = edge[i].begin();it != edge[i].end();it++){
			int fa = find((*it).x), fb = find((*it).y);
			if (fa != fb) insert((*it).x,  (*it).y, i), f[fa] = fb;
		}
}

int dep[M];
void dfs(int x){
	vis[x] = 1;
	reg(i,x) if (!vis[v]) dep[v] = dep[x] + 1, fa[v] = x, R[v] = ec, dfs(v);
}

int g[M][20], g1[M][20];

#define max(a,b) ((a) < (b) ? (b) : (a))
int qry(int a, int b){
	if (find(a) != find(b)) return -1;
	if (dep[a] < dep[b]) swap(a,b);
	int ans = 0;
	dep(i,19,0) if (g[a][i] && dep[g[a][i]] >= dep[b]) ans = max(ans, g1[a][i]), a = g[a][i];
	dep(i,19,0) if (g[a][i] != g[b][i]) ans = max(ans, g1[a][i]), ans = max(ans, g1[b][i]), a = g[a][i], b = g[b][i];
	if (a != b) ans = max(ans, R[a]), ans = max(ans, R[b]);
	return ans;
}
#undef v

int main(){
	init();
	scanf("%d%d%d%d",&n,&m,&p,&Q);
	rep(i,1,n) scanf("%s",mp[i] + 1);
	int a, b;
	rep(i,1,p) scanf("%d%d",&a,&b), bd[i].x = a, bd[i].y = b, q[r++] = mp(a,b), v[a][b] = mp(0, i);
	bfs();
	kruskal();
	rep(i,1,p) if (vis[i] == 0) dep[i] = 1, dfs(i);
	rep(i,1,p) if (fa[i]) g[i][0] = fa[i], g1[i][0] = R[i];
	rep(j,1,19)
		rep(i,1,p)
			g[i][j] = g[g[i][j - 1]][j - 1], g1[i][j] = max(g1[g[i][j - 1]][j - 1], g1[i][j - 1]);
	rep(i,1,Q){
		scanf("%d%d",&a,&b);
		printf("%d\n",qry(a,b));
	}
}
Problem4243

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

const int N = 200000 + 10;
int f[N], s[N];
int find(int x){
	return f[x] == x ? x : f[x] = find(f[x]);
}
void Union(int a, int b){
	int fa = find(a), fb = find(b);
	if (fa != fb){
		s[fa] += s[fb];
		f[fb] = fa;
	}
}

int n, m;
struct edge{int to, pre;}e[N * 4];
int u[N], l = 0;
void ins(int a, int b){e[++l] = (edge){b, u[a]}, u[a] = l;} 
#define v e[i].to
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)

struct E{int a,b,c;}ed[N * 2];
bool operator < (const E &a, const E &b){
	return (a.a < b.a) || (a.a == b.a && a.b < b.b) || (a.a == b.a && a.b == b.b && a.c < b.c);
} 

bool vis[N];
int q[N];

void bfs(){
	int l = 0, r = 0;
	rep(i,1,n) if (vis[i]) q[r++] = i;
	while (l < r){
		int x = q[l++];
		reg(i,x) if (vis[v]) Union(x, v); else {
			vis[v] = 1, q[r++] = v;
			Union(x, v);
		}
	}
}


int main(){
	scanf("%d%d",&n,&m);
	int a, b;
	rep(i,1,n) s[i] = 1, f[i] = i, vis[i] = 0;
	rep(i,1,m) {
		scanf("%d%d",&a,&b);
		if (a < b) ed[i] = (E){a, b, 0}; else ed[i] = (E){b, a, 1};
	}
	sort(ed + 1, ed + m + 1);

	rep(i,1,m){
		if (i < m && ed[i].a == ed[i + 1].a && ed[i].b == ed[i + 1].b)
			Union(ed[i].a, ed[i].b), vis[ed[i].a] = vis[ed[i].b] = 1; 
		if (ed[i].c == 1) ins(ed[i].b, ed[i].a); else ins(ed[i].a, ed[i].b);
	}
	rep(x,1,n){
		int flag = 0, cnt = 0;
		reg(i,x){
			if (flag) Union(v, flag); else flag = v;
			cnt++;
		}
		if (cnt > 1) reg(i,x) vis[v] = 1;
	}

	bfs();
	long long ans = 0;
	rep(i,1,n) if (f[i] == i) ans += 1LL * s[i] * (s[i] - 1);
	rep(i,1,m){
		int a = ed[i].a, b = ed[i].b;
		if (find(a) != find(b)) ans++;
	}
	printf("%lld\n",ans);
	return 0;
}
Problem4244

#include <iostream>
#include <cstdio>
#include <algorithm>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 3000 + 10;
typedef long long LL;
int a[N], b[N], c[N], d[N];
LL f[N][N];
int main(){
    int n, T;  scanf("%d%d",&n,&T);
    rep(i,1,n){
        int u, v, D, e;
        scanf("%d%d%d%d",&u,&v,&D,&e);
        d[i] = u + e; 
        b[i] = u + v;
        c[i] = D + e;
        a[i] = v + D;
    }
    f[1][0] = b[1];
    rep(i,1,n) f[1][i] = a[1] * i;
 
    rep(i,2,n){
        f[i][n] = f[i - 1][n] + 2 * n * T + min(b[i], c[i]);
        dep(j,n - 1,0) {
            f[i][j] = f[i][j + 1] + d[i];
            f[i][j] = min(f[i][j], f[i - 1][j + 1] + 2 * (j + 1) * T + d[i]);
            f[i][j] = min(f[i][j], f[i - 1][j] + 2 * j * T + b[i]);
            if (j) f[i][j] = min(f[i - 1][j] + 2 * j * T + c[i], f[i][j]);
        }
        rep(j,1,n) {
            f[i][j] = min(f[i][j], f[i][j - 1] + a[i]);
            f[i][j] = min(f[i][j], f[i - 1][j - 1] + 2 * (j - 1) * T + a[i]);
        }
    }

    printf("%lld\n",f[n][0] + (n + 1) * T);
    return 0;
}
Problem4245

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
typedef long long LL;
using namespace std;
const int N = 500000 + 10;
LL s[N], ans = 0;
bool b[N], c[N];
int main(){
	int n, m; scanf("%d%d",&n,&m);
	s[0] = 0;
	rep(i,1,n) scanf("%lld",&s[i]), s[i] ^= s[i - 1];
	rep(i,1,n) b[i] = 1;
	ans = (1ull << 63) - 1;
	dep(i,62,0){
		LL t = 1LL << i;
		rep(j,1,n) c[j] = b[j] && ((s[j] & t) == 0);
		int tmp = 0;
		rep(j,1,n) if (c[j]) tmp++;
		if (tmp >= m && c[n]){
			ans -= t;
			rep(j,1,n) b[j] = c[j]; 
		}
	}
	printf("%lld\n",ans);
}
Problem4247

#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 2000 + 10, INF = 2000000010;
int a[N], b[N], f[N][N], q[N], Q;
int main(){
    int n; scanf("%d",&n);
    int l = 0, Q = 0;
    rep(i,1,n){
        int x, y;
        scanf("%d%d",&x,&y); if (x == 0) q[++Q] = y; else a[++l] = x, b[l] = y;
    }
    sort(q + 1, q + Q + 1);
    f[0][0] = -INF, f[0][1] = 0; rep(i,2,n) f[0][i] = -INF;
    rep(i,1,l){
        rep(j,0,n) f[i][j] = f[i - 1][j];
        rep(j,1,n)
            if (f[i - 1][j] != -INF){
                int k = j - 1 + a[i]; if (k > n) k = n;
                f[i][k] = max(f[i - 1][j] + b[i], f[i][k]);
            }
    }
    int j = Q, aj = 0, ans = 0;
    rep(i,0,n){
        if (j && i && q[j] > 0) aj += q[j], j--;
        if (f[l][i] != -INF) ans = max(ans, aj + f[l][i]);
    }
    printf("%d\n",ans);
}
﻿









HOMEBack

	

			 
		 
		 
		 
		
			
		
	
한국어中文فارسیEnglishไทย
版权所有 ©2008-2012 大视野在线测评 |  | 
湘ICP备13009380号站长统计
Based on opensource project .
hustoj
