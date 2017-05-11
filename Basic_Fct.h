#define MAXGRI 50
#define MAXPIL 7000
#define MAXLAR 75
#define MAXCOU 200
// structure policy
typedef struct
{
double policy[MAXGRI*MAXGRI * 4];
} poli;
// structure grille
typedef struct
{
//
// E: Value of a cell 
// F: Valeur d'une cellule
 
//                 |     /                           \        |
//       .    +    +    +    +-   +    +    +   -+    +      -+-
//                                 \   |   /                  |
//       0	  1    2    4    8    16   32  64  128   256  2+8+32+128
//		                                                    =170    
	int gri[MAXGRI][MAXGRI];
// E:list of legal moves
// F:liste des coups legaux
	int nbcoup;
	int coup[MAXLAR];
// E: code of move (used in NRPA)
// F: code du mouvement (NRPA)
	int code[MAXLAR];
// E: number of the dominated move
// F: coup dominant associé
	int dominateur[MAXLAR];
// E: priority of the move
// F: Priorité du coup
	int priorite[MAXLAR];
// E: number of moves in the historic
// F: nombre de mouvements dans l'historique
	int nbhc;
// E: List of all moves (historic)
// F: Historique des mouvements
	int hc[MAXCOU];
} grille;

// E: initialize the game grid
// F: init grille de jeu	
int init_jeu(grille *a);

// E: Display grid
// F: Affichage du jeu
void disp_jeu(grille *a, FILE* fichier);

// E: conversion of pack move in X, Y, D, K 
// F: conversion du mouvement en coordonnées X, Y, D, K
int cpX(int a);
int cpY(int a);
int cpD(int a);
int cpK(int a);

// E: Coordinate conversion X,Y,D,K => packed
// F: Conversion coordonnées X, Y, D, K => compacte
int cpXYDKP(int x, int y, int d, int k, int p);

// E: List of legal moves (not optimized version)
// F: recherche des coups legaux (version non optimisee)
void rech_coup(grille *a);

// E: List of legal moves (optimized version) need previous grid, previous list of moves and last played move 
// F: Recherche des coups legaux optimisée. nécessite la grille précedente, liste des coups précédente et dernier coup joué
void rech_coup_opti(grille *a, grille *b, int coup_joue);

// E: play and search legal mode
// F: joue et recherche optimise
void joue_rech(grille *a, int coup_joue);

// E: update dominateur fied in the grid structure 
// F: maj champ dominateur dans la structure grille
void maj_dominateur(grille *a);

// E : play a move
// F : joue le coup coup_joue sur la grille 
void joue_coup(grille *a, grille *b, int coup_joue);

// E : Grid signature
// F : Signature grille
int sign_grille(grille *a);

// E : Construction of a grid with init grid, historic and number of moves
// F : Reconstruit une grille a partir d'une grille initiale, d'un historique et du nombre de coup à jouer
void constr_jeu(grille *res, grille *MaxJ, grille *Init, int NIV, FILE *fichier);
