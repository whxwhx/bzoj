/*
	m堆石子，共n个，那么似乎要n+m-1次操作
	考虑可能有大小为1的石子堆
	但是游戏的中间新产生的大小为1的石子堆肯定没用，因为先手必胜的话，它总是可以选择把这个石子堆并到另外一堆上去
	同时后手也总可以用一次合并而不是取的操作，来避免出现大小为1的堆
	但是！前提是>=2的堆数>1
	如果只有一堆怎么办呢？在它取到1，也就是s==1的时候把它按照大小为1的堆算！

	处理问题的时候我们要注意把难处理的部分分离出来，同时我们每次要注意子问题的存在

	所以只有开始的1的石子堆数量有关系，别的石子堆我们其实可以直接看成一个大堆了
	每次我们有几个选择：取一个1的石子堆、合并两个1的石子堆、把1并到别的石子堆上、从别的石子堆取/合并
	后继状态其实是一个子问题！
	于是我们可以dp！f[i][j]表示i个大小为1的石子堆，别的石子堆n+m-1 = j的胜负情况
	i <= n j <= n * a[i] + n
*/
#include <iostream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

const int N = 55, M = 55000;
bool f[N][M], vis[N][M];
int a[N];

bool F(int c, int s){
	if (c == 0 && s == -1) return false;
	if (s == 1) s = -1, c++;
	if (vis[c][s + 1]) return f[c][s + 1]; vis[c][s + 1] = true;
	f[c][s + 1] = false;

	if (c > 1 && !f[c][s + 1])		f[c][s + 1] |= !F(c - 2, s + 3);
	if (c && !f[c][s + 1]) 			f[c][s + 1] |= !F(c - 1, s);
	if (s > 0 && !f[c][s + 1]) 		f[c][s + 1] |= !F(c, s - 1);
	if (c && s > 0 && !f[c][s + 1]) f[c][s + 1] |= !F(c - 1, s + 1);
	return f[c][s + 1];
}

int main(){
	int T; scanf("%d",&T);
	while (T--){
		int n; scanf("%d",&n); int cnt = 0, sum = -1;
		rep(i,1,n)
		{ scanf("%d",&a[i]); if (a[i] == 1) cnt++; else sum += a[i] + 1;}
		if (F(cnt, sum)) printf("YES\n"); else printf("NO\n");
	}
	return 0;
}