//Create a graph that for each ingredient there are two nodes one (+x) representing having 
//the ingredient and the other (-x) excluding it. Each edge is the condition that makes 
//impossible one family to be satisfied... for example if an input +1 +2 is given 
//then an edge -1,-2 will be put. Also you put an edge for (+x,-x) for every x-ingredient.
//The goal is to choose a subset on nodes (n in total by constraints) that contain no edge.

//Another way is for each constraint (A,B) (i.e. if A>0 means include A ingredient and if 
//A<0 eclude it) create two directed edges: (-A->B) and (-B->A). The problem no becomes of
//choosing for each ingredient X either +X of -X, but also having to choose for every node
//all other nodes that you could get to them through any path. ps... the graph is somehow 
//symmetrical since for each edge (A,B) there is also the edge (-A,-B)