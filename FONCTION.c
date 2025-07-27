#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#define max 256
#include "fonction.h"


///////////////////////////////////////////les fonction/////////////////////////////////////////////////////////////
//reponse1
//fonction pour allouer une chaine de caractère
char * allouerChaine(int n)
{
    char * s =(char*)malloc(n*sizeof(char ));
    if(s!=NULL) 
    return s;
    exit(-1);
}

//fonction qui donne la taille d un fichier donné 
long taille(FILE*f ){
   fseek (f, 0, SEEK_END);
   return ftell (f);
}

//fonction qui retourne une chaine d un fichier 
char*lire (FILE*f){
    long lg =taille(f);
    char*contenu=allouerChaine(lg+1);
    rewind(f);
    fread(contenu,1,lg,f);
    return contenu;
}

//fonction qui cree un noeud de la liste
liste creernoeud(char*mot){
    liste p=(liste)malloc(sizeof(noeud));
    if (!p)
    {
        printf("\n malloc de noeud retourne NULL!");
        exit(-1);
    }
   p->word=allouerChaine(max);
   strcpy(p->word,mot);
    p->suivant=NULL;
    return p;
}

//fonction qui affiche une liste
void afficherListe(liste L)
{

    printf("\n\nLa liste est: \n");
    while (L != NULL)
    {   
        printf("----> %s  " , L->word);

        L = L->suivant;
    }
}

//fonction qui cree une liste en LIFO
liste creeListeChaine(char *ch)
{
  liste M, p, q;
  char *m = allouerChaine(max);
  const char *separateurs = " ,.:;""\n";

  M = NULL;

  while(m != NULL)
    {
      m = strtok (ch, separateurs);
    

      while (m != NULL)
	{

	  p = creernoeud(m);
	  m = strtok (NULL, separateurs);

      if (M == NULL)
	{
	  M = p;
	  q = p;
	}
      else
	{
	  q->suivant = p;
	  q = p;
	}

	}//end of while

    }//end of for

  if (M != NULL)
    {
      q->suivant = NULL;
    }


  return M;
}

//void qui supprime tt les doublants dans la lite
void supprimerdoublants(liste L){
liste p,q,r;
p=NULL;

  p= L;

while(p->suivant!=NULL){
  r=p; //r est le precedent de q
  q=p->suivant;

while(q!=NULL){
  
  if(strcmp(q->word,p->word)==0){
    r->suivant=q->suivant;
    free(q);
    q=r->suivant;
  }else{
    r=q; 
    q=q->suivant;
  }

}

//si deux dernier identique p->suivant= NULL;
if(p->suivant!=NULL){
  p=p->suivant;
}}
}


//reponse 3

//une fonction qui retourne  loccurence d un mot donné
int count( liste head, char * search)  
{ 
    liste current = head; 
    int count = 0; 
    while (current != NULL) 
    {  
        if (strcmp(current->word,search) == 0) { 
           count++; 
        }
        current = current->suivant; 
    } 
    return count; 
} 

//fonction qui duplique une liste donné 
liste duplicate(liste l){
  liste dup,p,q;
  dup=NULL;
  while (l!=NULL){
    p=creernoeud(l->word);
    if (dup == NULL)
	{
	  dup = p;
	  q = p;
	}
      else
	{
	  q->suivant = p;
	  q = p;
	}

    l=l->suivant;
  }
 if (dup != NULL)
    {
      q->suivant = NULL;
    }

  return dup;
}

//void qui fais la permutation 
void permuter(listefreq L1,listefreq L2){
char* temp =L1->mot;
L1->mot=L2->mot;
L2->mot=temp;
int tempOcc=L1->nbapp;
L1->nbapp=L2->nbapp;
L2->nbapp=tempOcc;
}

