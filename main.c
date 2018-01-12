#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

int main(){
  Monde monde;
  Unite unite;
  Unite UListe;
  initialiserMonde(&monde);
  creerUnite(SERF,ROUGE,&unite,&UListe);
  //placerSurPlateau(&unite,&monde,2,2,ROUGE);
  //afficherGrille(&monde);
  return 0;
}
