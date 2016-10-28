n, c, Q = map(int, raw_input().split())
a = [0 for i in range(n + 1)]
for i in range(n):
	a[i + 1] = input()
for i in range(Q):
	l, r = map(int, raw_input().split())
	if (l > r):
		l, r = r, l
	s=[0 for i in range(c + 1)]
	for j in range(l,r + 1):
		s[a[j]] += 1
	ans = 0
	for j in range(c + 1):
		if ((s[j] & 1) == 0 and s[j]):
			ans += 1
	print ans
