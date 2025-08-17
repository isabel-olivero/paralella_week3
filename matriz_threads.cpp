#include <iostream>
#include <pthread.h>
#include <vector>
#include <random>

using namespace std;

const int N = 40;


vector<vector<int>> A(N, vector<int>(N));
vector<vector<int>> B(N, vector<int>(N));
vector<vector<int>> sumResult(N, vector<int>(N));
vector<vector<int>> diffResult(N, vector<int>(N));
vector<vector<int>> finalResult(N, vector<int>(N));

void fillMatrix(vector<vector<int>>& M) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            M[i][j] = dist(gen);
        }
    }
}

//suma
void* computeSum(void*) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sumResult[i][j] = A[i][j] + B[i][j];
        }
    }
    return nullptr;
}

// resta
void* computeDiff(void*) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            diffResult[i][j] = A[i][j] - B[i][j];
        }
    }
    return nullptr;
}

// Multiplicación
void multiplyMatrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += sumResult[i][k] * diffResult[k][j];
            }
            finalResult[i][j] = sum;
        }
    }
}

int main() {
    fillMatrix(A);
    fillMatrix(B);

    pthread_t t1, t2;

    pthread_create(&t1, nullptr, computeSum, nullptr);
    pthread_create(&t2, nullptr, computeDiff, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    multiplyMatrices();


    cout << "Result (" << N << "x" << N << "):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << finalResult[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
