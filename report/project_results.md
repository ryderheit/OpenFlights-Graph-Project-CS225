# Final Project Results

When we set out to work on this project, we had the main goal to gain insight into the
operation of flight networks. We used 2 algorithms for this: Floyd-Warshall's Algorithm and
Betweenness Centrality. Floyd Warshall's Algorithm told us the shortest route between any
two airports, and Betweenness Centrality gave us an interesting insight into the importance
of airports. This is the output when you run our code:

### Full dataset BFS
```
Starting BFS

Total distinct routes in file: 37042
Unexplored edges: 0
Discovery edges: 3231
Cross edges: 33811
Total distinct routes found in BFS: 37042
```

### United States Floyd Warshall and Betweenness Centrality
```
Looking for Airports in United States
Starting BFS

Total distinct routes in file: 5450
Unexplored edges: 0
Discovery edges: 538
Cross edges: 4912
Total distinct routes found in BFS: 5450

Floyd Warshall's Progress:
1512/1512

src: CMI  dst: GEG
CMI->ORD->MSP->GEG

Airports: 1512; Routes: 5450
Centrality Progress:
1512,1512

The most central airport is ANC
The least central airport is CLM
```


There are 3 important parts of the output, the Breadth First Search, the Shortest Path, and the 
Centrality. The BFS output tells us about the amount of edges in the graph, which represents the
amount of distinct routes in the large dataset, which sums up to 33881 unique routes. The next is
Floyd Warshall's Algorithm. This is a very hefty algorithm that takes O(n<sup>3</sup>), which is
very slow. However, once the algorithm is calculated, it can be used to quickly find the shortest
path between any and all vertices or airprots. It can be seen used here to calculate the path from
CMI to GEG. The interesting thing about the shortest paths is that it usually seems to work by
attempting to go to travel using the large airports between them. It comes up with the shortest 
path between the two
airports. The next thing to note is the most and least central airport. There is nothing much to be
learned from the least central as CLM is one of many tiny airports around the country that have very few
routes in and out of the aiport, but the most central is more interesting. The most central
is ANC, in Anchorage, Alaska, which is not a massive airport like ATL in Atlanta or DFW in Dallas,
but instead one that is at a "bottle neck" of the graph, where there is a lot of flow that
exclusively goes through there. This makes sense as to if the ANC airport was removed, it would
spell issues for all the regional airports of Alaska halting all travel inside and outside of Alaska.
This finding is confirmed in [this](https://arxiv.org/pdf/1301.2223.pdf#:~:text=A%20high%20closeness%20centrality%20score,other%20nodes%20in%20the%20network.)
article which also says that the most central airport is the Anchorage airport.
