#include "tp3.h"

int main()
{
    t_ludotheque *ludo1;
    t_jeu *jeu1, *jeu2, *jeu3;

    /*creer_ludotheque*/

    ludo1 = creer_ludotheque();
    //printf("%d", ludo1->nb_jeu);


    /*creer_jeu*/

    jeu1 = creer_jeu("Time's Up",AMBIANCE,4,8,35);
    jeu2 = creer_jeu("Endor",RPG,3,8,90);
    jeu3 = creer_jeu("Les Aventuriers du rail",PLATEAU,2,6,60);
    printf("Jeux crees\n\n");
    //printf("%s",jeu1->nom);


    /*ajouter_jeu*/

    printf("%d  jeu1 ajoute\n", ajouter_jeu(ludo1,jeu1));
    printf("%d  jeu2 ajoute\n", ajouter_jeu(ludo1,jeu2));
    printf("%d  jeu3 ajoute\n", ajouter_jeu(ludo1,jeu3));

    /*afficher_ludotheque*/
    afficher_ludotheque(ludo1);

    return 0;
}
