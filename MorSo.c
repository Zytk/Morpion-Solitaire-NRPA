﻿#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Basic_Fct.h"
#include "NRPA.h"

int main(int argc, char** argv)

{
	
//
// fichier texte de sortie
//
FILE* fichier;
fichier = fopen("c:/users/MS/toto_iter.txt","w");
//
// declaration des grilles de jeu
//
grille *Node, *Init, *Max;
Node=malloc(sizeof(grille));
Init = malloc(sizeof(grille));
Max = malloc(sizeof(grille));
//
// source alea
//
srand(89765);
//
// niveau de jeu
//
int NIV;
NIV = init_jeu(Init);
//
// grille initiale
//
memcpy(Node, Init, sizeof(grille));
rech_coup(Node);
//
// boucle principale de jeu
//
Max->nbhc = 0;
while(Node->nbcoup > 0)
	{
	NRPA_ITE(Max, 3, Node, fichier);
	NIV++;
	printf("%d %d %010d\n",  NIV, Max->nbhc, sign_grille(Max));
	constr_jeu(Node, Max, Init, NIV,fichier);
	rech_coup(Node);
	fprintf(fichier,"Grille Max\n");
	disp_jeu(Max, fichier);
	}
//
// sortie des resultats
//
disp_jeu(Max, fichier);
}
