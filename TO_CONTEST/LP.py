
def printMatrix(A):
	for i in A:
		for j in i:
			print(j,end=' ')
		print("")

def dot(v1,v2):
	return sum([v1[i]*v2[i] for i in range(len(v1))])

def introduce_slack(f,A,b):
	number_of_slack=len(A)
	finalMatrix=[[-i for i in f]+[0]*(number_of_slack+1)]
	
	for i in range(number_of_slack):
		finalMatrix.append(A[i]+[0]*i+[1]+[0]*(number_of_slack-i-1)+[b[i]])
	
	return(finalMatrix)

def done(A):
	for i in range(len(A[0])-1):
		if A[0][i]<0:
			return False
	return True

def find_pivot(A):
	mini=0
	minind=-1
	for i in range(len(A[0])):
		if A[0][i]<0 and A[0][i]<mini:
			mini=A[0][i]
			minind=i
	pivot_col=minind
	
	mini=0
	minind=-1
	for i in range(1,len(A)):
		if (A[i][-1]>0 or A[i][-1]<0) and A[i][pivot_col]/A[i][-1]>mini:
			mini=A[i][pivot_col]/A[i][-1]
			minind=i
	pivot_row=minind
	return((pivot_row,pivot_col))

def row_add(A,r1,r2,scalar): #r2 += scalar * r1
	for i in range(len(A[0])):
		A[r2][i]+=scalar*A[r1][i]

def clear_column(A,pivot):
	row=pivot[0]
	col=pivot[1]
	for i in range(len(A)):
		if i!=row and (A[i][col]>0 or A[i][col]<0):
			scalar=-A[i][col]/A[row][col]
			row_add(A,row,i,scalar)
		elif i==row:
			a=A[row][col]
			for j in range(len(A[row])):
				A[row][j]/=a

def pivot(A,B,pivot):
	print("PIVOT",pivot,B)
	B[pivot[0]-1]=pivot[1]
	clear_column(A,pivot)

def conclude(A,B,f):
	result=[0 for i in f]
	
	for i in range(len(B)):
		if B[i]<len(f):
			result[B[i]]=A[i+1][-1]
	
	return(result,A[0][-1])

def simplex(f,A,b):
	N=len(f)
	S=len(A)
	incoming=[N+i for i in range(S)]
	finalMatrix=introduce_slack(f,A,b)
	
	while not done(finalMatrix):
		printMatrix(finalMatrix)
		pivot_coordinates=find_pivot(finalMatrix) #row,col
		pivot(finalMatrix,incoming,pivot_coordinates)
	printMatrix(finalMatrix)
	return conclude(finalMatrix,incoming,f)


f=[30,20]
A=[[2,1],
   [1,1],
   [1,0]]
b=[100,80,40]

print(simplex(f,A,b))

