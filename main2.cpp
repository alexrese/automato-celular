#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>

struct Automaton {
    int **cells;
    const int n, m, k, d;
    /**
     * n: quantidade de celulas do automato
     * m: valor máximo permitido para cada estado
     * d: distância de vizinhança
     * k: quantidade de passos
     * input: vetor de inteiros que contém os estados de entrada para o automato
    */
    Automaton(int n, int m, int d, int k) : n(n), m(m), k(k), d(d) {
        cells = new int*[2] { new int[n], new int[n] };
    };

    /**
     * step: o passo de referência para acessar as células
     * cellIndex: índice de uma célula do automato
     * Obtem o novo estado de uma determinada celula
     * Os vizinhos são considerados com base na distancia d     
    */
    int getCellNewState(int step, int cellIndex) {
        int sum = 0;
        int start = n + cellIndex - d;
        for (int i = 0; i < (d * 2 + 1) && i < n; i++) {
            sum += cells[step][(start + i) % n];
        }
        return (sum % m);
    }

    /**
     * step: o número do passo a ser realizado
     * Realiza um passo k
     * Cada celula é atualizada para seu novo estado      
    */
    void doStep(int step) {
        int previous = (step + 1) % 2;
        int sum = 0;
        for (int i = 0; i < (d * 2 + 1) && i < n; i++) {
            sum += cells[previous][(n - d + i) % n];
        }
        cells[step][0] = sum % m;        
        for (int i = 1; i < n; i++) {            
            sum -= cells[previous][(n + i - d - 1) % n];
            sum += cells[previous][(i + d) % n];
            cells[step][i] = sum % m;
        }
    }

    /**
     * Realiaza todos os passos k
    */
    void run() {
        for (int i = 1; i <= k; i++)
            doStep(i % 2);
    }

    /**
     * Imprime os estados atuais das celulas do automato
    */
    void print() {
        for (int i = 0; i < n; i++) {
            std::cout << cells[k%2][i];
            if (i < n - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    // std::ifstream inputFile("cell.in");
    // std::ofstream outputFile("cell.out");
    // int n, m, d, k;

    // while(inputFile >> n >> m >> d >> k) {
    //     Automaton aut(n, m, d, k);
                
    //     for (int j = 0; j < n; j++) {
    //         inputFile >> aut.cells[0][j];
    //     }
        
    //     aut.run();
    //     for (int i = 0; i < n; i++) {
    //         outputFile << aut.cells[k%2][i];
    //         if (i < n - 1) {
    //             outputFile << " ";
    //         }
    //     }
    //     outputFile << "\n";
    // }
    
    int n, m, d, k;

    while(std::cin >> n >> m >> d >> k) {
        Automaton aut(n, m, d, k);
        
        aut.cells[0] = new int[n];
        for (int j = 0; j < n; j++) {
            std::cin >> aut.cells[0][j];
        }
        
        aut.run();
        aut.print();
    }

    return 0;
}