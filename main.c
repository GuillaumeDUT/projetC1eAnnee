#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

int main(){
  //printf("nique sa mere le terminal OUPS\n");
  Monde monde;
  Unite unite;
  initialiserMonde(&monde);
  
  creerUnite(ROUGE,&unite);
  
  afficherGrille(&monde);
  return 0;
}