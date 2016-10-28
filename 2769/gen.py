n = 40000
print n
import random
a=[]
for i in xrange(n):
	if (i % 2 == 0):
		a.append(n - i);
	else:
		a.append(i);
for i in xrange(n):
	print a[i], 