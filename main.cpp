#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>

int main() {
    std::ifstream inputFile("cell.in");
    std::ofstream outputFile("cell.out");
    int n, m, d, k;
    while(inputFile >> n >> m >> d >> k) {
        int **cells = new int*[k+1];
        cells[0] = new int[n];

        for (int j = 0; j < n; j++) {
            inputFile >> cells[0][j];
        }

        for (int step = 1; step <= k; step++) {
            cells[step] = new int[n];
            for (int cell = 0; cell < n; cell++) {
                int sum = 0;
                int start = n + cell - d;
                for (int i = 0; i < (d * 2 + 1); i++) {
                    sum += cells[step-1][(start + i) % n];
                }
                cells[step][cell] = sum % m;

                if (step == k) {
                    outputFile << cells[step][cell];
                    if (cell < n - 1) {
                        outputFile << " ";
                    } else {
                        outputFile << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}