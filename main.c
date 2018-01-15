#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

int main(){
  Monde monde;
  initialiserMonde(&monde);

  // for(int j =4;j<7;j++){
  //   creerUnite(SERF,BLEU,&unite,&UListe);
  //   placerSurPlateau(&unite,&monde,j,j,BLEU);
  // }

  placerSurPlateau(creerUnite(SERF,ROUGE),&monde,1,1,ROUGE);
  placerSurPlateau(creerUnite(SERF,ROUGE),&monde,1,2,ROUGE);
  placerSurPlateau(creerUnite(GUERRIER,ROUGE),&monde,1,3,ROUGE);

  placerSurPlateau(creerUnite(SERF,BLEU),&monde,2,1,ROUGE);
  placerSurPlateau(creerUnite(SERF,BLEU),&monde,2,2,ROUGE);
  placerSurPlateau(creerUnite(GUERRIER,BLEU),&monde,2,3,ROUGE);

  // placerSurPlateau(creerUnite(SERF,ROUGE),&monde,2,2,ROUGE);
  // // }
  // placerSurPlateau(creerUnite(SERF,BLEU),&monde,3,2,BLEU);
  //creerUnite(SERF,ROUGE,&unite,&UListe);
  //placerSurPlateau(&unite,&monde,2,2,ROUGE);


  //deplacerUnite(monde.rouge,&monde,10,1);
  afficherListe(monde.rouge);
  afficherListe(monde.bleu);
  afficherGrille(&monde);

  printf("---------------------------------\nTest pour attaquer\n");
  //attaquer(monde.rouge,&monde,2,3);
  attaquer(monde.plateau[1][2],&monde,2,2);

    printf("\nFin Test pour attaquer\n--------------------------------\n");
  afficherListe(monde.rouge);
  afficherListe(monde.bleu);
  afficherGrille(&monde);

  return 0;
}
