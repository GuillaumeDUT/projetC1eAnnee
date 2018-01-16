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
  printf("X \\ Y");
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
    printf("\n     --------------------------------------------------------------------------------------\n");
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

int attaquer(Unite *unite, Monde * monde, int destX, int destY){
  if(monde->plateau[destX][destY]!= NULL){
    //printf("unite : genre %c couleur %c posX %d  posY %d\n",unite->genre,unite->couleur,unite->posX,unite->posY);
    //printf("unite : genre %c couleur %c posX %d  posY %d\n",monde->plateau[destX][destY]->genre,monde->plateau[destX][destY]->couleur,monde->plateau[destX][destY]->posX,monde->plateau[destX][destY]->posY);
    if(unite->genre == monde->plateau[destX][destY]->genre ){

      if(monde->plateau[destX][destY]->couleur == BLEU){
        enleverUniteDesListe(monde->bleu,monde,monde->plateau[destX][destY]->id);
      }else{
        enleverUniteDesListe(monde->rouge,monde,monde->plateau[destX][destY]->id);
      }
      return 1;
    }
    else{
      if(unite->genre == SERF && monde->plateau[destX][destY]->genre == GUERRIER){
        if(unite->couleur == BLEU){
          enleverUniteDesListe(monde->bleu,monde,unite->id);
        }else{
          enleverUniteDesListe(monde->rouge,monde,unite->id);
        }
        return 0;
      }else if(unite->genre == GUERRIER && monde->plateau[destX][destY]->genre == SERF){
        if(monde->plateau[destX][destY]->couleur == BLEU){
          enleverUniteDesListe(monde->bleu,monde,monde->plateau[destX][destY]->id);
        }else{
          enleverUniteDesListe(monde->rouge,monde,monde->plateau[destX][destY]->id);
        }
        return 1;
      }
    }
  }
  return 0;
}

int enleverUniteDesListe(UListe liste,Monde *monde,int id){

  Unite * tmp;
  Unite * previous;
  previous = liste;
  if(liste->id == id){
    monde->plateau[liste->posX][liste->posY] = NULL;
    liste = liste->suiv;
    free(previous);
    return 1;
  }
  tmp=previous->suiv;
  while(tmp != NULL){
    if(tmp->id == id){
      monde->plateau[tmp->posX][tmp->posY] = NULL;
      previous->suiv = tmp->suiv;
      free(tmp);
      return 1;
    }
    previous = tmp;
    tmp = tmp->suiv;
  }
  return 0;
}

int deplacerOuAttaquer(Unite *unite, Monde *monde, int destX, int destY){
  //check si les coodonnées sont bonnes
  if(destX<=11 && destX>=0 &&  destY>=0 && destY<=18){
    printf("Coordonnées valides \n");
    if( destX<=unite->posX+1 && destX>=unite->posX-1 && destY<=unite->posY+1 && destY>=unite->posY-1){
      printf("Yes c'est dans la range\n\n");
      if(monde->plateau[destX][destY] == NULL){
        printf("L'unitée %c%c en X : %d | Y : %d a été déplacée en X : %d | Y : %d",unite->couleur,unite->genre,unite->posX,unite->posY,destX,destY);
        deplacerUnite(unite,monde,destX,destY);
        return 1;
      }else{
        if(unite->couleur == monde->plateau[destX][destY]->couleur){
          printf("Vous ne pouvez attaquer une unité alliée !\n");
          return -3;
        }else{
          printf("On attaque l'unitée %c%c en X : %d | Y : %d\n",monde->plateau[destX][destY]->couleur,monde->plateau[destX][destY]->genre,destX,destY);
          Unite * temp;
          temp = monde->plateau[destX][destY];
          if(attaquer(unite,monde,destX,destY) == 1){

            printf("L'unité %c%c en X : %d | Y : %d a gagné son combat contre l'unité %c%c en X: %d | Y : %d.\n",unite->couleur,unite->genre,unite->posX,unite->posY,temp->couleur,temp->genre,destX,destY);
          }else{
              printf("L'unité %c%c en X : %d | Y : %d a perdu son combat contre l'unité %c%c en X: %d | Y : %d.\n",unite->couleur,unite->genre,unite->posX,unite->posY,monde->plateau[destX][destY]->couleur,monde->plateau[destX][destY]->genre,destX,destY);
          }

        }
      }
    }else{
      printf("La portée doit être comprise dans les 8 cases adjacentes à l'unité. \n");
      return -2;
    }
  }else{
    return -1;
  }
  //check si les coordonnées sont dans la range de 1 case autour de l'unité
  return 0;
}
