from sys import *
from math import *

def binSearch( minx, maxx, val, eps, tol, funk ):

	mid = (maxx + minx) / 2.0

	if ( maxx-minx < tol ):
		return mid

	vv = funk(mid)
	if ( vv < val-eps ):
		return binSearch( minx, mid, val, eps, tol, funk )
	if ( vv > val+eps ):
		return binSearch( mid, maxx, val, eps, tol, funk )
	return mid

def intersect( time, currP, V, person ):

	persP = person[:2]
	persA = person[3]
	persV = person[2]
	persVX = persV * cos(persA)
	persVY = persV * sin(persA)
	persCP = [ persP[0]+(persVX*time), persP[1]+(persVY*time)]

	f = lambda t: ((currP[0]-(persCP[0]+persVX*t))**2 + (currP[1]-(persCP[1]+persVY*t))**2)**0.5 -V*t
	T = binSearch( 0, 10**6, 0, 10**-2, 10**-2, f)
	#print( time, currP, V, person, T, "intersected")

	intP = [(persCP[0]+persVX*T),(persCP[1]+persVY*T)]
	retT = ((intP[0]**2 + intP[1]**2)**0.5)/persV
	return [T,intP,retT]



def solve( t, v, A, cp ):


	if len(A)==0:
		return t
	if len(A)==1:
		val = intersect( t, cp, v, A[0] )
		time = val[0]
		np = val[1]
		rt = val[2]
		return time + rt + t

	val = None
	time = None
	np = None

	best = float('inf')
	for x in range(0,len(A)):

		val = intersect( t, cp, v, A[x] )
		time = val[0]
		np = val[1]
		rt = val[2]

		tot = max(t+rt+time, solve( t+time, v, A[:x]+A[x+1:], np ) )

		#print( "P: ", A[x], " res: ", val, tot)

		if tot < best:
		#	print( "improvement ", t, tot, val )
			best = tot


	#print( "done: ", best, t, v, A, cp )

	return best

while True:

	N=int(stdin.readline())
	if N==0:
		break

	v=float(stdin.readline())

	A = [None]*N
	for i in range(N):
		A[i] = [float(i) for i in stdin.readline().split()]

	#print( N, v, A )

	print( round( solve( 0, v, A, [0,0] ) ) )

