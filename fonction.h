#ifndef fonction_h
#define fonction_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include "FONCTION.c"
#define max 256

/////////////////////////////////////////////////definition des structs//////////////////////////////////////////
//1 DEFINIR LE TYPE LISTE
typedef struct noeud*liste;
typedef struct noeud{
    char*word;
    liste suivant;
}noeud;
// DEFINIR LISTE FREQ 
typedef struct noeuds* listefreq;
typedef struct noeuds{
    int nbapp;
    char*mot;
    listefreq suivants;
}noeuds;
//3 DEFINIR LE TYPE DICTIONNAIRE 
typedef struct dict*dictionnaire;
typedef struct dict{
  char* motDict;
  listefreq contextes;
  dictionnaire suivantDict;
}dict;

///////////////////////////////////////////les fonction/////////////////////////////////////////////////////////////
//reponse1
//fonction pour allouer une chaine de caractère
char * allouerChaine(int n);
long taille(FILE*f );
char*lire (FILE*f);
liste creernoeud(char*mot);
void afficherListe(liste L);
liste creeListeChaine(char *ch);
void supprimerdoublants(liste L);
int count( liste head, char * search);
liste duplicate(liste l);
void permuter(listefreq L1,listefreq L2);
void selectionSortAscending(listefreq tete);
void selectionSortdescending(listefreq tete);
listefreq creernoeudlistefrequence(char*word,int nombreocc);
void afficherlistefrequence(listefreq list);
liste contexterMot(liste list, char* m);
listefreq  frequencesDe(liste ContexteAvcDouble);
void affichagedictionnaire(dictionnaire Ldiction);
dictionnaire creerNouedDictionnaire(char* mot, listefreq contextesMot);
dictionnaire creationdictionary(liste desmots);
char*maxcontexte(dictionnaire dict,char*m);
int freqCont(dictionnaire dict ,char*m , char*n);
int nombremotliste(liste L);
int generernbr(int n);
char*aleatoirement(int k,dictionnaire d);
void genererTEXTE(dictionnaire d,int naff,char*aword);


#endif


