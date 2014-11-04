#include "tp3.h"

int main()
{
    t_ludotheque *ludo1;
    t_jeu *jeu1, *jeu2, *jeu3, *jeu4, *jeu5;

    /*creer_ludotheque*/

    ludo1 = creer_ludotheque();


    /*creer_jeu*/

    jeu1 = creer_jeu("Time's Up",AMBIANCE,4,8,35);
    jeu2 = creer_jeu("Endor",RPG,3,8,90);
    jeu3 = creer_jeu("Les Aventuriers du rail",PLATEAU,2,6,60);
    jeu4 = creer_jeu("Carcassonne",PLATEAU,2,6,80);
    jeu5 = creer_jeu("Carcassonne",PLATEAU,2,6,80);
    printf("Jeux crees\n\n");

    /*ajouter_jeu*/

    printf("%d  jeu1 ajoute\n", ajouter_jeu(ludo1,jeu1));
    printf("%d  jeu2 ajoute\n", ajouter_jeu(ludo1,jeu2));
    printf("%d  jeu4 ajoute\n", ajouter_jeu(ludo1,jeu4));
    printf("%d  jeu3 ajoute\n", ajouter_jeu(ludo1,jeu3));
    printf("%d  jeu5 ajoute\n", ajouter_jeu(ludo1,jeu5));

    /*afficher_ludotheque*/
    afficher_ludotheque(ludo1);

    /*retirer_jeu*/
    //printf("%d jeu retiré\n",retirer_jeu(ludo1, "Carcassonne"));
    //afficher_ludotheque(ludo1);

    /*requete_jeu*/
    afficher_ludotheque(requete_jeu(ludo1,-1, 3, 60));

    /*supprimer_ludotheque*/
    supprimer_ludotheque(ludo1);

    return 0;
}
