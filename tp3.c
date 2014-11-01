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
