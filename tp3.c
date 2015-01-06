#include "tp3.h"

/* Creer ludotheque et jeu */

t_ludotheque * creer_ludotheque()
{
    t_ludotheque* ludo_nouveau = (t_ludotheque*)malloc(sizeof(t_ludotheque));
    if (ludo_nouveau == NULL)
        exit (EXIT_FAILURE); //ludo_nouveau==NULL , si l'allocation a échoué
    ludo_nouveau->nb_jeu = 0;
    ludo_nouveau->debut = NULL;
    return ludo_nouveau; //Si l'allocation a réussi, renvoie de la nouvelle ludo créer
}

t_jeu * creer_jeu( char * nom, genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree)
{
    t_jeu* jeu_nouveau = (t_jeu*)malloc(sizeof(t_jeu));
    if (jeu_nouveau == NULL)
        exit (EXIT_FAILURE); //jeu_nouveau==NULL , si l'allocation a échoué
    jeu_nouveau->nom = nom;
    jeu_nouveau->genre = genre;
    jeu_nouveau->nbJoueurMin = nbJoueurMin;
    jeu_nouveau->nbJoueurMax = nbJoueurMax;
    jeu_nouveau->duree = duree;
    return jeu_nouveau; //Si l'allocation a réussi, renvoie ddu jeu_nouveau
}

/* Ajouter Jeu */

int ajouter_jeu (t_ludotheque *ludo, t_jeu *j)
{
    //Ludotheque vide
    if ((ludo->debut == NULL) || (strcmp(j->nom, ludo->debut->nom) < 0))
    {
        inserer_debut(ludo, j);
        return 1;
    }
    if (strcmp(j->nom, ludo->debut->nom) == 0)
        return 0;

    //Ludotheque non vide
    if (inserer_milieu(ludo, j) == 1)//Le jeu a été inséré correctement
        return 1;
    else //Le jeu était déjà dans la liste
        return 0;
}

int inserer_debut(t_ludotheque *ludo, t_jeu *j)
{
    ludo->nb_jeu++;
    t_jeu *tmp = ludo->debut;
    ludo->debut = j;
    j->suivant = tmp;
    return 1;
}

int inserer_milieu(t_ludotheque *ludo, t_jeu *j)
{
    t_jeu *tmp;
    tmp = ludo->debut;
    //On parcourt la liste jusqu'à la fin ou jusqu'à ce que le nom du suivant soit plus grand (ou égal) alphabétiquement
    while ((tmp->suivant != NULL) && (strcmp(j->nom, tmp->suivant->nom) > 0))
        tmp = tmp->suivant;

    //on verifie si le jeu est déjà dans la liste
    if ((tmp->suivant != NULL) && (tmp->suivant->nom == j->nom))
        return 0;
    else //On insère à la bonne place
    {
        j->suivant = tmp->suivant;
        tmp->suivant = j;
        ludo->nb_jeu++;
        return 1;
    }
}

/* Afficher_ludotheque*/

void afficher_ludotheque(t_ludotheque *ludo)
{
    if (ludo->nb_jeu != 0)
    {
        int lmax;
        lmax = longueur_nom_max(ludo);
        printf("\n\n| NOM");
        afficher_espaces(lmax-3);
        printf("GENRE");
        afficher_espaces(7);
        printf("NOMBRE DE JOUEURS |");
        printf("DUREE MOYENNE |\n");
        afficher_separateur(lmax+50);

        t_jeu * tmp = ludo->debut;
        while(tmp != NULL)
        {
            printf("| %s",tmp->nom);
            fflush(stdout);
            afficher_espaces(lmax-strlen(tmp->nom));
            afficher_genre(tmp->genre);
            fflush(stdout);
            afficher_espaces(12 - taille_genre(tmp->genre));
            fflush(stdout);
            printf("%2d-%-2d",tmp->nbJoueurMin, tmp->nbJoueurMax);
            afficher_espaces(13);
            printf("%3d'", tmp->duree);
            afficher_espaces(10);
            printf("\n");
            tmp=tmp->suivant;
        }
        afficher_separateur(lmax+50);
        printf("TOTAL    %d\n", ludo->nb_jeu);
    }
    else printf("\nLudotheque vide.\n");
}

