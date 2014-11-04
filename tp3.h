#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum genre_jeu //Creation du type genre_jeu en meme temps que l'enum
{
    PLATEAU,
    RPG,
    COOPERATIF,
    AMBIANCE,
    HASARD
} genre_jeu;

typedef struct jeu //Creation du type t_jeu en meme temps que la struct jeu
{
    char *nom;
    genre_jeu genre;
    int nbJoueurMin;
    int nbJoueurMax;
    int duree;
    struct jeu * suivant;
} t_jeu;

typedef struct ludotheque //Creation du type t_ludotheque en meme temps que la struct ludotheque
{
    int nb_jeu;
    t_jeu *debut;
} t_ludotheque;

t_ludotheque * creer_ludotheque();

t_jeu * creer_jeu( char * nom, genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree);

int ajouter_jeu (t_ludotheque *ludo, t_jeu *j);

int inserer_debut(t_ludotheque *ludo, t_jeu *j);

int inserer_milieu(t_ludotheque *ludo, t_jeu *j);

void afficher_ludotheque(t_ludotheque *ludo);

int retirer_jeu(t_ludotheque * ludo, char* nom);

void supprimer_ludotheque(t_ludotheque *ludo);

t_ludotheque * requete_jeu(t_ludotheque *ludo, genre_jeu genre, int nbJoueurs, int duree);

t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2);

/*Fonctions esthétiques pour l'affichage*/

int longueur_nom_max(t_ludotheque *ludo);

void afficher_espaces(int x);

void afficher_genre(genre_jeu genre);

int taille_genre(genre_jeu genre);

void afficher_separateur(int x);

