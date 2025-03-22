# Projet kover : Gestionnaire de positionnement d'antennes de communication

## Description
`kover` est une application en ligne de commande permettant de gérer le positionnement d'antennes de communication en tenant compte des bâtiments environnants. L'application lit une description de scène depuis l'entrée standard et peut effectuer diverses opérations d'analyse comme le calcul de la boîte englobante, la description détaillée de la scène ou un résumé des éléments présents.

Ce projet a été développé dans le cadre du cours INF3135 - Construction et maintenance de logiciels à l'UQAM, sous la supervision du professeur Alexandre Blondin Massé. L'énoncé complet du travail est disponible dans le fichier [sujet.md](https://gitlab.info.uqam.ca/millimounou.guy_olivier_yanouba/inf3135-251-tp2/-/blob/master/sujet-tp2.md?ref_type=heads)

## Auteur
Guy Olivier Yanouba Millimouno (MILG69360006)

## Fonctionnement

### Compilation
Le projet utilise un Makefile pour automatiser la compilation. Pour compiler l'application :
```sh
$ make
```
Cette commande générera l'exécutable `kover`.

### Utilisation
L'application accepte une sous-commande obligatoire et lit la description de la scène depuis l'entrée standard. Les sous-commandes disponibles sont :

* `bounding-box` : Calcule et affiche la boîte englobante de la scène
* `describe` : Fournit une description détaillée de la scène
* `help` : Affiche l'aide de l'application
* `summarize` : Présente un résumé de la scène
* `validate` : Vérifie si la scène est valide et retourne le résultat

### Format de la scène
La scène doit respecter la syntaxe suivante :
* Première ligne : `begin scene`
* Dernière ligne : `end scene`
* Entre ces lignes : définitions de bâtiments et d'antennes

Format des bâtiments :
```
building ID X Y W H
```
où :
* `ID` : identifiant unique du bâtiment
* `X,Y` : coordonnées du centre
* `W,H` : demi-largeur et demi-hauteur

Format des antennes :
```
antenna ID X Y R
```
où :
* `ID` : identifiant unique de l'antenne
* `X,Y` : coordonnées de l'antenne
* `R` : rayon de portée

### Exemples d'utilisation

#### Sous-commande `bounding-box`
```sh
$ ./kover bounding-box < scene.txt
bounding box [-10, 25] x [-5, 20]
```

#### Sous-commande `describe`
```sh
$ ./kover describe < scene.txt
A scene with 2 buildings and 3 antennas
  building b1 at 5 10 with dimensions 15 10
  building b2 at 15 5 with dimensions 10 10
  antenna a1 at 0 0 with range 12
  antenna a2 at 10 10 with range 5
  antenna a3 at 20 15 with range 5
```

#### Sous-commande `summarize`
```sh
$ ./kover summarize < scene.txt
A scene with 2 buildings and 3 antennas
```

#### Sous-commande `validate`
```sh
$ ./kover validate < scene.txt
ok
```

```sh
$ ./kover validate < invalid_scene.txt
not ok
error: buildings b1 and b2 are overlapping
```

#### Sous-commande `help`
```sh
$ ./kover help
Usage: kover SUBCOMMAND
Handles positioning of communication antennas by reading a scene on stdin.

SUBCOMMAND is mandatory and must take one of the following values:
  bounding-box: returns a bounding box of the loaded scene
  describe: describes the loaded scene in details
  help: shows this message
  summarize: summarizes the loaded scene
  validate: validates the scene and reports if it's valid

A scene is a text stream that must satisfy the following syntax:

  1. The first line must be exactly 'begin scene'
  2. The last line must be exactly 'end scene'
  3. Any line between the first and last line must either be a building line,
     or an antenna line
  4. A building line has the form 'building ID X Y W H' (with any number of
     blank characters before or after), where
       ID is the building identifier
       X is the x-coordinate of the building
       Y is the y-coordinate of the building
       W is the half-width of the building
       H is the half-height of the building
  5. An antenna line has the form 'antenna ID X Y R' (with any number of
     blank characters before or after), where
       ID is the building identifier
       X is the x-coordinate of the antenna
       Y is the y-coordinate of the antenna
       R is the radius scope of the antenna
```

## Tests
Les tests automatiques peuvent être exécutés avec :
```sh
$ make test
```
La suite de tests utilise Bats (Bash Automated Testing System) et vérifie :
* La validation des arguments
* Le traitement des erreurs
* Le calcul de la boîte englobante
* La détection des chevauchements
* La gestion des identifiants uniques
* La validation des scènes
* Le formatage des sorties

## Dépendances
* [GCC](https://gcc.gnu.org/) (≥ 9.4.0) : Compilateur C
* [GNU Make](https://www.gnu.org/software/make/) (≥ 4.2.1) : Automatisation de la compilation
* [Bats](https://github.com/bats-core/bats-core) (≥ 1.2.0) : Framework de tests
* [Valgrind](https://valgrind.org/) (≥ 3.15.0) : Détection des fuites mémoire

## Références
* [The GNU C Reference Manual](https://www.gnu.org/software/gnu-c-manual/)
* [GCC Command Options](https://gcc.gnu.org/onlinedocs/gcc/Invoking-GCC.html)
* [Bats Documentation](https://bats-core.readthedocs.io/)
* [C Programming Language Specification](https://www.iso.org/standard/74528.html)

## État du projet
* [X] Le nom du dépôt GitLab est exactement `inf3135-251-tp2`
* [X] L'URL du dépôt GitLab est exactement `https://gitlab.info.uqam.ca/millimounou.guy_olivier_yanouba/inf3135-251-tp2`
* [X] Les utilisateurs *`blondin_al`* et *`guite-vinet.julien`* ont accès au projet en mode *Maintainer*
* [X] Le dépôt GitLab est un *fork* du gabarit fourni
* [X] Le dépôt GitLab est privé
* [X] Le dépôt contient un fichier `.gitignore` approprié
* [X] La branche `validate-scene` est implémentée
* [X] Toutes les sections du fichier `README.md` sont complétées
* [X] Toutes les fonctions des fichiers sources sont documentées avec des docstrings
* [X] Les tests automatiques passent avec succès
* [X] Le code est bien formaté et respecte les conventions de style
* [X] La mémoire est correctement gérée (vérifié avec Valgrind)
* [X] Le projet compile sans avertissements avec `-Wall -Wextra -Werror`