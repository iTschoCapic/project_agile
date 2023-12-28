# project_agile

## ORUEZABALA Antoine
## MACHECOURT-BOURGEOIS Renaud

Pré-requis:
    Bibliothèques:
        - SDL2
        - SDL2_image
        - SDL2_ttf
    Makefile est un plus mais n'est pas nécessaire,
    Il faut par contre un compilateur C comme Mingw64. Je laisse une version .exe si jamais vous êtes aussi sur Windows cela peut fonctionner.
    Vous trouverez aussi la commande pour compiler : gcc -I include -L lib -o gameLoop gameLoop.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf 

Ce projet à pour objectif de fournir une application permettant de réaliser un Poker Planning.
Nous avons décidez de le coder en C.
Pour nous aider dans notre construction du projet, nous allons nous même faire le Poker Planning de ce dernier.
Pour cela, il nous faut d'abord réaliser une liste des différentes tâches à accomplir.
En ce qui concerne les cartes utilisées pour noter les tâches, nous avons simplement repris celle du projet.

Liste des tâches avec coefficient de difficulté estimé:
- Choix du mode de jeu (minimun deux, dont strict et un au choix parmi: moyenne, médiane, majorité absolue, majorité relative), 1;
- Système de votes (Premier tour est toujours à l'unanimité), 13;
- Jouable en local,
- Choix du pseudo, 2;
- Enregistrement de la partie dans un fichier JSON, 5;
- Démarrage/Reprise d'une partie à partir d'un fichier JSON, 5;
- Chronomètre, 3;
- Chat, 8;
- Choix du thème (Fond, cartes, sons), 5;

Il nous faut aussi choisir un minimum de trois patrons de conception (Design Pattern):
- Factory (Il nous permettra d'initialiser les images des cartes rapidement et de manière automatisée)
- Prototype (Il servira à la création des objects des cartes à partir d'un prototype, cela veut dire un meilleur temps de traitement)
- State (Ce dernier nous laissera suivre l'état de la partie, et ainsi de pouvoir l'enregistrer dans les JSON rapidement et facilement).

En ce qui concerne le format du JSON, nous avons décidé de partir sur cela:
Mode de jeu;
État;
Nombre de tâches restant à évaluer;
Dernière tâche évaluée;
Tâche n°1, [Note](si décidé);

Cela pourrait par exemple donner:
Strict;
En cours;
2;
1;
Tâche n°0, 1;
Tâche n°1, 5;
Tâche n°2;
Tâche n°3;

Nous avons décidé de ne pas sauvegarder le nom des participants car ces derniers pourraient changer.
De plus, l'ordre des tâches n'a pas d'importance à l'exception qu'il faut que toutes les tâches déjà évaluées soient en premières et les autres après.
On enregistre le nombre de tâche total ainsi que le nombre de tâches déjà faites afin de ne pas avoir tout le fichier à parcourir en redémarrant la partie (gain de temps de calcul).