# Final Project Results

When we set out to work on this project, we had the main goal to gain insight into the
operation of flight networks. We used 2 algorithms for this, Floyd-Warshall's Algorithm and
Betweenness Centrality. Floyd Warshall's Algorithm told us the shortest route between any
two airports, and Betweenness Centrality gave us an interesting insigeht into the importance
of airports. We gained key insight into not only which airports are the most important, but
we also learned about what makes a node "central," such as it being a bottle neck to the graph,
instead of having a lot of edges going to and from it. This is most obvious when you run 
Betwenness Centrality on the set of United States graphs, and it outputs:
``
Looking for Airports in United States
Starting BFS

Total distinct routes in file: 5450
Unexplored edges: 0
Discovery edges: 538
Cross edges: 4912
Total distinct routes found in BFS: 5450

Floyd Warshall's Progress:
1512/1512

Airports: 1512; Routes: 5450
Centrality Progress:
1512,1512

The most central airport is ANC
The least central airport is CLM
``
The interesting part of this is that the most central airport is ANC, which is the airport in 
Anchorage, Alaska. While Anchorage is not the most busy airport (It is actually the 57th), it
is one that all of the regional airports of alaska fly out of. This makes it a bottle neck and
therefore the most central.
