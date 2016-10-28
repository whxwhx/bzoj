n = 100000
c = 100000
Q = 100000
print n, c, Q
import random
for i in range(n):
	print random.randint(1,c)
for i in range(Q):
	print random.randint(1,n), random.randint(1,n)