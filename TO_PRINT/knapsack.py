
def print_matrix(m):
    count=0
    for i in m:
        print(count,end='| ')
        count+=1
        for j in i:
            print(j, end=' ')
        print('')
    print('\n')


def binknap(maxsize, things):
    """things = [ (size,value), ... ]"""
    n = len(things)

    f = [[0 for i in range(n)] for j in range(maxsize+1)]
    p = [[0 for i in range(n)] for j in range(maxsize+1)]

    print_matrix(f)
    print_matrix(p)

    for i in range(1,maxsize+1):
        if i>=things[0][0]:
            p[i][0]=1
            f[i][0]=things[0][1]

    for j in range(1,n):
        t = things[j]
        for i in range(1,maxsize+1):
            if i-t[0]>=0:
                (f[i][j],p[i][j]) = max((f[i][j-1],0),(t[1]+f[i-t[0]][j-1],1))
            else:
                (f[i][j],p[i][j]) = (f[i][j-1],0)

    print_matrix(f)
    print_matrix(p)

    packing = [0]*n

    i = maxsize
    j = n-1

    while i>0:
        if p[i][j]:
            packing[j]=1
            (i,j) = (i-things[j][0],j-1)
        else:
            j-=1

    return (f[-1][-1],packing)


def intknap(maxsize, things):
    """things = [ (size,value), ... ]"""
    n = len(things)

    f = [[0 for i in range(n)] for j in range(maxsize+1)]
    p = [[0 for i in range(n)] for j in range(maxsize+1)]

    print_matrix(f)
    print_matrix(p)

    for i in range(1,maxsize+1):
        if i>=things[0][0]:
            p[i][0]=1
            f[i][0]=things[0][1] * (i//things[0][0])

    for j in range(1,n):
        t = things[j]
        for i in range(1,maxsize+1):
            if i-t[0]>=0:
                (f[i][j],p[i][j]) = max((f[i][j-1],0),(t[1]+f[i-t[0]][j],1))
            else:
                (f[i][j],p[i][j]) = (f[i][j-1],0)

    print_matrix(f)
    print_matrix(p)

    packing = [0]*n

    i = maxsize
    j = n-1

    while i>0:
        if p[i][j]:
            packing[j]+=1
            (i,j) = (i-things[j][0],j)
        else:
            j-=1

    return (f[-1][-1],packing)


things = [(2,10),(1,7),(6,25),(5,24)]
maxsize=7

print(binknap(maxsize,things))

things = [(3,7),(4,9),(1,2),(7,15)]
maxsize=10

print(intknap(maxsize,things))

