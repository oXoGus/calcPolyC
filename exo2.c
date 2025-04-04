#include <stdio.h>
#define DGMAX 5

typedef struct Polynomes {
    // +1 pour le dernier coef
    int coef[DGMAX + 1];
    int polyDeg;
}Polynomes;

int LirePolynome(Polynomes *poly){
    int deg = 0;
    int coef = 0;
    int dgPoly = 0;
    printf("entrez le degré du poly\n");
    scanf(" %d", &dgPoly);
    if (dgPoly > DGMAX){
        return 1;
    }
    poly->polyDeg = dgPoly;
    for (int i = 0; i < dgPoly + 1; i++){
        printf("deg = ");
        scanf("%d", &deg);
        printf("coef = ", &coef);
        scanf("%d", &coef);
        poly->coef[deg] = coef; 
    }
    return 0;
}

void printPoly(Polynomes poly){

    int isFirstDigit = 1;
    
    for (int i = 0; i < poly.polyDeg + 1; i++){
        if (poly.coef[i] == 0){
            continue;
        }
        // on affiche quelque chose

        // positif 
        if (poly.coef[i] > 0){

            // premier coef
            if (isFirstDigit){
                printf("%d", poly.coef[i]);
            } else {
                printf("+%d", poly.coef[i]);
            }
        }
        else {
            printf("%d", poly.coef[i]);

        }

        // premier chiffre print
        isFirstDigit = 0;
        
        // les *x^n
        int n = poly.polyDeg - i;
        // x^1
        if (n == 1){
            printf("*x");
        }
        else if (n > 1){
            printf("*x^%d", n);
        }
    }
    printf("\n");
}

int main(){
    Polynomes poly;
    int res = LirePolynome(&poly);
    printPoly(poly);
}


