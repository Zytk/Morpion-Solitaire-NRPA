
// E : algo NRPA
// F : algo NPRA
grille NRPA(int level, grille *node, poli strat, FILE *fichier);

// E : algo NRPA
// F : algo NPRA
grille NRPA_ITE(int level, grille node, FILE *fichier);

// E : NRPA playout 
// F : NRPA rollout
grille NRPA_playout(grille *gri, poli *policy, FILE *fichier);

// E : select a move with NRPA algorithm
// F : selection d'un coup (algo NRPA)
int NRPA_sel_coup(grille *a, poli *policy, FILE * fichier);

// E : adapt strategy (NRPA)
// F : adaptation de la strategie
poli NRPA_adapt(poli policy, grille *root, grille *best, FILE *fichier);

// E : calculation of field "code" (NRPA algorithm)
// F : calcul du "code" des coups legaux (NRPA)
void NRPA_gen_code(grille *a, FILE *fichier);

// E : Display NRPA strategy
// F : Affichage strategie NRPA
void NRPA_disp_pol(poli strat, FILE * fichier);