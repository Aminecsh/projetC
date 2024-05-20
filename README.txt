Ce projet réimplémente les dataframes de la librairie Pandas en Python en C :


Pour compiler le projet, il faut faire la commande "clang main.c cdataframe.c column.c list.c sort.c -o programme" sur la ligne de commande
Ensuite il faut écrire "./programme" pour l'exécuter

	- La fonction main teste les fonctions à implémenter

	- La fonction create_columns renvoie un pointeur vers une columns

	- La fonction create_empty_cdataframe renvoie un pointeur vers un cdataframe

	- La fonction add_column permet d'ajouter une columns à un CDataframe

Le projet contient plusieurs fonctions d'affichage pour pouvoir visualiser l'effet qu'ont eu les fonctions utilisées
Les noms des fonctions sont assez explicites (display_cdataframe, display_column_names, display_line_count, etc..)

Le CDataframe est une liste doublement chaînée de plusieurs columns, utiliser une liste chaînée permet d'ajouter des column sans devoir faire de réallocation, cela ajoute de la flexibilité ce qui est assez pratique.


Lien gitHub : https://github.com/Aminecsh/projetC

Loris FEGHOUL / Amine CHAMSSAN

