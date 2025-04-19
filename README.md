# project progress-

# 🐍 Snaketris – Projet C++/SDL

Bienvenue sur mon projet **Snaketris**, développé en C++ avec la bibliothèque **SDL2** dans le cadre de la Séance 6 du module de Programmation.

---

## 🎯 Objectif

Combiner les mécaniques du **jeu Snake** (serpent qui grandit en mangeant) avec des règles inspirées du **Tetris** (suppression d’éléments).

Ce projet s’inscrit dans une progression par étapes.  
💡 **Cette version correspond à l'étape 4.2** :  
👉 _“Afficher uniquement la tête du serpent, gérée au clavier et se déplaçant automatiquement.”_

Déplacement de la tête du snake et gestion des événements clavier

- Implémentation de la structure Snake avec position (x,y) et direction.
- Création des fonctions init_snake, set_direction, advance.
- Affichage de la tête en SDL (rectangle bleu clair).
- Gestion des événements clavier (flèches ↑ ↓ ← →) sans demi-tour.
- Déplacement automatique de la tête toutes les 200ms.

✅ Étape validée : affichage minimal du snake avec direction contrôlable.

## 🔧 Compilation

### Prérequis

- `g++`
- `libsdl2-dev`, `libsdl2-image-dev`, `libsdl2-ttf-dev`

### Commandes

```bash
make
./snake

🎯 Prochaine étape : ajout des anneaux (croissance + corps)."
