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


### Week of December 3rd:
This week was another important one in the development of our project, as it felt like the beginning of the end
of our project. This week we had 2 major developments, Betweeness Centrality and Better Command Line Arguments.
The construction of the Betweeness Centrality means that we have built all three of our major algorithms, and
optimizations and cleaning up the code, we are technically done. The other thing we
developed this week was we added more Command Line Arguments that allow us to filter our graph to only 
include airports from a certain country, or region, and more. We need next week to flesh out our testing suite
and to improve commenting in the next week of work.

### Week of December 10th:
This was the last full week of our project. After our mid week check-in went extraordinarily well, we had little
work left. The first of our two major work chunks was to fix up a testing suite. This included a lot of effort
to get the catch tests compiling and working, including reworking our make file, but once we got it working,
it gave us a very nice testing suite to work with and build up. The next thing we had to do was to write our 
report and add our finishing touches to the project. We added all the necessary and important bug fixes and
fancification of our user interface and we wrote up the results report. We have begun working on the presentation
and that is the final piece of this fun final project puzzle.
