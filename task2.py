from math import*

#This class represents a directed graph using adjacency matrix representation
class Graph:
  
    def __init__(self,graph):
        self.graph = graph # residual graph
        self. ROW = len(graph)
        #self.COL = len(gr[0])
         
  
    '''Returns true if there is a path from source 's' to sink 't' in
    residual graph. Also fills parent[] to store the path '''
    def BFS(self,s, t, parent):
 
        # Mark all the vertices as not visited
        visited =[False]*(self.ROW)
         
        # Create a queue for BFS
        queue=[]
         
        # Mark the source node as visited and enqueue it
        queue.append(s)
        visited[s] = True
         
        # Standard BFS Loop
        while queue:
 
            #Dequeue a vertex from queue and print it
            u = queue.pop(0)
         
            # Get all adjacent vertices's of the dequeued vertex u
            # If a adjacent has not been visited, then mark it
            # visited and enqueue it
            for ind, val in enumerate(self.graph[u]):
                if visited[ind] == False and val > 0 :
                    queue.append(ind)
                    visited[ind] = True
                    parent[ind] = u
 
        # If we reached sink in BFS starting from source, then return
        # true, else false
        return True if visited[t] else False
             
     
    # Returns the maximum flow from s to t in the given graph
    def FordFulkerson(self, source, sink):
 
        # This array is filled by BFS and to store path
        parent = [-1]*(self.ROW)
 
        max_flow = 0 # There is no flow initially
 
        # Augment the flow while there is path from source to sink
        while self.BFS(source, sink, parent) :
 
            # Find minimum residual capacity of the edges along the
            # path filled by BFS. Or we can say find the maximum flow
            # through the path found.
            path_flow = float("Inf")
            s = sink
            while(s !=  source):
                path_flow = min (path_flow, self.graph[parent[s]][s])
                s = parent[s]
 
            # Add path flow to overall flow
            max_flow +=  path_flow
 
            # update residual capacities of the edges and reverse edges
            # along the path
            v = sink
            while(v !=  source):
                u = parent[v]
                self.graph[u][v] -= path_flow
                self.graph[v][u] += path_flow
                v = parent[v]
 
        return max_flow

def compute_portions(needed_for_1, given):
    """
    ans = []
    count = 0
    amount = 0

    while amount <= 2*given:
        amount += needed_for_1
        count+=1
        if 0.9*amount<=given and 1.1*amount>=given:
            ans.append(count)
    """

    left = floor(given / (0.9*needed_for_1))
    right = ceil(given / (1.1*needed_for_1))

    return [right,left]

def intersect(a,b):
    return a[0]<=b[1] and b[0]<=a[1]


def solve(N,P,R,Q):
    numports = [[compute_portions(R[i],Q[i][j]) for j in range(P)] for i in range(N)]

    #print(numports)

    # Form adjacency matrix
    A = [[0 for j in range(N*P+2)] for i in range(N*P+2)]

    for i in range(N*P):
        row = i//P
        col = i%P

        if row < N-1 and numports[row][col][0] <= numports[row][col][1]:
            for j in range(P):
                if intersect(numports[row][col],numports[row+1][j]):
                    A[i][(row+1)*P + j] = 1

    for i in range(P):
        if numports[0][i][0] <= numports[0][i][1]:
            A[N*P][i] = 1
        if numports[N-1][i][0] <= numports[N-1][i][1]:
            A[(N-1)*P+i][N*P+1] = 1

    #for k in A:
    #    print(k)

    G = Graph(A)

    ans = G.FordFulkerson(N*P,N*P+1)
    #print(ans)

    return ans

f = open("B-small-attempt0.in","r")
g = open("output.txt","w")

T = int(f.readline())

for i in range(T):
    [N,P] = [int(j) for j in f.readline().split()]
    R = [int(j) for j in f.readline().split()]
    Q = [[int(k) for k in f.readline().split()] for j in range(N)]

    ans = solve(N,P,R,Q)

    g.write("Case #{}: {}\n".format(i+1,ans))

f.close()
g.close()
