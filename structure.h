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
  int id;
} Unite;

typedef Unite * UListe;

typedef struct monde{
  Unite *plateau[LONG][LARG];
  int tour;   /* Numero du tour */
  UListe rouge, bleu; /*Listes des deux joueurs*/
} Monde;

/* fonction qui initialise le monde */
void initialiserMonde(Monde * monde);

/* fonction qui créé une unité*/
Unite * creerUnite(char genre,char couleurUnite);

/* fonction qui créé une unité*/
int placerSurPlateau(Unite *unite, Monde *monde, int posX,int posY, char couleur);

/* fonction qui afficher un tableau */
void afficherGrille(Monde * monde);

/* fonction afficher liste*/
void afficherListe(UListe  list);

/* Fonction deplacer pion */
void deplacerUnite(Unite *unite, Monde *monde, int destX,int destY);

/* attaquer une unite */
int attaquer(Unite *unite, Monde *monde, int destX, int destY);

/* enlever une unite */
int enleverUniteDesListe(UListe liste,Monde *monde,int id);

/* fonction qui regarde si on peut se déplacer et si on peut attaquer */
int deplacerOuAttaquer(Unite *unite, Monde *monde, int destX, int destY);

/* gérer les actions des pions d'un joueur */
void gererDemiTour(char joueur, Monde *monde);

/* gérer les entrées utilisateurs pendant le demi tour */
void gererChoixJoueur(UListe liste,Monde *monde,Unite *unite);

/* trigger la fonction demi tour pour les deux joueurs*/
void gererTour(Monde *monde);

/* vider le monde et le réinitialiser à 0 */
void viderMonde(Monde *monde);

/* retire tous les éléments d'une liste */
void viderListe(UListe liste,Monde *monde);
