import numpy as np



def aleatorio(r, n):
	v1 = np.random.randint(r,size = (1,n))
	v2 = np.random.randint(r,size = (1,n))
	v11 = [str(e) for e in v1[0]]
	v22 = [str(e) for e in v2[0]]
	v1 = ', '.join(v11)
	v2 = ', '.join(v22)
	print(n)
	print(v1)
	print(v2)

r, n = map(int,input().split())
aleatorio(r, n)