//void qui fais l ordre croissant d une liste de type listefreq
void selectionSortAscending(listefreq tete)
 {
   listefreq debut=tete;
   listefreq traverser;
   listefreq min;
   while (debut->suivants){
     min=debut;
     traverser=debut->suivants;
     while(traverser){
       //find minimum
       if(  (min->nbapp) > (traverser->nbapp) ) {
         min=traverser;
       }
       traverser=traverser->suivants;
     }
     permuter(debut,min);
     debut=debut->suivants;

   }

 }  

//void qui fais l ordre decroissant d une liste de type listefreq
void selectionSortdescending(listefreq tete){
   listefreq debut=tete;
   listefreq traverser;
   listefreq maximum;
   while (debut->suivants){
     maximum=debut;
     traverser=debut->suivants;
     while(traverser){
       //find maximum
       if(  (maximum->nbapp) < (traverser->nbapp) ) {
         maximum=traverser;
       }
       traverser=traverser->suivants;
     }
     permuter(debut,maximum);
     debut=debut->suivants;

   }

 }

//fonction qui cree une liste de type listefreq
listefreq creernoeudlistefrequence(char*word,int nombreocc){
listefreq listefrequence=(listefreq)malloc(sizeof(noeuds));
if(!listefrequence){
  printf("error");
  exit(-1);
}
listefrequence->mot=allouerChaine(max);
strcpy(listefrequence->mot,word);
listefrequence->nbapp=nombreocc;
listefrequence->suivants=NULL;

return listefrequence;
}

//void qui affiche la liste de type listefreq
void afficherlistefrequence(listefreq list){
printf("\nLISTE:\n");
while(list != NULL){
  printf("\n  ------------------");    
  printf("\n---> |  [%s,%d]  |\n",list->mot,list->nbapp);
  printf("   ------------------\n"); 
  list=list->suivants;
}
}

//reponse4

//fonction qui cree une liste des contextes d'un mot donné sans leurs nb de freq
liste contexterMot(liste list, char* m){
  liste contexte =NULL, p,parcours;
 int vrf=0;
  parcours=list;
  while(parcours->suivant!= NULL){
  if(strcmp(parcours->word ,m)==0){
    vrf=1;
  p=creernoeud(parcours->suivant->word);
  p->suivant=contexte;
  contexte=p;
  }
parcours=parcours->suivant;
  }
  if(vrf==0){ printf("\nle mot n'existe pas dans la liste!!\n");
      exit(-1);}
return contexte;
  }

//fonction qui retourne la liste de type listefreq des contextes d un mot 
listefreq  frequencesDe(liste ContexteAvcDouble){
    listefreq listeOcc,temp;
    liste SnsDouble = duplicate(ContexteAvcDouble);
    supprimerdoublants(SnsDouble);
    int nbOccMot;
    listeOcc=NULL;
    liste parcours;
    parcours=SnsDouble;
    while (parcours!=NULL){
      nbOccMot=count(ContexteAvcDouble,parcours->word);
      temp=creernoeudlistefrequence(parcours->word,nbOccMot);
     temp->suivants=listeOcc;
     listeOcc=temp;
     parcours=parcours->suivant;
    } 
    return listeOcc;
  }

//reponse5

//void qui affiche le dictionnaire
void affichagedictionnaire(dictionnaire Ldiction)
{
  printf("\nle dictionnaire est =");
  while(Ldiction != NULL){
    printf("\n");
    printf("_______________________\n");
    printf("\nLE MOT =\n%s\n",Ldiction->motDict);
    printf("\n");
    printf("SES CONTEXTES =\n");
    afficherlistefrequence(Ldiction->contextes);
    printf("_______________________\n");
    Ldiction=Ldiction->suivantDict;
  }
}

