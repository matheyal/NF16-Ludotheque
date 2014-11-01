#include "tp3.h"

int main()
{
    t_ludotheque *ludo1;
    t_jeu *jeu1, *jeu2, *jeu3, *jeu4, *jeu5;

    /*creer_ludotheque*/

    ludo1 = creer_ludotheque();
    //printf("%d", ludo1->nb_jeu);


    /*creer_jeu*/

    jeu1 = creer_jeu("Time's Up",AMBIANCE,4,8,35);
    jeu2 = creer_jeu("Endor",RPG,3,8,90);
    jeu3 = creer_jeu("Les Aventuriers du rail",PLATEAU,2,6,60);
    jeu4 = creer_jeu("Carcassonne",PLATEAU,2,6,80);
    jeu5 = creer_jeu("Carcassonne",PLATEAU,2,6,80);
    printf("Jeux crees\n\n");
    //printf("%s",jeu1->nom);


    /*ajouter_jeu*/

    printf("%d  jeu1 ajoute\n", ajouter_jeu(ludo1,jeu1));
    afficher_ludotheque(ludo1);
    printf("%d  jeu2 ajoute\n", ajouter_jeu(ludo1,jeu2));
    afficher_ludotheque(ludo1);
    printf("%d  jeu4 ajoute\n", ajouter_jeu(ludo1,jeu4));
    afficher_ludotheque(ludo1);
    printf("%d  jeu3 ajoute\n", ajouter_jeu(ludo1,jeu3));
    afficher_ludotheque(ludo1);
    printf("%d  jeu5 ajoute\n", ajouter_jeu(ludo1,jeu5));
    afficher_ludotheque(ludo1);

    /*afficher_ludotheque*/


    return 0;
}
