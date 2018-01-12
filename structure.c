#include <stdio.h>
#include <stdlib.h>
#include "structure.h"


void initialiserMonde(Monde * monde){
  for(int i=0;i<LONG;i++){
    for(int j=0;j<LARG;j++){
      monde->plateau[i][j]=NULL;
    }
  }
  monde->rouge = NULL;
  monde->bleu = NULL;
  monde->tour = 0;
}
Unite * creerUnite(char genre,char couleurUnite){
  Unite * unite;
  unite = malloc(sizeof(Unite));
  if(unite == NULL){
    printf("L'allocation a planté\n");
    return 0;
  }
  unite->genre = genre;
  unite->couleur = couleurUnite;
  unite->posX=NULL;
  unite->posY=NULL;
  unite->suiv=NULL;

  return unite;
}
int placerSurPlateau(Unite *unite, Monde *monde, int posX,int posY, char couleur){
  unite->posX = posX;
  unite->posY = posY;

  if(monde->plateau[posX][posY] != NULL){
    return 0;
  }else{
    monde->plateau[posX][posY] = unite;

    if(couleur == ROUGE){
      unite->suiv = monde->rouge;
      monde->rouge = unite;
    }
    if(couleur == BLEU){
      unite->suiv = monde->bleu;
      monde->bleu = unite;
    }

    return 1;
  }
}

void afficherGrille(Monde * monde){
  printf("\n--------------------------------------------------------------------------------------\n");
  for(int i=0;i<LONG;i++){
    for(int j=0;j<LARG;j++){
     if(monde->plateau[i][j]!= NULL){
        printf("| %c%c ",monde->plateau[i][j]->couleur,monde->plateau[i][j]->genre);
      }else{
        printf("|    ");
      }
    }
    printf("\n--------------------------------------------------------------------------------------\n");
  }
}

void afficherListe(UListe list){
  while (list->suiv != NULL){
		printf("UNITE :  genre %c couleur %c posX %d posY %d\n",list->genre,list->couleur,list->posX,list->posY);
		list = list->suiv;
	}
}
