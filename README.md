# DCS_Problem_S_intership_2022
To reduce the very large Graph into subgraph in order to reduce the complexity of the graph.

We implemented 3 Functions : -
a ) . Funciton_two :
1.We are iterating through each edges {u,v}. where u and v is vertex .
2.for each vertex , we have stored its previous degree(number of edges connected with it). we have also a constructed a newdegree which keeps track of its
current edges.
3.Now we maintain a variable ratio which will keep track of by how much our particular edges is decreased.
     ratio1 = newdeg[u] / olddegree[u];
     ratio1 = newdeg[v] / olddegree[v];
4.if both ratio1 and ratio2 is between alpha and beeta then we will not remove that edges.
5.if either of them is greater than beeta and remaining other one is greater than alpha than we will reduce that vertex.

b ) . Funciton_three : 
1 . Till step 4 we will do the same stuff as done in function 2 .
2.Before removing any edges we will check if due to removal of that edges if either of ratio1 or ratio2 is comming below that alpha value than will not 
remove that edges.

c ) Function_four : 
1 . In function 4 we are provided with only lower bound and we have to compress the data.
2 . We will use similar kind of algorithm but here ratio1 and ratio 2 is checked with respect to lower bound ( alpha ) only.

** : We noticed at the time of implementation that some of the node were violating the upper bound and lower bound. So we measured them in parameters such
     as total node violation , maximum node violaton, minimum node violation , average node violaton. We also calculated graph compression and percenctage
     node violation. We plotted these values obtained from different function. 
     
** : We plotted the graph for static range (i.e. shifting the range from 0.2 every times . Initially alpha = 0.1 and beta = 0.2 ) and observed the shift
     in pattern in graph.
     
** : We plotted the graph for dynamic range (i.e. kepping the alpha = 0.3 every times and changing the beta from o.4 to 0.9) and observed the trend in the
     pattern of graph.
