
def printmatrix(A):
    print('')
    for i in A:
        print(i)
    print('')

def Hungarian(M):
    A=[[j for j in i] for i in M]
    
    #Preamble
    optval=-1
    
    n=len(A)
    
    assignments=[]
    
    #printmatrix(A)
    
    #Rows
    for i in range(n):
        k=min(A[i])
        A[i]=[j-k for j in A[i]]
    
    #printmatrix(A)
    
    #Columns
    for i in range(n):
        k=min([A[j][i] for j in range(n)])
        for m in range(n):
            A[m][i]-=k
        
    #printmatrix(A)
    
    #print("TRUTH BOMB")
    
    while(True):
        rowzero=[0]*n
        colzero=[0]*n
        
        rowmark=[0]*n
        colmark=[0]*n
    
        #Assign zeros
        for i in range(n):
            for j in range(n):
                if A[i][j]==0 and colzero[j]==0:
                    rowzero[i]=1
                    colzero[j]=1
                    assignments.append((i,j))
                    break
        
        #print(assignments)
        
        if len(assignments)==n:
            #Compute optval
            optval=0
            for p in assignments:
                optval+=M[p[0]][p[1]]
            return(assignments,optval)
        else:
            assignments=[]
        
        #Draw lines
        for i in range(n):
            if rowzero[i]==0:
                rowmark[i]=1
                for j in range(n):
                    if A[i][j]==0:
                        colmark[j]=1
        
        for j in range(n):
            if colmark[j]==1:
                for i in range(n):
                    if rowmark[i]==0 and (i,j) in assignments:
                        rowmark[i]=1
        
        #Find minimum outside lines
        k=float('inf')
        for i in range(n):
            for j in range(n):
                if rowmark[i]==1 and colmark[j]==0:
                    k=min(A[i][j],k)
        
        #print("MINIMUM: ",k)
        
        for i in range(n):
            for j in range(n):
                if rowmark[i]==1 and colmark[j]==0:
                    A[i][j]-=k
                elif rowmark[i]==0 and colmark[j]==1:
                    A[i][j]+=k
        
        #print(rowmark, colmark, rowzero, colzero)
        #printmatrix(A)
    
    
    return(assignments, optval)
    

A=[[3,4,5,4,6],[4,4,2,3,6],[5,1,6,5,1],[6,7,7,10,8],[4,5,3,5,6]]

printmatrix(A)

print(Hungarian(A))

B=[[36,11,23,25,39,32],[81,23,14,77,65,53],[10,43,26,18,19,30],[35,31,19,76,24,25],[55,73,89,30,54,41],[33,85,99,32,31,20]]

printmatrix(B)

print(Hungarian(B))