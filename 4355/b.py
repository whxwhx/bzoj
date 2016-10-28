、 n,m = map(int, raw_input().split())
a = map(int, raw_input().split())
for i in xrange(m):
	t = map(int, raw_input().split())
	if t[0] == 1:
		t[1] -= 1
		for j in xrange(t[1], t[2]):
			a[j] = t[3]
	if t[0] == 2:
		t[1] -= 1
		for j in xrange(t[1], t[2]):
			a[j] = max(a[j] + t[3], 0)
	if t[0] == 3:
		t[1] -= 1
		ans = 0
		for j in xrange(t[1], t[2]):
			if a[j] == 0:
				ans += 1
		print ans             