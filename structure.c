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
int creerUnite(char genre, Unite * unite){
  Unite * temp;
  temp = malloc(sizeof(Unite));
  if(temp == NULL){
    printf("Erreur\n");
    exit(0);
  }
  unite->genre = genre;
  return 0;
}

int placerAuMonde(Unite *unite, Monde *monde, int posX,int posY, char couleur){
  unite->couleur = couleur;
  unite->posX = posX;
  unite->posY = posY;
  if(monde->plateau[posX][posY] != NULL){
    return 0;
  }else{
    monde->plateau[posX][posY] = unite;
    //UListe* unite = malloc(sizeof(UListe));
    return 1;
  }
}

void afficherGrille(){
  printf("---------------------------------------------------------------------\n");
  for(int i=0;i<LONG;i++){
    for(int j=0;j<LARG;j++){
      printf("|   ");
    }
    printf("\n---------------------------------------------------------------------\n");
  }
}











