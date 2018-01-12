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
  for(int i =0;i<4;i++){
    placerSurPlateau(creerUnite(SERF,ROUGE),&monde,i,i,ROUGE);
  }
  for(int i =4;i<7;i++){
    placerSurPlateau(creerUnite(SERF,BLEU),&monde,i,i,BLEU);
  }
  // placerSurPlateau(creerUnite(SERF,ROUGE),&monde,2,2,ROUGE);
  // // }
  // placerSurPlateau(creerUnite(SERF,BLEU),&monde,3,2,BLEU);
  //creerUnite(SERF,ROUGE,&unite,&UListe);
  //placerSurPlateau(&unite,&monde,2,2,ROUGE);


  //deplacerUnite(monde.rouge,&monde,1,1);

  afficherGrille(&monde);

  afficherListe(monde.rouge);
  afficherListe(monde.bleu);
  return 0;
}
