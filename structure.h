/* dimension du monde en nombre de cases */
#define LONG 12
#define LARG 18

/* l'origine est en haut a gauche */
#define ROUGE 'R' //identifiant du premier joueur
#define BLEU 'B' //identifiant du deuxi`eme joueur

/* les genres d'unites */

#define SERF 's'
#define GUERRIER 'g'

typedef struct unite{
  int posX, posY;   /*pour stocker les coordonn ́ees de l'unit ́e*/
  char couleur;     /* ROUGE ou BLEU */
  char genre;       /* GUERRIER ou SERF */
  struct unite *suiv;   /* liste des unit ́es suivantes*/
} Unite;

typedef Unite* UListe;

typedef struct monde{
  Unite *plateau[LONG][LARG];
  int tour;   /* Numero du tour */
  UListe rouge, bleu; /*Listes des deux joueurs*/
} Monde;

/* fonction qui initialise le monde */
void initialiserMonde(Monde * monde);

/* fonction qui créé une unité*/
int creerUnite(char type, Unite * unite);

/* fonction qui créé une unité*/
int placerSurPlateau(Unite *unite, Monde *monde, int posX,int posY, char couleur);

/* fonction qui afficher un tableau */
void afficherGrille();