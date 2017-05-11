
// E : algo NRPA
// F : algo NPRA
void NRPA_ITE(grille *res,int level, grille *node, FILE *fichier);

// E : NRPA playout 
// F : NRPA rollout
 void NRPA_playout(grille *res, grille *gri, poli *policy, FILE *fichier);

// E : select a move with NRPA algorithm
// F : selection d'un coup (algo NRPA)
int NRPA_sel_coup(grille *a, poli *policy, FILE * fichier);

// E : adapt strategy (NRPA)
// F : adaptation de la strategie
void NRPA_adapt(poli *policy, grille *root, grille *best, FILE *fichier);

// E : calculation of field "code" (NRPA algorithm)
// F : calcul du "code" des coups legaux (NRPA)
void NRPA_gen_code(grille *a, FILE *fichier);

// E : Display NRPA strategy
// F : Affichage strategie NRPA
void NRPA_disp_pol(poli strat, FILE * fichier);