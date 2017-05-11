# Morpion-Solitaire-NRPA
Eng:
What is Morpion Solitaire ?
Morpion Solitaire is a pencil-and-paper puzzle on a square grid that is presumed to be infinite. Given a current configuration of dots (marked intersections on the grid), a legal turn requires the addition of one more dot such that a new line of 5 dots in a row can be formed, horizontally or vertically or diagonally. The line is also added to the grid, and new lines cannot overlap any previous line. Solutions are scored by the number of lines they contain, and the goal is to maximize this. We consider the version “Touching”
that allows parallel lines to share an endpoint.

Goal of the project
The goal of this project is to maximize the score of the game. This project implement the NRPA algorithm (Nested Rollout Policy Adaptation for Monte Carlo Tree Search). With this algorithm, Christopher D. Rosin has found in  2011 a new record with 178 lines. More information here: http://www.chrisrosin.com/rosin-ijcai11.pdf

Fr:
Morpion Solitaire, qu'est-ce que c'est ?
Morpion Solitaire est un jeu papier-crayon qui se joue sur une grille carrée présumée infinie. En partant d'une configuration donnée de points (généralement croix de Malte), un coup légal consiste en l'ajout d'un point supplémentaire inclus dans une ligne formée de 5 points (horizontalement, verticalement ou en oblique). La nouvelle ligne ainsi formée est ajoutée à la grille. Chaque nouvelle ligne formée ne peut pas avoir plus d'un point en commun avec n'importe quelle autre ligne déjà formée. Le but de la partie est de maximiser le nombre de lignes. On considère ici la version "5T" où deux lignes parallelles peuvent avoir un point en commun. Il existe aussi une version "5D" dans laquelle deux lignes parallelles ne peuvent pas avoir de point en commun.

But du projet
Le but de ce projet est d'écrire un programme qui maximise le score du jeu. Ce projet met en oeuvre l'algorithme NRPA (Nested Rollout Policy Adaptation for Monte Carlo Tree Search). Avec cet algorithme, Christopher D. Rosin a, en 2011, battu le record de ce jeu avec 178 lignes. Plus d'information ici: http://www.chrisrosin.com/rosin-ijcai11.pdf
