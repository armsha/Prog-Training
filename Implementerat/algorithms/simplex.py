

def insertSlack(A):
	# Add a slack variable for each <= to get ==
	pass

def findBaseSoltion(A):
	# Remove n-m vars and solve leftover mxm system
	pass

def buildTablo( c, A, b ):
	# Build the simplex tablo
	pass

def simplexSolve( c, A, b ):
	#solve max ctx, where Ax<=b
	# x >= 0 all, also added as -1 0 ... <= 0 all vars
	# First make A to lteq for all before passing here, and see that all added
	
	A = insertSlack(A)
	base = findBaseSoltion(A)
	tablo = buildTablo( c, A, b )
	#...


c = [30,20]
b = [100,80,40,0,0]
A = [[2,1],[1,1],[1,0],[-1,0],[0,-1]]

print simplexSolve(c,b,A)

