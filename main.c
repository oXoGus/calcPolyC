#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define DGMAX 100



typedef struct Rationnel {
    int num;
    int den;
} Rationnel;

typedef struct Polynomes {
    Rationnel *polyCoef;
    int degre;
}Polynomes;

int Pgcd(int n, int m){
    
    // algorithme d'Euclide
    while (m != 0){
        int tmp = m;
        m = n % m;
        n = tmp;
    }
    return n;
}

Rationnel simplifier(Rationnel q){

    // tant que le pgcd pas 0
    int pgcd = Pgcd(q.num, q.den);
    q.num = q.num / pgcd;
    q.den = q.den / pgcd;
    pgcd = Pgcd(q.num, q.den);

    return q;
}

void printRationnel(Rationnel q){
    if (q.den == 1){
        printf("%d", q.num);
    }
    else if (!q.num){
        printf("0");
    }
    else {
        printf("%d/%d", q.num, q.den);
    }
}

Rationnel LireRationnel(){
    Rationnel q;
    
    // le retionnel est rentré sous la forme a/b
    scanf(" %d/%d", &q.num, &q.den);

    q = simplifier(q);

    // gestion du signe
    // si le den est negatif on met le signe au num
    if (q.den < 0){
        q.num = -q.num;
        q.den = abs(q.den);
    } 

    return q;
}


Rationnel SommeRationnel(Rationnel q1, Rationnel q2){
    Rationnel nQ;
    
    // meme den commun
    nQ.den = q1.den * q2.den;
    nQ.num = q1.num * q2.den + q2.num * q1.den;
    return simplifier(nQ);
}

int LirePolynome(Polynomes *poly){
    int deg = 0;
    Rationnel polyCoef;
    int dgPoly = 0;
    printf("entrez le degré du poly (entre 0 et %d)\n", DGMAX);
    scanf(" %d", &dgPoly);
    if (dgPoly > DGMAX){
        return 1;
    }


    poly->degre = dgPoly;
    
    // alocation dynamique de la mémoir pour le tableau
    poly->polyCoef = (Rationnel *) malloc(sizeof(Rationnel) * (dgPoly + 1));

    // on initialise toutes les cases du tableau a 0
    Rationnel zero = {0, 1}; // 0/1
    for (int i = 0; i < dgPoly + 1; i++){
        poly->polyCoef[i] = zero; 
    }

    for (int i = 0; i < dgPoly + 1; i++){
        
        // le user doit rentrer un degré valide
        do {
            printf("deg <= %d = ", dgPoly);
            scanf("%d", &deg);
        } while (deg > dgPoly);
        

        
        printf("coef (forme : a/b) = ");
        polyCoef = LireRationnel();
        while (polyCoef.den == 0){
            printf("b != 0\n");
            printRationnel(polyCoef);
            printf("coef (forme : a/b) = ");
            polyCoef = LireRationnel();
        }
        

        poly->polyCoef[deg] = polyCoef; 
    }
    return 0;
}

void printPoly(Polynomes poly){

    int isFirstDigit = 1;
    
    for (int i = poly.degre; i >= 0; i--){

        Rationnel coef = poly.polyCoef[i];
        if (coef.num == 0){
            continue;
        }

        // premier polyCoef
        if (!isFirstDigit && coef.num >= 0){
            printf("+");

        }
        // ne pas afficher 1*x^n sauf si c'est le dernier coef
        if (coef.num != coef.den || i == 0){
            printRationnel(coef);

            if (i > 0){
                printf("*");
            }
        }
        

        // premier chiffre print
        isFirstDigit = 0;
        
        // les *x^n
        int n = i;

        // x^1
        if (n == 1){
            printf("x");
        }
        else if (n > 1){
            printf("x^%d", n);
        }
    }
    printf("\n");
}


Rationnel copy(Rationnel q){

    // copie un rationnel pour 
    // eviter de modifier plusieurs Rationnels 
    // en meme temps
    Rationnel nQ;
    nQ.num = q.num;
    nQ.den = q.den;
    return nQ;
}

