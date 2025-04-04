#include <stdio.h>

typedef struct Rationnel {
    int num;
    int denum;
} Rationnel;

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
    int pgcd = Pgcd(q.num, q.denum);
    q.num = q.num / pgcd;
    q.denum = q.denum / pgcd;
    pgcd = Pgcd(q.num, q.denum);

    return q;
}

Rationnel LireRationnel(){
    Rationnel q;
    printf("entrez a puis b\n");
    scanf(" %d", &q.num);
    scanf(" %d", &q.denum);
    return simplifier(q);
}

void printRationnel(Rationnel q){
    if (q.denum == 1){
        printf("%d\n", q.num);
    }
    else if (!q.num){
        printf("0\n");
    }
}

Rationnel SommeRationnel(Rationnel q1, Rationnel q2){
    Rationnel nQ;
    
    // meme denum commun
    nQ.denum = q1.denum * q2.denum;
    nQ.num = q1.num * q2.denum + q2.num * q1.denum;
    return simplifier(nQ);
}



int main(){
    Rationnel q = LireRationnel();
    printRationnel(q);
}