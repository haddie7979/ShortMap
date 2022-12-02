# ShortMap
Team Members: Lindsay Goldberg-Custer, Divyanshi Saini, Jordan Sheehan
1. Problem: We are trying to solve the problem of finding the shortest path in a simulated
network of locations and roads connecting them. Given a starting and ending
location in the network, we will navigate the shortest path between them,
including accounting for traffic delays on certain roads.
2. Motivation: This is a very relevant problem because an enormous amount of people rely on
GPS services to navigate to their destination. Finding the shortest path between
two locations is one of the core functionalities of GPS. Factoring in traffic and
routing around major delays also creates an even better experience for the user.
3. Features: Part of knowing we have solved the problem is when our program can randomly
generate a graph of at least 100,000 vertices. Whether or not two given vertices
are connected should be randomly decided and each edge should have a
randomly generated weight. The second part of knowing we have solved the
problem is when our program can take in two locations (i.e. vertices represented
by some integer value) from the user and calculate the shortest path between
them that accounts for simulated traffic delays (i.e. edge weights). This shortest
path and the total traffic delays experienced should be output to the user.
4. Data:  The data for our simulated network will be randomly generated. In the adjacency
matrix that backs our graph, which will be a large 2-D array of integers, we will
randomly set whether two vertices are connected. The edge weights, which will
also be randomly-generated integers, will be stored in an adjacency matrix. For
instance, the weight of the edge connecting vertices “u” and “v” will be stored in
adj_mat[u][v] and adj_mat[v][u], since the graph is undirected.
5. Tools: Our group will use C++ to complete this project. Currently, we do not plan on
utilizing any additional tools or frameworks. At the most, we may incorporate
additional STL data structures if we find that they are useful for our solution.
6. Strategy: Our simulated network of roads will be represented by a weighted, undirected
graph. Each vertex will serve as a location the user can start or end their route at,
and each edge connecting the vertices will represent a road. The weights of each
edge will represent the number of minutes of delay caused by traffic. We have
selected an undirected graph because each road in our simulated network will
allow for travel in either direction. Next, considering that our graph is weighted, we
will use Dijkstra’s algorithm to find the shortest path between two vertices and compare
it with a simple Breadth First Search.
7. Backend: At each index of the matrix, whether a vertex is connected to another vertex
will be randomly decided. With regard to Dijkstra’s algorithm, we
plan to implement it with a priority queue. As we conduct more research and learn
more about graphs and shortest paths algorithms, we will finalize this decision. We
will also implement the adjacency matrix with consideration of the memory it
needs and switch our implementation if necessary.
