

def Kosaraju(graph):
	S=[]
	marked=[0 for i in graph]
	for vertex in range(len(graph)):
		if marked[vertex]==0:
			DFS1(graph,marked,S,vertex)
	
	g2=reverse(graph)
	marked=[-1 for i in range(len(graph))]
	result=[i for i in range(len(graph))]
	numberOfSCC=0
	while len(S):
		if marked[S[-1]]==-1:
			DFS2(g2,marked,S,result,S[-1],numberOfSCC)
			numberOfSCC+=1
		del(S[-1])
	
	return([i for i in result])

def DFS1(graph,marked,S,v):
	if marked[v]==1:
		return
	marked[v]=1
	for u in graph[v]:
		DFS1(graph,marked,S,u)
	S.append(v)

def DFS2(graph,marked,S,result,v,leader):
	if marked[v]==1:
		return
	marked[v]=1
	result[v]=leader
	for u in graph[v]:
		DFS2(graph,marked,S,result,u,leader)

def reverse(graph):
	rev=[[] for lis in graph]
	for i in range(len(graph)):
		for elem in graph[i]:
			rev[elem].append(i)
	return(rev)

def formulaToGraph(formula,N):
	graf=[[] for i in range(2*N)]

	for clause in formula:
		l1=clause[0]
		l2=clause[1]
		if l1[1]==1 and l2[1]==1:
			graf[l1[0]+N].append(l2[0])
			graf[l2[0]+N].append(l1[0])
		elif l1[1]==1 and l2[1]==0:
			graf[l1[0]+N].append(l2[0]+N)
			graf[l2[0]].append(l1[0])
		elif l1[1]==0 and l2[1]==1:
			graf[l1[0]].append(l2[0])
			graf[l2[0]+N].append(l1[0]+N)
		elif l1[1]==0 and l2[1]==0:
			graf[l1[0]].append(l2[0]+N)
			graf[l2[0]].append(l1[0]+N)
	return graf

def countLiterals(formula):
	lit=[]
	
	for clause in formula:
		for literal in clause:
			if literal[0] not in lit:
				lit.append(literal[0])
	
	return len(lit)

def solvable(table,N):
	for i in range(N):
		if table[i+N]==table[i]:
			return 0
	return 1

def SATisfy(table,N):
	TF=[-1 for i in range(N)]
	
	
	return TF

def splitter(SCC):
	groups=[]
	
	for i in SCC:
		if i not in groups:
			groups.append(i)
	
	result={}
	for i in range(len(SCC)):
		result.setdefault(SCC[i],[])
		result[SCC[i]].append(i)
	
	return [result[i] for i in result]

def solve2SAT(formula):
	N=countLiterals(formula)
	graph=formulaToGraph(formula,N)
	SCC=Kosaraju(graph)
	table=splitter(SCC)
	if solvable(SCC,N):
		return SATisfy(table,N)
	else:
		return [-1 for i in range(N)]






N=7

#(index, true/false) or (index, true/false)
formula=[[(0,1),(2,1)],
		 [(0,1),(3,0)],
		 [(1,1),(3,0)],
		 [(1,1),(4,0)],
		 [(2,1),(4,0)],
		 [(0,1),(5,0)],
		 [(1,1),(5,0)],
		 [(2,1),(5,0)],
		 [(3,1),(6,1)],
		 [(4,1),(6,1)],
		 [(5,1),(6,1)]]

graf=formulaToGraph(formula,N)

unsat=[[(0,1),(1,0)], [(0,1),(1,1)], [(0,0),(1,1)], [(0,0),(1,0)]]

for l in graf:
	print(l)

SCC=Kosaraju(graf)

print(SCC)
print(splitter(SCC))
print(solvable(SCC,N))

ungraf=formulaToGraph(unsat,2)

print(ungraf)

SCC=Kosaraju(ungraf)

print(SCC)

print(splitter(SCC))
print(solvable(SCC,2))









