# N7OS

## Aperçu

Ce projet est un système d'exploitation minimaliste développé pour des fins éducatives. Il inclut divers composants tels qu'un noyau, un chargeur de démarrage une ordonanceur, un driver clavier, ... .


## Prérequis

- Installer Qemu

## Compilation du Projet

Pour compiler le projet, naviguez jusqu'au répertoire racine et exécutez :

```sh
make run 
```

## Structure du Répertoire

- ``bin/`` : Contient les binaires compilés et les fichiers objets.
- ``boot/`` : Contient les fichiers relatifs au chargeur de démarrage.
- ``build/`` : Contient les fichiers de l'environnement de compilation.
- ``docs/`` : Fichiers de documentation.
- ``include/`` : Fichiers d'en-tête.
- ``kernel/`` : Fichiers source du noyau.
- ``lib/`` : Bibliothèques.


## Contexte du Projet

Ce projet a été réalisé dans le cadre de mes cours. Une base de code initiale a été fournie pour démarrer le développement, et j'ai ensuite ajouté et amélioré les fonctionnalités pour atteindre les objectifs pédagogiques fixés.
