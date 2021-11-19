# Development

### Week of November 19th:
This was a very important week of the project, as this was the week that we built the foundation for our data structure.
We started first of all by deciding how we wanted to represent everything, finalizing on a map to represent the vertices
and each of them holding data, such as latitude, longitude, and a standard library list (might be changed to a vector),
that holds the edges. The key for the vertices are the IATA and ICAO codes of the airports. We also implemented the csv
parser to be able to read the route and airport data, and fill out the graph.
