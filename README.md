# MINISHELL
[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](http://forthebadge.com/images/badges/built-with-love.svg)](http://forthebadge.com)
## WORKFLOW
![build workflow](https://github.com/tmatis/minishell/actions/workflows/build.yml/badge.svg) ![check norm workflow](https://github.com/tmatis/minishell/actions/workflows/norm.yml/badge.svg) ![unit test workflow](https://github.com/tmatis/minishell/actions/workflows/unit_test.yml/badge.svg)
## SUJET

L’objectif de ce projet est de créer un simple shell. Ca sera votre propre petit bash, ou zsh. Vous en apprendrez beaucoup sur les process et les file descriptors

### TODO

 - [x] Historique (flèche du haut, flèche du bas)
 - [x] Edition de ligne (flèche de droite, flèche de gauche)
 - [x] $ variable (rework)
 - [x] backslash \
 - [x] Séparation en mots (tokenization)
 - [x] Parsing des tokens
 - [x] Analyse des erreurs de syntax
 - [x] Proteger toutes les fonctions
 - [x] pipes
 - [x] $?
 - [x] exit
 - [x] cd
 - [x] echo
 - [x] unset
 - [x] pwd
 - [x] export
 - [x] env
 - [x] Signals ctrl-c ctrl-\
 - [x] Redirection
 - [x] Verification des path d'exec comme bash
 - [x] Erreur d'execution de commande comme dans bash
 - [ ] check des valeur de retours
 - [ ] Mode non TTY
 - [ ] Mise a la norme (16 / 33 fichiers)


## Démarrage
Pour compiler le projet:

    make all

## Auteurs
* **Théo Matis** _alias_ [@tmatis](https://profile.intra.42.fr/users/tmatis)
* **Julien Mazoyer** _alias_ [@jmazoyer](https://profile.intra.42.fr/users/jmazoyer)


[![tmatis's 42 stats](https://badge42.herokuapp.com/api/stats/tmatis)](https://github.com/JaeSeoKim/badge42)
[![jmazoyer's 42 stats](https://badge42.herokuapp.com/api/stats/jmazoyer)](https://github.com/JaeSeoKim/badge42)
