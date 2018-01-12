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
int creerUnite(char genre,char couleurUnite, Unite * unite,Unite *UListe){
  Unite * temp;
  temp = malloc(sizeof(Unite));
  if(temp == NULL){
    printf("L'allocation a planté\n");
    return 0;
  }
  unite->genre = genre;
  unite->couleur = couleurUnite;
  temp->suiv = UListe;
  UListe = temp;
  return 0;
}
int placerSurPlateau(Unite *unite, Monde *monde, int posX,int posY, char couleur){
  UListe tmp;
  if(couleur == ROUGE)
    tmp = monde->rouge;
  else
    tmp = monde->bleu;

  unite->couleur = couleur;
  unite->posX = posX;
  unite->posY = posY;
  if(monde->plateau[posX][posY] != NULL){
    return 0;
  }else{
    monde->plateau[posX][posY] = unite;
    unite->suiv= tmp;
    tmp = unite;
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
