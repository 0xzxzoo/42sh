# 42sh - Shell

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Makefile](https://img.shields.io/badge/Build-Makefile-success.svg)
![Epitech](https://img.shields.io/badge/Project-Epitech-red.svg)

**42sh** est un interpréteur de commandes UNIX, inspiré de `tcsh`. Il s'agit du projet final de programmation système en C à Epitech. L'objectif est de recréer un shell fonctionnel capable de gérer l'exécution de binaires, un environnement dynamique, et des combinaisons complexes d'opérateurs via un Arbre Syntaxique Abstrait (AST).

## ✨ Fonctionnalités implémentées

### Fonctionnalités de base
*   **Prompt interactif** : Affichage dynamique avec gestion des signaux (`Ctrl+C`, `Ctrl+D`).
*   **Exécution de commandes** : Recherche et exécution de binaires via la variable d'environnement `PATH` ou via des chemins absolus/relatifs.
*   **Gestion de l'environnement** : Création, modification et suppression de variables d'environnement.

### Les Built-ins
Les commandes internes suivantes ont été recréées pour reproduire le comportement de `tcsh` :
*   `cd` : Changement de répertoire (avec gestion de `cd -` et `cd ~`).
*   `env` : Affichage de l'environnement actuel.
*   `setenv` : Ajout ou modification d'une variable d'environnement.
*   `unsetenv` : Suppression d'une variable d'environnement.
*   `exit` : Quitte le shell proprement avec gestion de la valeur de retour.

### L'Arbre Syntaxique Abstrait (AST)
Le cœur de notre parser gère de multiples opérateurs avec une gestion stricte des erreurs de syntaxe :
*   **Séparateurs** : `;` (exécution séquentielle).
*   **Pipes** : `|` (communication entre processus).
*   **Redirections** : 
    *   Droite : `>` (écrasement) et `>>` (concaténation).
    *   Gauche : `<` (lecture).
*   **Opérateurs logiques** : `&&` (ET logique) et `||` (OU logique).

---

## 🛠️ Installation et Utilisation

### Prérequis
*   GCC ou Clang
*   Make

### Compilation
Clonez le dépôt et compilez le projet à l'aide du `Makefile` inclus :

```bash
git clone [https://github.com/0xzxzoo/42sh.git](https://github.com/0xzxzoo/42sh.git)
make
