#include <stdio.h>
#define MAXNOTES 20

typedef struct  Date {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct Fiche {
    char nom[10];
    char prenom[10];
    Date Naissance;
    char formation[2];
    int redoublant;
    int groupe;
    int note[MAXNOTES];
    int nbnotes;
} Fiche;

Fiche LireFiche (){
    Fiche f;
    printf("nom : ");
    scanf("%s", &f.nom);
    printf("prenom : ");
    scanf("%s", &f.prenom);
    printf("date de naissance (jour) : ");
    scanf("%d", &f.Naissance.jour);
    printf("date de naissance (mois) : ");
    scanf("%d", &f.Naissance.mois);
    printf("date de naissance (année) : ");
    scanf("%d", &f.Naissance.annee);
    printf("formation (en 2 lettres) : ");
    scanf("%s", &f.formation);
    printf("redoublant (0/1) : ");
    scanf("%d", &f.redoublant);
    printf("groupe (entier) : ");
    scanf("%d", &f.groupe);
    f.nbnotes = 0;
    
    return f;
}

void EcrireFiche(Fiche f){
    printf("nom : %s\n", f.nom);
    printf("prenom : %s\n", f.prenom);
    printf("date de naissance : %d/%d/%d\n", f.Naissance.jour, f.Naissance.mois, f.Naissance.annee);
    printf("formation : %s\n", f.formation);
    if (f.redoublant){
        printf("redoublant\n"  );
    }
    else {
        printf("non redoublant\n");
    }
    printf("groupe : %d\n", f.groupe);
    for (int i = 0; i < f.nbnotes; i++){
        printf("%d/20\n", f.note[i]);
    }
}

int AjouteNote(Fiche f, int note){
    if (f.nbnotes + 1 > MAXNOTES){
        return 1;
    }
    f.note[f.nbnotes] = note;
    f.nbnotes++;
    return 1;
}

float Moyenne(Fiche f){
    
    if (!f.nbnotes){
        return 0;
    }

    int s = 0;
    for (int i = 0; i < f.nbnotes; i++){
        s += f.note[i];
    }

    return (float) s / f.nbnotes;
}

