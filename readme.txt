C++
make


Azan Nazar
B00882606



HOW TO RUN:
1. Create 
> make

2. For compiling the executable for the lcs program
> ./lcs <input-string1> <input-string2>

3. For compiling the executable for the floyd program
> ./floyd <graph-file>

4. For clearing the executables
> make clean


- LCS EXPLANATION
The program begins by making a 2D table to store the length of the LCS and the direction of the optimal choice at each cell
The LCS function recursively traces wihtin the table in order to make the LCS string 
The main function then takes two input strings, fills the DP table, and prints the length and the LCS itself

- FLOYD EXPLANATION
The floyd function obtains the shortest distances and p-table information for each pair of vertices
The makePath function remakes the shortest path between two vertices using the p-table information
The printSolution function outputs the shortest path matrix and the shortest paths with their respective distances
The main function finally reads the graph input, calls the floyd function, and prints the results