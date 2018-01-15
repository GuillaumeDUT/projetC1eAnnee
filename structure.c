#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
static int id = 1;

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
  unite->id = id;
  id++;
  return unite;
}

int placerSurPlateau(Unite *unite, Monde *monde, int posX,int posY, char couleur){
  if(monde->plateau[posX][posY] != NULL){
    return 0;
  }else{

    unite->posX = posX;
    unite->posY = posY;
    if(unite->couleur == ROUGE){
      unite->suiv = monde->rouge;
      monde->rouge = unite;
    }
    if(unite->couleur == BLEU){
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
  char couleurListe = list->couleur;
  printf("-------------------------------\nAffichage de la liste %c\n",couleurListe);
  while (list != NULL){
		printf("UNITE :  genre %c | couleur %c | posX %d | posY %d | id :%d\n",list->genre,list->couleur,list->posX,list->posY,list->id);
		list = list->suiv;
	}
    printf("Fin de la liste %c\n-------------------------------\n",couleurListe);
}


void deplacerUnite(Unite *unite, Monde *monde, int destX,int destY){
  if(monde->plateau[destX][destY]==NULL){
    monde->plateau[unite->posX][unite->posY] = NULL;
    unite->posX = destX;
    unite->posY = destY;
    monde->plateau[unite->posX][unite->posY] = unite;

  }else{
    printf("Why u keep doing it ? \n");
  }
}

void enleverUnite(Unite *unite, Monde *monde){

  //printf("couleur d'unite %c\n",unite->couleur);
  monde->plateau[unite->posX][unite->posY] = NULL;
  //printf("pos d'unite %d\n",unite->posX);
}

int attaquer(Unite *unite, Monde * monde, int destX, int destY){
  if(monde->plateau[destX][destY]!= NULL){
    //printf("unite : genre %c couleur %c posX %d  posY %d\n",unite->genre,unite->couleur,unite->posX,unite->posY);
    //printf("unite : genre %c couleur %c posX %d  posY %d\n",monde->plateau[destX][destY]->genre,monde->plateau[destX][destY]->couleur,monde->plateau[destX][destY]->posX,monde->plateau[destX][destY]->posY);

    if(unite->genre == monde->plateau[destX][destY]->genre ){



      if(monde->plateau[destX][destY]->couleur == BLEU){
        enleverUniteDesListe(monde->bleu,monde->plateau[destX][destY]->id);
      }else{
        enleverUniteDesListe(monde->rouge,monde->plateau[destX][destY]->id);
      }
      // if(unite->couleur == BLEU){
      //   enleverUniteDesListe(monde->bleu,unite);
      // }else{
      //   enleverUniteDesListe(monde->rouge,unite);
      // }

      enleverUnite(monde->plateau[destX][destY],monde);
      enleverUnite(unite,monde);
      //free(monde->plateau[destX][destY])
      return 0;
    }
    // else{
    //   if(unite->genre == SERF && monde->plateau[destX][destY]->genre == GUERRIER){
    //     enleverUnite(monde->plateau[unite->posX][unite->posY],monde);
    //     free(unite);
    //     return 0;
    //   }else if(unite->genre == GUERRIER && monde->plateau[destX][destY]->genre == SERF){
    //
    //     // if(monde->plateau[destX][destY]->couleur == BLEU){
    //     //   enleverUniteDesListe(monde->bleu,monde->plateau[destX][destY]);
    //     // }
    //     enleverUnite(monde->plateau[destX][destY],monde);
    //     //free(monde->plateau[destX][destY]);
    //     return 1;
    //   }
    // }
  }
  return 0;
}

void enleverUniteDesListe(UListe liste,int id){

  Unite * debut;
  debut = liste;
  Unite * precedent;
  while (liste != NULL){
    precedent = liste;

    if(id == liste->id && id == precedent->id){

      printf("id %d\n",liste->id);
      liste->suiv = liste->suiv->suiv;
    }

    printf("id %d\n",liste->id);
    if(liste->suiv == NULL){
      printf("dernier id");
    }
    //printf("unite : genre %c couleur %c posX %d  posY %d\n",liste->genre,liste->couleur,liste->posX,liste->posY);
    // if(liste->posX == unite->posX && liste->posY == unite->posY && liste->couleur == unite->couleur && liste->genre == unite->genre){
    //   temp = liste;
    //   liste = liste->suiv;
    //   free(temp);
    // }else if(liste->suiv->posX == unite->posX && liste->suiv->posY == unite->posY && liste->suiv->couleur == unite->couleur && liste->suiv->genre == unite->genre){
    //   temp = liste->suiv;
    //   liste->suiv = liste->suiv->suiv;
    //   free(temp);
    // }else{
  	// 	liste = liste->suiv;
    // }
    liste = liste->suiv;
	}
}
