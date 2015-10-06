
# From the wikipedia page on Push-relabel.
# In python-3
# using discharge and nodelist to decide actions in effective order.

height = [] #Height of nodes
excess = [] #Excess flow in nodes flow into - flow outfrom
seen = []	# Nodes seen since last relabel
nodelist = []	# 'queue' to act on
Cap = [[]]	# Capacity matrix
Flo = [[]]	# Preflow matrix
	#	Residual capacity = C[u][v] - F[u][v]

N = 0




def discharge( u ):
	# Decide whether to push or relabel and do thusly

	while excess[u] > 0:

		# If we have not checked all neighbours
		if seen[u] < N:

			#Check next
			v = seen[u]

			if Cap[u][v] - Flo[u][v] > 0 and height[u] > height[v]:
				# Residual capacity positive and we are higer, then push
				Push(u,v)
			else:
				seen[u] += 1 # else check next 

		else:
			# Every neighbour checked, relabel
			Relabel(u)
			seen[u] = 0 # Now none checked

def Push( u, v ):

	# Do when rescap(u,v) > 0 and u height = v height +1
	# Should push dflow units of flow from u to v.

	dflow = min( excess[u], Cap[u][v] - Flo[u][v] )

	Flo[u][v] = Flo[u][v] + dflow
	Flo[v][u] = Flo[v][u] - dflow

	excess[u] = excess[u] - dflow
	excess[v] = excess[v] + dflow


def Relabel( u ):

	# Do when u is overflowing, and for all v in V, such that (u,v) in Ef, 
	#	we have u.h <= v.h. (Note that there should be one outedge, else we are not overflowing)
	minh = float('inf')
	for v in range(N):
		if Cap[u][v] - Flo[u][v] > 0:
			minh = min( minh, height[v] )
			height[u] = minh + 1



def Initialize( C, so, si ):

	global height
	global excess
	global seen
	global N
	global Cap
	global Flo 
	global nodelist

	N = len(C)

	height = [0]*N
	excess = [0]*N
	seen = [0]*N

	nodelist = [ i for i in range(N) if i != so and i != si ]

	Cap = C
	Flo = [[0]*N for i in range(N)]

	height[so] = N
	excess[so] = float('inf')

	for v in range(N):
		Push( so, v )

def PushRelabel( C, so, si ):

	Initialize( C, so, si )

	p = 0 # Start going through all nodes, as long as they are still in queueueue
	while p<len(nodelist):

		# print(p, nodelist, Flo)
		# print(height, excess)
		
		u = nodelist[p]

		old_height = height[u]

		discharge(u)

		if height[u] > old_height:
			nodelist.insert(0, nodelist.pop(p))
			p = 0
			# Move to front of list and restart
		else:
			p = p+1 # Else move forwards

	tot = 0
	for v in range(N):
		tot = tot + Flo[so][v]
	return tot

C = [[0,15,4,0,0,0],[0,0,0,12,0,0],[0,0,0,0,10,0],[0,0,3,0,0,7],[0,5,0,0,0,10],[0,0,0,0,0,0]]
so = 0
si = 5
print( PushRelabel(C,so,si) )
print( Flo )





