#include <stdio.h>
#include <stdlib.h>

#include "structure.h"


int main(){
  Monde monde;
  initialiserMonde(&monde);


  placerSurPlateau(creerUnite(SERF,ROUGE),&monde,1,1,ROUGE);
  placerSurPlateau(creerUnite(SERF,ROUGE),&monde,1,2,ROUGE);
  placerSurPlateau(creerUnite(GUERRIER,ROUGE),&monde,1,3,ROUGE);

  placerSurPlateau(creerUnite(SERF,BLEU),&monde,2,1,BLEU);
  placerSurPlateau(creerUnite(SERF,BLEU),&monde,2,2,BLEU);
  placerSurPlateau(creerUnite(GUERRIER,BLEU),&monde,2,3,BLEU);

  //deplacerUnite(monde.rouge,&monde,10,1);
  //afficherListe(monde.rouge);
  //afficherListe(monde.bleu);
  //afficherGrille(&monde);

  //printf("---------------------------------\nTest pour deplacerOuAttaquer\n");
  //attaquer(monde.rouge,&monde,2,3);
  //attaquer(monde.plateau[1][2],&monde,2,3);
  //deplacerOuAttaquer(monde.plateau[1][2],&monde,2,1);
  //printf("\nFin Test pour deplacerOuAttaquer\n--------------------------------\n");
  // afficherListe(monde.rouge);
// afficherListe(monde.bleu); 
  //afficherGrille(&monde);
  //gererDemiTour(BLEU,&monde);
  //gererTour(&monde);
  afficherGrille(&monde);
  afficherListe(monde.rouge);
  afficherListe(monde.bleu);
  viderMonde(&monde);

  afficherGrille(&monde);
  afficherListe(monde.rouge);
  afficherListe(monde.bleu);
  return 0;
}
