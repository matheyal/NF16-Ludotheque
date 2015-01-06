#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NB_LUDO_MAX 10

/* Creation du type genre_jeu en même temps que l'enum */

typedef enum genre_jeu
{
    PLATEAU,
    RPG,
    COOPERATIF,
    AMBIANCE,
    HASARD
} genre_jeu;

 /* Creation du type t_jeu en même temps que la struct jeu */

typedef struct jeu
{
    char *nom;
    genre_jeu genre;
    int nbJoueurMin;
    int nbJoueurMax;
    int duree;
    struct jeu * suivant;
} t_jeu;

/* Creation du type t_ludotheque en même temps que la struct ludotheque */

typedef struct ludotheque
{
    int nb_jeu;
    t_jeu *debut;
} t_ludotheque;

/* Creer ludotheque et jeu */

t_ludotheque * creer_ludotheque();

t_jeu * creer_jeu( char * nom, genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree);

/* Ajouter Jeu */

int ajouter_jeu (t_ludotheque *ludo, t_jeu *j);

//Meilleur compréhension de la fonction
int inserer_debut(t_ludotheque *ludo, t_jeu *j);
int inserer_milieu(t_ludotheque *ludo, t_jeu *j);

/* Afficher Ludo */

void afficher_ludotheque(t_ludotheque *ludo);

//Esthétiques de la fonction
int longueur_nom_max(t_ludotheque *ludo);
void afficher_espaces(int x);
void afficher_genre(genre_jeu genre);
int taille_genre(genre_jeu genre);
void afficher_separateur(int x);
genre_jeu string_to_genre(char * s);
char * format_str (char * s);

/* Supprimer jeu et ludotheque */

int retirer_jeu(t_ludotheque * ludo, char* nom);

void supprimer_ludotheque(t_ludotheque *ludo);

/* Fonction requete et fusion */

t_ludotheque * requete_jeu(t_ludotheque *ludo, genre_jeu genre, int nbJoueurs, int duree);

t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2);
