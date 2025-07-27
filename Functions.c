#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define max 256

#include "fonction.h"

/////////////////////////////////////////// UTILITY FUNCTIONS ///////////////////////////////////////////

// Allocate a string of n characters
char *allouerChaine(int n) {
    char *s = (char*)malloc(n * sizeof(char));
    if (s != NULL) return s;
    exit(-1);
}

// Return the size of a file
long taille(FILE *f) {
    fseek(f, 0, SEEK_END);
    return ftell(f);
}

// Read entire content of a file
char *lire(FILE *f) {
    long lg = taille(f);
    char *contenu = allouerChaine(lg + 1);
    rewind(f);
    fread(contenu, 1, lg, f);
    return contenu;
}

/////////////////////////////////////////// SIMPLE LINKED LIST ///////////////////////////////////////////

// Create a new node
liste creernoeud(char *mot) {
    liste p = (liste)malloc(sizeof(noeud));
    if (!p) {
        printf("\n malloc de noeud retourne NULL!");
        exit(-1);
    }
    p->word = allouerChaine(max);
    strcpy(p->word, mot);
    p->suivant = NULL;
    return p;
}

// Display a list
void afficherListe(liste L) {
    printf("\n\nLa liste est: \n");
    while (L != NULL) {
        printf("----> %s  ", L->word);
        L = L->suivant;
    }
}

// Create list from string (tokenized input)
liste creeListeChaine(char *ch) {
    liste M = NULL, p, q;
    char *m = strtok(ch, " ,.:;\"\n");

    while (m != NULL) {
        p = creernoeud(m);
        if (M == NULL) {
            M = p;
            q = p;
        } else {
            q->suivant = p;
            q = p;
        }
        m = strtok(NULL, " ,.:;\"\n");
    }
    return M;
}

// Remove duplicate words from the list
void supprimerdoublants(liste L) {
    liste p = L, q, r;

    while (p && p->suivant) {
        r = p;
        q = p->suivant;

        while (q) {
            if (strcmp(q->word, p->word) == 0) {
                r->suivant = q->suivant;
                free(q);
                q = r->suivant;
            } else {
                r = q;
                q = q->suivant;
            }
        }
        p = p->suivant;
    }
}

// Count the number of occurrences of a word
int count(liste head, char *search) {
    int count = 0;
    while (head != NULL) {
        if (strcmp(head->word, search) == 0) count++;
        head = head->suivant;
    }
    return count;
}

// Duplicate a list
liste duplicate(liste l) {
    liste dup = NULL, p, q;
    while (l != NULL) {
        p = creernoeud(l->word);
        if (dup == NULL) {
            dup = p;
            q = p;
        } else {
            q->suivant = p;
            q = p;
        }
        l = l->suivant;
    }
    return dup;
}

/////////////////////////////////////////// FREQUENCY LIST ///////////////////////////////////////////

// Swap two nodes in frequency list
void permuter(listefreq L1, listefreq L2) {
    char *temp = L1->mot;
    L1->mot = L2->mot;
    L2->mot = temp;

    int tempOcc = L1->nbapp;
    L1->nbapp = L2->nbapp;
    L2->nbapp = tempOcc;
}

// Sort frequency list in ascending order
void selectionSortAscending(listefreq tete) {
    listefreq debut = tete, traverser, min;
    while (debut->suivants) {
        min = debut;
        traverser = debut->suivants;
        while (traverser) {
            if (min->nbapp > traverser->nbapp)
                min = traverser;
            traverser = traverser->suivants;
        }
        permuter(debut, min);
        debut = debut->suivants;
    }
}

// Sort frequency list in descending order
void selectionSortdescending(listefreq tete) {
    listefreq debut = tete, traverser, maximum;
    while (debut->suivants) {
        maximum = debut;
        traverser = debut->suivants;
        while (traverser) {
            if (maximum->nbapp < traverser->nbapp)
                maximum = traverser;
            traverser = traverser->suivants;
        }
        permuter(debut, maximum);
        debut = debut->suivants;
    }
}

// Create a node for frequency list
listefreq creernoeudlistefrequence(char *word, int nombreocc) {
    listefreq lf = (listefreq)malloc(sizeof(noeuds));
    if (!lf) {
        printf("error");
        exit(-1);
    }
    lf->mot = allouerChaine(max);
    strcpy(lf->mot, word);
    lf->nbapp = nombreocc;
    lf->suivants = NULL;
    return lf;
}

// Display frequency list
void afficherlistefrequence(listefreq list) {
    printf("\nLISTE:\n");
    while (list != NULL) {
        printf("\n  ------------------");
        printf("\n---> |  [%s,%d]  |\n", list->mot, list->nbapp);
        printf("   ------------------\n");
        list = list->suivants;
    }
}

/////////////////////////////////////////// CONTEXT FUNCTIONS ///////////////////////////////////////////

