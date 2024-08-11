import numpy as np

def aleatorio(n,x):
	print(f'{n} ')
	for i in range(n):
		v = np.random.randint(x+1,size = (1,n))
		v = [str(e) for e in v[0]]
		v = ', '.join(v)
		print(v)
	print()
	for i in range(n):
		v = np.random.randint(x+1,size = (1,n))
		v = [str(e) for e in v[0]]
		v = ', '.join(v)
		print(v)
# n : num of size matrix
# b: num of tiles
# x: max num of aleatory generation
n, x = map(int,input().split())
aleatorio(n,x)