int longueur_nom_max(t_ludotheque *ludo) //Renvoie la longueur du nom le plus long de la ludothèque
{
    t_jeu * tmp = ludo->debut;
    int max = 0, l;
    l = strlen(tmp->nom);
    if(l > max)
        max = l;
    while(tmp != NULL)
    {
        l = strlen(tmp->nom);
        if(l > max)
            max = l;
        tmp=tmp->suivant;
    }
    return max;
}

void afficher_espaces(int x) // Affiche les espaces pour avoir une ludothèque esthétique
{
    int i = 0;
    for (i = 0 ; i<x ; i++)
        printf(" ");
    printf("|");
}

void afficher_genre(genre_jeu genre) // Affiche les genres en caractères ( et non en entier )
{
    switch (genre){
        case PLATEAU : printf("Plateau"); break;
        case RPG : printf("RPG"); break;
        case COOPERATIF : printf("Cooperatif"); break;
        case AMBIANCE : printf("Ambiance"); break;
        case HASARD : printf("Hasard"); break;
    };
}

void afficher_separateur(int x) // Fonction esthétique servant a afficehr les séparateurs dde la ludothèque à l'affichage
{
    int i = 0;
    for (i = 0 ; i<x ; i++)
        printf("-");
    printf("\n");
}

int taille_genre(genre_jeu genre) // Fonction calculant la taille des genre pour optimiser la taille de la ludothèque à l'affichage
{
    switch (genre)
    {
        case PLATEAU : return 7;
        case RPG : return 3;
        case COOPERATIF : return 10;
        case AMBIANCE : return 8;
        case HASARD : return 6;
        default : return 0;
    }
}

genre_jeu string_to_genre(char * s) // Fonction transformant une chaine de caractères en genre
{
    //int l;
    for (int i = 0, l = strlen(s) ; i<l ; i++)
    {
        if (s[i]<='z' && s[i]>='a')
            s[i] = s[i] - 'a' + 'A';
    }

    if (strcmp(s, "PLATEAU")==0)
        return PLATEAU;
    if (strcmp(s, "RPG")==0)
        return RPG;
    if (strcmp(s, "COOPERATIF")==0)
        return COOPERATIF;
    if (strcmp(s, "AMBIANCE")==0)
        return AMBIANCE;
    if (strcmp(s, "HASARD")==0)
        return HASARD;
    return -1;
}

char * format_str (char * s)
{
    int i = 0, l;
    if (s[i]<='z' && s[i]>='a')
            s[i] = s[i] - 'a' + 'A';

    for (i = 1, l = strlen(s) ; i<l ; i++)
    {
        if (s[i]<='Z' && s[i]>='A')
            s[i] = s[i] - 'A' + 'a';
    }
    return s;
}


/* Supprimer jeu et ludotheque */

int retirer_jeu(t_ludotheque * ludo, char* nom)
{
    t_jeu *tmp = ludo->debut;
    t_jeu *tmp2;

    if (tmp == NULL) // Cas d'une liste vide
        return 0;

    if (strcmp(tmp->nom,nom) == 0) // Nom trouvé à la première case de la liste
    {
        if (tmp->suivant == NULL) // Liste à un seul élément
        {
            free(tmp); // Rend l'allocation mémoire au jeu
            ludo->debut = NULL;
            ludo->nb_jeu--;
            return 1;
        }
        else // Liste à plusieurs éléments
        {
            ludo->debut = tmp->suivant;
            free(tmp); // Rend l'allocation mémoire au jeu
            ludo->nb_jeu--;
            return 1;
        }
    }

    while ((tmp->suivant != NULL) && (strcmp(tmp->suivant->nom, nom) != 0)) // On parcourt la liste jusqu'à ce qu'on rencontre le nom recherché ou jusqu'à la fin
    {
        tmp = tmp->suivant;
    }

    if (tmp->suivant ==  NULL) // On a atteint la fin de la liste sans rencontrer le nom
        return 0;

    tmp2 = tmp->suivant; // cas ou tmp->suivant->nom == nom
    tmp->suivant = tmp2->suivant;
    free(tmp2); // Rend l'allocation mémoire au jeu
    ludo->nb_jeu--;
    return 1;
}

