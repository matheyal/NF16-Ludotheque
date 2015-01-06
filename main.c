#include "tp3.h"

int main()
{
    int choix = -1;
    int i=1, j=0, requete = 0;
    t_ludotheque** tab_ludo = malloc(NB_LUDO_MAX* sizeof(t_ludotheque));

    /* Affichage de l'en-tete du programme */
    printf("\t");
    afficher_separateur(59);
    printf("\t| Bienvenue dans votre programme de gestion de ludotheque |\n");
    printf("\t");
    afficher_separateur(59);
    printf("\n");

    /* Affichage et choix du menu */
    while (choix != 6)
    {
        while (choix <=0 || choix >7)
        {
            printf("Selectionner une fonction : \n\n");
            printf("\t1- Creer une ludotheque\n");
            printf("\t2- Afficher une ludotheque\n");
            printf("\t3- Ajouter un jeu dans une ludotheque\n");
            printf("\t4- Supprimer un jeu d'une ludotheque\n");
            printf("\t5- Effectuer une recherche de jeu dans une ludothque\n");
            printf("\t6- Fusionner deux ludotheques\n");
            printf("\t7- Quitter le programme\n\n");
            printf("Votre choix ? ");
            scanf("%d",&choix);
        }
        switch(choix)
        {
            /* Creation ludotheque */
            case 1 : tab_ludo[i]=creer_ludotheque();
                     printf("\n\nLudotheque %d cree.\n\n",i);
                     i++;
                     choix = -1;
                     break;

            /* Afficher ludotheque */
            case 2 : printf("\n\nDonnez le numero de la ludotheque a afficher ( ludotheque 1 a %d cree ) : ",i-1);
                     scanf("%d",&j);
                     printf("\n\n");
                     afficher_ludotheque(tab_ludo[j]);
                     printf("\n");
                     choix = -1;
                     break;

            /* Ajouter jeu dans ludotheque */
            case 3 : printf("\n\nDonnez le numero de la ludotheque ou ajouter le jeu ( ludotheque 1 a %d cree ) : ",i-1);
                     scanf("%d",&j);
                     fflush(stdin);

                     /* Variables pour cette fonction reiniatialiser a chaque fois */
                     char * nom_new = malloc(50 * sizeof(char));
                     t_jeu * jeu_new;
                     genre_jeu genre_test = -1;
                     int nbJoueurMin = 0, nbJoueurMax = 0, duree = 0, verif =0;
                     char genre_str[10];

                     /* Saisie caracterisque jeu */
                     printf("Saisie des caracteristiques du jeu : \n");
                     fflush(stdin);
                     printf("\n\tEntrez le nom de votre jeu : ");
                     fgets(nom_new, 50, stdin);
                     nom_new = format_str(nom_new);
                     fflush(stdin);

                     while (genre_test <0 || genre_test > 4)
                     {
                     printf("\n\tEntrez le genre de votre jeu (PLATEAU, RPG, COOPERATIF, AMBIANCE OU HASARD ) : ");
                     scanf("%s",genre_str);
                     genre_test = string_to_genre(genre_str);
                     fflush(stdin);
                     }

                     while (nbJoueurMin <=0 || nbJoueurMin >50)
                     {
                     printf("\n\tEntrez le nombre de joueur minimum de votre jeu : ");
                     scanf("%d",&nbJoueurMin);
                     fflush(stdin);
                     }

                     while (nbJoueurMax <nbJoueurMin || nbJoueurMax >100)
                     {
                     printf("\n\tEntrez le nombre de joueur maximum de votre jeu : ");
                     scanf("%d",&nbJoueurMax);
                     fflush(stdin);
                     }

                     while (duree <=0 || duree >1000)
                     {
                     printf("\n\tEntrez la duree estimee de votre jeu : ");
                     scanf("%d",&duree);
                     fflush(stdin);
                     }

                     /* Creation et ajout du jeu a la ludotheque */
                     char* nom1 = (char*)malloc(strlen(nom_new));
                     memcpy(nom1, nom_new, strlen(nom_new)+1);
                     jeu_new = creer_jeu(nom1,genre_test,nbJoueurMin,nbJoueurMax,duree);
                     printf("\n");
                     printf("Jeu cree\n\n");
                     verif = ajouter_jeu(tab_ludo[j],jeu_new);
                     if (verif == 1)
                     printf("Jeu ajoute a la ludotheque\n\n");
                     else printf("Ereur : jeu non ajoute a la ludotheque\n");
                     choix = -1;
                     free(nom_new);
                     break;

            /* Supprimer un jeu en indiquant son nom */
            case 4 : printf("\n\nDonnez le numero de la ludotheque ou rechercher ( ludotheque 1 a %d cree ) : ",i-1);
                     scanf("%d",&j);
                     fflush(stdin);
                     char * nom_suppr = malloc(50 * sizeof(char));
                     printf("\nEntrez le nom du jeu a supprimer : ");
                     fgets(nom_suppr, 50, stdin);
                     nom_suppr = format_str(nom_suppr); // Met le nom dans le format classique d'un titre de jeu
                     if (retirer_jeu(tab_ludo[j], nom_suppr) == 1)
                        printf("Jeu '%s' retire de la ludo %d\n\n",nom_suppr,j);
                     else printf("Erreur lors de la suppression. Jeu non supprime.\n\n");
                     choix = -1;
                     free(nom_suppr);
                     break;

            /* Recherche avec critere */
            case 5 : printf("\n\nDonnez le numero de la ludotheque ou rechercher ( ludotheque 1 a %d cree ) : ",i-1);
                     scanf("%d",&j);
                     genre_jeu genre_souhait = -2 ;
                     int nbJoueurSouhait = -2, duree_souhait = -2;
                     char genre_str2[10];

                     /* Saisie des caracteristiques de la requètes */
                     printf("Entrer les caracteristique de votre requete :  (-1 pour ignore la caracterisque ) ");

                     while ((int)genre_souhait < -1 || (int)genre_souhait > 4)
                     {
                     printf("\n\tEntrez le genre souhaite ( -1 = IGNORE, PLATEAU, RPG, COOPERATIF, AMBIANCE OU HASARD ) : ");
                     scanf("%s",genre_str2);
                     genre_souhait = string_to_genre(genre_str2);
                     fflush(stdin);
                     }

                     while (nbJoueurSouhait <-1 || nbJoueurSouhait >100)
                     {
                     printf("\n\tEntrez le nombre de joueur souhaite (-1 pour ignore ) : ");
                     scanf("%d",&nbJoueurSouhait);
                     fflush(stdin);
                     }

                     while (duree_souhait <-1 || duree_souhait >1000)
                     {
                     printf("\n\tEntrez la duree estimee de votre jeu (-1 pour ignore ) : ");
                     scanf("%d",&duree_souhait);
                     fflush(stdin);
                     }

                     /* Creation de la ludotheque possedant le retour de la requete */
                     tab_ludo[0]=creer_ludotheque();
                     printf("\n");
                     printf("Resultat de la requete dans la ludotheque 0 : ");
                     tab_ludo[0]=requete_jeu(tab_ludo[j],genre_souhait,nbJoueurSouhait,duree_souhait);
                     afficher_ludotheque(tab_ludo[0]);
                     requete = 1;
                     choix = -1;
                     break;

            /* Fusion de 2 ludotheques */
            case 6 : printf("\n\nDonnez le numero de la ludotheque 1 a fusionner ( ludotheque 1 a %d cree ) : ",i-1);
                     scanf("%d",&j);
                     int k ;
                     k=j;

                     /* Saisie des 2 ludotheques a fusionner */
                     while ( k == j)
                     {
                        printf("\n\nDonnez le numero de la ludotheque 2 a fusionner ( ludotheque 1 a %d cree ) : ",i-1);
                        scanf("%d",&k);
                     }

                     /* Creation de la ludotheque fusionnée */
                     tab_ludo[i] = creer_ludotheque();
                     tab_ludo[i] = fusion(tab_ludo[j], tab_ludo[k]);
                     printf("La ludotheque fusionner est la %d : ",i);
                     afficher_ludotheque(tab_ludo[i]);
                     i++;
                     choix = -1;
                     break;

            /* Quitter le programme */
            case 7 : printf("\nSuppression de vos ludotheques\n\n");
                     j=0;
                     /* On retire la mémoire alouée a la ludo de la requète si on l'a utilisé */
                     if (requete == 1)
                        supprimer_ludotheque(tab_ludo[0]);
                     /* On retire la mémoires allouée dans les ludos utilisées */
                     for (j=1 ; j<i; j++)
                     {
                        if (tab_ludo[j] != NULL) // vérifie si elle est nulle pour économiser du temps
                        {
                            supprimer_ludotheque(tab_ludo[j]);
                            tab_ludo[j]=NULL;
                        }
                     }
                     /* On retire la mémoire allouée au tableau */
                     free(tab_ludo);
                     printf("\n\nAu revoir !\n");
                     return 0;
        }
    }
    return 0;
}

    /*  Test Des fonctions */
    /*
    t_ludotheque *ludo1, *ludo2, *ludo3;
    t_jeu *jeu1, *jeu2, *jeu3, *jeu4, *jeu5, *jeu6;


    //creer_ludotheque
    ludo1 = creer_ludotheque();
    ludo2 = creer_ludotheque();
    ludo3 = creer_ludotheque();

    //creer_jeu
    jeu1 = creer_jeu("Time's Up",AMBIANCE,4,8,35);
    jeu2 = creer_jeu("Endor",RPG,3,8,90);
    jeu3 = creer_jeu("Les Aventuriers du rail",PLATEAU,2,6,60);
    jeu4 = creer_jeu("Carcassonne",PLATEAU,2,6,80);
    jeu5 = creer_jeu("Carcassonne",PLATEAU,2,6,80);
    jeu6 = creer_jeu("Bluff Party",AMBIANCE,2,8,20);
    printf("Jeux crees\n\n");

    //ajouter_jeu
    printf("%d  jeu1 ajoute\n", ajouter_jeu(ludo1,jeu1));
    printf("%d  jeu2 ajoute\n", ajouter_jeu(ludo1,jeu2));
    printf("%d  jeu4 ajoute\n", ajouter_jeu(ludo1,jeu4));
    printf("%d  jeu3 ajoute\n", ajouter_jeu(ludo1,jeu3));
    printf("%d  jeu5 ajoute\n", ajouter_jeu(ludo1,jeu5));

    //afficher_ludotheque
    afficher_ludotheque(ludo1);

    //retirer_jeu
    printf("%d jeu retiré\n",retirer_jeu(ludo1, "Carcassonne"));
    afficher_ludotheque(ludo1);

    //requete_jeu
    ludo2 = requete_jeu(ludo1,-1, 3, 60);
    ajouter_jeu(ludo2, jeu6);
    //afficher_ludotheque(ludo2);

    //Fusion
    ludo3 = fusion(ludo1, ludo2);
    afficher_ludotheque(ludo3);

    //supprimer_ludotheque
    supprimer_ludotheque(ludo1);
    supprimer_ludotheque(ludo2);

    */