//fonction pour creer un noeud dictionaire
dictionnaire creerNouedDictionnaire(char* mot, listefreq contextesMot){
//dictionnaire noeudDict=(dictionnaire)malloc(sizeof(dict));
dictionnaire noeudDict=(dictionnaire)malloc(sizeof(dict));
if(!noeudDict){
  printf("error");
  exit(-1);
}
noeudDict->motDict=allouerChaine(max);
strcpy(noeudDict->motDict,mot);
noeudDict->contextes=contextesMot;
noeudDict->suivantDict=NULL;
return noeudDict;
}

// fonction pour creer le dictionaire
dictionnaire creationdictionary(liste desmots){
dictionnaire dict, tmp;
liste parcours ;
//creer une liste snsDouble copie de la liste mais sans les doublons
liste snsDouble =duplicate(desmots);
supprimerdoublants(snsDouble);
//initialiser dict a NULL
dict=NULL;
parcours=snsDouble;
  while(parcours->suivant!=NULL){
  //calcul du liste freq du mot snsDouble->word
  liste ContexteAvcDouble=contexterMot(desmots,parcours->word);
  listefreq  saListeContex=frequencesDe(ContexteAvcDouble);
  selectionSortdescending(saListeContex);//trie decroissant des freq de contextes
  //creation du noeud
  tmp=creerNouedDictionnaire(parcours->word,saListeContex);
  tmp->suivantDict=dict;
  dict=tmp;
  //avancer
 parcours=parcours->suivant;
  }
return dict;
   }

//REPONSE6
//fonction qui afficher le contexte le plus frequent s'il existe
char*maxcontexte(dictionnaire dict,char*m){
char*theword=allouerChaine(max);
int vrf=0;
dictionnaire parcours =dict;

while(parcours != NULL){
      if(strcmp(parcours->motDict,m)==0){ 
      vrf=1;  
      strcpy(theword,parcours->contextes->mot); 
             }      
      parcours=parcours->suivantDict;
}
if (vrf==0){
      printf("\nle mot n'existe pas dans le dictionnaire!!\n");
      exit(-1);
      } 
return theword;      
}

//REPONSE7
//fonction qui affiche le nombre d occurence d un contexte donné d un mot donné
int freqCont(dictionnaire dict ,char*m , char*n){
int nombreocc;
int existeDansDic=0;
int existeDansContex=0;
while(dict!=NULL){
      if(strcmp(dict->motDict,m)==0){
          existeDansDic=1;
            while(dict->contextes!=NULL){
                  if(strcmp(dict->contextes->mot,n)==0){
                        existeDansContex=1;
                        nombreocc=dict->contextes->nbapp;
                  }
                  dict->contextes=dict->contextes->suivants;
            }
      }
      dict=dict->suivantDict;
}
if (existeDansDic==0){
      printf("\nle mot n'existe pas dans le dictionnaire!!\n");
      exit(-1);
      } 
if (existeDansContex==0){
      printf("\nle mot n'existe pas dans les contextes!!\n");
      exit(-1);
      } 

return nombreocc;
}

//reponse8
//fonction qui retourne le nombre des mots dans une liste sans doublants 
int nombremotliste(liste L){
      int nbr=0;
      while(L != NULL){
            nbr++;
            L=L->suivant;
      }
      return nbr;
}

//fonction qui genere un numero entre 1 et nombre de mots d une liste 
int generernbr(int n){    
      srand(time(0));
      return (rand()%(n+1));
}

//fonction qui genere un mot aleatoirement 
char*aleatoirement(int k,dictionnaire d){
      int i;
      char*aword=allouerChaine(strlen(aword));
      for(i=0;i<k;i++){
            d=d->suivantDict;
      }
      strcpy(aword,d->motDict);
      return aword;
}

//fonction qui genere une sequence de mots 
//reponse8
void genererTEXTE(dictionnaire d,int naff,char*aword){
      int i;
      printf("\nLA SEQUENCE DES MOTS:\n");
      for(i=0;i<naff;i++){
            printf("-- %s\n",maxcontexte(d,aword));
            strcpy(aword,maxcontexte(d,aword));
      }
}

