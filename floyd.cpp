#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits.h>
using namespace std;

int INF = INT_MAX;

// Floyd algorithm based on ch7 slides
void floyd(int n, vector<vector<int>>& D, vector<vector<int>>& pred) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    pred[i][j] = k + 1; // Save index for path making
                }
            }
        }
    }
}

// Path from start to end with p matrix
void makePath(int start, int end, vector<vector<int>>& pred, vector<int>& path) {
    if (pred[start][end] == -1) { // No path
        return;
    }

    int intermediate = pred[start][end] - 1; // Add 1 for indexing
    
    if (intermediate == start) {
        path.push_back(start + 1); 
        path.push_back(end + 1);
    } 
    else {
        makePath(start, intermediate, pred, path); // Avoid duplicates of intermediate nodes
        path.pop_back(); 
        makePath(intermediate, end, pred, path);
    }
}

// Print Dances and paths
void printSolution(ofstream& outfile, int n, vector<vector<int>>& D, vector<vector<int>>& pred) {
    outfile << "P matrix:\n"; // Printing the P-table
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                outfile << "0 ";
            } else {
                // Find min weight for (i, j) and (j, i)
                int min_weight = min(D[i][j], D[j][i]);

                // Print 1-based index
                outfile << pred[i][j] << " ";
            }
        }
        outfile << "\n";
    }
    outfile << "\n";

    for (int i = 0; i < n; i++) { // Printing the vertices
        outfile << "V" << i + 1 << "-Vj: shortest path and length\n";

        for (int j = 0; j < n; j++) {
            vector<int> path;
            makePath(i, j, pred, path);

            if (i == j) { // Same start and end vector
                outfile << "V" << i + 1 << " V" << j + 1 << ": 0\n";
            } 
            else if (D[i][j] == INF) { // Vectors with no path
                outfile << "V" << i + 1 << " V" << j + 1 << ": No path\n";
            } 
            else { // Different start and end vectors including intermediates
                for (int i = 0; i < path.size(); i++) {
                    if (i == path.size() - 1) {
                        outfile << "V" << path[i];
                    } else {
                        outfile << "V" << path[i] << " ";
                    }
                }
                outfile << ": " << D[i][j] << "\n";
            }
        }
        outfile << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Format: floyd <graph-file>\n";
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile("output.txt");

    if (!infile.is_open() || !outfile.is_open()) {
        cout << "Can't open necessary file\n";
        return 1;
    }

    int problemNumber = 0;
    string line;

    while (getline(infile, line)) {
        if (line.find("Problem") != string::npos) { // Reading graph file
            problemNumber++;
            int n;
            string temp;

            istringstream iss(line);
            iss >> temp >> temp >> temp >> temp >> n;

            vector<vector<int>> D(n, vector<int>(n));
            vector<vector<int>> pred(n, vector<int>(n, -1));

            // Read adj matrix
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    infile >> D[i][j];
                    if (i != j && D[i][j] == 0) { // Big value for no path
                        D[i][j] = INF;
                    } 
                    if (i != j && D[i][j] != INF) { // Direct paths
                        pred[i][j] = i + 1;
                    }
                }
            }

            floyd(n, D, pred);
            outfile << "Problem " << problemNumber << ": n = " << n << "\n";
            printSolution(outfile, n, D, pred);
        }
    }

    infile.close();
    outfile.close();
    return 0;
}