void supprimer_ludotheque(t_ludotheque *ludo)
{
    t_jeu *tmp, *j = ludo->debut;
    while ( j != NULL)
    {
        tmp = j;
        j = j->suivant;
        free(tmp); // Rend l'allocation mémoire à la mémoire des ludothèque
    }
    free(ludo);
}

/* Fonction requete et fusion */

t_ludotheque *requete_jeu(t_ludotheque *ludo, genre_jeu genre, int nbJoueurs, int duree)
{
    t_ludotheque *ludo2 = (t_ludotheque*)malloc(sizeof(t_ludotheque));
    ludo2 = creer_ludotheque();
    t_jeu *tmp = ludo->debut;
    int good;

    while (tmp != NULL)
    {
        good = 1; // Requete accepté au début de boucle pour la comparaison avec chaque jeu
        if ((genre != -1) && (tmp->genre != genre))
            good = 0; //Requete refusé si genre différent de celui demandé (-1 est ignoré)
        if ((nbJoueurs != -1) && (nbJoueurs < tmp->nbJoueurMin || nbJoueurs > tmp->nbJoueurMax))
            good = 0; //Requete refusé si nombre de joueur différent de celui demandé (-1 est ignoré)
        if ((duree != -1) && (duree < 0.9*tmp->duree || duree > 1.1*tmp->duree))
            good = 0; //Requete refusé si durée 10% différente de celle demandée (-1 est ignoré)
        if (good == 1) // Requete non refuré pour tout les critere : on ajoute le jeu a la nouvelle ludo de requete
            ajouter_jeu(ludo2,creer_jeu(tmp->nom, tmp->genre, tmp->nbJoueurMin, tmp->nbJoueurMax, tmp->duree));
        tmp=tmp->suivant;
    }
    return ludo2;
}

t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2)
{
    t_jeu *tmp1 = ludo1->debut;
    t_jeu *tmp2 = ludo2->debut;
    t_ludotheque * res = creer_ludotheque();
    while (tmp1 != NULL || tmp2 != NULL) // Boucle s'arretant une fois que les 2 ludothèques ont été entièrement parcourue
    {
        if ((tmp2 == NULL) || ((tmp1 != NULL) && (strcmp(tmp1->nom, tmp2->nom) < 0))) // cas ou l'ordre alphabetique du jeu dans la ludo 1 est inférieur a celui de la ludo 2
        {
            ajouter_jeu(res,creer_jeu(tmp1->nom, tmp1->genre, tmp1->nbJoueurMin, tmp1->nbJoueurMax, tmp1->duree));
            tmp1 = tmp1->suivant;
        }
        else if ((tmp1 == NULL) || ((tmp2 != NULL) && (strcmp(tmp1->nom, tmp2->nom) > 0))) // cas ou l'ordre alphabetique du jeu dans la ludo 2 est inférieur a celui de la ludo 1
        {
            ajouter_jeu(res,creer_jeu(tmp2->nom, tmp2->genre, tmp2->nbJoueurMin, tmp2->nbJoueurMax, tmp2->duree));
            tmp2 = tmp2->suivant;
        }
        else if ((tmp2 != NULL) && (tmp1 != NULL)) // Cas ou les ludotheque ont le meme jeu
        {
            ajouter_jeu(res,creer_jeu(tmp1->nom, tmp1->genre, tmp1->nbJoueurMin, tmp1->nbJoueurMax, tmp1->duree));
            tmp1 = tmp1->suivant;
            tmp2 = tmp2->suivant;
        }
    }
    return res;
}
