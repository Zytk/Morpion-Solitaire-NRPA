#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Basic_Fct.h"
#include "NRPA.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
grille NRPA(int level, grille *node, poli strat, FILE *fichier)
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// E : algo "nested rollout policy adaptation" 
//     parameters:
//     p1 = level of algo
//     p2 = grid to evaluate
//     p3 = initial grid
//     p4 : current policy
//     p5 : output file
// 
// F : algo "nested rollout policy adaptation" 
//     parametres
//     p1 = level de la recherche
//     p2 = grille a partir de laquelle la recherche est r�alis�e
//     p3 : strategie courante
//     p4 : fichier de sortie
//
{
if (level == 0)
	{
//
// E : At level 0, playout with policy
// F : Au niveau 0, rollout sur la grille en utilisant la strategie
//
	return(NRPA_playout(node, &strat, fichier));
	}
else
	{
	int N = 5, i;
	grille result,max;
	max.nbhc=0;
	for (i = 0; i<N; i++)
		{
		result=NRPA(level - 1, node, strat, fichier);
		if (result.nbhc >= max.nbhc)
			{
			memcpy(&max, &result, sizeof(grille));
			strat=NRPA_adapt(strat, node, &max, fichier);
			}
		}
	return(max);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
grille NRPA_playout(grille *gri, poli *policy, FILE *fichier)
/////////////////////////////////////////////////////////////////////////////////////////////
//
// E : rollout with move selection according policy
// F : rollout avec selection du coup selon la strategie "policy"
//
{
grille a,b;
int coup;
//
// E : copy current grid on a
// F : copie grille courante sur a
//
memcpy(&a, gri, sizeof(grille));
rech_coup(&a);
//
// E : while game is not over
// F : tant que le jeu n'est pas fini
//
while (a.nbcoup>0)
	{
//
// E: select best move and play it on grid b
// F: recherche le meilleur coup et le joue sur la grille b
//
	coup = NRPA_sel_coup(&a, policy, fichier);
	joue_coup(&a, &b, coup);
	rech_coup_opti(&a, &b, coup);
	if (b.nbcoup > 0)
		{
//
// E: if one move available on b, play the best move on grid a
// F: si un coup possible sur b, joue le meilleur coup sur a
//
		coup = NRPA_sel_coup(&b, policy, fichier);
		joue_coup(&b, &a, coup);
		rech_coup_opti(&b, &a, coup);
		}
	else
//
// E: if no move avail on b, just copy grid b on grid a
		{
		memcpy(&a, &b, sizeof(grille));
		}
	}
//
// E: end of game, return a grid
// F: fin de jeu, retour grille a
//
return(a);
}
/////////////////////////////////////////////////////////////////////////////////////////
int NRPA_sel_coup(grille *a, poli *strat, FILE * fichier)
////////////////////////////////////////////////////////////////////////////////////////
//
// E : selection of a move using policy
// F : selection d'un coup avec la strategie
//
{
int i;
double sum_coef, nb_alea, tr_max, tr_min;
//
// E : compute the code of each move
// F : calcul du code de chaque coup
//
NRPA_gen_code(a, fichier);
//
// E : first iteration on moves for sum calculation
// F : premiere iteration sur les coups pour calcul de la somme des coefs
//
sum_coef = 0.;
for (i = 0; i < a->nbcoup; i++)
	if (a->priorite[i]==1000)
		sum_coef += exp(strat->policy[a->code[i]])/1000;
	else
		if (a->priorite[i] == 1005)
			sum_coef += exp(strat->policy[a->code[i]]) / 34;
		else
			sum_coef += exp(strat->policy[a->code[i]]);
//
// E : random number between 0 and 1
// F : generation d'un nombre al�atoire compris entre 0 et 1
//
	nb_alea = rand() / (RAND_MAX + 1.);
//
// E : second iteration on moves and stop corresponding alea
// F : Deuxieme iteration sur tous les coups possibles et arret sur la tranche qui correspond � nb_alea
//
tr_min = 0;
tr_max = 0;
for (i = 0; i < a->nbcoup; i++)
	{
	if (a->priorite[i] == 1000)
		tr_max += exp(strat->policy[a->code[i]]) / 1000 / sum_coef;
	else
		if (a->priorite[i] == 1005)
			tr_max += exp(strat->policy[a->code[i]]) / 34 / sum_coef;
		else
			tr_max += exp(strat->policy[a->code[i]]) / sum_coef;
	if ((nb_alea >= tr_min) && (nb_alea <= tr_max))
		return(i);
	tr_min = tr_max;
	}
//
// E : no move selected : problem...
// F : pas de coup selectionn� : probleme ...
//
printf("probleme dans selection coup. alea=%f\n", nb_alea);
for (i = 0; i<a->nbcoup; i++)
	printf("coup %02d %f %f\n", i, strat->policy[a->code[i]], exp(strat->policy[a->code[i]]) / sum_coef);
exit(1);
}
//////////////////////////////////////////////////////////////////////////////////////////////
poli NRPA_adapt(poli strat, grille *root, grille *best, FILE *fichier)
//////////////////////////////////////////////////////////////////////////////////////////////
//
// E : for each move between root and best, adaptation of the policy
// F : pour chaque coup entre root et best, adaptation de la strategie
//
{
int i, j_ok, j;
double z, alpha = 1;
//
// E : duplicate policy into policynew
// F : duplication de policy dans policynew
// 
poli stratnew;
for (i = 0; i<MAXGRI*MAXGRI*4;i++)
	stratnew.policy[i] = strat.policy[i];
//
// E : duplicate root into node
// F : duplication de root dans node
//
grille node;
memcpy(&node, root, sizeof(grille));
rech_coup(&node);
//
// E : iteration of each move of best
// F : iteration sur tous les coups de best
//
for (i = node.nbhc; i < best->nbhc; i++)
	{
//
// E : evaluation of code[] for each move of node
// F : calcul des codes pour les coups de node
//
	NRPA_gen_code(&node, fichier);
//
// iteration of all moves of node
//
	z = 0.;
	j_ok = 999;
	for (j = 0; j < node.nbcoup; j++)
		{
//
// E : sum in Z for normalization
// F : cumul dans Z pour normaliser
//
		z += exp(strat.policy[node.code[j]]);
//
// E : if the current move is the best move, add alpha in the policynew and mark the number of the move
// F : si le coup courant est celui qui a ete choisi dans best, ajout de alpha dans le policynew
//
		if ((node.coup[j]) == (best->hc[i]))
			{
			j_ok = j;
			stratnew.policy[node.code[j]] += alpha;
			}
		}
//
// E : check for integrity
// F : test d'integrite
//
	if (j_ok == 999)
		{
		printf("Le coup de best %d n'a pas ete retrouve. Il y a quelque chose qui daube\n", i);
		fprintf(fichier, "Le coup de best %d n'a pas ete retrouve. Il y a quelque chose qui daube\n", i);
		fprintf(fichier, "BEST\n");
		disp_jeu(best, fichier);
		fprintf(fichier, "NODE\n");
		disp_jeu(&node, fichier);
		fclose(fichier);
		exit(1);
		}
//
// E : iteration for normalization
// F : re-iteration sur les coups de node pour normalisation
//
	for (j = 0; j < node.nbcoup; j++)
		stratnew.policy[node.code[j]] -= alpha * exp(strat.policy[node.code[j]]) / z;
//
// E : Next move of best
// F : on joue le coup suivant dans l'historique des coups de best
//
	joue_coup(&node, &node, j_ok);
	rech_coup(&node);
	}
return (stratnew);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NRPA_gen_code(grille *a, FILE *fichier)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// E : evaluate code for each mode of a
// F : calcule le code de chaque coup legal de la grille a 
//
{
	int i, coup_joue, coupX, coupY, coupD, coupK, ii1, jj1, ii2, jj2, n1, n2, ni, xi, yi, xa, ya, pos;
//
// E : direction table
// F : table des directions
//
	int dirX[4] = { 0, 1, 1, 1 };
	int dirY[4] = { 1, 1, 0, -1 };
	int dirD[4] = { 2, 4, 8, 16 };
	int dirO[4] = { 32, 64, 128, 256 };
	int dirDO[4] = { 34, 68, 136, 272 };
//
// E : iteration of all move
// F : iteration sur tous les coups legaux de a
//
for (i = 0; i < a->nbcoup; i++)
	{
	coup_joue = i;
//
// E : evaluation coordinate of the played move 
// F : recuperation des coordonn�es du point joue
//
	coupX = cpX(a->coup[coup_joue]);
	coupY = cpY(a->coup[coup_joue]);
	coupD = cpD(a->coup[coup_joue]);
	coupK = cpK(a->coup[coup_joue]);
// 
// E : calculation of code
// F : calcul de code
//
	ii1 = coupX + coupK*dirX[coupD];
	jj1 = coupY + coupK*dirY[coupD];
	ii2 = coupX + (coupK - 4)*dirX[coupD];
	jj2 = coupY + (coupK - 4)*dirY[coupD];
	n1 = (MAXGRI - 1)*jj1 + ii1;
	n2 = (MAXGRI - 1)*jj2 + ii2;
	ni = n2;
	xi = ii2;
	yi = jj2;
	xa = ii1;
	ya = jj1;
	if (n1<n2)
		{
		ni = n1;
		xi = ii1;
		yi = jj1;
		xa = ii2;
		ya = jj2;
		}
	if (xa < xi) pos = 0;
	if (xa == xi) pos = 1;
	if (xa > xi)
		if (ya > yi)
			pos = 2;
		else
			pos = 3;
	a->code[coup_joue] = 4 * ni + pos;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void NRPA_disp_pol(poli strat, FILE * fichier)
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// E : display policy
// F : affichage de la strategie
//
{
int p1;
fprintf(fichier, "STRATEGIE\n");
for (p1 = 0; p1<MAXGRI*MAXGRI * 4; p1++)
	if (strat.policy[p1] != 0)
		fprintf(fichier, "exp(strat)=%e strat=%e code=%05d\n", exp(strat.policy[p1]), strat.policy[p1], p1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int sign_grille(grille *a)
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// E : evaluate the signature of a grid
// F : calcule la signature d'une grille 
{
int i, j, tot = 0;
for (i = 0; i<MAXGRI; i++)
	for (j = 0; j<MAXGRI; j++)
		tot += a->gri[i][j] * i*j;
return (tot);
}
