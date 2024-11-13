#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LEN = 101;

void LCS(char b[MAX_LEN][MAX_LEN], const string &X, int i, int j, string &lcs) {
    if (i == 0 || j == 0) { // End of either string
        return;
    }
    if (b[i][j] == 'D') { // Diagonal with char matched
        LCS(b, X, i - 1, j - 1, lcs);
        lcs += X[i - 1]; // Append character to LCS string
    } 
    else if (b[i][j] == 'U') {// With no match, move up
        LCS(b, X, i - 1, j, lcs);
    } else { // With no match move left
        LCS(b, X, i, j - 1, lcs);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Format: ./lcs <input-string1> <input-string2>" << endl;
        return 1;
    }

    string X = argv[1];
    string Y = argv[2];
    int m = X.length();
    int n = Y.length();

    // Check str len
    if (m >= MAX_LEN || n >= MAX_LEN) {
        cout << "Error: Input strings should be at most 100 characters each." << endl;
        return 1;
    }

    // Initialize matrices for len (c) and arrows (b)
    int c[MAX_LEN][MAX_LEN] = {0};
    char b[MAX_LEN][MAX_LEN] = {' '};

    // Populate LenLCS table (c) & arrow table (b)
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'D'; // Diagonal
            } 
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 'U'; // Up
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 'L'; // Left
            }
        }
    }

    // Make LCS using arrow table (b)
    string lcs;
    LCS(b, X, m, n, lcs);

    cout << "Length of LCS: " << lcs.length() << endl;
    cout << "LCS: " << lcs << endl;

    return 0;
}