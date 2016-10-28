#include<iostream>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
int n,k,p,f[3010][3010]={{1}};int main(){std::cin >>n>>k>>p;rep(i,2,n)rep(j,1,k)f[i+1][j]=(1LL*f[i][j]*i+1LL*f[i-2][j-1]*(i-1)*i)%p;std::cout <<f[n][k];}