// Return list of context words (next word of each occurrence)
liste contexterMot(liste list, char *m) {
    liste contexte = NULL, p, parcours = list;
    int found = 0;

    while (parcours->suivant != NULL) {
        if (strcmp(parcours->word, m) == 0) {
            found = 1;
            p = creernoeud(parcours->suivant->word);
            p->suivant = contexte;
            contexte = p;
        }
        parcours = parcours->suivant;
    }

    if (!found) {
        printf("\nle mot n'existe pas dans la liste!!\n");
        exit(-1);
    }
    return contexte;
}

// Convert list of context words to frequency list
listefreq frequencesDe(liste ContexteAvcDouble) {
    listefreq listeOcc = NULL, temp;
    liste SnsDouble = duplicate(ContexteAvcDouble);
    supprimerdoublants(SnsDouble);

    while (SnsDouble != NULL) {
        int nbOccMot = count(ContexteAvcDouble, SnsDouble->word);
        temp = creernoeudlistefrequence(SnsDouble->word, nbOccMot);
        temp->suivants = listeOcc;
        listeOcc = temp;
        SnsDouble = SnsDouble->suivant;
    }
    return listeOcc;
}

/////////////////////////////////////////// DICTIONARY FUNCTIONS ///////////////////////////////////////////

// Display the dictionary
void affichagedictionnaire(dictionnaire Ldiction) {
    printf("\nle dictionnaire est =");
    while (Ldiction != NULL) {
        printf("\n_______________________\n");
        printf("LE MOT =\n%s\n", Ldiction->motDict);
        printf("SES CONTEXTES =\n");
        afficherlistefrequence(Ldiction->contextes);
        printf("_______________________\n");
        Ldiction = Ldiction->suivantDict;
    }
}

// Create a dictionary node
dictionnaire creerNouedDictionnaire(char *mot, listefreq contextesMot) {
    dictionnaire noeudDict = (dictionnaire)malloc(sizeof(dict));
    if (!noeudDict) {
        printf("error");
        exit(-1);
    }
    noeudDict->motDict = allouerChaine(max);
    strcpy(noeudDict->motDict, mot);
    noeudDict->contextes = contextesMot;
    noeudDict->suivantDict = NULL;
    return noeudDict;
}

// Create full dictionary from a list of words
dictionnaire creationdictionary(liste desmots) {
    dictionnaire dict = NULL, tmp;
    liste parcours = duplicate(desmots);
    supprimerdoublants(parcours);

    while (parcours->suivant != NULL) {
        liste ContexteAvcDouble = contexterMot(desmots, parcours->word);
        listefreq saListeContex = frequencesDe(ContexteAvcDouble);
        selectionSortdescending(saListeContex);
        tmp = creerNouedDictionnaire(parcours->word, saListeContex);
        tmp->suivantDict = dict;
        dict = tmp;
        parcours = parcours->suivant;
    }
    return dict;
}

// Return most frequent context of a word
char *maxcontexte(dictionnaire dict, char *m) {
    char *theword = allouerChaine(max);
    int found = 0;

    while (dict != NULL) {
        if (strcmp(dict->motDict, m) == 0) {
            found = 1;
            strcpy(theword, dict->contextes->mot);
        }
        dict = dict->suivantDict;
    }

    if (!found) {
        printf("\nle mot n'existe pas dans le dictionnaire!!\n");
        exit(-1);
    }
    return theword;
}

// Return frequency of a given context for a given word
int freqCont(dictionnaire dict, char *m, char *n) {
    int foundWord = 0, foundContext = 0, nombreocc = 0;

    while (dict != NULL) {
        if (strcmp(dict->motDict, m) == 0) {
            foundWord = 1;
            while (dict->contextes != NULL) {
                if (strcmp(dict->contextes->mot, n) == 0) {
                    foundContext = 1;
                    nombreocc = dict->contextes->nbapp;
                }
                dict->contextes = dict->contextes->suivants;
            }
        }
        dict = dict->suivantDict;
    }

    if (!foundWord) {
        printf("\nle mot n'existe pas dans le dictionnaire!!\n");
        exit(-1);
    }
    if (!foundContext) {
        printf("\nle mot n'existe pas dans les contextes!!\n");
        exit(-1);
    }
    return nombreocc;
}

/////////////////////////////////////////// RANDOM TEXT GENERATION ///////////////////////////////////////////

// Count number of nodes in a list
int nombremotliste(liste L) {
    int nbr = 0;
    while (L != NULL) {
        nbr++;
        L = L->suivant;
    }
    return nbr;
}

// Generate random number [0, n]
int generernbr(int n) {
    srand(time(0));
    return rand() % (n + 1);
}

// Select a random word from dictionary
char *aleatoirement(int k, dictionnaire d) {
    int i;
    char *aword = allouerChaine(max);
    for (i = 0; i < k; i++) {
        d = d->suivantDict;
    }
    strcpy(aword, d->motDict);
    return aword;
}

// Generate sequence of most frequent words
void genererTEXTE(dictionnaire d, int naff, char *aword) {
    printf("\nLA SEQUENCE DES MOTS:\n");
    for (int i = 0; i < naff; i++) {
        printf("-- %s\n", maxcontexte(d, aword));
        strcpy(aword, maxcontexte(d, aword));
    }
}
