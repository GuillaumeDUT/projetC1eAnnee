#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

static int id = 1;

void initialiserMonde(Monde * monde){
  for(int i=0;i<LONG;i++){
    for(int j=0;j<LARG;j++){
      monde->plateau[i][j]=NULL;
    }
  }
  monde->rouge = NULL;
  monde->bleu = NULL;
  monde->tour = 1;
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
  printf(GRN "\n___________________________________________MONDE___________________________________________\n\n" RESET);
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
       printf("| ");
       if(monde->plateau[i][j]->couleur == ROUGE){
         printf(RED "%c%c " RESET,monde->plateau[i][j]->couleur,monde->plateau[i][j]->genre);
       }else{
         printf(BLU "%c%c " RESET,monde->plateau[i][j]->couleur,monde->plateau[i][j]->genre);
        }
      }else{
        printf("|    ");
      }
    }
    printf("\n     --------------------------------------------------------------------------------------\n");
  }
    printf(GRN "___________________________________________________________________________________________\n\n" RESET);
}



void afficherListe(UListe list){
  if(list == NULL){
    printf("Il n'y a aucun élément dans la liste\n");
    return;
  }
  char couleurListe = list->couleur;
  printf("-------------------------------\nAffichage de la liste %c\n",couleurListe);
  while (list != NULL){
    if(list->couleur == ROUGE){
      printf(RED "UNITE :  genre %c | couleur %c | posX %d | posY %d | id :%d\n" RESET,list->genre,list->couleur,list->posX,list->posY,list->id);
    }else{
      printf(BLU "UNITE :  genre %c | couleur %c | posX %d | posY %d | id :%d\n" RESET,list->genre,list->couleur,list->posX,list->posY,list->id);
    }
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
    printf("C'est déjà utilisé oups.\n");
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
    if(liste->couleur == ROUGE){
      monde->rouge = liste->suiv;
    }else{
      monde->bleu = liste->suiv;
    }
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
    //printf("Coordonnées valides \n");
    if( destX<=unite->posX+1 && destX>=unite->posX-1 && destY<=unite->posY+1 && destY>=unite->posY-1){
      //printf("Yes c'est dans la range\n\n");
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
            return 2;
          }else{
              printf("L'unité %c%c en X : %d | Y : %d a perdu son combat contre l'unité %c%c en X: %d | Y : %d.\n",unite->couleur,unite->genre,unite->posX,unite->posY,monde->plateau[destX][destY]->couleur,monde->plateau[destX][destY]->genre,destX,destY);
              return 3;
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

void gererDemiTour(char couleurJoueur, Monde *monde){
    printf("\n________________________________________TOUR DES %c_________________________________________\n\n",couleurJoueur);

    if(couleurJoueur == ROUGE){
      Unite * temp;
      temp = monde->rouge;
      while(temp != NULL){
        printf("C'est au tour de l'unité %c%c placée en X : %d | Y : %d  de jouer.\n\n",temp->couleur,temp->genre,temp->posX,temp->posY);
        afficherGrille(monde);
        gererChoixJoueur(temp,monde,monde->plateau[temp->posX][temp->posY]);

        temp = temp->suiv;
      }
      if(monde->rouge == NULL){

        printf("Fin de votre tour ! L'adversaire va jouer.\n");
      }
      //monde->rouge = debut;
      printf("Debug Debut de liste bizarre \n");
      afficherListe(monde->rouge);
      afficherListe(monde->bleu);
    }else{
      Unite * temp;
      temp = monde->bleu;
      while(temp != NULL){
        printf("C'est au tour de l'unité %c%c placée en X : %d | Y : %d  de jouer.\n\n",temp->couleur,temp->genre,temp->posX,temp->posY);
        afficherGrille(monde);
        gererChoixJoueur(temp,monde,monde->plateau[temp->posX][temp->posY]);
        temp = temp->suiv;
      }

      if(monde->bleu == NULL){
        printf("Fin de votre tour ! L'adversaire va jouer.\n");
      }

      //monde->bleu = debut;
      printf("Debug Debut de liste bizarre \n");
      afficherListe(monde->bleu);
      afficherListe(monde->rouge);
    }
}

void gererChoixJoueur(UListe liste,Monde *monde,Unite *unite){
    int choix,destX,destY;
    printf("Que voulez vous faire ?\n 1. Déplacer l'unité\n 2. Attaquer une unité\n 3. Ne rien faire\n 4. Déclarer forfait\n");
    scanf("%d",&choix);
    switch(choix){
      case 1:
        printf("\nVous avez choisi de déplacer l'unité, veuillez entrer les coordonnées X et Y de la destination\n");
        scanf("%d",&destX);
        scanf("%d",&destY);
        printf("__________________________\n\n");
        deplacerOuAttaquer(unite,monde,destX,destY);
        break;
      case 2:
        printf("\nVous avez choisi d'attaquer une unité adverse, entre les coordonnées X et Y  de la cible \n");
        scanf("%d",&destX);
        scanf("%d",&destY);
        printf("__________________________\n\n");
        deplacerOuAttaquer(unite,monde,destX,destY);
        break;
      case 3:
        printf("\nVous ne faites rien ce tour ci.\n");
        break;
      case 4:
        if(liste->couleur == ROUGE){
          afficherFinJeu(ROUGE,monde);
        }else{
          afficherFinJeu(BLEU,monde);
        }
        break;
      default:
        printf("\nVous n'avez pas entré une bonne valeur.\nC'est au tour de l'unité suivante\n");
        while( getchar() != '\n' );
        break;
    }
    //afficherListe(liste);
}

void gererTour(Monde *monde){
  while(calculerLongeurChaine(monde->rouge) != 0 || calculerLongeurChaine(monde->bleu) != 0){
    printf("\n######################################## TOUR N° %d ########################################\n",monde->tour);
    // printf("Debut tour\n");
    // afficherListe(monde->bleu);
    // afficherListe(monde->rouge);

    gererDemiTour(ROUGE,monde);
    if(calculerLongeurChaine(monde->rouge) == 0){
      afficherFinJeu(BLEU,monde);
    }else if(calculerLongeurChaine(monde->bleu) == 0){
      afficherFinJeu(ROUGE,monde);
    }

    // printf("Entre deux tour\n");
    // afficherListe(monde->bleu);
    // afficherListe(monde->rouge);

    gererDemiTour(BLEU,monde);
    if(calculerLongeurChaine(monde->rouge) == 0){
      afficherFinJeu(BLEU,monde);
    }else if(calculerLongeurChaine(monde->bleu) == 0){
      afficherFinJeu(ROUGE,monde);
    }
    // printf("Fin tour\n");
    // afficherListe(monde->bleu);
    // afficherListe(monde->rouge);
    printf("\n######################################## FIN TOUR N° %d ########################################\n",monde->tour);
    monde->tour++;
  }
}

void afficherFinJeu(char couleur,Monde *monde){
  printf("\n\n\n LES %c ONT GAGNÉ ! \n",couleur);
  viderMonde(monde);
  int menuFin,triggerMenuFin;
  triggerMenuFin = 0;
  while(!triggerMenuFin){
    printf("Voulez vous : \n 1. Revenir au menu principal\n 2. Quitter le programme");
    scanf("%d",&menuFin);
    switch(menuFin){
      case 1:
        gererPartie(monde);
        break;
      case 2:
        exit(0);
        break;
      default:
        printf("Vous avez entré une mauvaise valeur\n");
        while( getchar() != '\n' );
        break;
    }
  }
}

void viderMonde(Monde *monde){
  viderListe(monde->rouge,monde);
  viderListe(monde->bleu,monde);
  initialiserMonde(monde);
}

void viderListe(UListe liste,Monde *monde){
  Unite * temp;
  while(liste != NULL){
    temp = liste;
    free(liste);
    liste = temp->suiv;
  }
}
int calculerLongeurChaine(UListe list){
  int n = 0;
  while(list!= NULL){
    n++;
    list = list->suiv;
  }
  return n;
}

void gererPartie(Monde * monde){
  initialiserMonde(monde);
  /* ROUGE */
  placerSurPlateau(creerUnite(SERF,ROUGE),monde,1,1,ROUGE);
  placerSurPlateau(creerUnite(SERF,ROUGE),monde,1,2,ROUGE);
  placerSurPlateau(creerUnite(GUERRIER,ROUGE),monde,1,3,ROUGE);
  /* BLEU */
  placerSurPlateau(creerUnite(SERF,BLEU),monde,2,1,BLEU);
  placerSurPlateau(creerUnite(SERF,BLEU),monde,2,2,BLEU);
  placerSurPlateau(creerUnite(GUERRIER,BLEU),monde,2,3,BLEU);
  int triggerJeu = 0;
  int repTrigger;


  while(!triggerJeu){
    printf(CYN"\n                                 ####################\n");
    printf(CYN"                                 #                  #\n");
    printf(CYN"                                 #    FIGHT CLUB    #\n");
    printf(CYN"                                 #                  #\n");
    printf(CYN"                                 ####################\n"RESET);
    printf("\nBonjour et bienvenue dans Fight Club.\n");
    printf(MAG "Vous voulez :\n 1. Lancer une partie\n 2. Afficher les règles\n 3. Quitter le programme \n" RESET);
    scanf("%d",&repTrigger);
    switch(repTrigger){
      case 1:
        gererTour(monde);
        triggerJeu=1;
        break;
      case 2:
        printf("Deux adversaires"RED" ROUGE"RESET" et "BLU"BLEU"RESET" s'affrontent sur un plateau de 12x18.\n");
        printf("Chaque adversaire possède deux unité de type "YEL"SERF"RESET" (s) et une unité de type "GRN"GUERRIER"RESET" (g)\n");
        printf("A chaque tour, le joueur correspondant peut déplacer ses unités mais seulement dans la zone adjacente à sa position actuelle.\n");
        printf("Il peut aussi décider d'attaquer une unité adverse.");
        printf("Les "GRN"GUERRIER"RESET" gagnent toujours contre les "YEL"SERF"RESET". \n");
        printf("Si les deux unités engagées dans un combat ont le même type, celle qui attaque gagne toujours.\n");
        printf("La partie se termine si un des joueur perd tout ses pions.\n");
        break;
      case 3:
        exit(0);
        break;
      default:
        printf("Vous ne pouvez pas entrer une valeur incorrecte.\n");
        while( getchar() != '\n' );
        break;
    }
  }
}