Polynomes somme(Polynomes poly1, Polynomes poly2){
    
    // on créer le nouveau polynome
    Polynomes nPoly;
    
    // polynome de degré du poly qui a le plus grand degré
    int maxDeg = 0;
    if (poly1.degre > poly2.degre){
        maxDeg = poly1.degre;
    }
    else {
        maxDeg = poly2.degre;
    }

    nPoly.degre = maxDeg;
    
    // taille du tableau qui dépend du plus grand degré 
    nPoly.polyCoef = (Rationnel *) malloc(sizeof(Rationnel) * (maxDeg + 1));


    // on 'recopie' les coef du plus grnad poly
    Polynomes maxPoly;
    Polynomes minPoly;
    if (poly1.degre > poly2.degre){
        maxPoly = poly1; 
        minPoly = poly2;
    }
    else {
        maxPoly = poly2; 
        minPoly = poly1;
    }

    for (int i = 0; i < nPoly.degre + 1; i++){
        nPoly.polyCoef[i] = copy(maxPoly.polyCoef[i]);
    }

    // somme avec les nouveaux coef
    for (int i = 0; i < minPoly.degre + 1; i++){
        nPoly.polyCoef[i] = SommeRationnel(nPoly.polyCoef[i], minPoly.polyCoef[i]);
    }

    return nPoly;
}

Rationnel produitRationnel(Rationnel q1, Rationnel q2){
    Rationnel nQ;

    nQ.num = q1.num * q2.num;
    nQ.den = q1.den * q2.den;
    return simplifier(nQ);
}


Polynomes produit(Polynomes poly1, Polynomes poly2){
    
    // on créer le nouveau polynome
    Polynomes nPoly;
    
    // on additionne les degrés des deux poly 
    nPoly.degre = poly1.degre + poly2.degre;
    
    // taille du tableau qui dépend du plus grand degré 
    nPoly.polyCoef = (Rationnel *) malloc(sizeof(Rationnel) * (nPoly.degre + 1));

    // on initialise toutes les cases du tableau a 0
    Rationnel zero = {0, 1}; // 0/1
    for (int i = 0; i < nPoly.degre + 1; i++){
        nPoly.polyCoef[i] = zero; 
    }

    // distributivité
    for (int i = 0;  i < poly1.degre + 1; i++){
        for (int j = 0; j < poly2.degre + 1; j++){
            nPoly.polyCoef[i+j] = SommeRationnel(nPoly.polyCoef[i+j], produitRationnel(poly1.polyCoef[i], poly2.polyCoef[j]));
        }
    }

    return nPoly;
}

Rationnel puissance(Rationnel q, int n){
    Rationnel nQ;
    
    nQ.num = pow(q.num, n);
    nQ.den = pow(q.den, n);
    return simplifier(nQ);
}

Rationnel evaluation(Polynomes poly, Rationnel x){
    // on calcul l'image pour x monome par monome
    // on init un rationnel nul
    Rationnel res = {0, 1};
    
    // pour chaque coef
    for (int i = 0; i < poly.degre + 1; i++){
        res = SommeRationnel(res, produitRationnel(poly.polyCoef[i], puissance(x, i)));
    }
    return res;
}

Polynomes derive(Polynomes poly){
    // on recreer le poly de degré n-1 
    if (poly.degre - 1 < 0){

        // on renvoi un poly nul
        Rationnel zeroRationnel = {0, 1};
        Polynomes zeroPoly;
        zeroPoly.degre = 0;
        zeroPoly.polyCoef = (Rationnel *) malloc(sizeof(Rationnel) * 1);
        zeroPoly.polyCoef[0] = zeroRationnel;
        return zeroPoly;
    }

    Polynomes nPoly;
    
    nPoly.degre = poly.degre - 1;
    
    nPoly.polyCoef = (Rationnel *) malloc(sizeof(Rationnel) * (nPoly.degre + 1));
    
    // pour chaque coef du poly suf pour l'index 0 qui disparait
    for (int i = 1; i < poly.degre; i++){

        Rationnel mult = {i, 1};
        nPoly.polyCoef[i - 1] = produitRationnel(poly.polyCoef[i], mult);
    }
}




int main(){
    
    Polynomes poly1;
    LirePolynome(&poly1);
    printPoly(poly1);
    Polynomes poly2;
    LirePolynome(&poly2);
    printPoly(poly2);
    printPoly(produit(poly1, poly2));
    

    /*
    Rationnel q1 = LireRationnel();
    Rationnel q2 = LireRationnel();
    printRationnel(q1);printf("+");printRationnel(q2);printf(" = ");printRationnel(SommeRationnel(q1, q2));
    */
}
