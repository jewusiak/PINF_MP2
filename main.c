#include <stdio.h>
#include <malloc.h>
#include <limits.h>

typedef struct pnt {
    int w0,     //stan po symbolu 0
    w1,         //stan po symbolu 1
    type;       //0 - stan, 1 - stan akceptowalny
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
    printf("  q%d", *sequenceResult);
    for (int i = 0; i < seqLength; i++)
        printf("  -- %d -->  q%d", sequence[i], sequenceResult[i + 1]);
    printf("\n");
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
        printf("Nie mozna otworzyć wejscia!\n");
        return 1;
    }
    char c;
    while ((c = fgetc(p)) != 10)
        if (c != 48 && c != 49) {
            printf("Ciag zawiera bladne znaki. Mozliwe znaki: 0, 1.\n");
            return 1;
        } else if(seqLength>=INT_MAX) {
            printf("Wpisano zbyt duzo znakow. Maksymalna ilosc znakow to: %d.\n", INT_MAX);
            return 1;
        }
        else
            (sequence = realloc(sequence, ++seqLength * sizeof *sequence))[seqLength - 1] = c - 48;


    int *sequenceResult = run(sequence, seqLength, actState, states);//długością jest seqLength+1


    if (*sequenceResult == -1) {
        printf("Niepowodzenie dzialania maszyny!\n");
        return 1;
    } else if (states[sequenceResult[seqLength]].type == 1) {
        printf("Zaakceptowano ciag!\n");
        WriteDiagram(sequenceResult, sequence, seqLength);
    } else if (seqLength == 0) {
        printf("Nie wpisano znakow!\n");
        return 1;
    } else {
        printf("Ciag nie zostal zaakceptowany!\n");
        WriteDiagram(sequenceResult, sequence, seqLength);
        return 1;
    }


}
