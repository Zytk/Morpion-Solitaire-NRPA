#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Basic_Fct.h"
#include "NRPA.h"

int main(int argc, char** argv)
{
int i;
//
// fichier texte de sortie
//
FILE* fichier;
fichier = fopen("c:/users/MS/toto_recurs.txt","w");
//
// declaration des grilles de jeu
//
grille Node, Init, Max;
//
// declaration et init de la stratégie
//
poli strat;
for (i = 0; i < MAXGRI*MAXGRI*4; i++)
	strat.policy[i] = 0;
//
// source alea
//
srand(89765);
//
// niveau de jeu
//
int NIV;
NIV = init_jeu(&Init);
//
// grille initiale
//
memcpy(&Node, &Init, sizeof(grille));
rech_coup(&Node);
//
// boucle principale de jeu
//
Max.nbhc = 0;
while(Node.nbcoup > 0)
	{
	Max=NRPA(2,&Node,strat,fichier);
	fprintf(fichier, "fin recurs level=2 n=3\n");
	fclose(fichier);
	exit(66);
	NIV++;
	printf("%d %d %010d\n", NIV, Max.nbhc, sign_grille(&Max));
	Node=constr_jeu(&Max, &Init, NIV,fichier);
	rech_coup(&Node);
	fprintf(fichier,"Grille Max\n");
	disp_jeu(&Max, fichier);
	NRPA_disp_pol(strat, fichier);
	}
//
// sortie des resultats
//
disp_jeu(&Max, fichier);
NRPA_disp_pol(strat, fichier);
}

