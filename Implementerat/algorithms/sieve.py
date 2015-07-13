from math import *

def euclides_sieve(n):
	sieve = [x for x in range(n+1)]

	for i in range(2,int (n**(0.5))+1):
		for x in range(2*i,n+1,i):
			sieve[x] = None
	
	sieve = [x for x in sieve[2:] if x is not None]
	print sieve

euclides_sieve(30)