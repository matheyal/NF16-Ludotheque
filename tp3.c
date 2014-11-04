#include "tp3.h"

t_ludotheque * creer_ludotheque()
{
    t_ludotheque *ludo = malloc(sizeof(t_ludotheque));
    ludo->nb_jeu = 0;
    ludo->debut = NULL;
    return ludo; //Si l'allocation a échoué, ludo=NULL et donc la fonction retournera NULL
}

t_jeu * creer_jeu( char * nom, genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree)
{
    t_jeu *jeu = malloc(sizeof(t_jeu));
    jeu->nom = nom;
    jeu->genre = genre;
    jeu->nbJoueurMin = nbJoueurMin;
    jeu->nbJoueurMax = nbJoueurMax;
    jeu->duree = duree;
    return jeu;
}

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
    if (inserer_milieu(ludo, j) == 1) //Le jeu a été inséré correctement
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
    {
        tmp = tmp->suivant;
    }

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

void afficher_ludotheque(t_ludotheque *ludo)
{
    int lmax = longueur_nom_max(ludo);
    printf("\nNOM");
    afficher_espaces(lmax-1);
    printf("GENRE");
    afficher_espaces(7);
    printf("NOMBRE DE JOUEURS |");
    printf("DUREE MOYENNE |\n");
    afficher_separateur(lmax+50);

    t_jeu * tmp = ludo->debut;
    while(tmp != NULL)
    {
        printf("%s",tmp->nom);
        fflush(stdout);
        afficher_espaces(lmax-strlen(tmp->nom)+2);
        afficher_genre(tmp->genre);
        fflush(stdout);
        afficher_espaces(12 - taille_genre(tmp->genre));
        fflush(stdout);
        printf("%d-%d",tmp->nbJoueurMin, tmp->nbJoueurMax);
        afficher_espaces(15);
        printf("%3d'", tmp->duree);
        afficher_espaces(10);
        printf("\n");
        tmp=tmp->suivant;
    }
    afficher_separateur(lmax+50);
    printf("TOTAL    %d\n", ludo->nb_jeu);
}

int longueur_nom_max(t_ludotheque *ludo) //Renvoie la longueur du nom le plus long de la ludothèque
{
    t_jeu * tmp = ludo->debut;
    int max = 0, l;
    while(tmp != NULL)
    {
        l = strlen(tmp->nom);
        if(l > max)
            max = l;
        tmp=tmp->suivant;
    }
    return max;
}

void afficher_espaces(int x)
{
    for (int i = 0 ; i<x ; i++)
        printf(" ");
    printf("|");
}

void afficher_genre(genre_jeu genre)
{

    switch (genre){
        case PLATEAU : printf("Plateau"); break;
        case RPG : printf("RPG"); break;
        case COOPERATIF : printf("Cooperatif"); break;
        case AMBIANCE : printf("Ambiance"); break;
        case HASARD : printf("Hasard"); break;
    };
}

int taille_genre(genre_jeu genre)
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

void afficher_separateur(int x)
{
    for (int i = 0 ; i<x ; i++)
        printf("-");
    printf("\n");
}

int retirer_jeu(t_ludotheque * ludo, char* nom)
{
    t_jeu *tmp = ludo->debut;
    t_jeu *tmp2;

    if (tmp == NULL) // Cas d'une liste vide
        return 0;

    if (tmp->nom == nom) // Nom trouvé à la première case de la liste
    {
        if (tmp->suivant == NULL) // Liste à un seul élément
        {
            free(tmp);
            ludo->debut = NULL;
            ludo->nb_jeu--;
        }
        else // Liste à plusieurs éléments
        {
            ludo->debut = tmp->suivant;
            free(tmp);
            ludo->nb_jeu--;
            return 1;
        }

        return 1;
    }

    while ((tmp->suivant != NULL) && (tmp->suivant->nom != nom)) // On parcourt la liste jusqu'à ce qu'on rencontre le nom recherché ou jusqu'à la fin
    {
        tmp = tmp->suivant;
    }

    if (tmp->suivant ==  NULL) // On a atteint la fin de la liste sans rencontrer le nom
        return 0;

    tmp2 = tmp->suivant;
    tmp->suivant = tmp->suivant->suivant;
    free(tmp2);
    ludo->nb_jeu--;
    return 1;

}

void supprimer_ludotheque(t_ludotheque *ludo)
{
    t_jeu *tmp, *j = ludo->debut;
    while (j != NULL)
    {
        tmp = j;
        j = j->suivant;
        free(tmp);
    }
}

t_ludotheque *requete_jeu(t_ludotheque *ludo, genre_jeu genre, int nbJoueurs, int duree)
{
    t_ludotheque *ludo2 = creer_ludotheque();
    t_jeu *tmp = ludo->debut;
    int good;

    while (tmp != NULL)
    {
        good = 1;
        if ((genre != -1) && (tmp->genre != genre))
            good = 0;
        if ((nbJoueurs != -1) && (nbJoueurs < tmp->nbJoueurMin || nbJoueurs > tmp->nbJoueurMax))
            good = 0;
        if ((duree != -1) && (duree < 0.9*tmp->duree || duree > 1.1*tmp->duree))
            good = 0;

        if (good == 1)
        {
            ajouter_jeu(ludo2,creer_jeu(tmp->nom, tmp->genre, tmp->nbJoueurMin, tmp->nbJoueurMax, tmp->duree));
            ludo2->nb_jeu++;
            printf("jeu ajoute\n");
        }

        tmp=tmp->suivant;
    }

    return ludo2;
}

t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2)
{
    t_jeu *tmp1 = ludo1->debut;
    t_jeu *tmp2 = ludo2->debut;
    t_ludotheque * res = creer_ludotheque();
    while (tmp1 != NULL || tmp2 != NULL)
    {
        if ((tmp2 == NULL) || (strcmp(tmp1->nom, tmp2->nom) < 0))
        {
            ajouter_jeu(res,creer_jeu(tmp1->nom, tmp1->genre, tmp1->nbJoueurMin, tmp1->nbJoueurMax, tmp1->duree));
            tmp1 = tmp1 ->suivant;
        }
        else if ((tmp1 == NULL) || (strcmp(tmp1->nom, tmp2->nom) > 0))
        {
            ajouter_jeu(res,creer_jeu(tmp2->nom, tmp2->genre, tmp2->nbJoueurMin, tmp2->nbJoueurMax, tmp2->duree));
            tmp2 = tmp2->suivant;
        }
        else if ((tmp2 != NULL) && (tmp1 != NULL))
        {
            ajouter_jeu(res,creer_jeu(tmp1->nom, tmp1->genre, tmp1->nbJoueurMin, tmp1->nbJoueurMax, tmp1->duree));
            tmp1 = tmp1 ->suivant;
            tmp2 = tmp2 ->suivant;
        }

    }

    return res;
}

