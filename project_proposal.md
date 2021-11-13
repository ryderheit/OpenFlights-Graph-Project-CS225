# Final Project Proposal

1. **Leading Question:** The goal for our presentation will be to represent all flight data around the world. We can use this graph to calculate the shortest paths
or the most critical airports. The main goal of this project will be to develop a tool to help learn about flight-paths aroudn the world.

2. **Dataset Acquisition:** We are getting our data from [openflights.org](https://openflights.org/data.html). We will download two raw text files for the airports which will be our nodes,
and then the routes, which will be our directed edges. Each node will represent an airport and store its unique OpenFlights ID and coordinates in a tuple.
Each edge will represent a one-way route from one airport to another and store the its length, which can be calculated from the coordinates of the two airports. If there are any errors, we will edit certain edges or nodes, based on the simplest way to fix the error.

3. **Graph Algorithms:** We are planning on two main algorithms and a traversal. The traversal will simply be a Breadth First Search Traversal, which will be O(n). 
For our algorithms, we will have a shortest path algorithm that will allow us to input two airports, and return the shortest path between the two airports
which will represent the best path to get to each airport. We will most likely use Floyd-Warshall's Algorithm which is O(n<sup>3</sup>). We will also implement a betweeness centrality
algorithm to determine which airports are the most important to the world which runs in O(n*m). 

4. **Timeline:** We will try and get through all the setup for the program by the start of Thanksgiving break; this includes data acquisition and refining, data representation,
further research on how the algorithms are accomplished, and an early testing suite developed. By the mid-project checkin, we will have the basics of each algorithm done. This means 
they all work and are tested thoroughly, though not perfect. The next week will be spent cleaning up the code base, and adding any final touches on top of the base algorithms. The 
final week will be spent writing the report and doing the presentation.
