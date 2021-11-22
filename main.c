#include <stdio.h>
#include <malloc.h>
#include <process.h>

typedef struct pnt {
    int w0,   //stan po symbolu 0
    w1,     //stan po symbolu 1
    type;   //0 - stan, 1 - stan akceptowalny
} pnt_t;


//zwraca ciąg stanów włącznie ze stanem początkowym actState i stanem końcowym. Zwracany wektor ma długość seqLength+1
int *run(int *sequence, int seqLength, int actState, pnt_t *availStates) {
    int *result = malloc((seqLength + 1) * sizeof *result);
    *result = actState;
    for (int i = 0; i < seqLength; i++)
        switch (*(sequence + i)) {
            case 0:
                actState = availStates[actState].w0;
                *(result + i + 1) = actState;
                break;
            case 1:
                actState = availStates[actState].w1;
                *(result + i + 1) = actState;
                break;
            default:
                return (int[1]) {-1};
        }
    return result;

}

void WriteDiagram(int *sequenceResult, int *sequence, int seqLength) {
    printf("\033[0;31m");
    printf("  q%d", *sequenceResult);
    for (int i = 0; i < seqLength; i++)
        printf("  -- %d -->  q%d", sequence[i], sequenceResult[i + 1]);

    printf("\033[0m");
}


int main() {
    pnt_t *states = (pnt_t[]) {{2, 1, 0},
                               {3, 0, 0},
                               {0, 3, 1},
                               {1, 2, 0}};
    int actState = 3; //stan początkowy q3
    int seqLength = 0;
    int *sequence = malloc(seqLength * sizeof *sequence);
       

    FILE *p = stdin;

    if (p == NULL) {
        printf("Nie można otworzyć wejścia!\n");
        return 1;
    }
    char c;
    while ((c = fgetc(p)) != 10)
        if (c != 48 && c != 49) {
            printf("Ciąg zawiera błędne znaki. Możliwe znaki: 0, 1.\n");
            return 1;
        } else
            (sequence = realloc(sequence, ++seqLength * sizeof *sequence))[seqLength - 1] = c - 48;




    int *sequenceResult = run(sequence, seqLength, actState, states);//długością jest seqLength+1


    if (*sequenceResult == -1) {
        printf("Niepowodzenie działania maszyny!\n");
        return 1;
    } else if (states[sequenceResult[seqLength]].type == 1) {
        printf("Zaakceptowano ciąg!\n");
        WriteDiagram(sequenceResult, sequence, seqLength);
    } else if (seqLength == 0) {
        printf("Nie wpisano znaków!\n");
        return 1;
    } else {
        printf("Ciąg nie został zaakceptowany!\n");
        return 1;
    }


}
