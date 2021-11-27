# Development

### Week of November 19th:
This was a very important week of the project, as this was the week that we built the foundation for our data structure.
We started first of all by deciding how we wanted to represent everything, finalizing on a map to represent the vertices
and each of them holding data, such as latitude, longitude, and a standard library list (might be changed to a vector),
that holds the edges. The key for the vertices are the IATA and ICAO codes of the airports. We also implemented the csv
parser to be able to read the route and airport data, and fill out the graph.


### Week of November 26th:
This week was where we made great strides in the code base. The first thing we did, was implement our weights. In 
planning for the rest of the project, we realized that using both the distance and the inverse of the route count
of the source and destination of the route. We store both of these, and depending on the algorithm we can choose
either one. Next, we started and "Finished" two algorithms, the Breadth First Traversal and Floyd Warshall's Algorithm.
The reason its finished in quotes, is because while both of them are functional, they can and will be improved
as we continue with the project development. On problem we ran into was we would run out of memory with Floyd
Warshall's Algorithm because we were storing over 59 million airports (around 7,700 squard for the 2D vector), but we 
switched to just hold the indexes of the airport is our airports_ vector. Next week, we hope to improve those two
algorithms and build the betweennes centrality algorithm.
