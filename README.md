# Refactoring avec git

L'objectif de ce TD est d'utiliser git en équipe pour restructurer un programme mal conçu. Le programme d'exemple permet de lire des données de type `double`, de les stocker, d'effectuer des calculs dessus et d'écrire le résultat.

En l'état du du début du TD, le programme fonctionne (plus ou moins), permet de lire depuis un fichier binaire ou texte, de stocker dans une structure soit à base de `vector`, soit à base de liste chaînée, et d'écrire le résultat dans un fichier texte, binaire, ou sur la sortie standard.

Le changement de type de stockage, de calcul, et des formats d'entrée et de sortie se fait en modifiant le code.

## Constitution des équipes

Pour réaliser ce travail, vous constituerez des équipes de 3 à 4 étudiants. Il est préférable que chaque équipe comporte au moins un membre familiarisé avec C++, de préférence au moins le standard C++11.

## Refactoring

Le programme actuel n'est pas maintenable ni testable facilement. Votre équipe est donc chargée de réaliser cette restructuration en vue de l'évolution du programme. Vous devez dans un premier temps réfléchir à une structure qui rende facile l'évolution et le test du programme. Vous appliquerez notamment la loi de Demeter et les bonnes pratiques du C++ vues en cours. Déléguer la gestion des données à un manager est également souhaitable.

Si vous peinez à trouver les évolutions du code nécessaires, vous pouvez vous inspirer de la liste disponible [ici](TODO.md)

## Livrable

Vous déposerez votre travail sur un dépôt git. Il sera notamment nécessaire que l'historique des contributions soit visible pour me permettre d'évaluer votre capacité à utiliser git dans le cadre d'un travail en équipe. Il vous sera nécessaire pour cela de commiter vos contributions avec l'option `--no-ff`
