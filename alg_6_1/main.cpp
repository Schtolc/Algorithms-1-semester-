/*Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков
пирамиду.

Формат входных данных:
На вход подается количество кубиков N.

Формат выходных данных:
Вывести число различных пирамид из N кубиков.

6_1.​Высокая пирамида. ​Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
N ≤ 200.*/

#include <iostream>
#include <string.h>
#include <inttypes.h>
#define MAX_NUMBER 201


using namespace std;



uint64_t pyr_amount(const int N,const int K, uint64_t** ANSWERS) {
    uint64_t amount = 0;

    if (ANSWERS[N][K] != -1)
        return ANSWERS[N][K];

    for (int i = N - K; i < N; i++) {
        amount += pyr_amount(i, min(i, N-i), ANSWERS);
    }

    ANSWERS[N][K] = amount;

    return amount;
}

int main() {



    int N = 0;
    cin>>N;

    uint64_t** answers = NULL;

    answers = new uint64_t* [N+1];
    for (int i = 0; i <= N; i++){
        answers[i] = new uint64_t[N+1];
        for (int j = 0; j <= N; j++) {
            answers[i][j] = -1;
        }
    }

    for (int i =0; i <= N; i++) {
        answers[i][0] = 1;
        answers[0][i] = 1;
    }

    cout << pyr_amount(N,N, answers) ;

    for (int i =0 ; i <= N ; i++) {
        delete [] answers[i];
    }
    delete [] answers;
    return 0;
}