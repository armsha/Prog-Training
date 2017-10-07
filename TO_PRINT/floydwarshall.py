
def printm(M):
    for row in M:
        print(row)

def fw(G):
    n = len(G)
    A = [[elem for elem in row] for row in G]
    P = [[i for i in range(len(row))] for row in G]

    printm(A)
    print(' ')
    printm(P)

    for k in range(n):
        for i in range(n):
            for j in range(n):
                if A[i][j] > A[i][k] + A[k][j]:
                    A[i][j] = A[i][k] + A[k][j]
                    P[i][j] = P[i][k]
    
    return (A,P)


f = float('Inf')
G = [[0,f,-2,f],
     [4,0,3,f],
     [f,f,0,2],
     [f,-1,f,0]]

(A,P) = fw(G)

print(' ')
printm(A)
print(' ')
printm(P)
