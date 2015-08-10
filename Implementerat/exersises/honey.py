
from sys import *

t = int( stdin.readline() )

l = [[[-1 for i in range(30) ] for j in range( 30 )] for k in range(15)] 

l[0][14][14] = 0
l[1][14][14] = 0
l[2][14][14] = 6
 
def getNeigh( x, y ):
	nn = []
	nn = nn + [[x+1,y]] + [[x-1,y]]
	nn = nn + [[x-y%2,y+1]] + [[x+1-y%2,y+1]]
	nn = nn + [[x-y%2,y-1]] + [[x+1-y%2,y-1]]
	return nn

def solvr( n, x, y ):

	if n == 0:
		l[n][x][y] = 0
		if x == 14 and y == 14:
			return 1
		return 0

	if l[n][x][y] == -1:
		sum = 0
		for i in getNeigh( x, y ):
			sum += solvr( n-1, i[0], i[1] )

		l[n][x][y] = sum

	# print( n, x, y, l[n][x][y])

	return l[n][x][y]

def solv( n ):

	if l[n][14][14] == -1:
		l[n][14][14] = solvr(n,14,14)

	return l[n][14][14]

for i in range(t):
	
	n = int( stdin.readline() )
	
	print( solv(n) )

# for i in range(14):
# 	for j in range(30):
# 		for k in range(30):
# 			print(l[i][j][k], end=" ")
# 		print(j)
# 	print(i)

# print( 0, 0, getNeigh(0, 0) )
# print( 1, 0, getNeigh(1, 0) )
# print( 2, 0, getNeigh(2, 0) )
# print( 0, 1, getNeigh(0, 1) )
# print( 1, 1, getNeigh(1, 1) )
# print( 2, 1, getNeigh(2, 1) )
