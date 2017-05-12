#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Basic_Fct.h"
#include "NRPA.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int init_jeu(grille *a)
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// E:
// Setup a new game on the grid(cross of Malta)
// Calculate new coordinates in order to center the game on the grid
// Return the level of the grid (=0 if only a cross of Malta)
// F:
// Initialise le tableau de jeu (croix de malte)
// Centre le jeu en fonction de MAXGRI (dimension maxi de la grille de jeu)
// Retourne le niveau 
//
{
	int i, j, delta;
//
// E: init of game historic
// F: mise à zero historique des coups
//
a->nbhc = 0;
//
// E: zero for all cells
// F:mise à zero de toutes les cases
//
for (i = 0; i<MAXGRI; i++)
	for (j = 0; j<MAXGRI; j++)
		a->gri[i][j] = 0;
//
// E: cross of Malta
// F: croix de malte
//
a->gri[31][34] = 1;
a->gri[31][35] = 1;
a->gri[31][36] = 1;
a->gri[31][37] = 1;
a->gri[32][34] = 1;
a->gri[32][37] = 1;
a->gri[33][34] = 1;
a->gri[33][37] = 1;

a->gri[34][34] = 1;
a->gri[34][37] = 1;

a->gri[34][31] = 1;
a->gri[34][32] = 1;
a->gri[34][33] = 1;
a->gri[34][38] = 1;
a->gri[34][39] = 1;
a->gri[34][40] = 1;

a->gri[35][31] = 1;
a->gri[35][40] = 1;
a->gri[36][31] = 1;
a->gri[36][40] = 1;
a->gri[37][31] = 1;
a->gri[37][32] = 1;
a->gri[37][33] = 1;
a->gri[37][34] = 1;
a->gri[37][37] = 1;
a->gri[37][38] = 1;
a->gri[37][39] = 1;
a->gri[37][40] = 1;
a->gri[38][34] = 1;
a->gri[38][37] = 1;
a->gri[39][34] = 1;
a->gri[39][37] = 1;
a->gri[40][34] = 1;
a->gri[40][35] = 1;
a->gri[40][36] = 1;
a->gri[40][37] = 1;
//
// E: Centering the cross
// F: Recentrage de la croix
//
delta = (MAXGRI - 30) / 2;
for (i = 0; i<MAXGRI; i++)
	for (j = 0; j<MAXGRI; j++)
		if ((i>delta) && (j>delta))
			{
			a->gri[i - delta][j - delta] = a->gri[i][j];
			a->gri[i][j] = 0;
			}
//
// E: return game level
// F: retour niveau de jeu
//
return(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void disp_jeu(grille *a, FILE* fichier)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// E: display the game and main parameters (game, historic, legal moves) on the text file in output
// F: affiche la grille de jeu et les parametres principaux (jeu, historique, coups légaux) en sortie texte sur fichier en sortie
//
{
int i, ii, jj, j, tot, minGRx, maxGRx, minGRy, maxGRy;
char lig1[5 * MAXGRI + 20], lig2[5 * MAXGRI + 20], lig3[5 * MAXGRI + 20], lig4[5 * MAXGRI + 20], lig5[5 * MAXGRI + 20], vlf[10];
//
// E: centering de picture
// F: recentrage du dessin
//
tot = 0;
minGRx = MAXGRI;
maxGRx = 0;
minGRy = MAXGRI;
maxGRy = 0;
for (i = 1; i<MAXGRI; i++)
	for (j = 1; j<MAXGRI; j++)
		if ((a->gri[i][j] != 0) && (a->gri[i][j] != 512))
			{
			tot = tot + 1;
			if (i>maxGRx)maxGRx = i;
			if (i<minGRx)minGRx = i;
			if (j>maxGRy)maxGRy = j;
			if (j<minGRy)minGRy = j;
			}
fprintf(fichier, "Grille Score total =%d\n", tot);
fprintf(fichier, "xMin=%d xMax=%d yMin=%d yMax=%d\n", minGRx, maxGRx, minGRy, maxGRy);
//
// E: historic
// F: sortie de l'historique des coups 
//
fprintf(fichier, "Historique des coups\n");
for (i = 0; i<a->nbhc; i++)
	fprintf(fichier, "coup %02d %d x=%d y=%d d=%d k=%d \n", i + 1, a->hc[i], cpX(a->hc[i]), cpY(a->hc[i]), cpD(a->hc[i]), cpK(a->hc[i]) );
//
// E: legal moves
// F: coups legaux
//
fprintf(fichier, "Liste des coups possibles a partir de cette position\n");
for (i = 0; i<a->nbcoup; i++)
	fprintf(fichier, "coup %02d %d x=%d y=%d d=%d k=%d d=%03d p=%d c=%d\n", i, a->coup[i], cpX(a->coup[i]), cpY(a->coup[i]), cpD(a->coup[i]), cpK(a->coup[i]), a->dominateur[i], a->priorite[i],a->code[i]);
//
// E: display of the grid
// F: affichage de la grille
//
for (jj = MAXGRI - maxGRy - 1; jj <= MAXGRI - minGRy - 1; jj++)
	{
	j = MAXGRI - jj - 1;
	strcpy(lig1, "    | ");
	strcpy(lig2, "    | ");
	sprintf(vlf, "%03d | ", j);
	strcpy(lig3, vlf);
	strcpy(lig4, "    | ");
	strcpy(lig5, "    | ");
	for (i = minGRx; i <= maxGRx; i++)
		{
		if ((a->gri[i][j] & 256) == 256)
			{
			strcat(lig1, "\\ ");
			strcat(lig2, " \\");
			}
		else
			{
			strcat(lig1, "  ");
			strcat(lig2, "  ");
			}
		if ((a->gri[i][j] & 2) == 2)
			{
			strcat(lig1, "|");
			strcat(lig2, "|");
			}
		else
			{
			strcat(lig1, " ");
			strcat(lig2, " ");
			}

		if ((a->gri[i][j] & 4) == 4)
			{
			strcat(lig1, " /");
			strcat(lig2, "/ ");
			}
		else
			{
			strcat(lig1, "  ");
			strcat(lig2, "  ");
			}

		if ((a->gri[i][j] & 128) == 128)
			strcat(lig3, "-");
		else
			strcat(lig3, " ");

		if (((a->gri[i][j]) % 2) == 0)
			if (a->gri[i][j]>0)
				strcpy(vlf, " ? ");
			else
				strcpy(vlf, "   ");
		else
			{
			strcpy(vlf, "xxx");
			for (ii = 0; ii<a->nbhc; ii++)
				if ((i == cpX(a->hc[ii])) && (j == cpY(a->hc[ii])))
					sprintf(vlf, "%03d", ii + 1);
			if (strcmp(vlf, "xxx") == 0)
				strcpy(vlf, " + ");
			}
		strcat(lig3, vlf);

		if ((a->gri[i][j] & 8) == 8)
			strcat(lig3, "-");
		else
			strcat(lig3, " ");

		if ((a->gri[i][j] & 64) == 64)
			{
			strcat(lig4, " /");
			strcat(lig5, "/ ");
			}
		else
			{
			strcat(lig4, "  ");
			strcat(lig5, "  ");
			}

		if ((a->gri[i][j] & 32) == 32)
			{
			strcat(lig4, "|");
			strcat(lig5, "|");
			}
		else
			{
			strcat(lig4, " ");
			strcat(lig5, " ");
			}

		if ((a->gri[i][j] & 16) == 16)
			{
			strcat(lig4, "\\ ");
			strcat(lig5, " \\");
			}
		else
			{
			strcat(lig4, "  ");
			strcat(lig5, "  ");
			}
		}
	fprintf(fichier, "%s\n", lig1);
	fprintf(fichier, "%s\n", lig2);
	fprintf(fichier, "%s\n", lig3);
	fprintf(fichier, "%s\n", lig4);
	fprintf(fichier, "%s\n", lig5);
	}
strcpy(lig1, "----+-");
for (i = minGRx; i <= maxGRx; i++)
	{
	sprintf(vlf, "-%03d-", i);
	strcat(lig1, vlf);
	}
fprintf(fichier, "%s\n", lig1);
}
///////////////////////////////////////////
int cpX(int a)
///////////////////////////////////////////
//
// E : unpack X coordinate of a move
// F : Etraction coordonnees X du coup 
//
{
return (a / 10000);
}

///////////////////////////////////////////
int cpY(int a)
///////////////////////////////////////////
//
// E: unpack Y coordinate of a move
// F: extraction coordonnees Y du coup 
//
{
return ((a % 10000) / 100);
}

///////////////////////////////////////////
int cpD(int a)
///////////////////////////////////////////
//
// E: unpack D coordinate of a move
// F: extraction coordonnees D du coup 
//
{
return ((a % 100) / 10);
}

///////////////////////////////////////////
int cpK(int a)
///////////////////////////////////////////
//
// E : unpack K coordinate of a move
// F: extraction coordonnees K du coup 
//
{
return (a % 10);
}

///////////////////////////////////////////////////
int cpXYDK(int x, int y, int d, int k)
///////////////////////////////////////////////////
//
// E : concatenate x,y,d,k in a packed move
// F : concatenation x,y,d,k
//
{
return(10000 * x + 100 * y + 10 * d + k);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rech_coup(grille *a)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// E: Search legal moves on a grid (parameter 1) and update de structure grid (nbcoup and coup[])
// F: Recherche les coups possibles sur la grille (p1) et renseigne les données dans la structure grille nbcoup et coup[]
//
{
int i, j, k, ii, jj, kk, dir, tot;
int tab[15], coupX, coupY, coupD, coupK;
//
// E: direction table
// F: table des directions
//
int dirX[4] = { 0, 1, 1, 1 };
int dirY[4] = { 1, 1, 0, -1 };
int dirD[4] = { 2, 4, 8, 16 };
int dirO[4] = { 32, 64, 128, 256 };
int dirDO[4] = { 34, 68, 136, 272 };
//
// E: number of legal = 0
// F: remise a zero du nb de coups trouves
//
a->nbcoup = 0;
//
// E: for each cell of the grid
// F: parcours de toutes les cases de la grille gri[ptr][MAXGRxMAXGR]
//
for (i = 1; i<MAXGRI-1; i++)
	{
	for (j = 1; j<MAXGRI-1; j++)
		{
//
// E: if the current cell is empty and something in the 8 cells
// F: si la case pointée est vide et il y a quelque chose dans une des 8 cases autour
//
		if (a->gri[i][j] == 0)
			{
			if ((a->gri[i - 1][j - 1] + a->gri[i - 1][j] + a->gri[i - 1][j + 1] + a->gri[i][j - 1] + a->gri[i][j + 1] + a->gri[i + 1][j - 1] + a->gri[i + 1][j] + a->gri[i + 1][j + 1]) != 0)
				{
//
// E: for each direction 
// F: Pour chaque direction (N-S, NE-SO, E-O, SE-NO)
//
				for (dir = 0; dir<4; dir++)
					{
					if ((a->gri[i + dirX[dir]][j + dirY[dir]] != 0) || (a->gri[i - dirX[dir]][j - dirY[dir]] != 0))
						{
//
// E : extraction of 15 cells (7 before, 7 after)
// F : extraction des 15 cases centrees sur la case courante (7 avant, 7 après)
//							
						for (k = -7; k <= 7; k++)
							{
							tab[k + 7] = 1023;
							ii = i + k*dirX[dir];
							jj = j + k*dirY[dir];
							if ((ii >= 0) && (ii<MAXGRI) && (jj >= 0) && (jj<MAXGRI))
								tab[k + 7] = a->gri[ii][jj];
							}
//
// E : the table tab[] contains the 15 cells, check if a line in possible
// F : la table tab[] est chargée, recherche d'une ligne dans ces cases
//
						for (k = 3; k<8; k++)
							{
							tot = 0;
							if ((tab[k] & dirD[dir]) == 0){ tot = tot + 1; }
							if ((tab[k + 1] & dirDO[dir]) == 0){ tot = tot + 1; }
							if ((tab[k + 2] & dirDO[dir]) == 0){ tot = tot + 1; }
							if ((tab[k + 3] & dirDO[dir]) == 0){ tot = tot + 1; }
							if ((tab[k + 4] & dirO[dir]) == 0){ tot = tot + 1; }
							for (kk = 0; kk<5; kk++)
								if (((k + kk) != 7) && ((tab[k + kk] & 1) == 1)){ tot = tot + 1; }
//
// E: if a line is possible, 
// F: si un alignement est possible, 
//
							if (tot == 9)
								{
								coupX = i;
								coupY = j;
								coupD = dir;
								coupK = k - 3;
//
// E: Setup of priorite[] : 1010 = high, 1005=normal, 1000 = low
//    a move has priority = 1010 (high) if the future line (L) the following properties
//    1) a line L1 already exists in the game with 1 commun point with L 
//    2) L parrallel with L1
//    
//      x-x-x-x-X x x x 1    the move (1) has high priority because the resulting situation is 2 consecutive lines  
//
//    in this case, priority[i] is set to 1010, else 1005.

// F: mise a jour de priorite[] : 1010 = haute, 1005 = normale, 1000=basse
//    un coup a une priorite = 1010 (haute) si la future ligne (L) a les propriete suivantes
//    1) une autre ligne L1 existe sur la grille avec un point commun avec L
//    2) L1 est parrallele à L
//
//      x-x-x-x-X x x x 1    le coup (1) est prioritaire car la situation resultante est deux lignes consecutives  
//
//    dans ce cas, priorite[i]=1010, 1005 sinon
//
								a->priorite[a->nbcoup]=1005;
								for (kk = 3; kk<8; kk++)
									if (kk == k)
										if (((tab[k] & dirO[dir]) == dirO[dir]) || ((tab[k + 4] & dirD[dir]) == dirD[dir]))
											a->priorite[a->nbcoup] = 1010;
//
// E: a move with low priority is defined if the situation is one of the following
//
//     case 1:    1 x x x x x-x-x-x-x        resulting situation   x-x-x-x-x x-x-x-x-x
//     case 2:    1 x x x x ? x-x-x-x-x      resulting situation   x-x-x-x-x ? x-x-x-x-x	
//     case 3:    1 x x x x ? ? x-x-x-x-x    resulting situation   x-x-x-x-x ? ? x-x-x-x-x	
//     case 4:    x-x-x-x-x x x x x 1        resulting situation   x-x-x-x-x x-x-x-x-x 	
//     case 5:    x-x-x-x-x ? x x x x 1      resulting situation   x-x-x-x-x ? x-x-x-x-x 
//     case 6:    x-x-x-x-x ? ? x x x x 1    resulting situation   x-x-x-x-x ? ? x-x-x-x-x 
//
//     of course, this rule applys for all cases of line (in the example  1 x x x x  but for  x x 1 x x  too)
//     the "?" replace any value of the cell except a cell played in the current direction
//
// F : on definit un coup comme mauvais (coupP[]=-1) si on se trouve dans l'un des cas suivants
//
//     cas 1:    1 x x x x x-x-x-x-x        situation résultante   x-x-x-x-x x-x-x-x-x
//     cas 2:    1 x x x x ? x-x-x-x-x      situation résultante   x-x-x-x-x ? x-x-x-x-x	
//     cas 3:    1 x x x x ? ? x-x-x-x-x    situation résultante   x-x-x-x-x ? ? x-x-x-x-x	
//     cas 4:    x-x-x-x-x x x x x 1        situation résultante   x-x-x-x-x x-x-x-x-x 	
//     cas 5:    x-x-x-x-x ? x x x x 1      situation résultante   x-x-x-x-x ? x-x-x-x-x 
//     cas 6:    x-x-x-x-x ? ? x x x x 1    situation résultante   x-x-x-x-x ? ? x-x-x-x-x 
//
//     Bien entendu, cette règle doit s'appliquer quelque soit la façon dont l'alignement est réalisé (dans l'exemple 1 x x x x mais x x 1 x x aussi)
//     Le point d'interrogation peut être n'importe quoi sauf une case jouée dans la direction traitée
//
								if (a->priorite[a->nbcoup] == 1005)
									{
									for (kk = 3; kk<8; kk++)
										{
										if ((tab[k - 1] & dirO[dir]) == dirO[dir])a->priorite[a->nbcoup] = 1000;
										if ((tab[k - 2] & dirO[dir]) == dirO[dir])a->priorite[a->nbcoup] = 1000;
										if ((tab[k - 3] & dirO[dir]) == dirO[dir])a->priorite[a->nbcoup] = 1000;
										if ((tab[k + 5] & dirD[dir]) == dirD[dir])a->priorite[a->nbcoup] = 1000;
										if ((tab[k + 6] & dirD[dir]) == dirD[dir])a->priorite[a->nbcoup] = 1000;
										if ((tab[k + 7] & dirD[dir]) == dirD[dir])a->priorite[a->nbcoup] = 1000;
										}
									}
//
// E: the new legal move is loaded in the table coup[]
// F: chargement du coup trouve dans la tables des coups legaux
//
								a->coup[a->nbcoup] = cpXYDK(coupX, coupY, coupD, coupK);
//
// E: initialize dominateur[i] (update at the end of the function)
// F: initialise dominateur[i] (mise à jour à la fin de la fonction)
//
								a->dominateur[a->nbcoup] = 999;
								a->nbcoup += 1;
//
// E: checks for data integrity
// F: verifications de coherence
//
								if (a->nbcoup>MAXCOU)
									{
									printf("table des coups possibles trop petite %d %d \n", a->nbcoup, MAXCOU);
									exit(1);
									}
								if ((i == 1) || (i == (MAXGRI - 1)) || (j == 1) || (j == (MAXGRI - 1)))
									{
									printf("table gri trop petite : coups trouvé en bordure %d %d", i, j);
									exit(1);
									}
								}
							}
						}
					}
				}
			}
		}
	}
//
// E: update of the field dominateur[] for all moves
// F: mise à jour du champ dominateur[]
//
maj_dominateur(a);
}
//////////////////////////////////////////////////////////////////////////////////////////
void rech_coup_opti(grille *a, grille *b, int coup_joue)
//////////////////////////////////////////////////////////////////////////////////////////
//
// E: search of legal moves (b->nbcoup, b->coup[]) with b = a + a->coup[coup_joue] 
// F: recherche les coups jouables (b->nbcoup, b->coup[]) avec  b = a + a->coup[coup_joue] 
//
{
int i, j, ix, jx, dir, k, ii, jj, kk, tot, res, xx, tab[15], prio, mauv;
int coupX_p, coupY_p, coupD_p, coupK_p, coupX, coupY, coupD, coupK;
//
// E: direction table
// F: table des directions
//
int dirX[4] = { 0, 1, 1, 1 };
int dirY[4] = { 1, 1, 0, -1 };
int dirD[4] = { 2, 4, 8, 16 };
int dirO[4] = { 32, 64, 128, 256 };
int dirDO[4] = { 34, 68, 136, 272 };
//
// E: for each previous move (a->coup[], check if it's still valid on b grid
//    if yes, the previous move is loaded in the current legal moves table (b->coup) 
// F: Pour chaque coup de la table des coups précédents (a) on regarde s'il est encore valide pour b
//    Si oui, on recopie le coup vers la table des coups valides de b
//
b->nbcoup = 0;
for (i = 0; i < a->nbcoup; i++)
	{
	coupX_p = cpX(a->coup[i]);
	coupY_p = cpY(a->coup[i]);
	coupD_p = cpD(a->coup[i]);
	coupK_p = cpK(a->coup[i]);
	if (b->gri[coupX_p][coupY_p] == 0)
		{
		tot = 0;
		prio = 0;
		mauv = 0;
		for (kk = -3; kk<8; kk++)
			{
			ii = coupX_p + (coupK_p + kk - 4)*dirX[coupD_p];
			jj = coupY_p + (coupK_p + kk - 4)*dirY[coupD_p];
			if ((kk == 0) && ((b->gri[ii][jj] & dirD [coupD_p]) == 0)){ tot = tot + 1; }
			if ((kk == 1) && ((b->gri[ii][jj] & dirDO[coupD_p]) == 0)){ tot = tot + 1; }
			if ((kk == 2) && ((b->gri[ii][jj] & dirDO[coupD_p]) == 0)){ tot = tot + 1; }
			if ((kk == 3) && ((b->gri[ii][jj] & dirDO[coupD_p]) == 0)){ tot = tot + 1; }
			if ((kk == 4) && ((b->gri[ii][jj] & dirO [coupD_p]) == 0)){ tot = tot + 1; }
//
// E: selection of move with priority high
// F: selection des coups prioritaires
//
			if ((kk == 4) && ((b->gri[ii][jj] & dirD [coupD_p]) == dirD[coupD_p])){ prio = 1; }
			if ((kk == 0) && ((b->gri[ii][jj] & dirO [coupD_p]) == dirO[coupD_p])){ prio = 1; }
//
// E: selection of move with priority low
// F: selection des mauvais coups
//
			if ((kk == -1) && ((b->gri[ii][jj] & dirO[coupD_p]) == dirO[coupD_p])){ mauv = 1; }
			if ((kk == -2) && ((b->gri[ii][jj] & dirO[coupD_p]) == dirO[coupD_p])){ mauv = 1; }
			if ((kk == -3) && ((b->gri[ii][jj] & dirO[coupD_p]) == dirO[coupD_p])){ mauv = 1; }
			if ((kk ==  5) && ((b->gri[ii][jj] & dirD[coupD_p]) == dirD[coupD_p])){ mauv = 1; }
			if ((kk ==  6) && ((b->gri[ii][jj] & dirD[coupD_p]) == dirD[coupD_p])){ mauv = 1; }
			if ((kk ==  7) && ((b->gri[ii][jj] & dirD[coupD_p]) == dirD[coupD_p])){ mauv = 1; }
			}
		if (tot == 5)
			{
//
// E: update priority (see rech_coup for more explanation)
// F: maj priorite (voir rech_coup pour plus d'explications)
//
			b->priorite[b->nbcoup] = 1005;
			if (prio>0)
				b->priorite[b->nbcoup] = 1010;
			if ((mauv>0) && (b->priorite[b->nbcoup]==1005))
				b->priorite[b->nbcoup] = 1000;
			b->coup[b->nbcoup] = cpXYDK(coupX_p, coupY_p, coupD_p, coupK_p);
//
// E: initialize dominateur[i] (update at the end of the function)
// F: initialise dominateur[i] (mise à jour à la fin de la fonction)
//
			b->dominateur[b->nbcoup] = 999;
			b->nbcoup += 1;
			}
		}
	}
//
// E: Search for legal move around the previous move
// F: Recherche des coups jouables autour de la case jouée au coup précédent
//
ix = cpX(a->coup[coup_joue]);
jx = cpY(a->coup[coup_joue]);
for (i = ix - 4; i <= ix + 4; i++)
	{
	for (j = jx - 4; j <= jx + 4; j++)
		{
		if ((b->gri[i][j] == 0) && (i>0) && (j>0) && (i<MAXGRI) && (j<MAXGRI))
			{
			if ((b->gri[i - 1][j - 1] + b->gri[i - 1][j] + b->gri[i - 1][j + 1] + b->gri[i][j - 1] + b->gri[i][j + 1] + b->gri[i + 1][j - 1] + b->gri[i + 1][j] + b->gri[i + 1][j + 1]) != 0)
				{
				for (dir = 0; dir<4; dir++)
					{
					if ((b->gri[i + dirX[dir]][j + dirY[dir]] != 0) || (b->gri[i - dirX[dir]][j - dirY[dir]] != 0))
						{
						for (k = -7; k<=7; k++)
							{
							tab[k + 7] = 1023;
							ii = i + k*dirX[dir];
							jj = j + k*dirY[dir];
							if ((ii >= 0) && (ii<MAXGRI) && (jj >= 0) && (jj<MAXGRI))
								tab[k + 7] = b->gri[ii][jj];
							}
						for (k = 3; k<8; k++)
							{
							tot = 0;
							if ((tab[k] & dirD[dir]) == 0){ tot = tot + 1; }
							if ((tab[k + 1] & dirDO[dir]) == 0){ tot = tot + 1; }
							if ((tab[k + 2] & dirDO[dir]) == 0){ tot = tot + 1; }
							if ((tab[k + 3] & dirDO[dir]) == 0){ tot = tot + 1; }
							if ((tab[k + 4] & dirO[dir]) == 0){ tot = tot + 1; }
							for (kk = 0; kk<5; kk++)
								if (((k + kk) != 7) && ((tab[k + kk] & 1) == 1)){ tot = tot + 1; }
							if (tot == 9)
								{
// 
// E: same algorithme than rech_coup, except a check for duplicates move
// F: meme algo que rech_coup, a l'exception d'une recherche de doublons sur les coups
//
								res = 0;
								for (xx = 0; xx < b->nbcoup; xx++)
									{
									coupX = cpX(b->coup[xx]);
									coupY = cpY(b->coup[xx]);
									coupD = cpD(b->coup[xx]);
									coupK = cpK(b->coup[xx]);
									if ((coupX == i) && (coupY == j) && (coupD == dir) && (coupK == (k - 3)))
										res = 1;
									}
								if (res == 0)
									{
									coupX = i;
									coupY = j;
									coupD = dir;
									coupK = k - 3;
									b->priorite[b->nbcoup] = 1005;
									for (kk = 3; kk<8; kk++)
										if (kk == k)
											if (((tab[k] & dirO[dir]) == dirO[dir]) || ((tab[k + 4] & dirD[dir]) == dirD[dir]))
												b->priorite[b->nbcoup] = 1010;
									if (b->priorite[b->nbcoup] == 1005)
										{
										for (kk = 3; kk<8; kk++)
											{
											if ((tab[k - 1] & dirO[dir]) == dirO[dir])b->priorite[b->nbcoup] = 1000;
											if ((tab[k - 2] & dirO[dir]) == dirO[dir])b->priorite[b->nbcoup] = 1000;
											if ((tab[k - 3] & dirO[dir]) == dirO[dir])b->priorite[b->nbcoup] = 1000;
											if ((tab[k + 5] & dirD[dir]) == dirD[dir])b->priorite[b->nbcoup] = 1000;
											if ((tab[k + 6] & dirD[dir]) == dirD[dir])b->priorite[b->nbcoup] = 1000;
											if ((tab[k + 7] & dirD[dir]) == dirD[dir])b->priorite[b->nbcoup] = 1000;
										}
									}
									b->coup[b->nbcoup] = cpXYDK(coupX, coupY, coupD, coupK);
//
// E: initialize dominateur[i] (update at the end of the function)
// F: initialise dominateur[i] (mise à jour à la fin de la fonction)
//
									b->dominateur[b->nbcoup] = 999;
									b->nbcoup += 1;
//
// E: checks for data integrity
// F: verifications de coherence
// 
									if (b->nbcoup > MAXCOU)
										{
										printf("table des coups possibles trop petite %d %d \n", b->nbcoup, MAXCOU);
										exit(1);
										}
									if ((i == 1) || (i == (MAXGRI - 1)) || (j == 1) || (j == (MAXGRI - 1)))
										{
										printf("table gri trop petite : coups trouvé en bordure %d %d", i, j);
										exit(1);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
//
// E: update of the field dominateur[] for all moves
// F: mise à jour du champ dominateur[]
//
maj_dominateur(b);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void maj_dominateur(grille *a)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// E: Update dominateur field : number of dominant move for domined moves 
// F: Mise a jour le champ dominateur: numero du coup dominateur pour les coups domines
//
{
int i,j,x1,x2,y1,y2,d1,d2;
if (a->nbcoup > 0)
	{
	for (i=0;i < a->nbcoup;i++)
		{
		if (a->priorite[i] == 1010)
			{
			x1 = cpX(a->coup[i]);
			y1 = cpY(a->coup[i]);
			d1 = cpD(a->coup[i]);
			for (j=0;j < a->nbcoup;j++)
				{
				if ((i != j) && (a->priorite[j] != 1010))
					{
					x2 = cpX(a->coup[j]);
					y2 = cpY(a->coup[j]);
					d2 = cpD(a->coup[j]);
					if ((x1 == x2) && (y1 == y2) && (d1==d2))
						a->dominateur[j] = i;
					}
				}
			}
		}
	}
}					
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void joue_coup(grille *a, grille *b, int coup_joue)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// E : play the move a->coup[coup_joue] on grid b
// F : joue le coup i de la grille a sur la grille b
//
{
int i, j, ii, jj, uu, alpha, coupX, coupY, coupD, coupK;
//
// E: direction table
// F: table des directions
//
int dirX[4] = { 0, 1, 1, 1 };
int dirY[4] = { 1, 1, 0, -1 };
int dirD[4] = { 2, 4, 8, 16 };
int dirO[4] = { 32, 64, 128, 256 };
int dirDO[4] = { 34, 68, 136, 272 };
//
// E: if grid b is not grid a, duplication of a to b
// F: si la grille cible est differente de la grille initiale, duplication de la grille et historique des coups
//
if (a != b)
	{
	for (i = 0; i<MAXGRI; i++)
		for (j = 0; j<MAXGRI; j++)
			b->gri[i][j] = a->gri[i][j];
	b->nbhc = a->nbhc;
	for (i = 0; i<b->nbhc; i++)
		b->hc[i] = a->hc[i];
	}
//
// E: if a dominated move is played, the dominant move is played
// F: si on joue un coup domine, on le remplace par le dominant
//
if (a->dominateur[coup_joue]!=999)
	coup_joue = a->dominateur[coup_joue];
//
// E: the move is added is the historic
// F: On ajoute le coup joue dans l'historique
//
b->hc[b->nbhc] = a->coup[coup_joue];
b->nbhc += 1;
//
// E: check integrity
// F: tests de coherence
//
if (b->nbhc>MAXCOU)
	{
	printf("Attention table de stockage des coups joués trop petite : indice actuel: %d\n", b->nbhc);
	exit(1);
	}
if (b->gri[cpX(a->coup[coup_joue])][cpY(a->coup[coup_joue])] != 0)
	{
	printf("Anomalie la grille contient quelque chose au point joue : contenu:%d i=%d j=%d\n", b->gri[cpX(a->coup[coup_joue])][cpY(a->coup[coup_joue])], cpX(a->coup[coup_joue]), cpY(a->coup[coup_joue]));
	exit(1);
	}
//
// E: play the move of grid b
// F: on joue le coup sur la grille b
//
coupX = cpX(a->coup[coup_joue]);
coupY = cpY(a->coup[coup_joue]);
coupD = cpD(a->coup[coup_joue]);
coupK = cpK(a->coup[coup_joue]);
b->gri[coupX][coupY] = 1;
for (uu = -4; uu <= 0; uu++)
	{
	alpha = coupK + uu;
	ii = coupX + (alpha*dirX[coupD]);
	jj = coupY + (alpha*dirY[coupD]);
//
// E: check integrity
// F: test integrite
//
	if (((b->gri[ii][jj]) % 2) != 1)
		{
		printf("\n");
		printf("Anomalie la grille est vide sur un point support d'un alignement : contenu:%d i=%d j=%d\n", b->gri[ii][jj], ii, jj);
		exit(1);
		}
	if (uu == -4)							    b->gri[ii][jj] = b->gri[ii][jj] + dirD[coupD];
	if (uu == 0)							    b->gri[ii][jj] = b->gri[ii][jj] + dirO[coupD];
	if ((uu == -3) || (uu == -2) || (uu == -1))	b->gri[ii][jj] = b->gri[ii][jj] + dirDO[coupD];
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
grille constr_jeu(grille *MaxJ, grille *Init, int NIV,FILE *fichier)
////////////////////////////////////////////////////////////////////////////////////////////////
//
// E: The grid Node is generated with the first NIV moves of MaxJ historic starting  with position Init
// F: La grille Node est generee avec les NIV premiers movement de l'historique de MaxJ en partant de la grille Init
//
{
int i,j,j0;
grille Node;
memcpy(&Node, Init, sizeof(grille));
for (i=0;i<NIV;i++)
	{
	rech_coup(&Node);
	j0=999;
	for (j=0;j<Node.nbcoup;j++)
		if ((Node.coup[j]) == (MaxJ->hc[i]))j0=j;
	if (j0==999)
		{
		printf("le coup de MajJ %d n'a pas ete retrouve. Il y a quelque chose qui daube\n", i);
		fprintf(fichier, "BEST\n");
		disp_jeu(MaxJ, fichier);
		fprintf(fichier, "NODE\n");
		disp_jeu(&Node, fichier);
		exit(1);
		}
	joue_coup(&Node,&Node,j0);
	}
return(Node);
}
