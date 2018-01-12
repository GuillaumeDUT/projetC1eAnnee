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
  unite->suiv=NULL;

  return unite;
}

int placerSurPlateau(Unite *unite, Monde *monde, int posX,int posY, char couleur){
  if(monde->plateau[posX][posY] != NULL){
    return 0;
  }else{

    unite->posX = posX;
    unite->posY = posY;
    if(couleur == ROUGE){
      unite->suiv = monde->rouge;
      monde->rouge = unite;
    }
    if(couleur == BLEU){
      unite->suiv = monde->bleu;
      monde->bleu = unite;
    }
    monde->plateau[posX][posY] = unite;
    return 1;
  }
}

void afficherGrille(Monde * monde){
  printf("     ");
  for(int a=0;a<18;a++){
    if(a<10)
      printf("   %d ",a   );
    if(a>10)
      printf("  %d ",a   );
  }
  printf("\n     --------------------------------------------------------------------------------------\n");
  for(int i=0;i<LONG;i++){
    printf(" %-2d  ",i);
    for(int j=0;j<LARG;j++){
     if(monde->plateau[i][j]!= NULL){
        printf("| %c%c ",monde->plateau[i][j]->couleur,monde->plateau[i][j]->genre);
      }else{
        printf("|    ");
      }
    }
    printf("\n    ---------------------------------------------------------------------------------------\n");
  }
}



void afficherListe(UListe list){
  while (list != NULL){
		printf("UNITE :  genre %c couleur %c posX %d posY %d\n",list->genre,list->couleur,list->posX,list->posY);
		list = list->suiv;
	}
}


void deplacerUnite(Unite *unite, Monde *monde, int destX,int destY){
  if(monde->plateau[destX][destY]==NULL){
    monde->plateau[unite->posX][unite->posY] = NULL;
    unite->posX = destX;
    unite->posY = destY;
    monde->plateau[unite->posX][unite->posY] = unite;
  }else{
    printf("You kante, cette case est déjà marxisée\n");
  }
}


void enleverUnite(Unite *unite, Monde *monde){
  Unite * temp;

}
