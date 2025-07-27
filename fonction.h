#ifndef FONCTION_H
#define FONCTION_H

// Standard Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define MAX 256

/////////////////////////////////////////////////
//               STRUCT DEFINITIONS            //
/////////////////////////////////////////////////

// 1. Linked list for storing words
typedef struct noeud* liste;
typedef struct noeud {
    char *word;
    liste suivant;
} noeud;

// 2. Frequency list (word + count)
typedef struct noeuds* listefreq;
typedef struct noeuds {
    int nbapp;
    char *mot;
    listefreq suivants;
} noeuds;

// 3. Dictionary (word + frequency list of contexts)
typedef struct dict* dictionnaire;
typedef struct dict {
    char *motDict;
    listefreq contextes;
    dictionnaire suivantDict;
} dict;

/////////////////////////////////////////////////
//             FUNCTION DECLARATIONS           //
/////////////////////////////////////////////////

// ----------- Utility & File Operations ----------
char *allouerChaine(int n);
long taille(FILE *f);
char *lire(FILE *f);

// ----------- Word List (liste) Operations ----------
liste creernoeud(char *mot);
void afficherListe(liste L);
liste creeListeChaine(char *ch);
void supprimerdoublants(liste L);
int count(liste head, char *search);
liste duplicate(liste l);
int nombremotliste(liste L);

// ----------- Frequency List (listefreq) ----------
listefreq creernoeudlistefrequence(char *word, int nombreocc);
void afficherlistefrequence(listefreq list);
void permuter(listefreq L1, listefreq L2);
void selectionSortAscending(listefreq tete);
void selectionSortdescending(listefreq tete);

// ----------- Context & Frequency Analysis ----------
liste contexterMot(liste list, char *m);
listefreq frequencesDe(liste ContexteAvcDouble);

// ----------- Dictionary (dictionnaire) ----------
dictionnaire creerNouedDictionnaire(char *mot, listefreq contextesMot);
dictionnaire creationdictionary(liste desmots);
void affichagedictionnaire(dictionnaire Ldiction);
char *maxcontexte(dictionnaire dict, char *m);
int freqCont(dictionnaire dict, char *m, char *n);

// ----------- Random Generation ----------
int generernbr(int n);
char *aleatoirement(int k, dictionnaire d);
void genererTEXTE(dictionnaire d, int naff, char *aword);

#endif // FONCTION_H
